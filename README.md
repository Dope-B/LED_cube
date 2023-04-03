# Arduino용 3*3*3 LED_cube

#### 사용 기술: VisualMicro

#### 예시 영상
[![Video Label](http://img.youtube.com/vi/gjpLUAW07vc/0.jpg)](https://www.youtube.com/watch?v=gjpLUAW07vc&ab_channel=Obtron)
<br/>

#### 작품 사진 및 설계도

<div align="center">
<img width="25%" src="https://user-images.githubusercontent.com/33209821/229534865-16b42abb-ecc0-464d-be03-202ef1069688.jpg"/>
<img width="70%" src="https://user-images.githubusercontent.com/33209821/229540186-af150b62-0ac2-459e-acac-afc290f929ea.jpg"/>	
</div>

<br/>

#### 사용 부품
- 부저
- red_LED 
- 가변저항
<br/>

#### 설명
- 총 12개 패턴 구현
- 점, 선 ,면 단위로 on,off 기능 구현
- 가변저항으로 패턴 속도 조절 가능

```C
void deltaTimeCheck() {deltaTime = map(analogRead(A2), 0, 1024, 50, 500);}
```

- 일정 시간마다 패턴 반복
```C
if (millis() - total_time > 10000) {// 10초 주기
		total_time = millis();
		curPatternIndex++;
		buzzer.play(1000, 200);
		clear();
		buzzer.play(600, 100);
		if (curPatternIndex >= maxIndex) { curPatternIndex = 0; }
	}
	deltaTimeCheck();
	patternCheck();// 변경된 인덱스의 패턴 출력

```
- 빗방울 패턴은 다음과 같이 구현

```C
if (!isRaining) { rainPos[0] = random(0, 5); rainPos[1] = random(0, 5); isRaining = true; }// 새로운 빗방울 생성 위치 할당(rainPos배열은 x,y좌표)
	for (numForPattern7 = 0; numForPattern7 < 10; numForPattern7 ++)
	{
		if (numForPattern7 < 5) { pointOn(rainPos[0], rainPos[1], 4 - numForPattern7, 1); delay(deltaTime/2); }// 한 줄에 다 불이 들어올 때까지 실행
		else { digitalWrite(numForPattern7 - 3, 0); delay(deltaTime/2); }// 불이 다 들어온다면 위쪽부터 1개씩 off
	}
	isRaining = false;
	clear();

```
