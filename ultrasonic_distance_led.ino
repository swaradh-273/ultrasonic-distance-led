// Pin configuration based on schematic
const int trigPin = 9;
const int echoPin = 10;
const int led1 = 2;        // LED1 (through 200Ω)
const int led2 = 3;        // LED2 (through 200Ω)
const int builtInLed = 13; // Built-in LED on Arduino Nano

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(builtInLed, OUTPUT);

  Serial.begin(9600);  // For debugging (optional)
}

void loop() {
  long duration;
  int distance;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo response
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED logic based on distance
  if (distance <= 5) {
    digitalWrite(builtInLed, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  } else if (distance > 5 && distance <= 10) {
    digitalWrite(builtInLed, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else if (distance > 10 && distance <= 15) {
    // Blink all 3 LEDs
    digitalWrite(builtInLed, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(builtInLed, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(200);
  } else {
    // No object nearby
    digitalWrite(builtInLed, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  delay(100);  // Small delay to stabilize readings
}
