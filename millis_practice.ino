// 1.
// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   unsigned long t_now = millis();
//   Serial.println(t_now);
// }

// 2.
// unsigned long t_prev = 0;
// const unsigned long t_delay = 1000;

// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   unsigned long t_now = millis();
//   if (t_now - t_prev >= t_delay) {
//     t_prev = t_now;

//     Serial.println(t_now);
//   }
// }


// 3.
//

// 4. for문 Blink
// const int LED = 13;

// void setup() {
//   pinMode(LED, OUTPUT);
// }

// void loop() {
//   for (int on_off = 0; on_off <= 1; on_off++) {
//     digitalWrite(LED, on_off);
//     delay(500);
//   }
// }

// 5. millis로 Blink
// const int LED = 13;
// int on_off = 0;

// unsigned long t_prev = 0;
// const unsigned long t_delay = 500;

// void setup() {
//   pinMode(LED, OUTPUT);
// }

// void loop() {
//   unsigned long t_now = millis();
//   if (t_now - t_prev >= t_delay) {
//     t_prev = t_now;

//     on_off++;
//     if (on_off > 1) on_off = 0;
//     digitalWrite(LED, on_off);
//   }
// }

// 5. for문 LED 밝기 조절
// const int LED = 11;

// void setup() {
// }

// void loop() {
//   for (int t_high = 0; t_high <= 255; t_high++) {
//     analogWrite(LED, t_high);
//     delay(4);
//   }
// }

// 6. millis로 LED 밝기 조절
// const int LED = 11;
// int t_high;

// unsigned long t_prev = 0;
// const unsigned long t_delay = 4;

// void setup() {
// }

// void loop() {
//   unsigned long t_now = millis();
//   if (t_now - t_prev >= t_delay) {
//     t_prev = t_now;

//     t_high++;
//     if (t_high > 255) t_high = 0;
//     analogWrite(LED, t_high);
//   }
// }

// 7. millis로 다중 작업하기

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

// 8. millis로 다중 작업하기

const int t1_LED = 13;
unsigned int on_off = 0;

const int t2_LED = 11;
unsigned int t_high = 0;

unsigned long t1_prev = 0;
const unsigned long t1_delay = 500;

unsigned long t2_prev = 0;
const unsigned long t2_delay = 1000;

const int buttonPin = 2;
const int analogPin = A0;

int buttonState = 0;

void setup() {
  pinMode(t1_LED, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  int sensorInput = analogRead(analogPin);

  unsigned long t1_now = millis();

  if (buttonState == HIGH) {
    if (t1_now - t1_prev >= t1_delay) {
      t1_prev = t1_now;

      on_off++;
      if (on_off > 1) on_off = 0;
      digitalWrite(t1_LED, on_off);
    }
  }

  unsigned long t2_now = millis();
  if (t2_now - t2_prev >= t2_delay / 2) {
    analogWrite(t2_LED, sensorInput / 4);
  }
  else if (t2_now - t2_prev < t2_delay /2){
    analogWrite(t2_LED, 0);
  }
  if (t2_now - t2_prev >= t2_delay) {
    t2_prev = t2_now;
    // analogWrite(t2_LED, 0);
  }
  Serial.println(t2_now - t2_prev);
}