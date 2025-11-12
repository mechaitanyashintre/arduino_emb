#include<ESP8266WiFi.h>


  const char* ssid= "TP-LINK_A340"; // put your router name
  const char* password="41081297"; //put your password
  
  const char* host = "maker.ifttt.com";
  
  
  const int buttonPin1 = 5; // D1 parcel ir email
  const int buttonPin2 = 4; // D2 file recieve ir email

  int noActionPin = 2; // noactionpin

  int ledPin1 = 14; // D5 table commands
  int ledPin2 = 12; // D6
  int ledPin3 = 13; // D7

  int buttonState1=0;
  int buttonState2=0;

  int fileFlag=0;
  

  WiFiServer server(80);


  void setup() {
    Serial.begin(115200);

    Serial.println("Wi-Fi Access Initiated");
    delay(100);


    pinMode(buttonPin1, INPUT);
   
    
    pinMode(buttonPin2, INPUT);
 
    

    pinMode(noActionPin,OUTPUT);
    digitalWrite(noActionPin, LOW);
    
          
    pinMode(ledPin1,OUTPUT);
    digitalWrite(ledPin1, LOW);
    
    pinMode(ledPin2,OUTPUT);
    digitalWrite(ledPin2, LOW);
    
    pinMode(ledPin3,OUTPUT);
    digitalWrite(ledPin3, LOW);
 


    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); 


    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");
    
    // Print the IP address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
      
 }
 

  void parcelEmail() { 
             
              buttonState1= digitalRead(buttonPin1);
              if (buttonState1==LOW){ 
                 
                  Serial.println("parcel pickup request");
                  delay(500);

              Serial.println();
              Serial.print("Connecting to ");
              Serial.println(ssid);
              
              WiFi.begin(ssid, password);
              
              while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
              }
            
              Serial.println("");
              Serial.println("IP address: ");
              Serial.println(WiFi.localIP());

        
             WiFiClient client; 
                  const int httpPort=80;
                  delay(500);
              if (!client.connect(host, httpPort)) {  
                    Serial.println("connection failed");  
              return;} 


              String url = "/trigger/parcel_pickup_request/with/key/mRXEd02mAs0LM4DPgaMe1KUai6XgnxtVUAmYmCLkfcu"; 
  
              Serial.print("Requesting URL: ");
              Serial.println(url);
           
               client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" +   
                                     "Connection: close\r\n\r\n");  

               Serial.println("parcel pick up request email sent");   

                  digitalWrite(buttonPin1, LOW);
                  buttonState1=0;
              }                                      
              else{
              Serial.println("no parcel pick up request");
              }
  }


void fileSentEmail() { 

           buttonState2= digitalRead(buttonPin2); 
           if (buttonState2==LOW){ 
                fileFlag=1;
                Serial.println("fileFlag=1");
                Serial.println("file sent request");
                delay(500);

                  
              Serial.println();
              Serial.print("Connecting to ");
              Serial.println(ssid);
              
              WiFi.begin(ssid, password);
              
              while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
              }
            
              Serial.println("");
              Serial.println("IP address: ");
              Serial.println(WiFi.localIP());

        
             WiFiClient client; 
                  const int httpPort=80;
                  delay(500);
              if (!client.connect(host, httpPort)) {  
                    Serial.println("connection failed");  
              return;} 

              
              String url = "/trigger/file_sent_request/with/key/mRXEd02mAs0LM4DPgaMe1KUai6XgnxtVUAmYmCLkfcu"; 
  
              Serial.print("Requesting URL: ");
              Serial.println(url);
           
               client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" +   
                                     "Connection: close\r\n\r\n");  

               Serial.println("file sent email sent");   

                 
              
    
              }                                      
              else{
              Serial.println("no file sent yet");
              }}
    

  void fileReceivedEmail(){
    
              buttonState2= digitalRead(buttonPin2);
              if (buttonState2==HIGH && fileFlag==1){ 
                
                Serial.println("file received request");
                delay(500);


              Serial.println();
              Serial.print("Connecting to ");
              Serial.println(ssid);
              
              WiFi.begin(ssid, password);
              
              while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
              }
            
              Serial.println("");
              Serial.println("IP address: ");
              Serial.println(WiFi.localIP());

        
             WiFiClient client; 
                  const int httpPort=80;
                  delay(500);
              if (!client.connect(host, httpPort)) {  
                    Serial.println("connection failed");  
              return;} 

              String url = "/trigger/file_received_request/with/key/mRXEd02mAs0LM4DPgaMe1KUai6XgnxtVUAmYmCLkfcu"; 
  
              Serial.print("Requesting URL: ");
              Serial.println(url);
           
               client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" +   
                                     "Connection: close\r\n\r\n");  

               Serial.println("file received email sent");   

                fileFlag=0;  
              }                                      
              else{
              Serial.println("no file received yet");
              }}



     void loop(){
 
      //Check if a client has connected
      WiFiClient client = server.available();
      if (!client) {
      return;
      }
      
      // Wait until the client sends some data
      Serial.println("new client");
      while(!client.available()){
      delay(1);
      }
      
      // Read the first line of the request
      String request = client.readStringUntil('\r');
      Serial.println(request);
      client.flush();
      
      
     if (request.indexOf("/noaction")!= -1){
      digitalWrite(noActionPin, HIGH);
      Serial.println("no action");
      delay(1000);
      digitalWrite(noActionPin,LOW);
      }
      
      if (request.indexOf("/table1")!= -1){
      digitalWrite(ledPin1, HIGH);
      Serial.println("table1 call");
      delay(1000);
      digitalWrite(ledPin1, LOW);
      }
      
      if (request.indexOf("/table2")!= -1){
      digitalWrite(ledPin2, HIGH);
      Serial.println("table2 call");
      delay(1000);
      digitalWrite(ledPin2, LOW);
      }
      
      if (request.indexOf("/table3")!= -1){
      digitalWrite(ledPin3, HIGH);
      Serial.println("table3 call");
      delay(1000);
      digitalWrite(ledPin3,LOW);
      }

      if (request.indexOf("/parelpickuprequestbutton")!= -1){
      parcelEmail();
      delay(500);
      }

      if (request.indexOf("/filesentbutton")!= -1){
      fileSentEmail();
      delay(500);
      }

      if (request.indexOf("/filereceivedbutton")!= -1){
      fileReceivedEmail();
      delay(500);
      }
      
      
      // Return the response
      client.println("HTTP/1.1 200 OK");
      client.println ("Content-Type: text/html");
      client.println("");// do not forget this one
      client.println("<!DOCTYPE HTML>");
      client.println("<html><center><body bgcolor=powderblue>");
      
      client.println("<h1>Ramukaka's Webpage</h1>");

      client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");

      client.println("<br><br>");

      client.println("<a href=\"/noaction\"\"><button>No Action</button></a><br/>");
      client.println("<br><br>");
      
      client.println("<a href=\"/table1\"\"><button>Table1</button></a><br/>");
      client.println("<br><br>");
    
      client.println("<a href=\"/table2\"\"><button>Table2</button></a><br/>");
      client.println("<br><br>");
      
      client.println("<a href=\"/table3\"\"><button>Table3</button></a><br/>");
      client.println("<br><br>");
      
      client.println("<a href=\"/parelpickuprequestbutton\"\"><button>Drop Parcel Pickup Request</button></a><br/>");
      client.println("<br><br>");
      
      client.println("<a href=\"/filesentbutton\"\"><button>File Sent</button></a><br/>");
      client.println("<br><br>");
      
      client.println("<a href=\"/filereceivedbutton\"\"><button>File Received</button></a><br/>");
      
      client.println("</body><center/></html>");
      
      delay(1);
      Serial.println("Client disconnected");
      Serial.println("");

    }
