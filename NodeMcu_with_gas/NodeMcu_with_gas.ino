int sensorValue;

void setup()
{
  Serial.begin(9600);      
  pinMode(A0,INPUT);
}

void loop()
{
  sensorValue = analogRead(A0);       
  
  Serial.println();

  if(sensorValue>=200)
   {  
    Serial.print("MQ135 Value: ");
    Serial.println(sensorValue);
    Serial.println("Bad Quality Air");
    }else{
      Serial.println("Good Quality Air");
      }
   
  delay(5000);                       
}
