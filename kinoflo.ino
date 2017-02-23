int hLedPin = 9;
int cLedPin = 10;

int hAddPin = 8; int hSubPin = 7;// hot led + / -  pins
int cAddPin = 5; int cSubPin = 6;// hot led + / -  pins
int brightness = 100;

int fullPin = 4;

float hVal = 0.1;  //initial h/c values
float cVal = 0.1;
void setup() {
  Serial.begin(9600);
  pinMode(hLedPin, OUTPUT);
  pinMode(cLedPin, OUTPUT);
  pinMode(hAddPin, INPUT); pinMode(hSubPin, INPUT);
  pinMode(cAddPin, INPUT); pinMode(cSubPin, INPUT);

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

  tempCtrl(); //temperature control

  Serial.print("h:"); Serial.print(hVal); Serial.print(" c:"); Serial.println(cVal);
  //Serial.println(hVal);
}

void tempCtrl() {
  if (digitalRead(hAddPin) == HIGH) {
    hVal = hVal + 0.01;
    if (hVal >= 1) {
      hVal = 1;

      ledCtrl(0, hLedPin);  //miganie ze max
      delay(10);
      ledCtrl(100, hLedPin);  //miganie ze max
    }
    delay(100);
  }
  if (digitalRead(hSubPin) == HIGH) {
    hVal = hVal - 0.01;
    if (hVal <= 0) {
      hVal = 0;
    }
    delay(100);
  }

  if (digitalRead(cAddPin) == HIGH) {
    cVal = cVal + 0.01;
    if (cVal >= 1) {
      cVal = 1;

      
      ledCtrl(0, cLedPin);  //miganie ze max
      delay(10);
      ledCtrl(100, cLedPin);  //miganie ze max
    }
    delay(100);
  }
  if (digitalRead(cSubPin) == HIGH) {
    cVal = cVal - 0.01;
    if (cVal <= 0) {
      cVal = 0;
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
