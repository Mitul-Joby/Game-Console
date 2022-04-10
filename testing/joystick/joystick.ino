// Pin Connections
int VRx = A0;
int VRy = A1;
int SW = 2;

void setup()
{
  Serial.begin(9600);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop()
{
  Serial.print("\nVRx: ");
  Serial.print(analogRead(VRx));
  Serial.print("\tVRy: ");
  Serial.print(analogRead(VRy));
  Serial.print("\tSW : ");
  Serial.print(digitalRead(SW));

  delay(200);
}
