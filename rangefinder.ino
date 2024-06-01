// Lib for nokia 5110 display
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// Sensor pinout
uint8_t PIN_SENSOR = 12;  // Digital sensor value D12

// Ultrasonic rangefinder pinout
uint8_t PIN_RANGEFINDER_TRIGGER = 9;  // Digital output to measure rangefinder D9
uint8_t PIN_RANGEFINDER_ECHO = 8;  // Pulse input to get a value from rangefinder D8

// Display pinout
uint8_t PIN_RST = 3;  // Reset D3
uint8_t PIN_CE = 4;  // Chip Select D4
uint8_t PIN_DC = 5;  // Data/Command select D5
uint8_t PIN_DIN = 6;  // Data in D6
uint8_t PIN_CLC = 7;  // Clock D7


uint8_t touch_signal;

uint32_t duration;
uint32_t distance;


Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_CLC, PIN_DIN, PIN_DC, PIN_CE, PIN_RST);


void setup() {
  // Display initialization
  display.begin();
  display.setContrast(50);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.clearDisplay();

  // Pin initialization
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_RANGEFINDER_TRIGGER, OUTPUT);
  pinMode(PIN_RANGEFINDER_ECHO, INPUT);

  // Reset rangefinder
  digitalWrite(PIN_RANGEFINDER_TRIGGER, LOW);
  delayMicroseconds(2);

}


void loop() {

  touch_signal = digitalRead(PIN_SENSOR);  // Read value from touch sensor

  if (touch_signal > 0) {  // If touched
    display.clearDisplay();

    // Give signal to rangefinder trigger
    digitalWrite(PIN_RANGEFINDER_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_RANGEFINDER_TRIGGER, LOW);

    duration = pulseIn(PIN_RANGEFINDER_ECHO, HIGH);  // Read value from ultrasonic rangefinder
    
    if (duration >= 38000) {
      display.println("Out range");
    }
    else {
      distance = duration / 58;
      display.print(distance);
      display.println(" sm");
    }

    display.display();
    delay(500);  // For restore display 
  }
}
