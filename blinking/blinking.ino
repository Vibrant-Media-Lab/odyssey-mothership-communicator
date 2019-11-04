/*
    Test script to make three LEDs blink at random for
    between 3 and 6 seconds and does not light same one twice

    @Author: Andrew Saba
*/

const int LED_1 = A1;
const int LED_2 = A2;
const int LED_3 = A3;

const int LOOP_DELAY = 100; // in ms, so 50hz

void setup() {
    // initialize LED pins as outputs
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);

    pinMode(LED_BUILTIN, OUTPUT);

    // seed the random number generator
    randomSeed(analogRead(0));

    Serial.begin(9600);
}

void display_error(){
    while (true) {
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, HIGH);
        Serial.println("SOMETHING HAPPENED");
        delay(100000);
    }
}

void loop() {
    long curr_led = random(3); // inclusive, so must be 3
    unsigned long on_time = millis() + 1000 * random(3, 7); // between 3 and 7 seconds, in ms

    while (true) {
        if (millis() >= on_time) {
            // time to reset
            long new_led = random(2); // inclusive, so must be 3
            on_time = millis() + 1000 * random(3, 7); // between 3 and 7 seconds

            switch (curr_led){
                case 0:
                    curr_led = new_led + 1;
                    break;
                case 1:
                    curr_led = (new_led == 1) ? 2 : 0;
                    break;
                case 2:
                    curr_led = new_led;
                    break;
                default:
                    // display error
                    display_error();
            }

            switch (curr_led){
                case 0:
                    digitalWrite(LED_1, HIGH);
                    digitalWrite(LED_2, LOW);
                    digitalWrite(LED_3, LOW);
                    break;
                case 1:
                    digitalWrite(LED_1, LOW);
                    digitalWrite(LED_2, HIGH);
                    digitalWrite(LED_3, LOW);
                    break;
                case 2:
                    digitalWrite(LED_1, LOW);
                    digitalWrite(LED_2, LOW);
                    digitalWrite(LED_3, HIGH);
                    break;
                default:
                    // display error
                    display_error();
            }
        }
        delay(LOOP_DELAY);
    }
}
