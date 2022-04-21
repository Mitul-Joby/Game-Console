const int buzzer = 3;

void setup()
{
    pinMode(buzzer, OUTPUT);
}

void loop()
{

    for (int i = 0; i < 100; i++)
    {
        digitalWrite(buzzer, 0);
        delay(10 * i);
        digitalWrite(buzzer, 1);
        delay(10 * i);
    }
}
