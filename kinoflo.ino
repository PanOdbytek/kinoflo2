int hLedPin = 9;
int cLedPin = 10;

int briAddPin = 8; int briSubPin = 7;// brightness + / -  pins
int brightness = 0;

int fullPin = 4;

int hVal = 1;  //initial h/c values
int cVal = 1;
void setup() {
  Serial.begin(9600);
  pinMode(hLedPin, OUTPUT);
  pinMode(cLedPin, OUTPUT);
  pinMode(briAddPin, INPUT); pinMode(briSubPin, INPUT);

  pinMode(fullPin, INPUT);
}

void loop() {
  int full = digitalRead(fullPin); // jak sie zewrze to swiecimy na 100%

  if (full == LOW) {
    ledCtrl(hVal * brightness, hLedPin);
    ledCtrl(cVal * brightness, cLedPin);
    //  Serial.println("h "+hVal+" c "+cVal);
  }
  if (full == HIGH) {
    ledCtrl(100, hLedPin);
    ledCtrl(100, cLedPin);
  }
  
briCtrl();

// Serial.print("+:"); Serial.print(digitalRead(briAddPin)); Serial.print(" -:"); Serial.println(digitalRead(briSubPin));
Serial.println(brightness);
}

void briCtrl(){
  if (digitalRead(briAddPin) == HIGH) {
    brightness = brightness + 1;
    if (brightness >= 100) {
      brightness = 100;
    }
    delay(100);
  }
  if (digitalRead(briSubPin) == HIGH) {
    brightness = brightness - 1;
    if (brightness <= 0) {
      brightness = 0;
    }
    delay(100);
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
