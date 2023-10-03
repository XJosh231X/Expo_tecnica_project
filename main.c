#include<arduino.h>
#include<Servo.h>
#include <LiquidCrystal_I2C.h>
int opticS1 = 4;
int opticS2 = 7;
int SDA = A4;
int SCL = A5;
int FDCI = 1; //fin de carrera inicial
int FDCF = 0; //fin de carrera final
int V1;
int decMetal = A3;
int counter;
int LCD;
//servo
int servoPin = 11;
int servoPos = 90;
int servoDelay = 10000;
//motor1
int IN1 = 2;			// IN1 de L298N a pin digital 2 
int IN2 = 3;			// IN2 de L298N a pin digital 3
int ENA = 5;			// ENA de L298N a pin digital 5
//motor2
int IN3 = 8;    
int IN4 = 9;
int ENB = 10;
int VELOCIDAD;			// variable para almacenar valor de velocidad
int VMotor1 = 255;
int VMotor2 = 255;
LiquidCrystal_I2C lcd(0x27,16,2);

int main() {
//setup
pinMode(opticS1,INPUT);
pinMode(opticS2,INPUT);
pinMode(FDCI,INPUT);
pinMode(FDCF,INPUT);
pinMode(SDA,INPUT);
pinMode(SCL,INPUT);
 pinMode(IN1, OUTPUT);		// pin 2 como salida
  pinMode(IN2, OUTPUT);		// pin 3 como salida	
  pinMode(ENA, OUTPUT);		// pin 5 como salida
  pinMode(IN3, OUTPUT);		// pin 8 como salida
  pinMode(IN4, OUTPUT);		// pin 9 como salida	
  pinMode(ENB, OUTPUT);		// pin 10 como salida
  lcd.init();
  lcd.backlight();
  lcd.clear();
myServo.attach(servoPin);
}
while(1){
do{
    V1 = digitalRead(FDCI);
switch(V1){
    case 1:
     for (VELOCIDAD = 0; VELOCIDAD < VMotor1; VELOCIDAD++){	// bucle que incrementa de a uno
  analogWrite(ENA, VELOCIDAD);				// el valor de velocidad y aplica a ENA
  digitalWrite(IN1, LOW);				// IN1 en 0
  digitalWrite(IN2, HIGH);	
    do{
  for (VELOCIDAD = 0; VELOCIDAD < VMotor1; VELOCIDAD++){	// bucle que incrementa de a uno
  analogWrite(ENA, VELOCIDAD);				// el valor de velocidad y aplica a ENA
  digitalWrite(IN1, LOW);				// IN1 en 0
  digitalWrite(IN2, HIGH);	
        digitalRead(opticS1)
    }while(opticS1 == 1);
    //apagado de cinta secundaria
    for (VELOCIDAD = 0; VELOCIDAD < 10; VELOCIDAD++){	// bucle que incrementa de a uno
    analogWrite(ENB, VELOCIDAD);				// el valor de velocidad y aplica a ENB
    digitalWrite(IN3, LOW);				// IN3 en 0
    digitalWrite(IN4, HIGH);	

    do{
        do{
        analogRead(decMetal);
        switch(decMetal){
            case 1:
            //Se detecto metal proceso detenido;
  lcd.setCursor(0,0);
  lcd.print("METAL DETECTADO!!"); 
  lcd.setCursor (0,1);
  lcd.print("PROCESO DETENIDO!");
  myServo.write(servoPos);
  delay(servoDelay);
  for (VELOCIDAD = 0; VELOCIDAD < 10; VELOCIDAD++){	// bucle que incrementa de a uno
  analogWrite(ENA, VELOCIDAD);				// el valor de velocidad y aplica a ENA
  digitalWrite(IN1, LOW);				// IN1 en 0
  digitalWrite(IN2, HIGH);	
  }
  for (VELOCIDAD = 0; VELOCIDAD < 10; VELOCIDAD++){	// bucle que incrementa de a uno
  analogWrite(ENB, VELOCIDAD);				// el valor de velocidad y aplica a ENB
  digitalWrite(IN3, LOW);				// IN3 en 0
  digitalWrite(IN4, HIGH);	
  } 
            break;
            default: 
            counter = 0;
            counter++;
        }
        LCD = opticS2;
        //mostrar por pantalla el cónteo
  lcd.setCursor(0,0);
  lcd.print("==>ENCENDIDO!<=="); 
  lcd.setCursor (0,1);
  lcd.print("PR:%d",counter);
        }while(opticS2 >= 5);
    }while(opticS2 == 5);
    //continua caja
     for (VELOCIDAD = 0; VELOCIDAD < VMotor2; VELOCIDAD++){	// bucle que incrementa de a uno
  analogWrite(ENB, VELOCIDAD);				// el valor de velocidad y aplica a ENA
  digitalWrite(IN3, LOW);				// IN3 en 0
  digitalWrite(IN4, HIGH);	
  }
    do{
        digitalRead(FDCF);
    }while(FDCF == 1);
    //Se detiene hasta que el FDCF = 1
    FDCI = 0;
    break;
    default;

}while(FDCI == 1);

}
}