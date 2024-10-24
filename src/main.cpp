#include <Arduino.h>

#define ROWS 10
#define COLS 8
#define D1 2
#define D2 3
#define ENC_SW 12
#define ENC_IN_A A1
#define ENC_IN_B A2

int counter = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
int pins[COLS] = {4, 5, 6, 7, 8, 9, 10, 11};

bool numbers[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 0}, // O
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 1, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // B
    {1, 1, 1, 1, 0, 1, 1}};// 9

void setup() {
  for (int i = 0; i < COLS; i++) {
    pinMode(pins[i], OUTPUT);
  }
  
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);

  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(ENC_IN_A, INPUT);
  pinMode(ENC_IN_B, INPUT);

  Serial.begin(9600);
}

void set_num(int number) {
  for (int i = 0; i < COLS; i++) {
    digitalWrite(pins[i], numbers[number][i]);
  }
}

void set_both_digits(int number) {
  int first_num = number / 10;
  int second_num = number % 10;
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  set_num(first_num);
  delay(5);
  digitalWrite(D2, LOW);
  digitalWrite(D1, HIGH);
  set_num(second_num);
  delay(5);
}

void loop() {
	currentStateCLK = digitalRead(ENC_IN_A);

	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1 && counter < 99 && counter > 0){
		if (digitalRead(ENC_IN_B) != currentStateCLK) {
			counter ++;
		} else {
			counter --;
		}
	}
  else if(currentStateCLK != lastStateCLK  && currentStateCLK == 1 && counter < 100 && counter >= -1){
    if (digitalRead(ENC_IN_B) == currentStateCLK && counter >= 99) {
			counter--;
    }
    else if (digitalRead(ENC_IN_B) != currentStateCLK && counter <= 0){
      counter++;
    }
  }

  int btnState = digitalRead(ENC_SW);

	if (btnState == LOW) {
		if (millis() - lastButtonPress > 50) {
			Serial.println("Couter reset!");
		}

		lastButtonPress = millis();
    counter = 0;
	}

	Serial.print("Counter: ");
	Serial.println(counter);
	lastStateCLK = currentStateCLK;
  set_both_digits(counter);
}