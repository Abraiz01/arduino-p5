// joystick ports
int dirUp = 7;
int dirDown = 6;
int dirRight = 5;
int dirLeft = 4;

// lives lights ports
int lives3Pin = 11;
int lives2Pin = 10;
int lives1Pin = 9;

// haptic feedback
int hapticPin = 8;

int lives, prevlives = 3;

void setup () {
// put your setup code here, to run once:
  pinMode( dirDown , INPUT);
  pinMode( dirUp , INPUT);
  pinMode( dirLeft , INPUT);
  pinMode( dirRight, INPUT);

  pinMode( lives3Pin , INPUT);
  pinMode( lives2Pin , INPUT);
  pinMode( lives1Pin, INPUT);

  pinMode( hapticPin, INPUT);

  Serial.begin(9600);

  // start the handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); // on/blink while waiting for serial data
    Serial.println("0"); // send a starting message
    delay(300);            // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}
void loop() {
// put your main code here, to run repeatedly:

// wait for data from p5 before doing something
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH); // led on while receiving data

    lives = Serial.parseInt();

    if (Serial.read() == '\n') {
      if (digitalRead( dirDown ) == LOW ){
        Serial.println(1);
      }
      else if (digitalRead( dirUp ) == LOW ){
        Serial.println(2);
      }
      else if (digitalRead( dirLeft ) == LOW ){
        Serial.println(3);
      }
      else if (digitalRead( dirRight ) == LOW ){
        Serial.println(4);
      }
      else {
        Serial.println(0);
      }
      delay(100);

      if (lives == 3) {
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
      }
      else if (lives == 2) {
        if(prevlives - lives == 1) {
          digitalWrite(hapticPin, HIGH); //vibrate
          delay(1000);  // delay one second
          digitalWrite(hapticPin, LOW);  //stop vibrating
          delay(1000); //wait 50 seconds.
        }
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);
      }
      else if (lives == 1) {
        if(prevlives - lives == 1) {
          digitalWrite(hapticPin, HIGH); //vibrate
          delay(1000);  // delay one second
          digitalWrite(hapticPin, LOW);  //stop vibrating
          delay(1000); //wait 50 seconds.
        }
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
      }
      else if (lives == 0) {
        if(prevlives - lives == 1) {
          digitalWrite(hapticPin, HIGH); //vibrate
          delay(1000);  // delay one second
          digitalWrite(hapticPin, LOW);  //stop vibrating
          delay(1000); //wait 50 seconds.
        }
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
      }

    }

    prevlives = lives;

  }
  digitalWrite(LED_BUILTIN, LOW);

}