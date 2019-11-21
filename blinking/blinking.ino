/*
    Test script to make three LEDs blink at random for
    between 3 and 6 seconds and does not light same one twice

    @Author: Andrew Saba
*/

#include "pitches.h"

// pitches.h has pitch macros with the note 
// and its frequency values 

// pins to use 
const int LED_1 = A1;
const int LED_2 = A2;
const int LED_3 = A3;
const int SPEAKER_PIN = 8;

// notes to play for LED_1, etc. 
const int TONE_1 = NOTE_A4;
const int TONE_2 = NOTE_G5;
const int TONE_3 = NOTE_C7;

// how long to hold note
// i.e. quarter note = 1000 / 4, eighth note = 1000/8, etc.
// so do 1.3 * 1000/4
const int NOTE_DURATION = 325;

// delay between loop updates
const int LOOP_DELAY = 100; // in ms, so 10hz

// delay between blinking hearbeat LED, which
// acts as a visual cue that arduino is running
// code and is operational
const int HEART_DELAY = 1000; // in ms

// selects random time t in seconds 
// between min and max, to nearest second
const int MIN_TIME =  3;
const int MAX_TIME = 5;

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
        // light up all LEDs when something bad happens
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("SOMETHING HAPPENED");
        delay(100000);
    }
}

void loop() {
    long curr_led = random(3); // inclusive, so must be 3
    unsigned long on_time = millis() + 1000 * random(MIN_TIME, MAX_TIME+1); // inclusive, so add 1

    int heart_state = HIGH;
    unsigned long heart_time = millis() + HEART_DELAY;
    digitalWrite(LED_BUILTIN, heart_state);

    unsigned long tone_end = millis() + NOTE_DURATION; 

    while (true) {
        // switch heartbeat LED
        if (millis() >= heart_time) {
            heart_state = (heart_state == HIGH) ? LOW : HIGH;
            digitalWrite(LED_BUILTIN, heart_state);
            heart_time = millis() + HEART_DELAY;
        }

        // stop playling tone
        if (millis() >= tone_end) { 
            noTone(SPEAKER_PIN);
        }

        // reset LED and tone states 
        if (millis() >= on_time) {
            // time to reset
            long new_led = random(2); // inclusive, so must be 3
            on_time = millis() + 1000 * random(MIN_TIME, MAX_TIME+1); // inclusive, so add 1
            tone_end = millis() + NOTE_DURATION;

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

            // light up LEDs
            switch (curr_led){
                case 0:
                    digitalWrite(LED_1, HIGH);
                    digitalWrite(LED_2, LOW);
                    digitalWrite(LED_3, LOW);
                    tone(SPEAKER_PIN, TONE_1);
                    break;
                case 1:
                    digitalWrite(LED_1, LOW);
                    digitalWrite(LED_2, HIGH);
                    digitalWrite(LED_3, LOW);
                    tone(SPEAKER_PIN, TONE_2);
                    break;
                case 2:
                    digitalWrite(LED_1, LOW);
                    digitalWrite(LED_2, LOW);
                    digitalWrite(LED_3, HIGH);
                    tone(SPEAKER_PIN, TONE_3);
                    break;
                default:
                    // display error
                    display_error();
            }
        }
        delay(LOOP_DELAY);
    }
}
