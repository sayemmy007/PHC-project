#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server;

const char *ssid =  "Lo";     
const char *pass =  "9833690916";
WiFiClient client;
                              // defines pins numbers
const int trigPin = 2; //D4
const int echoPin = 0; //D3
int sensorValue;
int buzzer = 4;  //D2
                          // defines variables
long duration;
int distance;

void setup() {
     pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
     pinMode(echoPin, INPUT); // Sets the echoPin as an Input
     pinMode(A0,INPUT);       // Gas Input
     pinMode(buzzer, OUTPUT);    // Buzzer Output   
     Serial.begin(2400); // Starts the serial communication      
     delay(1000);

     Serial.println("Connecting to");
     Serial.println(ssid);
     WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
           {
            delay(500);
            Serial.print(".");
            }
         

            Serial.println("");
            Serial.println("WiFi connected");
            Serial.println(WiFi.localIP());
            server.on("/", []() {});
            server.begin();
           }

void loop() {
       server.handleClient();
                                                   // Clears the trigPin
       digitalWrite(trigPin, LOW);
       delayMicroseconds(2);

                                                     // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

                                                     // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);

                                                    // Calculating the distance
      distance= duration*0.034/2;

                                                  // Prints the distance on the Serial Monitor
      sensorValue = analogRead(A0);
      Serial.println(distance);
      Serial.println(sensorValue);

     




     String str = String(distance);
     String strs = String(sensorValue);

 if(distance>=55 && sensorValue>=300)
  {
digitalWrite(buzzer, HIGH);
Serial.println("Water Level decreases....fill the tank && Bad Quality Air...clean the toilet");
server.send(300,"text/html","\t\t\t<br><br><br><h1 align = 'Center'>Welcome to Smart Toilet Monitoring System</h1><br> \n\n\t\t <h3 align = 'center'>Water Sensor Value is in cms :  "+ str =      "</h3>"+ "<br> \n\n\t\t <h3 align = 'center'> Gas Sensor Value is in PPM  :  "+ strs +  "</h3>"+ "\n\t\t<br>" + "\n\t\t<br> <h2 align = 'center'>Water Level Decreases...fill the tank  AND   Bad Quality Air...clean the toilet</h2>");
  }


else if(distance<=55 && sensorValue>=300){
digitalWrite(buzzer, HIGH);
Serial.println("Water  level normal && Bad Quality Air...clean the toilet");
server.send(300,"text/html","\t\t\t<br><br><h1 align = 'Center'>Welcome Smart Toilet Monitoring System</h1><br> \n\n\t\t <h3 align = 'center'>Water Sensor Value is in cms :  "+ str + "</h3>"+ "<br> \n\n\t\t <h3 align = 'center'> Gas Sensor Value is in PPM :  "+ strs + "</h3>"+ "\n\t\t<br>" + "\n\t\t<br> <h2 align = 'center'>Water Level Normal   AND   Bad Quality Air...clean the toilet</h2>");
     }


else if(distance>=55 && sensorValue<=300){
digitalWrite(buzzer, HIGH);
Serial.println("Water Level decreases....fill the tank && Good Quality Air");
server.send(300,"text/html","\t\t\t<br><br><h1 align = 'Center'>Welcome to Smart Toilet Monitoring System</h1><br> \n\n\t\t <h3 align = 'center'>Water Sensor Value is in cms :  "+ str + 
                                                                                                        "</h3>"+ "<br> \n\n\t\t <h3 align = 'center'> Gas Sensor Value is in PPM :  "+ strs + 
                                                                                                        "</h3>"+ "\n\t\t<br>" + "\n\t\t<br> <h2 align = 'center'>Water Level Decreases...fill the tank   AND   Good Quality Air</h2>");
   }



  else{
digitalWrite(buzzer, LOW);
Serial.println("Water  level normal && Good Quality Air");
server.send(300,"text/html","\t\t\t<br><br><h1 align = 'Center'>Welcome to Smart Toilet Monitoring System</h1><br> \n\n\t\t <h3 align = 'center'>Water Sensor Value is in cms :  "+ str +   "</h3>"+ "<br> \n\n\t\t <h3 align = 'center'> Gas Sensor Value is in PPM :  "+ strs +  "</h3>"+ "\n\t\t<br>" + "\n\t\t<br> <h2 align = 'center'>Water Level Normal   AND   Good Quality Air</h2>");
   }
 delay(1000);
 Serial.println();
 delay(5000);
}

