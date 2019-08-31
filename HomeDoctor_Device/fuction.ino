void Chk_sensor()
{
  
  Menu_select();
  
  while(1)
  {
    if(digitalRead(NEXT_SW) == LOW)
    {
      delay(100);
      select = !select;
      Menu_select();
      
      while(digitalRead(NEXT_SW) == LOW);
      delay(30);
    }

    if(digitalRead(OK_SW) == LOW)
    {  
      if(network)
        On_line_mode();
      else
        Off_line_mode();

      select = 1;
      Menu_select();
    
      while(digitalRead(OK_SW) == LOW);
      delay(30);    
    }
    
    if(digitalRead(RETURN_SW) == LOW)
    {
      network = 1;
      Menu_network();
  
      return;
    }
    
  }
}

int On_line_mode()
{
  back = 0;
  
   if(select) // Temperature mode
  {
    lcd.clear();
    lcd.home();
    lcd.print("Press chk btn");

    while(1)
    {
      if(digitalRead(CHECK_SW)==LOW)
      {
        String strTemp = String("");
        //strTemp = mlx.readObjectTempC();
        strTemp = 36.5;
        
        lcd.clear();
        lcd.home();
        lcd.print("Ok...");
        delay(3000);
        //부저
        lcd.clear();
        lcd.home();
        lcd.print("Temp: ");

        lcd.setCursor(6, 0);
        lcd.print(strTemp);
        lcd.setCursor(10, 0);
        lcd.print("`C");

        lcd.setCursor(0,1);
     
        if(strTemp.toInt()>= 36 && strTemp.toInt() <= 38)
          lcd.print("It`s Good!");
        else
          lcd.print("It`s bad...");
        delay(2500);

        btSerial.print(strTemp);
        lcd.clear();
        lcd.home();
        lcd.print("send complete!");
        
        delay(1000);
        break;
      }
        
      if(digitalRead(RETURN_SW)==LOW)
      {
        while(digitalRead(RETURN_SW)==LOW);
        delay(30);
        break;
      }  
    }
  }
  else //Heart rate mode
  {
    lcd.clear();
    lcd.home();
    lcd.print("Put Finger on");
    delay(1500);

   // EIFR |= (1<<INTF0);
    //EIFR |= (1<<INTF1);
    attachInterrupt(0, Check_bpm, FALLING);
    attachInterrupt(1, Return_select, FALLING);
    
    while(1)
    {
      if(back)
      {
        back = 0;

        if(returnSw)
        {
          lcd.clear();
          lcd.home();
          lcd.print("wait...");
          returnSw = LOW;
        }

        if(okSw)
        {
          lcd.clear();
          lcd.home();
          lcd.print("bpm: 87");

          lcd.setCursor(0,1);
          lcd.print("It` good!");
          okSw = LOW;
         
          delay(2000);
        }
        delay(1000);
        break;
      }
      else
      {
        lcd.clear();
        lcd.home();
        lcd.print("Heart-rate");
        lcd.setCursor(0, 1);
        lcd.print("87...");
        delay(1000);
        
        lcd.clear();
        lcd.home();
        lcd.print("Heart-rate");
        lcd.setCursor(0, 1);
        lcd.print("88...");
        delay(1000);
      }
    }
  }  
}


int Off_line_mode()
{
  back = 0;
  
   if(select) // Temperature mode
  {
    lcd.clear();
    lcd.home();
    lcd.print("Press chk btn");

    while(1)
    {
      if(digitalRead(CHECK_SW)==LOW)
      {
        String strTemp = String("");
        //strTemp = mlx.readObjectTempC();
        strTemp = 36.5;
        
        lcd.clear();
        lcd.home();
        lcd.print("Ok...");
        delay(3000);
        //부저
        lcd.clear();
        lcd.home();
        lcd.print("Temp: ");

        lcd.setCursor(6, 0);
        lcd.print(strTemp);
        lcd.setCursor(10, 0);
        lcd.print("`C");

        lcd.setCursor(0,1);
     
        if(strTemp.toInt()>= 36 && strTemp.toInt() <= 38)
          lcd.print("It`s Good!");
        else
          lcd.print("It`s bad...");
        delay(2500);
        break;
      }
        
      if(digitalRead(RETURN_SW)==LOW)
      {
        while(digitalRead(RETURN_SW)==LOW);
        delay(30);
        break;
      }  
    }
  }
  else //Heart rate mode
  {
    lcd.clear();
    lcd.home();
    lcd.print("Put Finger on");
    delay(1500);

   // EIFR |= (1<<INTF0);
    //EIFR |= (1<<INTF1);
    attachInterrupt(0, Check_bpm, FALLING);
    attachInterrupt(1, Return_select, FALLING);
    
    while(1)
    {
      if(back)
      {
        back = 0;

        if(returnSw)
        {
          lcd.clear();
          lcd.home();
          lcd.print("wait...");
          returnSw = LOW;
        }

        if(okSw)
        {
          lcd.clear();
          lcd.home();
          lcd.print("bpm: 87");

          lcd.setCursor(0,1);
          lcd.print("It` good!");
          okSw = LOW;
         
          delay(2000);
        }
        delay(1000);
        break;
      }
      else
      {
        lcd.clear();
        lcd.home();
        lcd.print("Heart-rate");
        lcd.setCursor(0, 1);
        lcd.print("87...");
        delay(1000);
        
        lcd.clear();
        lcd.home();
        lcd.print("Heart-rate");
        lcd.setCursor(0, 1);
        lcd.print("88...");
        delay(1000);
      }
    }
  }  
}
void Check_bpm()
{
  detachInterrupt(0);
  detachInterrupt(1);   
  
  back = !back;
  okSw = !okSw;
  
  while(digitalRead(CHECK_SW) == LOW);
  delayMicroseconds(300);
}

void Return_select()
{
  detachInterrupt(0);
  detachInterrupt(1);
  
  back = !back;
  returnSw = !returnSw;

  Serial.print("TEST");
  while(digitalRead(RETURN_SW) == LOW);
  delayMicroseconds(300);
}

void Menu_select()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("SELECT");

  if(select)//network on
  {
    lcd.setCursor(0, 1);
    lcd.print("1. Temperature");
  }
  else //network off
  {
    lcd.setCursor(0, 1);
    lcd.print("2. Heart-rate");
  }
}

void Menu_network()
{
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("MENU");
  
  if(network)//network on
  {
    lcd.setCursor(0, 1);
    lcd.print("1. On-line");
  }
  else //network off
  {
    lcd.setCursor(0, 1);
    lcd.print("2. Off-line");
  }
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

void Lcd_init()
{
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
}

void Lcd_hello()
{
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");

  lcd.setCursor(1, 1);
  lcd.print("I`m HomeDoctor");

  delay(2000);
}
void Bluetooth_init()
{
  btSerial.begin(9600);

  //while(1)
  //{
    if(btSerial.available())
    {
     Serial.write(btSerial.read()); 
    }
  
   if(Serial.available())
   {
      btSerial.write(Serial.read());
    }  
 // }
}
