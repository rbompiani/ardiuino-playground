#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

const int temp_pin = A0;

FirebaseData firebaseData;

// WiFi Config
const char ssid[] = "HOME-F600-2.4";
const char password[] = "7TDHE7DP3HACF793";

// Server, file, and port
const char hostname[] = "example.com";
const String uri = "/index.html";
const int port = 80;

// WiFi client
WiFiClient client;

void setup() {
  //4. Setup Firebase credential in setup()
  Firebase.begin("temperature-b8030.firebaseio.com", "GzU7rjt4kmAkK9PrnoaivjE6QEGHZ5waHERb3uu1");
  
  //5. Optional, set AP reconnection in setup()
  Firebase.reconnectWiFi(true);
  
  //6. Optional, set number of error retry
   Firebase.setMaxRetry(firebaseData, 3);
  
  //7. Optional, set number of error resumable queues
  Firebase.setMaxErrorQueue(firebaseData, 30);
  
  //8. Optional, use classic HTTP GET and POST requests. 
  //This option allows get and delete functions (PUT and DELETE HTTP requests) works for 
  //device connected behind the Firewall that allows only GET and POST requests.   
  Firebase.enableClassicRequest(firebaseData, true);
  
  //9. Optional, set the size of BearSSL WiFi to receive and transmit buffers 
  firebaseData.setBSSLBufferSize(1024, 1024); //minimum size is 4096 bytes, maximum size is 16384 bytes
  
  //10. Optional, set the size of HTTP response buffer
  firebaseData.setResponseSize(1024); //minimum size is 400 bytes
  
  // Initialize Serial
  Serial.begin(9600);
  delay(100);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  // Show that we are connected
  Serial.println("Connected!");
  // Print IP address
  Serial.println(WiFi.localIP());

  if (Firebase.getInt(firebaseData, "/temp")) {

    if (firebaseData.dataType() == "int") {
      Serial.println(firebaseData.intData());
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
 
  float voltage;
  float temp_c;
 
  // Read temperature sensor (remember to multiply by 3!)
  voltage = (analogRead(temp_pin) * 1.0 / 1023) * 3.0;
  temp_c = 100.0 * voltage - 50;
  float temp_f = temp_c*1.8 +32;
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("V degF: ");
  Serial.println(temp_f);
 
  //5. Try to set int data to Firebase
  //The set function returns bool for the status of operation
  //firebaseData requires for sending the data
  if(Firebase.pushDouble(firebaseData, "/temp", temp_f))
  {
    //Success
     Serial.println("Set int data success");

  }else{
    //Failed?, get the error reason from firebaseData

    Serial.print("Error in setInt, ");
    Serial.println(firebaseData.errorReason());
  }

 
  delay(30000);
}
