
#include <WiFiNINA.h> 
void setup() { 
Serial.begin(9600); // this function enables the communication between Arduino and other devices

if (WiFi.status() == WL_NO_MODULE) { 
Serial.println("WiFi module not found!"); // if no newtworks are found , this message are shoeweed. it must be in set up section not in loop
} 
} 
void loop() { 

Serial.println("Scanning available networks..."); // in a separate line the message is printed
uint8_t numNetworks = WiFi.scanNetworks(); //the number of networks are searched
for (uint8_t i = 0; i < numNetworks; i++) // in this FOR loop for each network the commands inside of loop are done. I added i in the code.
{ 
Serial.print("Network: "); 
Serial.print(WiFi.SSID(i)); // name of newtwork
Serial.print(" | Signal Strength: "); 
Serial.print(WiFi.RSSI(i)); //WiFi.RSSI(i) returns the signal strength (in dBm) of the network at index i.
Serial.print(" dBm | Encryption: "); 
Serial.println(WiFi.encryptionType(i)); 
} 
delay(30000); 
}
