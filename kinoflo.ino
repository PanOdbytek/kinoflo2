int hLedPin = 9;
int cLedPin = 10;

int hAddPin = 8; int hSubPin = 7;// piny dla hot plus i minius
int cAddPin = 6; int cSubPin = 5;// piny dla cold plus i minius

int fullPin = 4;

int hVal = 10;  //initial h/c values
int cVal = 10;
void setup() {
  Serial.begin(9600);
  pinMode(hLedPin, OUTPUT);
  pinMode(cLedPin, OUTPUT);
  pinMode(hAddPin, INPUT); pinMode(hSubPin, INPUT);
  pinMode(cAddPin, INPUT); pinMode(cSubPin, INPUT);

  pinMode(fullPin, INPUT);
}

void loop() {
  int full = digitalRead(fullPin);
  
  if (full == LOW) {
    ledCtrl(hVal, hLedPin);
    ledCtrl(cVal, cLedPin);
  //  Serial.println("h "+hVal+" c "+cVal);
    }

}



void ledCtrl(int val, int lPin) {
  analogWrite(lPin, linearPWM(val));  // val range: [0;100] 
}

int linearPWM(int percentage) {
  // coefficients
  double a = 9.7758463166360387E-01;
  double b = 5.5498961535023345E-02;
  return floor((a * exp(b * percentage) + .5)) - 1;
}
