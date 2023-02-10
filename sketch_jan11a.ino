#define outputA 2
#define outputB 3
#define PWM_PIN 9
#define B1_PIN 10
#define B2_PIN 11

int counter = 0;
int pre_time, current_time = millis();
int d_time = 100;
double errorValue = 0;
double pre_error = 0;
double kp = 0.2;
double ki = 0.000003;
double kd = 100;
double P, I, D, PID, pwm = 0;
double encoder = 0, rpm = 0;
const double MAX_SPEED = 1960 / (1000 / d_time);
double velocity = 100;

int countEncoder();
int multiSignal();
int calPID();

void setup() {
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);
  pinMode (PWM_PIN, OUTPUT);
  pinMode (B1_PIN, OUTPUT);
  pinMode (B2_PIN, OUTPUT);

  Serial.begin (115200);
  digitalWrite(B1_PIN, HIGH);
  digitalWrite(B2_PIN, LOW);
}

void loop() {
  current_time = millis();
  countEncoder();
  //  Serial.print(digitalRead(outputB));
  //  Serial.print(" ");
  //  Serial.println(digitalRead(outputA));
  if (current_time - pre_time > d_time) {
    PID = calPID();
    PID = map(PID, 0, MAX_SPEED, 0, 255);
    pwm += PID;
    if (pwm > 255) {
      pwm = 255;
    } else if (pwm < 0) {
      pwm = 0;
    }
    //    Serial.println(counter);
    counter = 0;
    pre_time = current_time;
    analogWrite(PWM_PIN, pwm);
    if (Serial.available()) {
      velocity = Serial.readString().toInt();
      delay(10);
      //      Serial.print(velocity);
    }
  }
  //    Serial.println(counter);
}

int calPID() {
  errorValue = velocity - counter; //Current position - target position (or setpoint)
  Serial.print("Velocity: ");
  Serial.print(velocity);
  //  Serial.print(" ERROR: ");
  //  Serial.print(errorValue);
  Serial.print(" Encoder ");
  Serial.print(counter);
    Serial.print(" PWM: ");
    Serial.println(pwm);
  P = kp * errorValue;
  I += ki * (errorValue * d_time);
  D = kd * ((errorValue - pre_error) / d_time);
  pre_error = errorValue;

  return P + I + D;
}

int countEncoder() {
  attachInterrupt(digitalPinToInterrupt(outputB), multiSignal, RISING);
  return counter;
}

int multiSignal() {
  if (digitalRead(outputB) * digitalRead(outputA) == 0) {
    counter++;
  } else {
    counter--;
  }
}
