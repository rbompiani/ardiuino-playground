#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

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

  /*
  // Connect to server
  Serial.print("Connecting to ");
  Serial.println(hostname);
  if (client.connect(hostname, port) == 0 ) {
    Serial.println("Connection failed");
  }

  // send request for file
  client.print("GET " + uri + " HTTP/1.1\r\n" +
                "Host: " + hostname + "\r\n" +
                "Connection: close\r\n" +
                "\r\n");

   delay(500);

   // Print reply from server
   while ( client.available() ) {
    String ln = client.readStringUntil('\r');
    Serial.print(ln);
   }

   // Close TCP connection
   client.stop();
   Serial.println();
   Serial.println("Connection closed");

   delay(10000);
   */
}
