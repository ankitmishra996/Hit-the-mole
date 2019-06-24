const int yellowLED = 12;
const int redLED = 11;
const int pinkLED = 10;
const int greenLED = 9;

const int yellowButton = 7;
const int redButton = 6;
const int pinkButton = 5;
const int greenButton = 4;

int waitTime = 3000; 
int counter = 1;

void setup() {
  
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(pinkLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(pinkButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  
  Serial.begin(9600);      // serial port = 9600 bps
  randomSeed(analogRead(0));   //shows random numbers are truly random
}

void loop() {
  int newColor = randomLED();
  ledOn(newColor);

  //check to see if hit or not
  if (hit(newColor)) {
    Serial.print("No. of mole hit:");
    Serial.println(counter);
    ledOff(newColor);
    delay(1000); 
    waitTime = 0.9*waitTime;
    counter++;
  } else {
    Serial.println("Miss the mole! Game over.");
    miss();
    waitTime = 3000;               // 1 sec = 1000 milisecond
    counter = 1;
  } 
}

boolean hit(int newColor) {
  int i = 0;
  int chkButton;
  boolean hit = false;
  boolean buttonPressed = false;

  //start the counter and wait for botton to be pressed..or timeout
  Serial.print("Wait Time: ");
  Serial.println(waitTime);
  while ((i < waitTime) and (!buttonPressed)) {
    
    chkButton = button(); //0 if nothing is pressed
    if (newColor == chkButton) { //correct button is pressed
      hit = true;
      buttonPressed = true;
    } else if (chkButton > 0) { //incorrect button is pressed
      hit = false;
      buttonPressed = true;
    } 
    i++;
    delay(1); //make each loop about 1ms
  }
  return hit;
}

 // 7 = yellow,6 = red, 5 = pink, 4=green
 //LOW = button is pressed
int button() {
    int buttonPressed = 0;
    if (digitalRead(yellowButton) == LOW) {
      ledOn(yellowLED);
      buttonPressed = yellowLED;
    }
    if (digitalRead(redButton) == LOW) {
      ledOn(redLED);
      buttonPressed = redLED;
    } 
    if (digitalRead(pinkButton) == LOW) {
      ledOn(pinkLED);
      buttonPressed = pinkLED;
    }  
    if (digitalRead(greenButton) == LOW) {
      ledOn(greenLED);
      buttonPressed = greenLED;
    }
    return buttonPressed;
}

void miss() {
  
   for (int i=0; i <= 2; i++){
     ledOn(yellowLED);
     ledOn(redLED);
     ledOn(pinkLED);
     ledOn(greenLED);
     delay(200);
     ledOff(yellowLED);
     ledOff(redLED);
     ledOff(pinkLED);
     ledOff(greenLED);
     delay(200);
   }
  delay(2000);
}  

//function shows to randomly pick a new color of LED
int randomLED () {
  int randomLED;
  randomLED = random(9,13);
  return randomLED;

}
void ledOn(int colorON) {

  if (colorON == yellowLED) {
    digitalWrite(yellowLED, HIGH);
  }
  else if (colorON == redLED) {
    digitalWrite(redLED, HIGH);
  }
  else if (colorON == pinkLED) {
    digitalWrite(pinkLED, HIGH);
  } 
  else if (colorON == greenLED) {
    digitalWrite(greenLED, HIGH);
  }
}

void ledOff(int colorOFF) {

  if (colorOFF == yellowLED) {
    digitalWrite(yellowLED, LOW);
  }
  else if (colorOFF == redLED) {
    digitalWrite(redLED, LOW);
  }
  else if (colorOFF == pinkLED) {
    digitalWrite(pinkLED, LOW);
  }
  else if (colorOFF == greenLED) {
    digitalWrite(greenLED, LOW);
  }
}
