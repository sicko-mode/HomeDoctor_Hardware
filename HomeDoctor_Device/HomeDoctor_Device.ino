#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Adafruit_MLX90614.h>
#include <Wire.h>

#define PIN_RX 12
#define PIN_TX 11

#define CHECK_SW 2
#define RETURN_SW 3
#define OK_SW 4
#define NEXT_SW 5

#define POWER_LED 8
#define SENSOR_CHECK_LED 9
#define PIEZO 10

#define TEMP 1
#define PULSE 2

int network = 1, select = 1;
volatile int back = LOW;
volatile int returnSw = LOW;
volatile int okSw = LOW;

byte data[4];

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial btSerial(PIN_TX, PIN_RX);

void Pin_init();
void Lcd_init();
void Lcd_hello();
void Menu_network();
void Menu_select();
void Chk_sensor();
void Print_error();
void Check_bpm();
void Return_select();
void Bluetooth_init();
int On_line_mode();
int Off_line_mode();

void setup() {
  // put your setup code here, to run once:
  Pin_init();
  Lcd_init();
  Lcd_hello();
  Bluetooth_init();
  mlx.begin();
  
  Menu_network();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(NEXT_SW) == LOW)
  {
    network = !network;
    delay(100);
    Menu_network();
    
    while(digitalRead(NEXT_SW) == LOW);
    delay(30);
  }

  if(digitalRead(OK_SW) == LOW)
  {    
    while(digitalRead(OK_SW)==LOW);
    delay(30);
    delay(100);
    Chk_sensor(); 
  }
} 
