#include <Adafruit_MLX90614.h> //온도측정 라이브러리
#include <Wire.h> //i2c 라이브러리

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");
  mlx.begin(); //센서 값 읽기 시작
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("*C\tObject = ");
  Serial.print(mlx.readObjectTempC());
  Serial.println("*C"); // 객체 온도 출력

  delay(1000);
}
