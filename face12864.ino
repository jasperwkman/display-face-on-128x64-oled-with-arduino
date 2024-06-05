#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

const int buttonPin = 8;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
int totalFaces = 8;
int currentFace = 1;

// eyeState 1=open, 2=close, 3=stop
int eyeState = 1;
int eyeWait = random(5, 20);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 9
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16


/*
  A4  > LCD|SDA
  A5  > LCD|SCL
  5V  > SW IN, LCD UCC, SCD 5V
  GND > LCD GND, SW OUT, RESISTOR, SD GND
  D4  > SW IN
  D10 > SD SS/CS
  D11 > MOSI
  D12 > MISO
  D13 > SCK/CLK
  }
*/

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  setupSerial();
  setupLCD();
}

void setupSerial(void) {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void setupLCD(void) {
  Serial.println("Setup LCD");
  //setup lcd
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.clearDisplay();
  display.setRotation(2); // rotate 180 degrees
  Serial.println("Setup LCD Complete");
}

void detectButton() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    eyeState = 3;
      currentFace++;
      if (currentFace > totalFaces ) {
        currentFace = 1;
      }
    digitalWrite(LED_BUILTIN, HIGH);   // set the LED on
    delay(100);              // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // set the LED off
  }
}

void loop(void) {
  //Serial.println("loop");
  delay(1000);
  display.clearDisplay();
  detectButton();
  if (eyeState == 1 || eyeState == 2) {
    eyeWait--;
    if (eyeWait < 1) {
      eyeState = 2;
      eyeWait = random(5, 20);
    }
    drawMe();
    eyeState = 1;
  } else {
    draw();
  }
  display.display();
}

void drawHeader() {
  drawHeader(String(currentFace) + "/" + String(totalFaces) + "  DANBOARD v1.0"); 
}

void drawHeader(String s) {
  display.setTextSize(1); 
  display.setTextColor(WHITE);  
  display.setCursor(5, 54); 
  display.println(s); 
}


void draw() {
  switch (currentFace) {
    case 1:
      draw1();
      break;
    case 2:
      draw2();
      break;
    case 3:
      draw3();
      break;
    case 4:
      draw4();
      break;
    case 5:
      draw5();
      break;
    case 6:
      draw6();
      break;
    case 7:
      draw7();
      break;
    case 8:
      draw8();
      break;
    default:
      drawMe();
      break;
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void drawMe() {

  drawHeader();

  display.setTextSize(3);
  display.setCursor(30, 12);
  display.println("( _ )");

  display.setTextSize(2);
  display.setCursor(55, 10);
  if (eyeState == 1) {
    display.println("o o");
  } else if (eyeState == 2) {
    //display.println(String(char(241))+" "+String(char(242)));
    display.println("- -");
  }

}
void draw1() {
  drawHeader();
  display.setTextSize(3);
  display.setCursor(40, 12);
  display.println(String(char(241)) + "  " + String(char(242)));
  display.setTextSize(2);
  display.setCursor(70, 30);
  display.println("w");
}

void draw2() {
  drawHeader();
  display.setTextSize(3);
  display.setCursor(40, 12);
  display.println("@  @");
  display.setTextSize(2);
  display.setCursor(70, 30);
  display.println("_");
}

void draw3() {
  drawHeader();
  display.setTextSize(2);
  display.setCursor(15, 12);
  display.println(String(char(14)) + "   " + String(char(14)));
  display.setCursor(34, 16);
  display.println(String(char(14)) + "   " + String(char(14)));
}

void draw4() {
  drawHeader();
  display.setTextSize(3);
  display.setCursor(30, 12);
  display.println(String(char(3)) + "  " + String(char(3)));
  display.setTextSize(2);
  display.setCursor(60, 35);
  display.println(String(char(31)));
}

void draw5() {
  drawHeader();

  display.setTextSize(3);
  display.setCursor(00, 12);
  display.println(String(char(170)) + "( _ )" + String(char(169)));

  display.setTextSize(2);
  display.setCursor(45, 10);

  display.println("= =");

}

void draw6() {
  drawHeader("#whateverittakes");
  display.setTextSize(2);
  display.setCursor(1, 10);

  display.println("I am ironman");

}

void draw7() {
  drawHeader();
  display.setTextSize(2);
  display.setCursor(1, 10);

  display.println("#whateverittakes");

}


void draw8() {
  drawHeader();
  display.drawPixel(9, 14, WHITE);
  display.drawPixel(9, 22, WHITE);
  display.drawPixel(9, 23, WHITE);
  display.drawPixel(9, 24, WHITE);
  display.drawPixel(9, 25, WHITE);
  display.drawPixel(10, 14, WHITE);
  display.drawPixel(10, 21, WHITE);
  display.drawPixel(10, 22, WHITE);
  display.drawPixel(10, 23, WHITE);
  display.drawPixel(10, 24, WHITE);
  display.drawPixel(10, 25, WHITE);
  display.drawPixel(10, 26, WHITE);
  display.drawPixel(11, 14, WHITE);
  display.drawPixel(11, 20, WHITE);
  display.drawPixel(11, 21, WHITE);
  display.drawPixel(11, 26, WHITE);
  display.drawPixel(11, 27, WHITE);
  display.drawPixel(12, 14, WHITE);
  display.drawPixel(12, 20, WHITE);
  display.drawPixel(12, 26, WHITE);
  display.drawPixel(12, 27, WHITE);
  display.drawPixel(13, 14, WHITE);
  display.drawPixel(13, 20, WHITE);
  display.drawPixel(13, 27, WHITE);
  display.drawPixel(14, 13, WHITE);
  display.drawPixel(14, 14, WHITE);
  display.drawPixel(14, 19, WHITE);
  display.drawPixel(14, 20, WHITE);
  display.drawPixel(14, 27, WHITE);
  display.drawPixel(15, 13, WHITE);
  display.drawPixel(15, 14, WHITE);
  display.drawPixel(15, 19, WHITE);
  display.drawPixel(15, 20, WHITE);
  display.drawPixel(15, 27, WHITE);
  display.drawPixel(16, 9, WHITE);
  display.drawPixel(16, 10, WHITE);
  display.drawPixel(16, 13, WHITE);
  display.drawPixel(16, 14, WHITE);
  display.drawPixel(16, 19, WHITE);
  display.drawPixel(16, 20, WHITE);
  display.drawPixel(16, 27, WHITE);
  display.drawPixel(17, 9, WHITE);
  display.drawPixel(17, 10, WHITE);
  display.drawPixel(17, 11, WHITE);
  display.drawPixel(17, 12, WHITE);
  display.drawPixel(17, 13, WHITE);
  display.drawPixel(17, 14, WHITE);
  display.drawPixel(17, 19, WHITE);
  display.drawPixel(17, 20, WHITE);
  display.drawPixel(17, 27, WHITE);
  display.drawPixel(18, 11, WHITE);
  display.drawPixel(18, 12, WHITE);
  display.drawPixel(18, 13, WHITE);
  display.drawPixel(18, 14, WHITE);
  display.drawPixel(18, 19, WHITE);
  display.drawPixel(18, 20, WHITE);
  display.drawPixel(18, 27, WHITE);
  display.drawPixel(19, 13, WHITE);
  display.drawPixel(19, 14, WHITE);
  display.drawPixel(19, 15, WHITE);
  display.drawPixel(19, 16, WHITE);
  display.drawPixel(19, 19, WHITE);
  display.drawPixel(19, 20, WHITE);
  display.drawPixel(19, 27, WHITE);
  display.drawPixel(20, 13, WHITE);
  display.drawPixel(20, 16, WHITE);
  display.drawPixel(20, 17, WHITE);
  display.drawPixel(20, 18, WHITE);
  display.drawPixel(20, 20, WHITE);
  display.drawPixel(20, 26, WHITE);
  display.drawPixel(20, 27, WHITE);
  display.drawPixel(21, 12, WHITE);
  display.drawPixel(21, 13, WHITE);
  display.drawPixel(21, 18, WHITE);
  display.drawPixel(21, 19, WHITE);
  display.drawPixel(21, 20, WHITE);
  display.drawPixel(21, 21, WHITE);
  display.drawPixel(21, 26, WHITE);
  display.drawPixel(21, 27, WHITE);
  display.drawPixel(22, 12, WHITE);
  display.drawPixel(22, 13, WHITE);
  display.drawPixel(22, 19, WHITE);
  display.drawPixel(22, 20, WHITE);
  display.drawPixel(22, 21, WHITE);
  display.drawPixel(22, 26, WHITE);
  display.drawPixel(23, 12, WHITE);
  display.drawPixel(23, 13, WHITE);
  display.drawPixel(23, 21, WHITE);
  display.drawPixel(24, 12, WHITE);
  display.drawPixel(32, 24, WHITE);
  display.drawPixel(32, 25, WHITE);
  display.drawPixel(32, 26, WHITE);
  display.drawPixel(33, 23, WHITE);
  display.drawPixel(33, 24, WHITE);
  display.drawPixel(33, 25, WHITE);
  display.drawPixel(33, 26, WHITE);
  display.drawPixel(33, 27, WHITE);
  display.drawPixel(34, 22, WHITE);
  display.drawPixel(34, 23, WHITE);
  display.drawPixel(34, 26, WHITE);
  display.drawPixel(34, 27, WHITE);
  display.drawPixel(35, 22, WHITE);
  display.drawPixel(35, 27, WHITE);
  display.drawPixel(35, 28, WHITE);
  display.drawPixel(36, 22, WHITE);
  display.drawPixel(36, 27, WHITE);
  display.drawPixel(36, 28, WHITE);
  display.drawPixel(37, 21, WHITE);
  display.drawPixel(37, 22, WHITE);
  display.drawPixel(37, 27, WHITE);
  display.drawPixel(37, 28, WHITE);
  display.drawPixel(38, 21, WHITE);
  display.drawPixel(38, 22, WHITE);
  display.drawPixel(38, 27, WHITE);
  display.drawPixel(38, 28, WHITE);
  display.drawPixel(39, 22, WHITE);
  display.drawPixel(39, 27, WHITE);
  display.drawPixel(39, 28, WHITE);
  display.drawPixel(40, 9, WHITE);
  display.drawPixel(40, 10, WHITE);
  display.drawPixel(40, 11, WHITE);
  display.drawPixel(40, 12, WHITE);
  display.drawPixel(40, 13, WHITE);
  display.drawPixel(40, 14, WHITE);
  display.drawPixel(40, 15, WHITE);
  display.drawPixel(40, 16, WHITE);
  display.drawPixel(40, 17, WHITE);
  display.drawPixel(40, 18, WHITE);
  display.drawPixel(40, 19, WHITE);
  display.drawPixel(40, 20, WHITE);
  display.drawPixel(40, 21, WHITE);
  display.drawPixel(40, 22, WHITE);
  display.drawPixel(40, 23, WHITE);
  display.drawPixel(40, 24, WHITE);
  display.drawPixel(40, 25, WHITE);
  display.drawPixel(40, 26, WHITE);
  display.drawPixel(40, 27, WHITE);
  display.drawPixel(41, 9, WHITE);
  display.drawPixel(41, 10, WHITE);
  display.drawPixel(41, 11, WHITE);
  display.drawPixel(41, 12, WHITE);
  display.drawPixel(41, 13, WHITE);
  display.drawPixel(41, 14, WHITE);
  display.drawPixel(41, 15, WHITE);
  display.drawPixel(41, 16, WHITE);
  display.drawPixel(41, 17, WHITE);
  display.drawPixel(41, 18, WHITE);
  display.drawPixel(41, 19, WHITE);
  display.drawPixel(41, 20, WHITE);
  display.drawPixel(41, 21, WHITE);
  display.drawPixel(41, 22, WHITE);
  display.drawPixel(41, 23, WHITE);
  display.drawPixel(41, 24, WHITE);
  display.drawPixel(41, 25, WHITE);
  display.drawPixel(41, 26, WHITE);
  display.drawPixel(42, 14, WHITE);
  display.drawPixel(42, 15, WHITE);
  display.drawPixel(42, 22, WHITE);
  display.drawPixel(42, 23, WHITE);
  display.drawPixel(43, 14, WHITE);
  display.drawPixel(43, 15, WHITE);
  display.drawPixel(43, 23, WHITE);
  display.drawPixel(44, 14, WHITE);
  display.drawPixel(44, 15, WHITE);
  display.drawPixel(44, 23, WHITE);
  display.drawPixel(44, 24, WHITE);
  display.drawPixel(45, 14, WHITE);
  display.drawPixel(45, 15, WHITE);
  display.drawPixel(45, 24, WHITE);
  display.drawPixel(45, 25, WHITE);
  display.drawPixel(46, 14, WHITE);
  display.drawPixel(46, 24, WHITE);
  display.drawPixel(46, 25, WHITE);
  display.drawPixel(47, 14, WHITE);
  display.drawPixel(47, 25, WHITE);
  display.drawPixel(47, 26, WHITE);
  display.drawPixel(48, 13, WHITE);
  display.drawPixel(48, 14, WHITE);
  display.drawPixel(48, 26, WHITE);
  display.drawPixel(48, 27, WHITE);
  display.drawPixel(57, 16, WHITE);
  display.drawPixel(57, 17, WHITE);
  display.drawPixel(58, 16, WHITE);
  display.drawPixel(58, 17, WHITE);
  display.drawPixel(59, 16, WHITE);
  display.drawPixel(59, 17, WHITE);
  display.drawPixel(60, 9, WHITE);
  display.drawPixel(60, 10, WHITE);
  display.drawPixel(60, 16, WHITE);
  display.drawPixel(61, 9, WHITE);
  display.drawPixel(61, 10, WHITE);
  display.drawPixel(61, 16, WHITE);
  display.drawPixel(61, 27, WHITE);
  display.drawPixel(61, 28, WHITE);
  display.drawPixel(62, 10, WHITE);
  display.drawPixel(62, 16, WHITE);
  display.drawPixel(62, 27, WHITE);
  display.drawPixel(62, 28, WHITE);
  display.drawPixel(63, 10, WHITE);
  display.drawPixel(63, 11, WHITE);
  display.drawPixel(63, 15, WHITE);
  display.drawPixel(63, 16, WHITE);
  display.drawPixel(63, 27, WHITE);
  display.drawPixel(64, 10, WHITE);
  display.drawPixel(64, 11, WHITE);
  display.drawPixel(64, 15, WHITE);
  display.drawPixel(64, 16, WHITE);
  display.drawPixel(64, 26, WHITE);
  display.drawPixel(64, 27, WHITE);
  display.drawPixel(65, 10, WHITE);
  display.drawPixel(65, 11, WHITE);
  display.drawPixel(65, 15, WHITE);
  display.drawPixel(65, 16, WHITE);
  display.drawPixel(65, 26, WHITE);
  display.drawPixel(65, 27, WHITE);
  display.drawPixel(66, 10, WHITE);
  display.drawPixel(66, 11, WHITE);
  display.drawPixel(66, 15, WHITE);
  display.drawPixel(66, 16, WHITE);
  display.drawPixel(66, 26, WHITE);
  display.drawPixel(67, 10, WHITE);
  display.drawPixel(67, 11, WHITE);
  display.drawPixel(67, 15, WHITE);
  display.drawPixel(67, 16, WHITE);
  display.drawPixel(67, 25, WHITE);
  display.drawPixel(67, 26, WHITE);
  display.drawPixel(68, 11, WHITE);
  display.drawPixel(68, 15, WHITE);
  display.drawPixel(68, 16, WHITE);
  display.drawPixel(68, 24, WHITE);
  display.drawPixel(68, 25, WHITE);
  display.drawPixel(68, 26, WHITE);
  display.drawPixel(69, 11, WHITE);
  display.drawPixel(69, 16, WHITE);
  display.drawPixel(69, 17, WHITE);
  display.drawPixel(69, 23, WHITE);
  display.drawPixel(69, 24, WHITE);
  display.drawPixel(69, 25, WHITE);
  display.drawPixel(70, 16, WHITE);
  display.drawPixel(70, 17, WHITE);
  display.drawPixel(70, 18, WHITE);
  display.drawPixel(70, 22, WHITE);
  display.drawPixel(70, 23, WHITE);
  display.drawPixel(70, 24, WHITE);
  display.drawPixel(71, 17, WHITE);
  display.drawPixel(71, 18, WHITE);
  display.drawPixel(71, 19, WHITE);
  display.drawPixel(71, 20, WHITE);
  display.drawPixel(71, 21, WHITE);
  display.drawPixel(71, 22, WHITE);
  display.drawPixel(71, 23, WHITE);
  display.drawPixel(72, 19, WHITE);
  display.drawPixel(72, 20, WHITE);
  display.drawPixel(79, 14, WHITE);
  display.drawPixel(79, 24, WHITE);
  display.drawPixel(80, 13, WHITE);
  display.drawPixel(80, 14, WHITE);
  display.drawPixel(80, 22, WHITE);
  display.drawPixel(80, 23, WHITE);
  display.drawPixel(80, 24, WHITE);
  display.drawPixel(81, 13, WHITE);
  display.drawPixel(81, 14, WHITE);
  display.drawPixel(81, 20, WHITE);
  display.drawPixel(81, 21, WHITE);
  display.drawPixel(81, 22, WHITE);
  display.drawPixel(81, 23, WHITE);
  display.drawPixel(82, 13, WHITE);
  display.drawPixel(82, 14, WHITE);
  display.drawPixel(82, 18, WHITE);
  display.drawPixel(82, 19, WHITE);
  display.drawPixel(82, 20, WHITE);
  display.drawPixel(82, 21, WHITE);
  display.drawPixel(83, 13, WHITE);
  display.drawPixel(83, 14, WHITE);
  display.drawPixel(83, 15, WHITE);
  display.drawPixel(83, 16, WHITE);
  display.drawPixel(83, 17, WHITE);
  display.drawPixel(83, 18, WHITE);
  display.drawPixel(83, 19, WHITE);
  display.drawPixel(84, 11, WHITE);
  display.drawPixel(84, 12, WHITE);
  display.drawPixel(84, 13, WHITE);
  display.drawPixel(84, 14, WHITE);
  display.drawPixel(84, 15, WHITE);
  display.drawPixel(84, 16, WHITE);
  display.drawPixel(85, 9, WHITE);
  display.drawPixel(85, 10, WHITE);
  display.drawPixel(85, 11, WHITE);
  display.drawPixel(85, 12, WHITE);
  display.drawPixel(85, 13, WHITE);
  display.drawPixel(85, 23, WHITE);
  display.drawPixel(85, 24, WHITE);
  display.drawPixel(85, 25, WHITE);
  display.drawPixel(85, 26, WHITE);
  display.drawPixel(86, 9, WHITE);
  display.drawPixel(86, 13, WHITE);
  display.drawPixel(86, 22, WHITE);
  display.drawPixel(86, 23, WHITE);
  display.drawPixel(86, 24, WHITE);
  display.drawPixel(86, 26, WHITE);
  display.drawPixel(86, 27, WHITE);
  display.drawPixel(87, 13, WHITE);
  display.drawPixel(87, 22, WHITE);
  display.drawPixel(87, 23, WHITE);
  display.drawPixel(87, 27, WHITE);
  display.drawPixel(87, 28, WHITE);
  display.drawPixel(88, 13, WHITE);
  display.drawPixel(88, 22, WHITE);
  display.drawPixel(88, 27, WHITE);
  display.drawPixel(88, 28, WHITE);
  display.drawPixel(89, 12, WHITE);
  display.drawPixel(89, 13, WHITE);
  display.drawPixel(89, 22, WHITE);
  display.drawPixel(89, 27, WHITE);
  display.drawPixel(89, 28, WHITE);
  display.drawPixel(90, 22, WHITE);
  display.drawPixel(90, 27, WHITE);
  display.drawPixel(90, 28, WHITE);
  display.drawPixel(91, 22, WHITE);
  display.drawPixel(91, 27, WHITE);
  display.drawPixel(91, 28, WHITE);
  display.drawPixel(92, 12, WHITE);
  display.drawPixel(92, 13, WHITE);
  display.drawPixel(92, 16, WHITE);
  display.drawPixel(92, 17, WHITE);
  display.drawPixel(92, 18, WHITE);
  display.drawPixel(92, 19, WHITE);
  display.drawPixel(92, 20, WHITE);
  display.drawPixel(92, 21, WHITE);
  display.drawPixel(92, 22, WHITE);
  display.drawPixel(92, 23, WHITE);
  display.drawPixel(92, 24, WHITE);
  display.drawPixel(92, 25, WHITE);
  display.drawPixel(92, 26, WHITE);
  display.drawPixel(92, 27, WHITE);
  display.drawPixel(93, 12, WHITE);
  display.drawPixel(93, 13, WHITE);
  display.drawPixel(93, 17, WHITE);
  display.drawPixel(93, 18, WHITE);
  display.drawPixel(93, 19, WHITE);
  display.drawPixel(93, 20, WHITE);
  display.drawPixel(93, 21, WHITE);
  display.drawPixel(93, 22, WHITE);
  display.drawPixel(93, 23, WHITE);
  display.drawPixel(93, 24, WHITE);
  display.drawPixel(93, 25, WHITE);
  display.drawPixel(93, 26, WHITE);
  display.drawPixel(94, 13, WHITE);
  display.drawPixel(94, 23, WHITE);
  display.drawPixel(95, 13, WHITE);
  display.drawPixel(95, 14, WHITE);
  display.drawPixel(95, 23, WHITE);
  display.drawPixel(95, 24, WHITE);
  display.drawPixel(96, 14, WHITE);
  display.drawPixel(96, 15, WHITE);
  display.drawPixel(96, 24, WHITE);
  display.drawPixel(96, 25, WHITE);
  display.drawPixel(97, 14, WHITE);
  display.drawPixel(97, 15, WHITE);
  display.drawPixel(97, 24, WHITE);
  display.drawPixel(97, 25, WHITE);
  display.drawPixel(97, 26, WHITE);
  display.drawPixel(98, 15, WHITE);
  display.drawPixel(98, 25, WHITE);
  display.drawPixel(98, 26, WHITE);
  display.drawPixel(105, 21, WHITE);
  display.drawPixel(105, 22, WHITE);
  display.drawPixel(106, 14, WHITE);
  display.drawPixel(106, 15, WHITE);
  display.drawPixel(106, 16, WHITE);
  display.drawPixel(106, 17, WHITE);
  display.drawPixel(106, 18, WHITE);
  display.drawPixel(106, 19, WHITE);
  display.drawPixel(106, 20, WHITE);
  display.drawPixel(106, 21, WHITE);
  display.drawPixel(106, 22, WHITE);
  display.drawPixel(107, 13, WHITE);
  display.drawPixel(107, 14, WHITE);
  display.drawPixel(107, 15, WHITE);
  display.drawPixel(107, 16, WHITE);
  display.drawPixel(107, 17, WHITE);
  display.drawPixel(107, 20, WHITE);
  display.drawPixel(107, 21, WHITE);
  display.drawPixel(107, 26, WHITE);
  display.drawPixel(108, 20, WHITE);
  display.drawPixel(108, 26, WHITE);
  display.drawPixel(108, 27, WHITE);
  display.drawPixel(109, 9, WHITE);
  display.drawPixel(109, 10, WHITE);
  display.drawPixel(109, 19, WHITE);
  display.drawPixel(109, 20, WHITE);
  display.drawPixel(109, 26, WHITE);
  display.drawPixel(109, 27, WHITE);
  display.drawPixel(110, 10, WHITE);
  display.drawPixel(110, 19, WHITE);
  display.drawPixel(110, 26, WHITE);
  display.drawPixel(110, 27, WHITE);
  display.drawPixel(111, 10, WHITE);
  display.drawPixel(111, 11, WHITE);
  display.drawPixel(111, 18, WHITE);
  display.drawPixel(111, 19, WHITE);
  display.drawPixel(111, 27, WHITE);
  display.drawPixel(112, 10, WHITE);
  display.drawPixel(112, 11, WHITE);
  display.drawPixel(112, 18, WHITE);
  display.drawPixel(112, 19, WHITE);
  display.drawPixel(112, 27, WHITE);
  display.drawPixel(113, 11, WHITE);
  display.drawPixel(113, 12, WHITE);
  display.drawPixel(113, 18, WHITE);
  display.drawPixel(113, 19, WHITE);
  display.drawPixel(113, 27, WHITE);
  display.drawPixel(114, 11, WHITE);
  display.drawPixel(114, 12, WHITE);
  display.drawPixel(114, 18, WHITE);
  display.drawPixel(114, 27, WHITE);
  display.drawPixel(115, 11, WHITE);
  display.drawPixel(115, 12, WHITE);
  display.drawPixel(115, 18, WHITE);
  display.drawPixel(115, 19, WHITE);
  display.drawPixel(115, 26, WHITE);
  display.drawPixel(115, 27, WHITE);
  display.drawPixel(116, 12, WHITE);
  display.drawPixel(116, 18, WHITE);
  display.drawPixel(116, 19, WHITE);
  display.drawPixel(116, 26, WHITE);
  display.drawPixel(116, 27, WHITE);
  display.drawPixel(117, 18, WHITE);
  display.drawPixel(117, 19, WHITE);
  display.drawPixel(117, 26, WHITE);
  display.drawPixel(117, 27, WHITE);
  display.drawPixel(118, 19, WHITE);
  display.drawPixel(118, 20, WHITE);
  display.drawPixel(118, 25, WHITE);
  display.drawPixel(118, 26, WHITE);
  display.drawPixel(119, 19, WHITE);
  display.drawPixel(119, 20, WHITE);
  display.drawPixel(119, 21, WHITE);
  display.drawPixel(119, 22, WHITE);
  display.drawPixel(119, 23, WHITE);
  display.drawPixel(119, 24, WHITE);
  display.drawPixel(119, 25, WHITE);
  display.drawPixel(120, 20, WHITE);
  display.drawPixel(120, 21, WHITE);
  display.drawPixel(120, 22, WHITE);
  display.drawPixel(120, 23, WHITE);
  display.drawPixel(120, 24, WHITE);
}
