#define EN        8

//Direction pin
#define X_DIR     5
#define Y_DIR     6
#define Z_DIR     7

//Step pin
//#define X_STP     2
#define Y_STP     3
#define Z_STP     4


//Read Pins
#define DRIVER_STEPS_INPUT 2 //
#define DRIVER_DIR_INPUT 5 //Y_limit

//DRV8825

int count = 0;
int countSteps = 0;



void setup() {
  Serial.begin(115200);

  //  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(DRIVER_STEPS_INPUT, INPUT);

  pinMode(DRIVER_DIR_INPUT, INPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

  attachInterrupt(digitalRead(DRIVER_STEPS_INPUT), count_inc, RISING );
  Serial.println("start");

}

void count_inc()
{
  digitalWrite(Y_DIR, digitalRead(DRIVER_DIR_INPUT));
  Serial.println(count);
  count++;
  countSteps++;
  if (count == 70) {//94
    digitalWrite(Y_STP, HIGH);
    delay(100);
    digitalWrite(Y_STP, LOW);
    count = 0;
  }
}

void loop() {
  Serial.println(countSteps);
}
