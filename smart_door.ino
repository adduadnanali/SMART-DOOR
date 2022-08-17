#include<WiFi.h>  //library for esp32 
#include <ThingSpeak.h>  //library for thingspeak cloud server

char ssid[] = "WIFI_NAME";   // your network SSID (name)
char pass[] = "PASSWORD";

WiFiClient client;

unsigned long myChannelNumber =  XXXXXXXX;
const char * myWriteAPIKey = "your write API key goes here";
const char * myReadAPIKey = "your write API key goes here";


int in1=8;
int in2=7;
int ir=9;

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    ThingSpeak.begin(client);
  
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(ir,INPUT);
 
}

void loop() {

   if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
   }
   
   while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);    
    }
   
  Serial.println("\nConnected.");
  
  if (digitalRead(ir)==0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    Serial.println("Door opened");
    delay(3000);
    
    digitalWrite(in1, LOW);  
    digitalWrite(in2, LOW);
    delay(3000);
    
    digitalWrite(in1, LOW);  
    digitalWrite(in2, HIGH);
    Serial.println("Door closed");
    delay(3000);
  }
  else { 
    digitalWrite(in1, LOW);  
    digitalWrite(in2, LOW);
  }
  
  int a = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey); //READ THE VALUE FROM FIELD AND STORE IN A VARIABLE (a)
  Serial.println("Door State");
  Serial.print(a);
  delay(1000);
 
  if (a==0){                     // IF VALUE IN CLOUD FIELD IS 0 THEN TURN MOTOR ON (DOOR OPEN)
   digitalWrite(in1,HIGH);       // DOOR OPEN .. MOTOR ROTATES IN FORWARD DIRECTION
   digitalWrite(in2,LOW);
   Serial.println("Door open");
   delay(3000);
   
   digitalWrite(in1, LOW);       //DOOR IS IN OPEN STATE  A FEW SECONDS THAT IS 3 SECONDS
   digitalWrite(in2, LOW);
   delay(3000);
    
   digitalWrite(in1, LOW);       // DOOR CLOSE MOTOR ROTATES BACK IN BACKWARD DIRECTION.
   digitalWrite(in2, HIGH);
   Serial.println("Door closed");
   delay(3000);
   
   }
   else if (a==1){                // IF VALUE IN CLOUD FIELD IS 1 THEN TURN MOTOR OFF (DOOR CLOSE STATE)
   digitalWrite(in1,LOW);
   digitalWrite(in2,LOW);
   Serial.println("Door Closed");
   }
}
