// Pin Connections
int SIG = 2;
int LED = 13;

void setup()
{
    Serial.begin(9600);
    pinMode(SIG, INPUT);
    pinMode(LED, OUTPUT);
}

void loop()
{
    if (digitalRead(SIG))
    {
        digitalWrite(LED, HIGH);
        Serial.print("\nON");
    }
    else
    {
        digitalWrite(LED, LOW);
        Serial.print("\nOFF");
    }

    delay(200);
}
