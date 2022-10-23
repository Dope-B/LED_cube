
/*
 Name:		CUbe.ino
 Created:	2022-05-30 오후 7:15:05
 Author:	김동빈
*/
#include <Tone.h>
#include <LiquidCrystal.h>
LiquidCrystal LCD1(53, 52, 51, 50, 49, 48);
Tone buzzer;
int buttonCount = 0;
int curPatternIndex = 0;
int maxIndex = 12;
int deltaTime = 500;// ms
int numForPattern2 = 0;
int numForPattern3 = 0;
int numForPattern5 = 0;
int numForPattern6 = 0;
int numForPattern7 = 0;
int numForPattern9 = 0;
int numForPattern10 = 0;
int numForPattern11 = 0;
int rainPos[2] = { 0,0 };
bool isRaining = false;
unsigned long time;
unsigned long total_time;

// the setup function runs once when you press reset or power the board
void setup() {
	//LCD1.begin(16, 2);
	buzzer.begin(A0);
	Serial.begin(9600);
	LCD1.begin(16, 2);
	//LCD1.print("asd");
	for (int i = 2; i <= 7; i++)
	{
		pinMode(i, OUTPUT);
	}
	for (int i = 22; i <= 46; i++)
	{
		pinMode(i, OUTPUT);
	}
	clear();
	time = millis();
	total_time = millis();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (millis() - total_time > 10000) {
		total_time = millis();
		curPatternIndex++;
		buzzer.play(1000, 200);
		clear();
		buzzer.play(600, 100);
		if (curPatternIndex >= maxIndex) { curPatternIndex = 0; }
	}
	//buttonCheck();
	//Serial.println(buttonCount);
	deltaTimeCheck();
	patternCheck();
	//atom();
	//LED_allON();
}

void buttonCheck() {
	if (digitalRead(46)) {  buttonCount++; }
	if (buttonCount > 5) {
		buzzer.play(1000, 200); 
		if (curPatternIndex >= maxIndex) { curPatternIndex = 0; }
		else{ curPatternIndex++; }
		buttonCount = 0;
		Serial.println(curPatternIndex);
		clear();//to change pattern
	}
	//else { if (buttonCount > 0) { buttonCount--; } }
}
void patternCheck() {
	switch (curPatternIndex)
	{
	case 0:
		 LED_allON(); 
		break;
	case 1:
		outLine();
		break;
	case 2:
		 crossHair();
		break;
	case 3:
		 innerSquare();
		break;
	case 4:
		crossingLine();
		break;
	case 5:
		climbingSnake();
		break;
	case 6:
		windMill();
		break;
	case 7:
		rain();
		break;
	case 8:
		crossPlane();
		break;
	case 9:
		DCU();
		break;
	case 10:
		flippingCard();
		break;
	case 11:
		spade();
		break;
	case 12:
		atom();
		break;
	default:
		break;
	}
}
void deltaTimeCheck() {
	deltaTime = map(analogRead(A2), 0, 1024, 50, 500);
}
// on->1, off->0
void LED_allON() {//  pattern 01
	for (int i = 2; i <= 6; i++)
	{
		digitalWrite(i, 1);
	}
	digitalWrite(7, 0);
	for (int i = 22; i <= 45; i++)
	{
		digitalWrite(i, 0);
	}
}
void outLine() {// pattern 02
		
	for (numForPattern2 = 0; numForPattern2 < 2; numForPattern2++)
	{
		clear();
		switch (numForPattern2) {
		case 0:colOn(0, 0, 1);
			colOn(0, 4, 1);
			colOn(4, 0, 1);
			colOn(4, 4, 1); break;
		case 1:xRowOn(0, 0, 1);
		xRowOn(4, 0, 1);
		xRowOn(4, 4, 1);
		xRowOn(0, 4, 1);
		yRowOn(0, 0, 1);
		yRowOn(0, 4, 1);
		yRowOn(4, 0, 1);
		yRowOn(4, 4, 1); break;
		}
		delay(10);
	}
	numForPattern2 = 0;
	
}
void crossHair() {// pattern 03
	for (numForPattern3 = 0; numForPattern3 < 2; numForPattern3++)
	{
		clear();
		if(numForPattern3==0){xRowOn(2, 2, 1); yRowOn(2, 2, 1);}
		else{ colOn(2, 2, 1); }
		delay(10);
	}
	
	
}
void innerSquare() {// pattern 04
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			for (int z = 1; z < 4; z++)
			{
				pointOn(i, j, z, 1);
			}
		}
	}
}

void crossingLine() {// pattern 05
	clear();
	if (numForPattern5 < 4) {
		colOn(3 - (numForPattern5 / 2), 3, 1);
		colOn(numForPattern5, 0, 1); numForPattern5 += 1;
	}
	else if (numForPattern5 < 8) {
		colOn(1, 3 - (numForPattern5 / 6), 1);
		colOn(4, numForPattern5 - 4, 1); numForPattern5 += 1;
	}
	else if (numForPattern5 < 12) {
		colOn(1 + (numForPattern5 / 10), 1, 1);
		colOn(12 - numForPattern5, 4, 1); numForPattern5 += 1;
	}
	else if (numForPattern5 < 16) {
		colOn(3, 1 + (numForPattern5 / 14), 1);
		colOn(0, 16 - numForPattern5, 1); numForPattern5 += 1;}
	if (numForPattern5 == 16) { numForPattern5 = 0; }
	delay(deltaTime);
}
void climbingSnake() {// pattern 06
		for (int j = 0; j < 5; j++)//y
		{
			for (int k = 0; k < 5; k++)//x
			{
				if (j % 2 == 0) { colOn(k, j, 1); }//even
				else { colOn(4 - k, j, 1); }//odd
				delay(deltaTime);
			}
		}
	
		for (int j = 0; j < 5; j++)//y
		{
			digitalWrite(6 - j, 0);
			delay(deltaTime);
		}
		clear();
	
}
void windMill() {//pattern 07
	
	
	for (numForPattern6 = 0; numForPattern6< 4; numForPattern6++)
	{
		clear();
		yRowOn(2, 2, 1);
		switch (numForPattern6)
		{
		case 0:yRowOn(2, 3, 1); yRowOn(2, 4, 1); break;
		
		case 1:yRowOn(3, 2, 1); yRowOn(4, 2, 1); break;
		
		case 2:yRowOn(2, 1, 1); yRowOn(2, 0, 1); break;
		
		case 3:yRowOn(1, 2, 1); yRowOn(0, 2, 1); break;
		
		default:
			break;
		}
		delay(deltaTime);
	}
	numForPattern6 = 0;
}
void rain() {//pattern 08
	if (!isRaining) { rainPos[0] = random(0, 5); rainPos[1] = random(0, 5); isRaining = true; }
	for (numForPattern7 = 0; numForPattern7 < 10; numForPattern7 ++)
	{
		if (numForPattern7 < 5) { pointOn(rainPos[0], rainPos[1], 4 - numForPattern7, 1); delay(deltaTime/2); }
		else { digitalWrite(numForPattern7 - 3, 0); delay(deltaTime/2); }
	}
	isRaining = false;
	clear();
}
void crossPlane() {
	for (int i = 0; i < 5; i++) {
		xPlaneOn(i, 1);
		yPlaneOn(i, 1);
		delay(deltaTime);
		clear();
	}
	for (int i = 4; i >= 0; i--) {
		xPlaneOn(i, 1);
		yPlaneOn(i, 1);
		delay(deltaTime);
		clear();
	}
	/*for (int i = 0; i < 5; i++) {
		xPlaneOn(i, 0);
		zPlaneOn(i, 0);
		delay(deltaTime);
	}*/
	//clear();
}
void DCU() {// pattern09
	for (numForPattern9 = 0;  numForPattern9< 33; numForPattern9++)
	{
		clear();
		switch (numForPattern9)
		{
		case 0:pointOn(0, 2, 0, 1); break;
		case 1:pointOn(0, 2, 1, 1); break;
		case 2:pointOn(0, 2, 2, 1); break;
		case 3:pointOn(0, 2, 3, 1); break;
		case 4:pointOn(0, 2, 4, 1); break;
		case 5:pointOn(1, 2, 4, 1); break;
		case 6:pointOn(2, 2, 4, 1); break;
		case 7:pointOn(3, 2, 3, 1); break;
		case 8:pointOn(3, 2, 2, 1); break;
		case 9:pointOn(3, 2, 1, 1); break;
		case 10:pointOn(2, 2 , 0, 1); break;
		case 11:pointOn(1, 2, 0, 1); break;
		case 12:pointOn(0, 2, 0, 1); break;

		case 13:pointOn(3, 2, 0, 1); break;
		case 14:pointOn(2, 2, 0, 1); break;
		case 15:pointOn(1, 2, 0, 1); break;
		case 16:pointOn(0, 2, 1, 1); break;
		case 17:pointOn(0, 2, 2, 1); break;
		case 18:pointOn(0, 2, 3, 1); break;
		case 19:pointOn(1, 2, 4, 1); break;
		case 20:pointOn(2, 2, 4, 1); break;
		case 21:pointOn(3, 2, 4, 1); break;

		case 22:pointOn(3, 2, 4, 1); break;
		case 23:pointOn(3, 2, 3, 1); break;
		case 24:pointOn(3, 2, 2, 1); break;
		case 25:pointOn(3, 2, 1, 1); break;
		case 26:pointOn(3, 2, 0, 1); break;
		case 27:pointOn(2, 2, 0, 1); break;
		case 28:pointOn(1, 2, 0, 1); break;
		case 29:pointOn(1, 2, 1, 1); break;
		case 30:pointOn(1, 2, 2, 1); break;
		case 31:pointOn(1, 2, 3, 1); break;
		case 32:pointOn(1, 2, 4, 1); break;

		}
		delay(50);
		if (numForPattern9 == 12) { delay(500); }
		if (numForPattern9 == 21) { delay(500); }
		if (numForPattern9 == 32) { delay(500); }
		
	}
	numForPattern9 = 0;
}

void spade() {
	for ( numForPattern10 = 0; numForPattern10 < 8; numForPattern10++)
	{
		clear();
		switch (numForPattern10/2)
		{
		case 0: pointOn(2 + (numForPattern10 % 2), 0, 0 + (numForPattern10 % 2), 1); pointOn(0, 2 - (numForPattern10 % 2), 0 + (numForPattern10 % 2), 1);
			    pointOn(2 + (numForPattern10 % 2), 4, 0 + (numForPattern10 % 2), 1); pointOn(4, 2 - (numForPattern10 % 2), 0 + (numForPattern10 % 2), 1); delay(deltaTime / 2);
			break;
		case 1: pointOn(4 - (numForPattern10 % 2), 0, 2 + (numForPattern10 % 2), 1); pointOn(0, 0 + (numForPattern10 % 2), 2 + (numForPattern10 % 2), 1);
			    pointOn(4 - (numForPattern10 % 2), 4, 2 + (numForPattern10 % 2), 1); pointOn(4, 0 + (numForPattern10 % 2), 2 + (numForPattern10 % 2), 1); delay(deltaTime / 2);
			break;
		case 2: pointOn(2 - (numForPattern10 % 2), 0, 4 - (numForPattern10 % 2), 1); pointOn(0, 2 + (numForPattern10 % 2), 4 - (numForPattern10 % 2), 1);
			    pointOn(2 - (numForPattern10 % 2), 4, 4 - (numForPattern10 % 2), 1); pointOn(4, 2 + (numForPattern10 % 2), 4 - (numForPattern10 % 2), 1); delay(deltaTime / 2);
			break;
		case 3: pointOn(0 + (numForPattern10 % 2), 0, 2 - (numForPattern10 % 2), 1); pointOn(0, 4 - (numForPattern10 % 2), 2 - (numForPattern10 % 2), 1);
			    pointOn(0 + (numForPattern10 % 2), 4, 2 - (numForPattern10 % 2), 1); pointOn(4, 4 - (numForPattern10 % 2), 2 - (numForPattern10 % 2), 1); delay(deltaTime / 2);
			break;
		default:
			break;
		}
		
	}
	numForPattern10 = 0;
}
void atom() {
	for (numForPattern11 = 0; numForPattern11 < 32; numForPattern11++)
	{
		clear();
		switch (numForPattern11/8)
		{
		case 0: switch (numForPattern11 / 2) {
				case 0: pointOn(2 - (numForPattern11 % 2), 2, 4 - (numForPattern11 % 2), 1); break;
				case 1: pointOn(0 + (numForPattern11 % 2), 2, 2 - (numForPattern11 % 2), 1); break;
				case 2: pointOn(2 + (numForPattern11 % 2), 2, 0 + (numForPattern11 % 2), 1); break;
				case 3: pointOn(4 - (numForPattern11 % 2), 2, 2 + (numForPattern11 % 2), 1); break;
				}
			break;
		case 2:switch (numForPattern11 / 2) {
				case 8: pointOn(2, 2 - (numForPattern11 % 2), 4 - (numForPattern11 % 2), 1); break;
				case 9: pointOn(2, 0 + (numForPattern11 % 2), 2 - (numForPattern11 % 2), 1); break;
				case 10: pointOn(2, 2 + (numForPattern11 % 2), 0 + (numForPattern11 % 2), 1); break;
				case 11: pointOn(2, 4 - (numForPattern11 % 2), 2 + (numForPattern11 % 2), 1); break;
		}
			break;
		case 3:switch (numForPattern11 / 2) {
				case 12: pointOn(2 - (numForPattern11 % 2), 2 + (numForPattern11 % 2), 4 - (numForPattern11 % 2), 1); break;
				case 13: pointOn(0 + (numForPattern11 % 2), 4 - (numForPattern11 % 2), 2 - (numForPattern11 % 2), 1); break;
				case 14: pointOn(2 + (numForPattern11 % 2), 2 - (numForPattern11 % 2), 0 + (numForPattern11 % 2), 1); break;
				case 15: pointOn(4 - (numForPattern11 % 2), 0 + (numForPattern11 % 2), 2 + (numForPattern11 % 2), 1); break;
		}
			break;
		case 1:switch (numForPattern11 / 2) {
				case 4: pointOn(2 + (numForPattern11 % 2), 2 - (numForPattern11 % 2), 4 - (numForPattern11 % 2), 1); break;
				case 5: pointOn(4 - (numForPattern11 % 2), 0 + (numForPattern11 % 2), 2 - (numForPattern11 % 2), 1); break;
				case 6: pointOn(2 - (numForPattern11 % 2), 2 + (numForPattern11 % 2), 0 + (numForPattern11 % 2), 1); break;
				case 7: pointOn(0 + (numForPattern11 % 2), 4 - (numForPattern11 % 2), 2 + (numForPattern11 % 2), 1); break;
		}
			break;
		default:
			break;
		}
		delay(deltaTime / 2);
	}
	numForPattern11 = 0;
}
void flippingCard() {
	for (int i = 0; i < 4; i++)
	{
		clear();
		switch (i)
		{
		case 0:yPlaneOn(2, 1); break;
		case 1:for (int j = 0; j < 5; j++) { colOn(0 + j, 0 + j, 1); }break;
		case 2:xPlaneOn(2, 1); break;
		case 3:for (int j = 0; j < 5; j++) { colOn(0 + j, 4 - j, 1); }break;
		default:
			break;
		}
		delay(deltaTime);
	}
}

void checkXY(int x, int y, bool onOff) {
	switch (x)
	{
	case 4:
		switch (y)
		{
		case 0:digitalWrite(41, !onOff);
			break;
		case 1:digitalWrite(42, !onOff);
			break;
		case 2:digitalWrite(43, !onOff);
			break;
		case 3:digitalWrite(44, !onOff);
			break;
		case 4:digitalWrite(45, !onOff);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (y)
		{
		case 0:digitalWrite(36, !onOff);
			break;
		case 1:digitalWrite(37, !onOff);
			break;
		case 2:digitalWrite(38, !onOff);
			break;
		case 3:digitalWrite(39, !onOff);
			break;
		case 4:digitalWrite(40, !onOff);
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (y)
		{
		case 0:digitalWrite(31, !onOff);
			break;
		case 1:digitalWrite(32, !onOff);
			break;
		case 2:digitalWrite(33, !onOff);
			break;
		case 3:digitalWrite(34, !onOff);
			break;
		case 4:digitalWrite(35, !onOff);
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (y)
		{
		case 0:digitalWrite(26, !onOff);
			break;
		case 1:digitalWrite(27, !onOff);
			break;
		case 2:digitalWrite(28, !onOff);
			break;
		case 3:digitalWrite(29, !onOff);
			break;
		case 4:digitalWrite(30, !onOff);
			break;
		default:
			break;
		}
		break;
	case 0:
		switch (y)
		{
		case 0:digitalWrite(7, !onOff);
			break;
		case 1:digitalWrite(22, !onOff);
			break;
		case 2:digitalWrite(23, !onOff);
			break;
		case 3:digitalWrite(24, !onOff);
			break;
		case 4:digitalWrite(25, !onOff);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void checkZ(int z,bool onOff) {
	switch (z)
	{
	case 0:digitalWrite(6, onOff);
		break;
	case 1:digitalWrite(5, onOff);
		break;
	case 2:digitalWrite(4, onOff);
		break;
	case 3:digitalWrite(3, onOff);
		break;
	case 4:digitalWrite(2, onOff);
		break;
	default:
		break;
	}
}
void pointOn(int x, int y, int z, bool onOff) {
	checkXY(x, y, onOff);
	checkZ(z, onOff);
}
void colOn(int x, int y, bool onOff) {
	for (int i = 2; i < 7; i++)
	{
		digitalWrite(i, onOff);
	}
	checkXY(x, y, onOff);
}
void yRowOn(int y, int z, bool onOff) {
	switch (y)
	{
	case 4:for (int i = 41; i < 46; i++) { digitalWrite(i, !onOff); }
		  break;
	case 3:for (int i = 36; i < 41; i++) { digitalWrite(i, !onOff); }
		  break;
	case 2:for (int i = 31; i < 36; i++) { digitalWrite(i, !onOff); }
		  break;
	case 1:for (int i = 26; i < 31; i++) { digitalWrite(i, !onOff); }
		  break;
	case 0:
		digitalWrite(7, !onOff);
		for (int i = 22; i < 26; i++) { digitalWrite(i, !onOff); }
		break;
	default:
		break;
	}
	checkZ(z, onOff);
}
void xRowOn(int x, int z, bool onOff) {
	switch (x)
	{
	case 0:
		digitalWrite(7, !onOff);
		for (int i = 0; i < 4; i++) { digitalWrite(26+(5*i), !onOff); }
		  break;
	case 1:for (int i = 0; i < 5; i++) { digitalWrite(22+(5*i), !onOff); }
		  break;
	case 2:for (int i = 0; i < 5; i++) { digitalWrite(23 + (5 * i), !onOff); }
		  break;
	case 3:for (int i = 0; i < 5; i++) { digitalWrite(24 + (5 * i), !onOff); }
		  break;
	case 4:for (int i = 0; i < 5; i++) { digitalWrite(25 + (5 * i), !onOff); }
		break;
	default:
		break;
	}
	checkZ(z,onOff);
}
void xPlaneOn(int y, bool onOff) {
	//digitalWrite(7, !onOff);
	switch (y)
	{
	case 0:
		digitalWrite(7, !onOff);
		for (int i = 0; i < 4; i++) { digitalWrite(26 + (5 * i), !onOff); }
		break;
	case 1:for (int i = 0; i < 5; i++) { digitalWrite(22 + (5 * i), !onOff); }
		  break;
	case 2:for (int i = 0; i < 5; i++) { digitalWrite(23 + (5 * i), !onOff); }
		  break;
	case 3:for (int i = 0; i < 5; i++) { digitalWrite(24 + (5 * i), !onOff); }
		  break;
	case 4:for (int i = 0; i < 5; i++) { digitalWrite(25 + (5 * i), !onOff); }
		  break;
	default:
		break;
	}
	for (int i = 2; i < 7; i++)
	{
		digitalWrite(i, onOff);
	}
}
void yPlaneOn(int x, bool onOff) {
	for (int i = 2; i < 7; i++)
	{
		digitalWrite(i, onOff);
	}
	switch (x)
	{
	case 4:for (int i = 41; i < 46; i++) { digitalWrite(i, !onOff); }
		  break;
	case 3:for (int i = 36; i < 41; i++) { digitalWrite(i, !onOff); }
		  break;
	case 2:for (int i = 31; i < 36; i++) { digitalWrite(i, !onOff); }
		  break;
	case 1:for (int i = 26; i < 31; i++) { digitalWrite(i, !onOff); }
		  break;
	case 0:
		digitalWrite(7, !onOff);
		for (int i = 22; i < 26; i++) { digitalWrite(i, !onOff); }
		break;
	default:
		break;
	}
}
void clear() {
	digitalWrite(7, 1);
	for (int i = 22; i < 46; i++)
	{
		digitalWrite(i, 1);
	}
	for (int i = 2; i < 7; i++)
	{
		digitalWrite(i, 0);
	}
}

