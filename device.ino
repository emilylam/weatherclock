// Test code for connecting with node.js

int led = D7;

void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Particle.function("temp",printTemp);

}

void loop() {}

int printTemp(String rcvTemp) {

  Serial.println(rcvTemp);
  return 1;

}
