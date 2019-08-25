#include <Adafruit_NeoPixel.h>
#define leds 9
#define numleds 9
#define button 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(leds, numleds, NEO_GRB + NEO_KHZ800);

int starttime;
int playtime;
int winsegment = 80;

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin as an input and enable the internal pull-up resistor
  pinMode(button, INPUT_PULLUP);
  pixels.begin();
  starttime = millis();

}

void loop() {
  //set pixels dark
  for (int i = 0; i < numleds; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.



  while (millis() < 3000) {//wait for button push
    if (!digitalRead(button)) { //if they press the button, they lose
      for (int i = 0; i < numleds; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // set all pixels red
      }
      pixels.show(); // update the pixels
      while (1) { //loop forever
      }
    }
    delay(10);
  }


  //GO!
  starttime = millis();  //get current time
  for (int i = 0; i < numleds; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));  //set pixels white
  }
  pixels.show();
  while (digitalRead(button)) {//wait for button push
  }

  //do the next stuff after they've pushed the button
  playtime = millis() - starttime;   //get their reaction time
  Serial.println(playtime);   //output the time to the serial monitor
  for (int i = 0; i < numleds; i++) {
    if (playtime < (i + 1)*winsegment)
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // set it green
    else
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // set it red
  }
  pixels.show(); // show the pixels we've set
  while (1) { //loop forever
    delay(50);
  }

}
