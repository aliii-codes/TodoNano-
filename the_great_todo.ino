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


const int upsensor = 12;
const int selector = 4;
const int downbtn = 10;


int screenMode = 0;

String defaultTODOS[] = {
  "Study Physics",
  "Learn RNN",
  "Learn Transformers",
  "Learn Attention"
};

int numTodos = sizeof(defaultTODOS) / sizeof(defaultTODOS[0]);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RES);



void setup() {
  // put your setup code here, to run once:
  pinMode(upsensor, INPUT);
  pinMode(selector, INPUT);
  pinMode(downbtn, INPUT_PULLUP);

  Serial.begin(9600);
  tft.initR(INITR_GREENTAB);
  mainMenu();
  gotoWATCHTODO();

  // Serial.println(numTodos);

}

void loop() {
  // put your main code here, to run repeatedly:
  int upsensor_state = digitalRead(upsensor);
  int selector_state = digitalRead(selector);

  if (upsensor_state == 1) {   // if touched
    screenMode += 1;  // increment screenMode
    if (screenMode > 2) {  // if screenMode is too big 
      screenMode = 0;  // reset to 0
    }
    mainMenu();
    // gotoADDTODO();

    // screenMode = 0;

    if (screenMode == 0) {
      gotoWATCHTODO();
    }
    if (screenMode == 1) {
      gotoADDTODO();
    }
    if (screenMode == 2) {
      gotoDELETETODO();
    }
    
  }
  
  if (screenMode == 0 && selector_state == 1) {
    watchTodos();
  }
}


void mainMenu() {
  tft.fillScreen(ST77XX_BLACK);
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

void gotoADDTODO() {
  tft.drawRect(15, 75, 60, 20, ST77XX_WHITE);
}

void gotoWATCHTODO() {
  tft.drawRect(15, 45, 70, 20, ST77XX_WHITE);
}

void gotoDELETETODO() {
  tft.drawRect(15, 105, 80, 20, ST77XX_WHITE);
}

void watchTodos() {
  tft.fillScreen(ST77XX_BLACK);
  
  tft.setTextSize(1);

  
  
  tft.setTextColor(ST77XX_WHITE);

  for (int i = 0; i < numTodos; i++) {
    tft.setCursor(10, 20 + (i * 20));
    tft.print(i + 1);
    tft.print(": ");
    tft.print(defaultTODOS[i]);
  }
} 
