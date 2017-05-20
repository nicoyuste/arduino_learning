int isON = false;

void setup() {
  
  // Debugging.
  Serial.begin(9600);

  // Asking for control of the seven pins  
  // that I am going to need to display the numbers.
  pinMode(2,OUTPUT); // A
  pinMode(3,OUTPUT); // B
  pinMode(4,OUTPUT); // C
  pinMode(5,OUTPUT); // D
  pinMode(6,OUTPUT); // E
  pinMode(7,OUTPUT); // F
  pinMode(8,OUTPUT); // G

  // Asking for the out for the color code of 10,20 and 30 degrees.
  pinMode(9, OUTPUT); // Blue, 10 degrees
  pinMode(10, OUTPUT); // Yellow, 20 degrees
  pinMode(11, OUTPUT); // Red, 30 degrees

  // Fire should be one.
  pinMode(12, OUTPUT); // Red, 30 degrees

}

/*
 * This function takes an integer and it is able to display into a NTE3052 led panel.
 *
 * @param: digit -> The number that is going to be displayed.
 * @param: firstOutputPin -> Led panel has 7 inputs: A,B,C,D,E,F and G.
 *     this param represents the pin number of the first led. It assumes that A=firstOutputPin and
 *     the others are progressively set up. So B will be firstOutputPin+1, etc...
*/
void showNumberInNTE3052(int digit,int firstOutputPin) {

  if (digit < 0 or digit > 9) {
    // Error, this only can show a one digit number.
    return;
  }

  int leds[7];
  switch (digit){ //      A,         B,         C,         D,         E,         F,         G
    case 0:       leds[0]=1; leds[1]=1; leds[2]=1; leds[3]=1; leds[4]=1; leds[5]=1; leds[6]=0; break;
    case 1:       leds[0]=0; leds[1]=1; leds[2]=1; leds[3]=0; leds[4]=0; leds[5]=0; leds[6]=0; break;
    case 2:       leds[0]=1; leds[1]=1; leds[2]=0; leds[3]=1; leds[4]=1; leds[5]=0; leds[6]=1; break;
    case 3:       leds[0]=1; leds[1]=1; leds[2]=1; leds[3]=1; leds[4]=0; leds[5]=0; leds[6]=1; break;
    case 4:       leds[0]=0; leds[1]=1; leds[2]=1; leds[3]=0; leds[4]=0; leds[5]=1; leds[6]=1; break;
    case 5:       leds[0]=1; leds[1]=0; leds[2]=1; leds[3]=1; leds[4]=0; leds[5]=1; leds[6]=1; break;
    case 6:       leds[0]=1; leds[1]=0; leds[2]=1; leds[3]=1; leds[4]=1; leds[5]=1; leds[6]=1; break;
    case 7:       leds[0]=1; leds[1]=1; leds[2]=1; leds[3]=0; leds[4]=0; leds[5]=0; leds[6]=0; break;
    case 8:       leds[0]=1; leds[1]=1; leds[2]=1; leds[3]=1; leds[4]=1; leds[5]=1; leds[6]=1; break;
    case 9:       leds[0]=1; leds[1]=1; leds[2]=1; leds[3]=0; leds[4]=0; leds[5]=1; leds[6]=1; break;
  }

  // Turning ON all the needed pins so the panel displays the right number.
  for (int i=0;i<7;i++){
    digitalWrite(i+firstOutputPin, leds[i]==true? LOW:HIGH );
  }

}

void showDegrees(int degrees) {
  int led_panel_number = degrees % 10;
  int color_led = degrees / 10;

  showNumberInNTE3052(led_panel_number,2);
  switch (color_led) {
      case 1:
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        break;
      case 2:
        digitalWrite(9,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(11,LOW);
        break;
      case 3:
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,HIGH);
      break;
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        break;
  }

}

void loop() {

  //Termometer Sensor.
  const int sensorPin = A0;
  const float temperatureGoal_low = 22.5;
  const float temperatureGoal_high = 26.5;

  // put your main code here, to run repeatedly:
  const int max_temp_attempts = 10;
  float temp_array[max_temp_attempts];
  
  for(int i=0;i<max_temp_attempts;i++){
    int sensorVal = analogRead(sensorPin);
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);

    float voltage = (sensorVal/1024.0) * 5.0;
    float temp = (voltage - .5) * 100;
    temp_array[i] = temp;
    Serial.print(" --- Temperature: ");
    Serial.println(temp);
    delay(2000);
  }

  float temperature = 0;
  for(int i=0;i<max_temp_attempts;i++) {
    temperature = temperature + temp_array[i];
  }
  
  temperature = temperature / max_temp_attempts;
  Serial.println(" -----------");
  Serial.print("Average Temperature: ");
  Serial.println(temperature);
  Serial.println(" -----------");
  

  if(temperature < temperatureGoal_low){
    isON = true;
  }else if (temperature > temperatureGoal_high){
    isON = false;
  }

  if(isON == true){
    digitalWrite(12,HIGH);
  } else {
    digitalWrite(12,LOW);   
  }

  showDegrees(temperature);
  delay(2000);
}