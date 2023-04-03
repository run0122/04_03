// 1. Servo와 LED를 동시에

// #include <Servo.h>

// Servo myservo;

// int potpin = A0;
// int ledpin = 11;
// int val;

// unsigned long t_prev = 0;
// unsigned long t_delay = 1000;

// void setup() {
//   myservo.attach(9);
// }

// void loop() {
//   val = analogRead(potpin);
//   int val1 = map(val, 0, 1023, 0, 180);
//   int val2 = map(val, 0, 1023, 0, 255);
//   myservo.write(val1);
//   delay(15);

//   unsigned long t_now = millis();
//   if (t_now - t_prev >= t_delay / 2) {
//     analogWrite(ledpin, val2);
//   } else if (t_now - t_prev < t_delay / 2) {
//     analogWrite(ledpin, 0);
//   }
//   if (t_now - t_prev >= t_delay) {
//     t_prev = t_now;
//   }
// }

// 2. NDelay 클래스 만들기

class NDelayFunc {
  unsigned long t_prev;
  const unsigned long t_delay;
  void (*func)();

public:
  NDelayFunc(
    const unsigned long t_delay,
    void (*func)())
    : t_prev(0), t_delay(t_delay), func(func) {}

  void run() {
    unsigned long t_now = millis();
    if (t_now - t_prev >= t_delay) {
      t_prev = t_now;

      func();
    }
  }
};

const int LED = 11;
unsigned int t_high = 0;
unsigned int t_high2 = 255;
int trigger = 0;

void fading() {
  t_high++;
  if (t_high > 255) {
    t_high = 0;
    trigger = 1;
  }
  analogWrite(LED, t_high);
}
void fadeout() {
  t_high2--;
  if (t_high2 == 0) {
    t_high2 = 255;
    trigger = 0;
  }
  analogWrite(LED, t_high2);
}

NDelayFunc nDelayFading(4, fading);
NDelayFunc nDelayFadeout(4, fadeout);

void setup() {
}

void loop() {
  if (trigger == 0) {
    nDelayFading.run();
  } else if (trigger == 1) {
    nDelayFadeout.run();
  }
}