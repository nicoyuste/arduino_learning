void setup() {
  
  // Asking for control of the seven pins  
  // that I am going to need to display the numbers.

  pinMode(2,OUTPUT); // A
  pinMode(3,OUTPUT); // B
  pinMode(4,OUTPUT); // C
  pinMode(5,OUTPUT); // D
  pinMode(6,OUTPUT); // E
  pinMode(7,OUTPUT); // F
  pinMode(8,OUTPUT); // G

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

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<10;i++){ 
    showNumberInNTE3052(i,2);
    delay(1000);
  }
}