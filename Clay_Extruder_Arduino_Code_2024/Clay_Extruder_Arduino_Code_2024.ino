// Driver Pin COnfiguration:
// https://www.diyengineers.com/wp-content/uploads/2022/12/CNC-Shield-Pins_3-1.png
#define EN    8
#define X_DIR 5
#define X_STP 2

// Input pin configuration
#define IN_EN  4
#define IN_DIR 6
#define IN_STP 3
#define POT_PIN A0

// Variables
long int count = 0;
int count_divisor = 1;   //number of steps to divide input signal with


void setup() {
  Serial.begin(115200);

 //Configure driver pins:
  pinMode(X_DIR, OUTPUT); 
  pinMode(X_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN,HIGH);

 //Configure input pins:
  pinMode(IN_DIR,INPUT_PULLUP);
  pinMode(IN_STP,INPUT_PULLUP);
  pinMode(IN_EN,INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(IN_STP), testInput, RISING);  //uncoment to test inputs from MKS unit test
  attachInterrupt(digitalPinToInterrupt(IN_STP), moveStepper, RISING);

}

void loop() {
//  testStepper(); uncomment to test steper motor working unit test
  }

int getCountDivisorValue(){
  count_divisor = map(analogRead(POT_PIN),0,1023,1,200); //map(value, fromLow, fromHigh, toLow, toHigh)
  return(count_divisor);
}

//Code to test stepper motor working. Uncomment in loop()
void testStepper() {
  digitalWrite(EN,LOW);
  for (int i=0;i<500;i++)
  {
    digitalWrite(X_DIR,HIGH);
    digitalWrite(X_STP,HIGH);
    delay(5);
    digitalWrite(X_STP,LOW);
    delay(5);
  }
  for (int i=0;i<500;i++)
  {
    digitalWrite(X_DIR,LOW);
    digitalWrite(X_STP,HIGH);
    delay(5);
    digitalWrite(X_STP,LOW);
    delay(5);
  }
  digitalWrite(EN,HIGH);
}

//code to test input from MKS. uncomment in setup() and comment out other ISR
void testInput() {
  if (digitalRead(IN_DIR) == HIGH)
    count++;
   else
    count--;
   Serial.println();
   Serial.print("Enable:");
   Serial.print(digitalRead(IN_EN));
   Serial.print("  Count: ");
   Serial.print(count);

}
// Actual production code
void moveStepper() {
  digitalWrite(X_DIR, digitalRead(IN_DIR));
  digitalWrite(EN,digitalRead(IN_EN));
  Serial.println(count);
  count++;
  if (count >= getCountDivisorValue()) { 
    digitalWrite(X_STP, HIGH);
    delay(100);
    digitalWrite(X_STP, LOW);
    delay(100);
    count = 0;
  }
  digitalWrite(EN,digitalRead(IN_EN));
}
