#include <Arduino.h>
#include "soc/gpio_struct.h"   // ESP32-S3 GPIO registers
#include <ArduinoJson.h>       // Install via Library Manager

// Pin definitions
#define FAN_PIN        16
#define HEATER_PIN     12
#define TEMP_ADC_PIN   1    // LM35 connected to GPIO1 (ADC1)
#define LIGHT_ADC_PIN  5    // Light sensor
#define LIGHT_LED_PIN  13
#define PIR_PIN        4
#define PIR_LED_PIN    15
#define AQ_ADC_PIN     7    // Air quality ADC
#define BUZZER_PIN     17

// Thresholds
#define TEMP_THRESHOLD   26
#define LIGHT_THRESHOLD  1000
#define TEMP_SAMPLES     10

// --------- Low level GPIO helpers ----------
static inline void gpio_set_output(uint8_t pin) {
  if (pin < 32) GPIO.enable_w1ts = (1UL << pin);
  else GPIO.enable1_w1ts.val = (1UL << (pin - 32));
}

static inline void gpio_write(uint8_t pin, bool level) {
  if (level) {
    if (pin < 32) GPIO.out_w1ts = (1UL << pin);
    else GPIO.out1_w1ts.val = (1UL << (pin - 32));
  } else {
    if (pin < 32) GPIO.out_w1tc = (1UL << pin);
    else GPIO.out1_w1tc.val = (1UL << (pin - 32));
  }
}

static inline int gpio_read(uint8_t pin) {
  if (pin < 32) return (GPIO.in >> pin) & 0x1;
  else return (GPIO.in1.val >> (pin - 32)) & 0x1;
}

// --------- Temperature reading ----------
float read_temperature() {
  long sum = 0;
  for (int i = 0; i < TEMP_SAMPLES; i++) {
    sum += analogRead(TEMP_ADC_PIN);
    delay(5);
  }
  float adc_avg = sum / (float)TEMP_SAMPLES;
  float voltage_mV = (adc_avg / 4095.0f) * 3300.0f;
  float tempC = voltage_mV / 10.0f;

  Serial.printf("ADC avg: %.0f, Voltage: %.2f mV, Temp: %.2f °C\n",
                adc_avg, voltage_mV, tempC);
  return tempC;
}

void setup() {
  delay(2000);
  Serial.begin(115200);

  // Outputs
  gpio_set_output(FAN_PIN);
  gpio_set_output(HEATER_PIN);
  gpio_set_output(LIGHT_LED_PIN);
  gpio_set_output(PIR_LED_PIN);
  gpio_set_output(BUZZER_PIN);

  // Inputs
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  float tempC = read_temperature();
  int light_val = analogRead(LIGHT_ADC_PIN);
  int motion = gpio_read(PIR_PIN);
  int aq_val = analogRead(AQ_ADC_PIN);

  // Temperature control
  if (tempC > 26) {
    gpio_write(FAN_PIN, LOW);
    gpio_write(HEATER_PIN, HIGH);
  } else if (tempC < 15) {
    gpio_write(FAN_PIN, HIGH);
    gpio_write(HEATER_PIN, LOW);
  } else {
    gpio_write(FAN_PIN, HIGH);
    gpio_write(HEATER_PIN, HIGH);
  }

  // Light control
  gpio_write(LIGHT_LED_PIN, light_val < LIGHT_THRESHOLD);

  // PIR LED
  gpio_write(PIR_LED_PIN, motion);

  // Buzzer for AQ
  gpio_write(BUZZER_PIN, aq_val > 3000);

  // Send JSON data
  StaticJsonDocument<200> doc;
  doc["temp"] = tempC;
  doc["light"] = light_val;
  doc["motion"] = motion;
  doc["aq"] = aq_val;

  String output;
  serializeJson(doc, output);
  Serial.println(output);

  delay(500);
}
