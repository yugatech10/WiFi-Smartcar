/* Create a WiFi access point and provide a web server on it to receive command to control motor. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "WiFI_Car_Rethi";
const char *password = "abcd1234";

//Motor
int PWMA=5;//Right side 
int PWMB=4;//Left side 
int DA=0;//Right reverse 
int DB=2;//Left reverse


ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/plain", "WiFi Car by Rethigesh And GRoup");
}

void motor_left(){
    
    digitalWrite(PWMA, HIGH); 
    digitalWrite(DA, LOW); 
    
    digitalWrite(PWMB, HIGH); 
    digitalWrite(DB, LOW);
  }
void motor_stop(){
  
    digitalWrite(PWMA, LOW); 
    digitalWrite(DA, LOW); 
    
    digitalWrite(PWMB, LOW); 
    digitalWrite(DB, LOW);
  }
void motor_right(){
    digitalWrite(PWMA, HIGH); 
    digitalWrite(DA, HIGH); 
    
    digitalWrite(PWMB, HIGH); 
    digitalWrite(DB, HIGH);
  }

void motor_back(){
    digitalWrite(PWMA, 450); 
    digitalWrite(DA, HIGH); 
    
    digitalWrite(PWMB, 450); 
    digitalWrite(DB, LOW);
  }
void motor_forward(){
    digitalWrite(PWMA, 450); 
    digitalWrite(DA, LOW); 
    
    digitalWrite(PWMB, 450); 
    digitalWrite(DB, HIGH);
}

void setup() {
  
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DA, OUTPUT); 
  pinMode(DB, OUTPUT);
  
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);

 
	server.on("/", handleRoot);
 
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/fw", []() {
    motor_forward();
    server.send(200, "text/plain", "Forward");
  });
  server.on("/bk", []() {
    motor_back();
    server.send(200, "text/plain", "Back");
  });

  server.on("/st", []() {
    motor_stop();
    server.send(200, "text/plain", "Stop");
  });
  server.on("/lt", []() {
    motor_left();
    server.send(200, "text/plain", "Left");
  });
  server.on("/rt", []() {
    motor_right();
    server.send(200, "text/plain", "Right");
  });

	server.begin();
	Serial.println("HTTP server started");


  
}

void loop() {
	server.handleClient();
}
