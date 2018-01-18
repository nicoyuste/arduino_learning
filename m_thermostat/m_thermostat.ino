
#include <LiquidCrystal.h>

int isON = false;

const float temperatureGoal_low = 17.0;
const float temperatureGoal_high = 23.0;

const int max_temp_attempts = 10;
float temp_array[max_temp_attempts];
float avg_temperature = 0;
int attempt_number = 0;
bool needsToUpdate = false;

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  
  // Debuggi
  Serial.begin(9600);
  lcd.display();
  lcd.begin(16,2);

  // Asking for control of the seven pins  
  // that I am going to need to display the numbers.
  pinMode(8,OUTPUT); // Relay
  pinMode(9,OUTPUT); // Contrast for Arduino screen
  analogWrite(9,120);


}

void loop() {

  //Termometer Sensor.
  const int sensorPin = A0;
  
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal/1024.0) * 5.0;
  float temp = (voltage - .5) * 100;
  temp_array[attempt_number] = temp;
  attempt_number = attempt_number + 1;

  if (attempt_number == max_temp_attempts) {
    attempt_number = 0;
    needsToUpdate = true;
    avg_temperature = 0.0;
    for(int i=0;i<max_temp_attempts;i++) {
      avg_temperature = avg_temperature + temp_array[i];
    }
    avg_temperature = avg_temperature / max_temp_attempts;
  }

  String tempString = String(((int)(temp * 100 )) / 100.0);
  String avg_tempString = String(((int)(avg_temperature * 100 ))/ 100.0);

  Serial.println(String("Sensor Value: " + String(sensorVal) + " --- Temperature: " + tempString));
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String("Temp: " + tempString));
  lcd.setCursor(0,1);
  lcd.print(String("Avg Temp: " + avg_tempString));

  if (needsToUpdate) {
    needsToUpdate = false;
    Serial.println(" -----------");
    Serial.print("Average Temperature: ");
    Serial.println(avg_temperature);

    if(avg_temperature < temperatureGoal_low){
      Serial.println("We should turn ON the fireplace.");
      digitalWrite(8,HIGH); // This turns ON the relay so the fireplace is ON.
    }else if (avg_temperature > temperatureGoal_high){
      Serial.println("We should turn OFF the fireplace.");
      digitalWrite(8,LOW); // This turns OFF the relay so the fireplace is PFF.
    }
    Serial.println(" -----------");
  }
  delay(2000);
}