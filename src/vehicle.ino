#include <AFMotor.h>
#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

const int obstacleThreshold = 30;

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  int distance = sonar.ping_cm();
  Serial.print("检测距离：");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < obstacleThreshold) {
    avoidObstacle();
  } else {
    moveForward();
  }

  delay(100);
}

void moveForward() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void turnLeft() {
  motor1.setSpeed(100);
  motor2.setSpeed(150);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void turnRight() {
  motor1.setSpeed(150);
  motor2.setSpeed(100);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void avoidObstacle() {
  moveBackward();
  delay(500);
  turnRight();
  delay(1000);
  moveForward();
}
