#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// stat이 1이면 메뉴등 출력
#define OK_SW 4
#define NEXT_SW 5
#define CHECK_SW 6
#define RETURN_SW 7
#define POWER_LED 8
#define SENSOR_CHECK_LED 9
#define PIEZO 10

#define ONLINE 1
#define OFFLINE 2

#define TEMP 1
#define PULSE 2

int mode, stat, sensor;

LiquidCrystal_I2C lcd(0x3F, 16, 2); //0x20 or 0x27 or 0x3F

void Pin_init();
void Lcd_start();
void Menu_blink();
void Print_menu();
void Select_menu_print();

void Chk_sensor_online();
void Chk_sensor_offline();

void setup() {
  // put your setup code here, to run once:
  Pin_init();
  Lcd_start();
  mode = 1;
  stat = 1;
}
//lcd.setCursor(0,0);            
//lcd.print("    "); 
//lcd.noBlink()
//lcd.blink()
void loop() {
  // put your main code here, to run repeatedly:
  if(stat) Print_menu(); 
  
  switch (mode) {
    case ONLINE: 
      if(stat) Menu_blink();
      
      if(digitalRead(NEXT_SW) == LOW)
      {
        stat = 1;
        mode = OFFLINE;
   
        while(digitalRead(NEXT_SW));
         delay(30);
      }

      if(digitalRead(OK_SW) == LOW)
      {
        lcd.setCursor(0, 0);
        lcd.print("Wait....");
        //if bluetooth on, print("complet");
        stat = 1;
        
        Chk_sensor_online();

        while(digitalRead(NEXT_SW));
        delay(30);
        
      }
      break;
    
    case OFFLINE:
      if(stat) Menu_blink();
      
      if(digitalRead(NEXT_SW) == LOW)
      {
        stat = 1;
        mode = ONLINE;
        
        while(digitalRead(NEXT_SW));
         delay(30);
      }
      
      if(digitalRead(OK_SW) == LOW)
      {
        stat = 1;
       
        Chk_sensor_offline();
        
        while(digitalRead(NEXT_SW));
        delay(30);
      }
      break;
  }


}

void Chk_sensor_online()
{
  while(1)
  {
    if(stat) Select_menu_print();
    
    if(digitalRead(NEXT_SW == LOW))
    {
      stat = 1;
      if(sensor = TEMP)
        sensor = PULSE;
      else if(sensor = PULSE)
        sensor = TEMP;
    }

    if(digitalRead(OK_SW == LOW))
    {
      //if(sensor == TEMP)
      
      //else if(sensor == PULSE)

      while(digitalRead(OK_SW == LOW));
      delay(30);
    }
   
  
    if(digitalRead(RETURN_SW == LOW))
    {
      while(digitalRead(RETURN_SW ==LOW));
      delay(30);
      break;
    }
  }
}

void Chk_sensor_offline()
{
  while(1)
  {
    if(stat) Select_menu_print();
    
    if(digitalRead(NEXT_SW == LOW))
    {
      stat = 1;
    }

    if(digitalRead(OK_SW == LOW))
    {
      if(sensor == TEMP)
        lcd.print("d");
      else if(sensor == PULSE)
        lcd.print("d");
      while(digitalRead(OK_SW == LOW));
      delay(30);
      
    }
  
    if(digitalRead(RETURN_SW == LOW))
    {
      while(digitalRead(RETURN_SW ==LOW));
      delay(30);
      
      break;
    }
  }
}

void Lcd_start()
{
  lcd.begin();
  lcd.backlight();

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Welcome!");

  lcd.setCursor(0,1);
  lcd.print("I`m HomeDoctor");
  delay(2000);
  //piezo melody
}

void Pin_init() //Pull-up
{
  int i;
  
  for(i=4;i<8;i++) //Switch input
     pinMode(i, INPUT); 

  for(i=8;i<11;i++) //led output
    pinMode(i, OUTPUT);  

  digitalWrite(POWER_LED, HIGH);
}

void Menu_blink()
{
  if(mode == ONLINE)
  {
    stat = 0;
    lcd.setCursor(0,1);
    lcd.blink();
  }
  else if(mode == OFFLINE)
  {
    stat = 0;
    lcd.setCursor(7, 1);
    lcd.blink();
  }
}

void Print_menu()
{
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("MENU");
  lcd.setCursor(0, 1);
  
  lcd.print("Online/Offline");  
}

void Select_menu_print()
{
  stat = 0;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select");
  
  lcd.setCursor(0, 1);
  lcd.print("Temp/Pulse");
}
