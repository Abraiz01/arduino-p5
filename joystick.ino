// joystick ports
int dirUp = 7;
int dirDown = 6;
int dirRight = 5;
int dirLeft = 4;

// lives lights ports
int lives3Pin = 11;
int lives2Pin = 10;
int lives1Pin = 9;
int lives = 3;
int prevlives = 3;
int vibrate = 0;

// int lives, prevlives = 3;
int motorPin = 3; //motor transistor is connected to pin 10
int motorState = LOW;  // motorState used to set the Motor Vibration
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1000;  // interval at which to blink (milliseconds)


void setup()
{
  pinMode( dirDown , INPUT);
  pinMode( dirUp , INPUT);
  pinMode( dirLeft , INPUT);
  pinMode( dirRight, INPUT);

  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);

  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); // on/blink while waiting for serial data
    Serial.println("0"); // send a starting message
    delay(300);            // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop(){
  
  while (Serial.available()) {
      prevlives = lives;
      lives = Serial.parseInt();
      if(prevlives != lives){
        vibrate=1;
      }

      if (Serial.read() == '\n') {
        if (digitalRead( dirDown ) == LOW ){
          Serial.println(3);
        }
        else if (digitalRead( dirUp ) == LOW ){
          Serial.println(4);
        }
        else if (digitalRead( dirLeft ) == LOW ){
          Serial.println(2);
        }
        else if (digitalRead( dirRight ) == LOW ){
          Serial.println(1);
          // digitalWrite(motorPin, HIGH); //vibrate
        }
        else {
          Serial.println(0);
      }

      if(vibrate == 1){
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
          // save the last time you blinked the LED
          previousMillis = currentMillis;

          // if the LED is off turn it on and vice-versa:
          if (motorState == LOW) {
            motorState = HIGH;
          } else {
            motorState = LOW;
            vibrate=0;
          }

          // set the LED with the ledState of the variable:
          digitalWrite(motorPin, motorState);
        }
        // else{
        //   vibrate=0;
        // }
      }

      if (lives == 3) {
        digitalWrite(lives1Pin, HIGH);
        digitalWrite(lives2Pin, HIGH);
        digitalWrite(lives3Pin, HIGH);
      }
      else if (lives == 2) {
        digitalWrite(lives1Pin, HIGH);
        digitalWrite(lives2Pin, HIGH);
        digitalWrite(lives3Pin, LOW);
        // digitalWrite(motorPin, HIGH); //vibrate
      }
      else if (lives == 1) {
        digitalWrite(lives1Pin, HIGH);
        digitalWrite(lives2Pin, LOW);
        digitalWrite(lives3Pin, LOW);
      }
      else if (lives == 0) {
        digitalWrite(lives1Pin, LOW);
        digitalWrite(lives2Pin, LOW);
        digitalWrite(lives3Pin, LOW);
        // digitalWrite(motorPin, HIGH); //vibrate
      }

    }
    } 

}