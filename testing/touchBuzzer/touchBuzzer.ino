const int SIG = 3;
const int BUZZER = 2;
void setup()
{
    Serial.begin(9600);
    pinMode(SIG, INPUT);
    pinMode(BUZZER, OUTPUT);
}

void loop() 
{
    if(digitalRead(SIG))
      digitalWrite(BUZZER,LOW);
     else
     digitalWrite(BUZZER,HIGH);
     
}
