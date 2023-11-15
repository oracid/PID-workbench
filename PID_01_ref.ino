// Minimalist workbench PID, based on a frequency period - 11/11/2023
volatile unsigned long feedback, tic, tac=millis();
float prvTime = 0, dt;
float periodTarget = 90.00, kp = 0.30, ki = 6.00, kd = 0.002;    

void setup(){
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);
}

void loop(){
  float time = millis(); dt = (time - prvTime) /1000.00; prvTime = time;
  float pid = PID();
  digitalWrite(12, HIGH); delay(pid/2); digitalWrite(12, LOW); delay(pid/2);
  Serial.print(periodTarget,0); Serial.print(","); Serial.print(feedback); Serial.print(","); Serial.print(140); Serial.print(","); Serial.println(0);
}

float PID(){
  static float errorSum, previousError;
  float error = periodTarget - feedback;
  float P = kp * error;
  float I = ki * (errorSum = errorSum + (error * dt));
  float D = kd * (error - previousError) / dt;  previousError = error;
  return P + I + D;
}

void interrupt(){
  tic = millis();
  feedback = tic - tac;
  tac = tic;
}
