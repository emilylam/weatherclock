// Test code for connecting with node.js
#include <math.h>

int testled = D7;
float floatTemp = 0;
int r,g,b = 0;

void setup() {

  Serial.begin(9600);
  pinMode(testled, OUTPUT);
  digitalWrite(testled, LOW);
  Particle.function("temp",printTemp);
  RGB.control(true);
  delay(2000);

}

void loop() {

  RGB.color(r, g, b);

}

int printTemp(String rcvTemp) {
  //float test = 20.34;
  Serial.println(rcvTemp);
  floatTemp = rcvTemp.toFloat();
  calcRGBvalue(floatTemp);
  return 1;

}

void calcRGBvalue(float value){

  if (value > 100) { value = 100; }
  else if (value < 0) { value = 0; }
  float f = value/100;
  float a = (1-f)/0.2;
  int X = floor(a);
  int Y = floor(255*(a-X));
  Serial.print("value: ");
  Serial.println(value);
  Serial.print("a: ");
  Serial.println(a);
  Serial.print("X: ");
  Serial.println(X);
  Serial.print("Y: ");
  Serial.println(Y);

  switch(X)
  {
    case 0: r=255;g=Y;b=0;break;
    case 1: r=255-Y;g=255;b=0;break;
    case 2: r=0;g=255;b=Y;break;
    case 3: r=0;g=255-Y;b=255;break;
    case 4: r=Y;g=0;b=255;break;
    case 5: r=255;g=0;b=255;break;
    default:r=0;g=0;b=0;break;
  }
}
