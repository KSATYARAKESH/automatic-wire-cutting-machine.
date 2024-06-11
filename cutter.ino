#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define ok 8
 #define up 9
  #define down 10
 int count = 0;
 int PBdelay = 200;
int state = 0;
int stateA = 0;
int push =0;
int qty =0;
int len = 0;
int countA = 0;
int countB = 0;
int i = 0;
#define feedstepPin 4
#define feeddirPin 3

#define cutstepPin 6
#define cutdirPin 5
float feedsteppermm = 105;
float cutstep = 3200;


void setup()
{
  pinMode (ok,INPUT_PULLUP);
   pinMode (up,INPUT_PULLUP);
   pinMode (down,INPUT_PULLUP);
    pinMode (feedstepPin,OUTPUT);
   pinMode (feeddirPin,OUTPUT);
   pinMode (cutstepPin,OUTPUT);
    pinMode (cutdirPin,OUTPUT);


   
   
   Serial.begin (9600);
	lcd.begin();
	lcd.backlight();

 lcd.clear();
 
}

void loop()

{  
	 
if (!digitalRead(ok)&& state ==0){
  if (push >=3){
  push = 0;
  }
  else{
  push+=1;
  
  }
  delay(PBdelay);
  Serial.println(push);
  lcd.clear();
}

switch (push){
    case 0:
      homescreen();
      break;
    case 1:
    
       setlength();
       break;
    case 2:
      setqty();
      break;
    case 3:
      confirm();
      break;
    case 4:
    finish();
      break;
  }

if (!digitalRead(up)&& stateA ==2){
  countA+=1;
  delay(PBdelay);
   len = countA;
}
if (!digitalRead(down)&& stateA ==2){
  countA-=1;
  delay(PBdelay);
   len = countA;
}


if (!digitalRead(up)&& stateA ==3){
  countB+=1;
  delay(PBdelay);
   qty = countB;
}
if (!digitalRead(down)&& stateA ==3){
  countB-=1;
  delay(PBdelay);
   qty = countB;
}

if (!digitalRead(ok)&& stateA==4){
   lcd.clear();
  push =4;
  int steptotake = len * feedsteppermm *10;
  for (i = 0; i<qty; i++){
 Cutting();
    digitalWrite(feeddirPin,HIGH);
    for (int x = 0; x < steptotake; x++){
      digitalWrite(feedstepPin ,HIGH);
      delayMicroseconds(100); 
      digitalWrite(feedstepPin,LOW);
      delayMicroseconds(100);
    }

    digitalWrite(cutdirPin,HIGH);
for (int y = 0; y < cutstep; y++){
      digitalWrite(cutstepPin ,HIGH);
      delayMicroseconds(100); 
     digitalWrite(cutstepPin,LOW);
      delayMicroseconds(100);
    }

/* digitalWrite(cutdirPin,LOW);
for (int y = 0; y < cutstep; y++){
      digitalWrite(cutstepPin ,HIGH);
      delayMicroseconds(250); 
      digitalWrite(cutstepPin,LOW);
      delayMicroseconds(250);
    }
  */  
 

    
  }



  
}

if (!digitalRead(ok)&& stateA==5){
lcd.clear();
push = 0;
len=0;
qty=0;
countA=0;
countB=0;
delay(PBdelay);
}

   
}
void homescreen(){
 lcd.setCursor(0, 0);
  lcd.print("WIRE CUTTER");
  lcd.setCursor(11, 1);
  lcd.print("NEXT>");
  stateA = 1;

}

void setlength(){
 lcd.setCursor(0, 0);
  lcd.print("SET LENGTH");
  lcd.setCursor(0, 1);
  lcd.print(len);
  lcd.setCursor(4, 1);
  lcd.print("CM");
  lcd.setCursor(11, 1);
  lcd.print("NEXT>");
stateA = 2;

}

void setqty(){
 lcd.setCursor(0, 0);
  lcd.print("SET QUANTITY");
  lcd.setCursor(0, 1);
  lcd.print(qty);
if (qty<2){
lcd.setCursor(4, 1);
  lcd.print("NO.");
}
else{
lcd.setCursor(4, 1);
  lcd.print("NOs.");
}

  
  lcd.setCursor(11, 1);
  lcd.print("NEXT>");
stateA = 3;

}

void confirm(){
 lcd.setCursor(0, 0);
  lcd.print("LENGTH = ");
  lcd.setCursor(9, 0);
  lcd.print(len);
   lcd.setCursor(11, 0);
  lcd.print("CM");
  lcd.setCursor(0, 1);
  lcd.print("QTY = ");
   lcd.setCursor(6, 1);
  lcd.print(qty);
  lcd.setCursor(11, 1);
  lcd.print("READY");
stateA = 4;
}

void Cutting(){
      lcd.setCursor(0, 0);
  lcd.print("CUTTING ");
  lcd.setCursor(8, 0);
  int k = qty-i;
  if (k==9){
    lcd.clear();
  }
  lcd.print(k);
   lcd.setCursor(11, 0);
  lcd.print("OF " +(String)qty);


}


void finish(){
      

 lcd.setCursor(0, 0);
  lcd.print("FINISH....          ");
lcd.setCursor(10, 1);
  lcd.print("HOME>");
  stateA = 5;
}


