const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
int valArr[10];
int pos;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pos = 0;
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration*0.034/2;

  printAverage(distance);
}

void printAverage(int newVal) {
  valArr[pos] = newVal;

  if (pos = 9) {
    int average;
    for (int i = 0; i < 10; i++) {
      average += valArr[i];
    }

    average = average / 10;
    
    Serial.print("Distance avg: ");
    Serial.println(average);
    pos = 0;
  } else {
    pos++;
  }
}
