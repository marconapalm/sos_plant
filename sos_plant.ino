/* sos_plant
 *
 * This little sketch (in Arduino this is the name for "program") helps our little
 * plant to survive. In fact, if it is very thirsty, the sketch will advise us thanks
 * to the SOS light code. The serial monitor will tell us what the plant thinks. 
 * 
 * Developed by Marco Rapaccini for an exam at the University of Perugia (Italy)
 *
 * Created on 18/12/2013
 * Updated on 02/06/2014
 *
 * This code is in the public domain.
 *
 */

static int SENSOR_PIN = A0;           // sensor pin number
static int LED_PIN = 13;              // LED pin number


static long data_speed=9600;          // speed of serial data's transmission. Usually it is set at 9600 bits per second
static long interval_1=10000;         // intervals for the millis timer
static long interval_2=15000;          

long previousMillis_1 = 0;            // variables for the millis timer
long previousMillis_2 = 0;            

static char message[]="Feed me, please!";  // messages to print on the monitor
static char message2[]="Thank you so much! I was very thirsty!";
static char message3[]="The recorded value is:";

int reading;                          // analog sensor reading
int led_state;                        // current led state
int threshold = 800;                  // threshold for activating the LED

void setup()
{
    pinMode(LED_PIN, OUTPUT);         // set the digital pin as output
    Serial.begin(data_speed);         // start sending and receiving serial data
}

void ledSOS(){                        // this is the light SOS message (with the Morse code)
  int i = 0;
  for (i=0; i<3; i++){                // letter S, made by 3 dots
    digitalWrite(LED_PIN, HIGH);      // turns on the LED
    delay(100);                       // wait
    digitalWrite(LED_PIN, LOW);       // turns off the LED
    delay(100);
  }
  delay(500);
  i = 0;
  for (i=0; i<3; i++){                // letter O, made by 3 dashes
    digitalWrite(LED_PIN, HIGH); 
    delay(900); 
    digitalWrite(LED_PIN, LOW); 
    delay(250);
  }
  delay(500);
  i = 0;
  for (i=0; i<3; i++){                // letter S, made by 3 dots
    digitalWrite(LED_PIN, HIGH); 
    delay(100); 
    digitalWrite(LED_PIN, LOW); 
    delay(100);
  }
} 

void loop()
{
  reading = analogRead(SENSOR_PIN);   // get the sensor reading 
  led_state = digitalRead(LED_PIN);   // get the current LED state
  
  if (reading<=threshold){            // if the recorded value is below 800
    unsigned long currentMillis_1 = millis();
    
    if (currentMillis_1-previousMillis_1>interval_1){ // if a few seconds have passed
      previousMillis_1=currentMillis_1;
      ledSOS();                         // launch the SOS light message
      Serial.println(message);          // print the messages to the serial monitor
      Serial.println(message3);
      Serial.println(reading);
    }
    
  }
  else if(reading>threshold){
    unsigned long currentMillis_2=millis();    // if the plant has enough water
    
    if (currentMillis_2-previousMillis_2>interval_2){ // if a few seconds have passed
      previousMillis_2=currentMillis_2;
      Serial.println(message2);         // print the messages to the serial monitor
      Serial.println(message3);
      Serial.println(reading);
    }
    
  }
} // end loop
