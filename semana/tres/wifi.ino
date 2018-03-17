#include <ESP8266WiFi.h>

/*
Curso IoT ESPE Innovativa
*Carlos Venegas
*Michael Baca
*Gustavo Salazar

*/
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


void setup() {
  
  Serial.begin(115200);

  pinMode(D0,INPUT);
  pinMode(D1,OUTPUT);
  pinMode(D3,INPUT);
  pinMode(D4,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  digitalWrite(D4,HIGH);
  digitalWrite(10,HIGH);

  delay(50);
  Serial.println(F("Iniciando...."));
  
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  char __ssssid[] = "mijo"; 
  char __spasswd[] = "mijitrin";  
  WiFi.begin(__ssssid,__spasswd);
  
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && retries<=70) {
    retries++;
    digitalWrite(10,HIGH);
    Serial.print("*");
    WiFi.begin(__ssssid,__spasswd);
    delay(350);
    digitalWrite(10,LOW);
    delay(250);
    Serial.println(".Intentando");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi conectado"));
    digitalWrite(10,HIGH);
    estado=1;
  }
  
  Serial.println(F("Conectado"));
  Serial.println(WiFi.status());
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  
 if(estado==0){
    Serial.println("E0");
    digitalWrite(10,LOW);  
  }
    
    
     
}


  






