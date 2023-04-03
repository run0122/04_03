# 04_03

millis_practice : millis() 함수 기본

millis_practice_2 : millis()와 servo를 동시에 & NDelayFunc 클래스 만들기(355p)

NDelayFunc : NDelayFunc 사용자 정의 라이브러리 만들기

<hr/>

## 1. millis()

아두이노의 동작이 시작된 이후의 현재 시간을 밀리 초 단위로 돌려줍니다. 1초에 1000값이 증가합니다.

millis() 함수는 크게 2가지 방식으로 사용됩니다.

**1) millis() - 저장된 값**

```
if (reading != last_buttonState) {
  button_pressed_time = millis();
}

if ((millis() - button_pressed_time) > button_delay) {
  if (reading != buttonState) {
    buttonState = reading;

    if (buttonState == HIGH) {
      ledState = !ledState;
    }
  }
}
```
이런 식으로 특정 시간을 millis()로 저장하여 작업이 수행된 시간을 재면서 작동할 수 있습니다. 

(Digital -> Debounce 참조)

<hr/>

**2) 값 = millis()**

```
t_now = millis();
if (t_now - t_prev >= t_delay) {
  t_prev = t_now;
}
```
이런 식으로 loop를 돌면서 증가하는 t_now값과, delay가 지날때마다 초기화되는 prev 값을 비교하여 반복적인 작업 수행이 가능합니다. 

(Basic -> BlinkWithoutDelay 참조)

<hr/>
