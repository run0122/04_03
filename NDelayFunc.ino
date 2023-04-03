// 1. 360p 619_0.ino

// #include "NDelayFunc.h"

// const int LED = 11;
// unsigned int t_high = 0;

// void fading(){
//   t_high++;
//   if(t_high>255) t_high = 0;
//   analogWrite(LED, t_high);
// }

// NDelayFunc nDelayFading(4,fading);

// void setup(){

// }

// void loop(){
//   nDelayFading.run();
// }

// 2. 361p 6110_1.ino

// const int t1_LED = 13;
// unsigned int on_off = 0;

// const int t2_LED = 11;
// unsigned int t_high = 0;

// unsigned long t1_prev = 0;
// const unsigned long t1_delay = 500;

// unsigned long t2_prev = 0;
// const unsigned long t2_delay = 4;

// void setup() {
//   pinMode(t1_LED, OUTPUT);
// }

// void loop() {
//   unsigned long t1_now = millis();
//   if (t1_now - t1_prev >= t1_delay) {
//     t1_prev = t1_now;

//     on_off++;
//     if (on_off > 1) on_off = 0;
//     digitalWrite(t1_LED, on_off);
//   }

//   unsigned long t2_now = millis();
//   if (t2_now - t2_prev >= t2_delay) {
//     t2_prev = t2_now;

//     t_high++;
//     if (t_high > 255) t_high = 0;
//     analogWrite(t2_LED, t_high);
//   }
// }

// 3. 362p 6110_2.ino

// #include "NDelayFunc.h"

// const int blink_LED = 13;
// unsigned int on_off = 0;

// const int fading_LED = 11;
// unsigned int t_high = 0;

// void blink() {
//   on_off++;
//   if (on_off > 1) on_off = 0;
//   digitalWrite(blink_LED, on_off);
// }

// void fading() {
//   t_high++;
//   if (t_high > 255) t_high = 0;
//   analogWrite(fading_LED, t_high);
// }

// NDelayFunc nDelayBlink(500, blink);
// NDelayFunc nDelayFading(4, fading);

// void setup() {
//   pinMode(blink_LED, OUTPUT);
// }

// void loop() {
//   nDelayBlink.run();
//   nDelayFading.run();
// }

#include "NDelayFunc.h"
#include <Servo.h>

Servo myservo;

// Servo
int pos = 0;
int servo_direction = 1;

// LED Blink
const int blink_LED = 13;
unsigned int on_off = 0;

// LED Fade In & Fade OUT
const int fading_LED = 11;
unsigned int t_high = 0;
unsigned int t_high2 = 255;

int trigger = 0;

// LED Blink
void blink() {
  on_off++;
  if (on_off > 1) on_off = 0;
  digitalWrite(blink_LED, on_off);
}

// LED Fade In & Fade OUT
void fading() {
  t_high++;
  if (t_high > 255) {
    t_high = 0;
    trigger = 1;
  }
  analogWrite(fading_LED, t_high);
}

void fadeout() {
  t_high2--;
  if (t_high2 == 0) {
    t_high2 = 255;
    trigger = 0;
  }
  analogWrite(fading_LED, t_high2);
}

// Servo
void sweep() {
  if (servo_direction == 1) {
    pos++;
    myservo.write(pos);
    if (pos == 180) {
      servo_direction = -1;
    }
  }
  if (servo_direction == -1) {
    pos--;
    myservo.write(pos);
    if (pos == 0) {
      servo_direction = 1;
    }
  }
}

NDelayFunc nDelayBlink(500, blink);     // LED Blink
NDelayFunc nDelayFading(4, fading);     // LED Fade In & Fade OUT
NDelayFunc nDelayFadeout(4, fadeout);
NDelayFunc nDelaySweep(10, sweep);      // Servo

void setup() {
  pinMode(blink_LED, OUTPUT);
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  nDelayBlink.run();
  if (trigger == 0) {
    nDelayFading.run();
  }
  if (trigger == 1) {
    nDelayFadeout.run();
  }
  nDelaySweep.run();
  Serial.println(pos);
}