
// constants won't change. Used here to set a pin number :
const int starttime = 100;  // the amount of time that each delay is going to
                            // have on the startup script.
const int NUM_OUTPUTS = 14;

long randNumber;
long NumberCounter;  // This is a counter to count how may times the program has
                     // looped before it triggers a function.
// Variables will change :
int ledState[NUM_OUTPUTS] = {LOW};


// Set what pins are enabled. (Low = Off, High = On)

int ledEnabled[NUM_OUTPUTS] = {LOW};

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change :
const long interval = 500;  // interval at which to blink (milliseconds)

void setup() {
  ledEnabled[8] = HIGH;
  ledEnabled[9] = HIGH;
  ledEnabled[10] = HIGH;
  // Get a random seed from analog 0
  randomSeed(analogRead(0));
  // set the digital pin as output:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // This is the light test section, we will run though all of the different
  // functions here.

  // Chase both on and off.
  Chase(starttime, HIGH);
  Chase(starttime, LOW);

  Blink(10, starttime);  // Blink 10 times.
}

void loop() {
  

  // Used for timed events.
  if (NumberCounter >
      1000)  // Resets the number counter if it is larger then 1000.
  {
    NumberCounter = 0;
  } else if ((NumberCounter == 100) || (NumberCounter == 300) ||
             (NumberCounter == 500) || (NumberCounter == 700) ||
             (NumberCounter == 900)) {
    LightsOff();
    Chase(starttime, HIGH);
    Chase(starttime, LOW);
  } else if ((NumberCounter == 200) || (NumberCounter == 400) ||
             (NumberCounter == 600) || (NumberCounter == 800) ||
             (NumberCounter == 1000)) {
    LightsOff();
    Blink(5, 1000);
  }

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    NumberCounter++;  // Add one to the number counter.
    // set the LED with the ledState of the variable:
    RandomLight();
  }
}

void RandomLight() {
  int randstatus = 0;
  do {
    randNumber = random(0, NUM_OUTPUTS);  // Random number to generate what pin should be
                                 // on/off. Add 1 to your final number. Eg. 13
                                 // pins would be a total of 14.
    for(int i=0; i < NUM_OUTPUTS; i++){
      if ((randNumber == i) && (ledEnabled[i] == HIGH)) {
        randstatus = 1;
        if (ledState[i] == LOW) {
          ledState[i] = HIGH; 
        } else {
          ledState[i] = LOW;
        }
        digitalWrite(i, ledState[i]);
      }
    }
  } while (randstatus == 0);  // Keep looping until we have a random number that
                              // will turn an output on or off.
}

void LightsOn()  // Turns all pins on.
{
  int i;
  for(i = 0; i < NUM_OUTPUTS; i++) {
    if (ledEnabled[i] == HIGH) {
      digitalWrite(i, HIGH);
    }
  }
}

void LightsOff()  // Turns all pins off
{
  int i;
  for(i = 0; i < NUM_OUTPUTS; i++) {
    if (ledEnabled[i] == HIGH) {
      digitalWrite(i, LOW);
    }
  }
}

void Blink(int times, int delays)  // Times = how many times the outputs should
                                   // blink, delays = how long between the
                                   // on/off
{
  int i;
  for (i = 0; i < times; i++) {
    LightsOn();
    delay(delays);
    LightsOff();
    delay(delays);
  }
}

void Chase(int delays, int type)  // Delays = How much of a delay between each
                                  // pin, type = High/Low for On/Off
{
  int i;
  for(i = 0; i < NUM_OUTPUTS; i++) {
    if (ledEnabled[i] == HIGH) {
      digitalWrite(i, type);
      delay(delays);
    }
  }
}
