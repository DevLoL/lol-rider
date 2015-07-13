

#include <Scheduler.h>

struct LedAdress
{
  unsigned int Bit_stateA;
  unsigned int Bit_stateB;
  unsigned int Bit_stateC;
  unsigned int Bit_stateL;
};

const int num_leds = 15;
LedAdress leds[num_leds];

#define trigPin A6
#define echoPin A7

void setup()
{
  leds[0].Bit_stateA = B11111011;
  leds[0].Bit_stateB = B11111111;
  leds[0].Bit_stateC = B11111111;
  leds[0].Bit_stateL = B11111111;

  leds[1].Bit_stateA = B11110111;
  leds[1].Bit_stateB = B11111111;
  leds[1].Bit_stateC = B11111111;
  leds[1].Bit_stateL = B11111111;

  leds[2].Bit_stateA = B11101111;
  leds[2].Bit_stateB = B11111111;
  leds[2].Bit_stateC = B11111111;
  leds[2].Bit_stateL = B11111111;

  leds[3].Bit_stateA = B00110000;
  leds[3].Bit_stateB = B00000000;
  leds[3].Bit_stateC = B00000000;
  leds[3].Bit_stateL = B00000000;

  leds[4].Bit_stateA = B11111111;
  leds[4].Bit_stateB = B11111111;
  leds[4].Bit_stateC = B01111111;
  leds[4].Bit_stateL = B11111111;

  leds[5].Bit_stateA = B01111111;
  leds[5].Bit_stateB = B11111111;
  leds[5].Bit_stateC = B11111111;
  leds[5].Bit_stateL = B11111111;

  leds[6].Bit_stateA = B11111111;
  leds[6].Bit_stateB = B11111111;
  leds[6].Bit_stateC = B11100011;
  leds[6].Bit_stateL = B11111111;

  leds[7].Bit_stateA = B11111111;
  leds[7].Bit_stateB = B11111111;
  leds[7].Bit_stateC = B11011111;
  leds[7].Bit_stateL = B11111111;

  leds[8].Bit_stateA = B11111111;
  leds[8].Bit_stateB = B11111111;
  leds[8].Bit_stateC = B11111110;
  leds[8].Bit_stateL = B11111111;

  leds[9].Bit_stateA = B11111111;
  leds[9].Bit_stateB = B11111101;
  leds[9].Bit_stateC = B11111111;
  leds[9].Bit_stateL = B11111111;

  leds[10].Bit_stateA = B11111111;
  leds[10].Bit_stateB = B11111111;
  leds[10].Bit_stateC = B11111101;
  leds[10].Bit_stateL = B11111111;

  leds[11].Bit_stateA = B11111111;
  leds[11].Bit_stateB = B11111111;
  leds[11].Bit_stateC = B11111111;
  leds[11].Bit_stateL = B11111110;

  leds[12].Bit_stateA = B11111111;
  leds[12].Bit_stateB = B11111011;
  leds[12].Bit_stateC = B11111111;
  leds[12].Bit_stateL = B11111111;

  leds[13].Bit_stateA = B11111111;
  leds[13].Bit_stateB = B11110111;
  leds[13].Bit_stateC = B11111111;
  leds[13].Bit_stateL = B11111111;

  leds[14].Bit_stateA = B11111111;
  leds[14].Bit_stateB = B11111110;
  leds[14].Bit_stateC = B11111111;
  leds[14].Bit_stateL = B11111111;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Scheduler.startLoop(light);
}

long led_speed = 100;

void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  // delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range");

    led_speed = 0;
  }
  else {
    led_speed = sqrt(distance * 2);
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(100);
}

void light()
{
  if (led_speed == 0) {
    PORTA = B00000000;
    PORTB = B00000000;
    PORTC = B00000000;
    PORTL = B00000000;
    delay(50);
    return;
  }

  for (int i = 0; i < num_leds; i++) {
    DDRA = B11111111;
    DDRB = B11111111;
    DDRC = B11111111;
    DDRL = B11111111;

    PORTA = leds[i].Bit_stateA & leds[num_leds - i].Bit_stateA;
    PORTB = leds[i].Bit_stateB & leds[num_leds - i].Bit_stateB;
    PORTC = leds[i].Bit_stateC & leds[num_leds - i].Bit_stateC;
    PORTL = leds[i].Bit_stateL & leds[num_leds - i].Bit_stateL;
    delay(led_speed);
  }
}
