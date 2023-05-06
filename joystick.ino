int dirUp = 7;
int dirDown = 6;
int dirRight =5;
int dirLeft = 4;
void setup () {
// put your setup code here, to run once:
  pinMode( dirDown , INPUT);
  pinMode( dirUp , INPUT);
  pinMode( dirLeft , INPUT);
  pinMode( dirRight, INPUT);
  Serial.begin(9600);

  // start the handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); // on/blink while waiting for serial data
    Serial.println("STOP"); // send a starting message
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

    String msgRcvd = Serial.readString();
    if (Serial.read() == '\n') {
      if (digitalRead( dirDown ) == LOW ){
      Serial.println("DOWN");
    }
    else if (digitalRead( dirUp ) == LOW ){
      Serial.println( "UP");
    }
    else if (digitalRead( dirLeft ) == LOW ){
      Serial.println( "LEFT");
    }
    else if (digitalRead( dirRight ) == LOW ){
      Serial.println( "RIGHT");
    }
    else {
      Serial.println("STOP");
    }
    delay(100);

    }
  }
  digitalWrite(LED_BUILTIN, LOW);

}