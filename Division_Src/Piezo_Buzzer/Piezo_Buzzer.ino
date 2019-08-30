const int piezo = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(piezo, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(piezo, 261);
  delay(500);
  noTone(piezo);
}
