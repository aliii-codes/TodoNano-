#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>

const int TFT_RES = 5;
const int TFT_DC = 7;
const int TFT_CS = 6;

const int upsensor = 12;
const int selector = 4;
const int downbtn = 10;

int screenMode = 0;

const int MAX_TODOS = 20;
String todos[MAX_TODOS];
int numTodos = 0;

char chars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%";
int currentCharIndex = 0;
String currentTodo = "";

bool inADDTODO = false;
bool inDELETETODO = false;
int deleteIndex = 0;

long selectorPressStart = 0;
bool selectorHeld = false;

long downbtnPressStart = 0;
bool downbtnHeld = false;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RES);

void saveTodosToEEPROM() {
  int addr = 0;
  EEPROM.write(addr++, numTodos);
  for (int i = 0; i < numTodos; i++) {
    for (int j = 0; j < todos[i].length(); j++) {
      EEPROM.write(addr++, todos[i][j]);
    }
    EEPROM.write(addr++, '\0');
  }
}

void loadTodosFromEEPROM() {
  int addr = 0;
  int n = EEPROM.read(addr++);
  if (n < 0 || n > MAX_TODOS) return;
  numTodos = n;
  for (int i = 0; i < numTodos; i++) {
    todos[i] = "";
    char c;
    while ((c = EEPROM.read(addr++)) != '\0') {
      todos[i] += c;
    }
  }
}

void setup() {
  pinMode(upsensor, INPUT);
  pinMode(selector, INPUT);
  pinMode(downbtn, INPUT_PULLUP);
  Serial.begin(9600);
  tft.initR(INITR_GREENTAB);
  loadTodosFromEEPROM();
  if (numTodos == 0) {
    todos[0] = "Study Physics";
    todos[1] = "Learn RNN";
    todos[2] = "Learn Transformers";
    todos[3] = "Learn Attention";
    numTodos = 4;
    saveTodosToEEPROM();
  }
  mainMenu();
  gotoWATCHTODO();
}

void loop() {
  int upsensor_state = digitalRead(upsensor);
  int selector_state = digitalRead(selector);
  int downbtn_state = digitalRead(downbtn);

  if (!inADDTODO && !inDELETETODO) {
    if (upsensor_state == 1) {
      screenMode++;
      if (screenMode > 2) screenMode = 0;
      mainMenu();
      if (screenMode == 0) { gotoWATCHTODO(); delay(200); }
      if (screenMode == 1) { gotoADDTODO();   delay(200); }
      if (screenMode == 2) { gotoDELETETODO(); delay(200); }
    }
    if (downbtn_state == 0) {
      screenMode--;
      delay(200);
      if (screenMode < 0) screenMode = 2;
      mainMenu();
      if (screenMode == 0) { gotoWATCHTODO(); }
      if (screenMode == 1) { gotoADDTODO(); }
      if (screenMode == 2) { gotoDELETETODO(); }
    }
    if (screenMode == 0 && selector_state == 1) { watchTodos(); delay(200); }
    if (screenMode == 1 && selector_state == 1) {
      inADDTODO = true;
      currentTodo = "";
      currentCharIndex = 0;
      addTODO();
      delay(400);
    }
    if (screenMode == 2 && selector_state == 1) {
      inDELETETODO = true;
      deleteIndex = 0;
      deleteTODOScreen();
      delay(400);
    }
  }

  if (inADDTODO) {
    if (upsensor_state == 1) {
      currentCharIndex++;
      delay(200);
      if (currentCharIndex > sizeof(chars) - 2) currentCharIndex = 0;
      tft.fillRect(38, 100, 20, 10, ST77XX_BLACK);
      tft.setCursor(38, 100);
      tft.print(chars[currentCharIndex]);
    }

    if (downbtn_state == 0 && !downbtnHeld) {
      downbtnPressStart = millis();
      downbtnHeld = true;
    }
    if (downbtn_state == 1 && downbtnHeld) {
      long dur = millis() - downbtnPressStart;
      downbtnHeld = false;
      if (dur > 800) {
        if (currentTodo.length() > 0) {
          currentTodo.remove(currentTodo.length() - 1);
          tft.fillRect(15, 55, 100, 18, ST77XX_BLACK);
          tft.setCursor(17, 60);
          tft.print(currentTodo);
        }
      } else {
        currentCharIndex--;
        if (currentCharIndex < 0) currentCharIndex = sizeof(chars) - 2;
        tft.fillRect(38, 100, 20, 10, ST77XX_BLACK);
        tft.setCursor(38, 100);
        tft.print(chars[currentCharIndex]);
      }
    }

    if (selector_state == 1 && !selectorHeld) {
      selectorPressStart = millis();
      selectorHeld = true;
    }
    if (selector_state == 0 && selectorHeld) {
      long dur = millis() - selectorPressStart;
      selectorHeld = false;
      if (dur > 800) {
        if (numTodos < MAX_TODOS && currentTodo.length() > 0) {
          todos[numTodos] = currentTodo;
          numTodos++;
          saveTodosToEEPROM();
        }
        inADDTODO = false;
        currentTodo = "";
        currentCharIndex = 0;
        screenMode = 0;
        mainMenu();
        gotoWATCHTODO();
        delay(300);
      } else {
        currentTodo += chars[currentCharIndex];
        tft.fillRect(15, 55, 100, 18, ST77XX_BLACK);
        tft.setCursor(17, 60);
        tft.print(currentTodo);
      }
    }
  }

  if (inDELETETODO) {
    if (upsensor_state == 1) {
      deleteIndex--;
      if (deleteIndex < 0) deleteIndex = numTodos - 1;
      deleteTODOScreen();
      delay(200);
    }

    if (downbtn_state == 0 && !downbtnHeld) {
      downbtnPressStart = millis();
      downbtnHeld = true;
    }
    if (downbtn_state == 1 && downbtnHeld) {
      long dur = millis() - downbtnPressStart;
      downbtnHeld = false;
      if (dur > 800) {
        inDELETETODO = false;
        screenMode = 2;
        mainMenu();
        gotoDELETETODO();
        delay(300);
      } else {
        deleteIndex++;
        if (deleteIndex >= numTodos) deleteIndex = 0;
        deleteTODOScreen();
      }
    }

    if (selector_state == 1 && !selectorHeld) {
      selectorPressStart = millis();
      selectorHeld = true;
    }
    if (selector_state == 0 && selectorHeld) {
      long dur = millis() - selectorPressStart;
      selectorHeld = false;
      if (dur > 800) {  // Long press - exit delete mode
        inDELETETODO = false;
        screenMode = 2;
        mainMenu();
        gotoDELETETODO();
        delay(300);
      } else {  // Short press - delete the selected todo
        for (int i = deleteIndex; i < numTodos - 1; i++) {
          todos[i] = todos[i + 1];
        }
        numTodos--;
        saveTodosToEEPROM();
        if (deleteIndex >= numTodos && deleteIndex > 0) deleteIndex--;
        if (numTodos == 0) {
          inDELETETODO = false;
          screenMode = 2;
          mainMenu();
          gotoDELETETODO();
        } else {
          deleteTODOScreen();
        }
        delay(300);
      }
    }
  }
}

void mainMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(25, 20);
  tft.print("THE GREAT TODO");
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

void gotoWATCHTODO()  { tft.drawRect(15, 45,  70, 20, ST77XX_WHITE); }
void gotoADDTODO()    { tft.drawRect(15, 75,  60, 20, ST77XX_WHITE); }
void gotoDELETETODO() { tft.drawRect(15, 105, 80, 20, ST77XX_WHITE); }

void watchTodos() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  for (int i = 0; i < numTodos; i++) {
    tft.setCursor(10, 20 + (i * 15));
    tft.print(i + 1);
    tft.print(": ");
    tft.print(todos[i]);
  }
}

void addTODO() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(1);
  tft.setCursor(40, 25);
  tft.print("ADD TODO");
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(1, 35);
  tft.print("-------------------------");
  tft.drawRect(15, 55, 100, 20, ST77XX_WHITE);
  tft.setCursor(2, 100);
  tft.print("Char: ");
  tft.setCursor(38, 100);
  tft.print(chars[currentCharIndex]);
  tft.setCursor(2, 110);
  tft.print("hold sel:save dn:bksp");
}

void deleteTODOScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(30, 5);
  tft.print("DELETE TODO");
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(5, 15);
  tft.print("----------------------");
  for (int i = 0; i < numTodos; i++) {
    tft.setTextColor(i == deleteIndex ? ST77XX_RED : ST77XX_WHITE);
    tft.setCursor(10, 25 + (i * 15));
    tft.print(i + 1);
    tft.print(": ");
    tft.print(todos[i]);
  }
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(5, 120);
  tft.print("sel:del hold dn:back");
}