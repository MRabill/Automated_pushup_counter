#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "SSID";
const char* password = "Password";

const int  buttonPin = 16;       

int buttonPushCounter = 0;   
int buttonState = 0;         
int lastButtonState = 0;  

int counter_to = 0;

const char* serverName = "http://maker.ifttt.com/trigger/EVENTNAME/with/key/YOURKEY"; // event name and key to be changed

unsigned long lastTime = 0;
unsigned long timerDelay = 100;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(analogRead(0));
}

void loop() {
  //Send an HTTP POST request every 10 seconds
  button_det();

    lastTime = millis();
  //}
  //}
}

void button_det()
{
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println(buttonPushCounter);
      if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "value1=" + String(buttonPushCounter);           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
          
      // Free resources
      http.end();
      
    } 
    }
  }
    // Delay a little bit to avoid bouncing
    delay(50);
    
 // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


}
