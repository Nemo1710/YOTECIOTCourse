
const int sensor= A0;
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  int value = analogRead(sensor);
  float milivoltios = (value / 1023.0) * 5000;
  float celsius = milivoltios / 10; 
  Serial.print(celsius);
  Serial.println(" C");
  delay(1000);
}
