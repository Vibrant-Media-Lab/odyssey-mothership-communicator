
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(A1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(A2, HIGH);
  delay(1000);                       // wait for a second
  digitalWrite(A1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(A2, LOW);
  delay(1000);                       // wait for a second
}


// one at a time at random for between 3 and 6 seconds randomly 
// dont select one that was just lit 

