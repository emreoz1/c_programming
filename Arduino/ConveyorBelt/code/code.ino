//Library, variables, connections start
#include <Servo.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_SPI.h> 
#include "font.h"

#define MODEL ILI9341
#define CS   A5    
#define CD   A3
#define RST  A4
#define LED  A0   
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define S0 4 
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8

Servo servo1 , servo2 , servo3;

unsigned long oldTime=0 , nowTime , oldTime1=0 , nowTime1 , oldTime2=0 , nowTime2 , oldTime3=0 , nowTime3 , oldTime4=0 , nowTime4 , oldTime5=0 , nowTime5; 

int frequency =0 , mycolor=0 , toplam =0 , red=0 , green =0 , blue=0;

char totalExit[4];
char redExit[4];
char greenExit[4];
char blueExit[4];

LCDWIKI_SPI mylcd(MODEL,CS,CD,RST,LED);
//Library, variables, connections end

// CODES RELATED TO NE555
int ne555 = 7;  

unsigned long
duration1; 
HIGH length of the pulse

unsigned long
duration2; 
LOW length of the pulse

float dc; 
// CODES RELATED TO NE555

void setup() {
  //Pin definition start
  pinMode(ne555, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  //Pin definition end

  //LCD screen definition start
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Text_Mode(0);
  mylcd.Set_Rotation(1);
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(3);
  mylcd.Print_String("Total Product =", 0, 0);
  mylcd.Print_String("Red =", 0, 50);
  mylcd.Print_String("Green =", 0, 100);
  mylcd.Print_String("Blue =", 0, 150);
  show_pic();
  //LCD screen definition end
 
  Serial.begin(9600);
}

void loop() {
  //SERVO RESET START
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  //SERVO RESET END

  // CODES RELATED TO NE555
  duration1 = pulseIn(ne555, HIGH);  //Reads a pulse on ne555

  Serial.print("Duty cycle: ");

  Serial.print(dc);  //print the length of the pulse on the serial
monitor

  Serial.print(" %");

  Serial.println();  
  // CODES RELATED TO NE555

  //TOTAL PRODUCT COUNTING START
  String totalValue = String(total);
  totalValue.toCharArray(totalExit, 4);

  String redValue = String(red);
  redValue.toCharArray(redExit, 4);

  String greenValue = String(green);
  greenValue.toCharArray(greenExit, 4);

  String blueValue = String(blue);
  blueValue.toCharArray(blueExit, 4);
  
  mylcd.Set_Text_colour(WHITE);
  mylcd.Print_String(totalExit, 260, 0);
  mylcd.Print_String(redExit, 170, 50); 
  mylcd.Print_String(greenExit, 150, 100);
  mylcd.Print_String(blueExit, 130, 150);
  //TOTAL PRODUCT COUNTING START
  
  mycolor = detectColor();

  //MİLİS(DELAY) CODES START
  unsigned long nowTime = millis();
  unsigned long nowTime1 = millis();
  unsigned long nowTime2 = millis();
  unsigned long nowTime3 = millis();
  unsigned long nowTime4 = millis();
  unsigned long nowTime5 = millis();
  //MİLİS(DELAY) CODES END

  // SERVO CODES BY COLOR START
  switch (mycolor) {
    case 1:
     if (nowTime - oldTime >= 5000) {
      servo1.write(180);
      oldTime = millis();
     }
     if (nowTime1 - oldTime1 >= 1000) {
      total += 1;
      red += 1; 
      oldTime1 = millis();
     }
    break;

    case 2:
     if (nowTime2 - oldTime2 >= 5000) {
      servo2.write(180);
      oldTime2 = millis();
     }
     if (nowTime3 - oldTime3 >= 1000) {
      total += 1;
      green += 1; 
      oldTime3 = millis();
     }
    break;

    case 3:
    if (nowTime4 - oldTime4 >= 5000) {
      servo3.write(180);
      oldTime4 = millis();
     }
     if (nowTime5 - oldTime5 >= 1000) {
      total += 1;
      blue += 1; 
      oldTime5 = millis();
     }
    break;
    
    case 0:
    break;
  }
  
  mycolor=0;
  // SERVO CODES BY COLOR END
}

//COLOR SENSOR CODES START
int detectColor() {

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);
  Serial.print("   ");

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");

  if(R<900 & R>400 & G<1800 & G>1200){
    mycolor = 1; // Red
    Serial.print("Detected Color is = ");
    Serial.println("RED");
  }
  if(R<1500 & R>900 & G<1199 & G>600){
    mycolor = 2; // Green
      Serial.print("Detected Color is = ");
    Serial.println("GREEN");
  }
  if (G<1000 & G>700 & B<150 &B>100){
    mycolor = 3; // Blue
     Serial.print("Detected Color is = ");
    Serial.println("BLUE");
  }
  return mycolor;  
}
//COLOR SENSOR CODES END

//LCD SCREEN IMAGE DISPLAY CODES START
void show_pic(void)
{
    int i;
    mylcd.Set_Addr_Window(mylcd.Get_Display_Width()-40-40, 50, mylcd.Get_Display_Width()-40-1, 100); 
    mylcd.Push_Any_Color(penguin_pic, 1600, 1, 1);
 }
//LCD SCREEN IMAGE DISPLAY CODES END