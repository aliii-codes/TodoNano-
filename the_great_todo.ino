// Typical Arduino nano

// 13 SCL
// 11 SDA 
// 5 RES
// 7 DC
// 6 CS


#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

const int TFT_RES = 5;
const int TFT_DC = 7;
const int TFT_CS = 6;

const int touchSensor = 12;

int screenMode = 0;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RES);



void setup() {
  // put your setup code here, to run once:
  pinMode(touchSensor, INPUT);

  Serial.begin(9600);
  tft.initR(INITR_GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  mainMenu();

  tft.drawRect(15, 45, 70, 20, ST77XX_WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
  // tft.print("TODO");
  int touch_state = digitalRead(touchSensor);

  if (touch_state == 1) {
    // Serial.println("WORKS");
    mainMenu();
    tft.drawRect(25, 65, 60, 20, ST77XX_WHITE);
  } else {
    Serial.println("Nothing ");
  }
  
}


void mainMenu() {
  tft.setTextColor(ST77XX_BLUE);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setCursor(25,20);


  
  tft.print("THE GREAT TODO");
  // tft.println("Yoo Ali broo !");
  // tft.fillRect(50, 50, 50, 50, ST77XX_BLUE);
  // tft.fillRoundRect(50, 60, 50, 60, 5, ST77XX_BLUE);

  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(5, 30);
  tft.print("----------------------");

  tft.setCursor(20, 50);
  tft.print("WATCH TODO");

  tft.setCursor(20, 80);
  tft.print("ADD TODO");

  tft.setCursor(20, 110);
  tft.print("DELETE TODO");
}
