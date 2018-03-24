
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3
#define D10 1

int estado=0;
void MQTT_connect();

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,"13.92.159.101", 1883);
unsigned long previousMillis=0;

Adafruit_MQTT_Publish alive = Adafruit_MQTT_Publish(&mqtt,"/dispositivo2/alive");
Adafruit_MQTT_Subscribe temprec = Adafruit_MQTT_Subscribe(&mqtt, "/dispositivo1/temp");


void keepalive1(double x) {
  Serial.print("Hey we're in a slider callback, the slider value is: ");
  Serial.println(x);
}
void fococallback(double x) {
  Serial.println(x);
  if(x<10){
    digitalWrite(D1,HIGH);  
  }else{
    digitalWrite(D1,LOW);
  }
  
  
  
}


void setup() {
  
  Serial.begin(115200);

  pinMode(D0,INPUT);
  pinMode(D1,OUTPUT);
  pinMode(D3,INPUT);
  pinMode(10,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  digitalWrite(D4,HIGH);
  digitalWrite(10,HIGH);
  
  Serial.println(F("Iniciando...."));
  
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);

  
  Serial.println("intentado");
  char __ssssid[] = "mijo"; //  your network SSID (name)
  char __spasswd[] = "mijitrin";    // your network password (use for WPA, or use as key for WEP)
  WiFi.begin(__ssssid,__spasswd);
  
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && retries<=70) {
    retries++;
    digitalWrite(10,HIGH);
    Serial.print("*");
    //WiFi.begin(__sssid,__passwd);
    WiFi.begin(__ssssid,__spasswd);

    delay(350);
    digitalWrite(10,LOW);
    delay(250);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi conectado"));
    digitalWrite(10,HIGH);
    estado=1;
  }
  
  Serial.println(F("Conectado"));
  Serial.println(WiFi.status());
  temprec.setCallback(fococallback);
  
  mqtt.subscribe(&temprec);
  
  

  
  
}


void loop() {
mqtt.processPackets(10000);
  

unsigned long currentMillis = millis();
  
   
  if(currentMillis - previousMillis >= 2000) {
    previousMillis = currentMillis;   
    
   
    

    
    
    
    
    //temp.publish(""+valor);
    alive.publish("1");
    
    if(! mqtt.ping()) {
      mqtt.disconnect();
    }
    
    
    
  }
  
  

  if(estado==0){
    Serial.println("E0");
    digitalWrite(10,LOW);  
  }
  if(estado==1){
    MQTT_connect();
    Serial.print("");
    digitalWrite(10,HIGH); 
    
    
     
  }


  
}


void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Conectando a  MQTT... ");

  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       digitalWrite(D4,HIGH);
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Reintentado Conexion...");
       mqtt.disconnect();
       delay(2000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("Conectado al servidor MQTT!");
  digitalWrite(D4,LOW);
  
}
