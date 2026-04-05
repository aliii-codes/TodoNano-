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

char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%";
int currentCharIndex = 0;
String currentTodo = "";

bool inADDTODO = false;

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
  int downbtn_state = digitalRead(downbtn); // just remember that on == 0 and off == 1 


  if (inADDTODO == false) {
    if (upsensor_state == 1) {  // if touched
      screenMode += 1;          // increment screenMode
      if (screenMode > 2) {     // if screenMode is too big
        screenMode = 0;         // reset to 0
      }
      mainMenu();
      // gotoADDTODO();

      // screenMode = 0;

    
      if (screenMode == 0) {
        gotoWATCHTODO();
        delay(200);
      }
      if (screenMode == 1) {
        gotoADDTODO();
        delay(200);
      }
      if (screenMode == 2) {
        gotoDELETETODO();
        delay(200);
      }
    }
    if (downbtn_state == 0) {
      screenMode -= 1;
      if (screenMode < 0) {
        screenMode = 2;
      }
      mainMenu();

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
  }

  if (inADDTODO == true) {
    if (upsensor_state == 1) {
      currentCharIndex++;
      delay(200);
      if (currentCharIndex > sizeof(chars) -2) {
        currentCharIndex = 0;
      } 
      tft.fillRect(38, 100, 20, 10, ST77XX_BLACK);
      tft.setCursor(38, 100);
      tft.print(chars[currentCharIndex]);
    }
    if (downbtn_state == 0) {
      currentCharIndex--;
      delay(200);
      if (currentCharIndex < 0) {
        currentCharIndex = sizeof(chars) -2;
      }
      tft.fillRect(38, 100, 20, 10, ST77XX_BLACK);
      tft.setCursor(38, 100);
      tft.print(chars[currentCharIndex]);
    }
    if (selector_state == 1) {
      currentTodo += chars[currentCharIndex];
      tft.fillRect(15, 55, 90, 10, ST77XX_BLACK);
      tft.setCursor(17, 57);
      tft.print(currentTodo); 
      delay(300);
    }
  }

  if (screenMode == 0 && selector_state == 1) {
    watchTodos();
  }
  if (screenMode == 1 && selector_state == 1) {
    inADDTODO = true;
    addTODO();
  }  
}


void mainMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_CYAN);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setCursor(25, 20);


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

void addTODO() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setCursor(40,25);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(1);
  tft.print("ADD TODO");

  tft.setCursor(1, 35);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("-------------------------");

  tft.drawRect(15, 55, 100, 20, ST77XX_WHITE);  

  tft.setCursor(2, 100);
  tft.print("Char: ");

  tft.setCursor(38, 100);
  tft.print(chars[currentCharIndex]);
  
  tft.setCursor(2, 110);
  tft.print("sel : add char");
}
