#include <arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
int opticS1 = 4;
int opticS2 = 7;
int sda = A4;
int scl = A5;
int fdcInicial = 1; // fin de carrera inicial
int fdcFinal = 0; // fin de carrera final
int decMetal = 6;
//int counter;
int lcDisplay;
// servo
Servo myServo;
int servoPin = 11;
int servoPos = 90;
int servoDelay = 10000;
// motor1
int IN1 = 2; // IN1 de L298N a pin digital 2
int IN2 = 3; // IN2 de L298N a pin digital 3
int ENA = 5; // ENA de L298N a pin digital 5
// motor2
int IN3 = 8;
int IN4 = 9;
int ENB = 10;
int speed; // variable para almacenar valor de velocidad
int vMotor1 = 255;
int vMotor2 = 255;
int counter = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int main()
{
    // setup
    pinMode(opticS1, INPUT);
    pinMode(opticS2, INPUT);
    pinMode(fdcInicial, INPUT);
    pinMode(fdcFinal, INPUT);
    pinMode(sda, INPUT);
    pinMode(scl, INPUT);
    pinMode(IN1, OUTPUT); // pin 2 como salida
    pinMode(IN2, OUTPUT); // pin 3 como salida
    pinMode(ENA, OUTPUT); // pin 5 como salida
    pinMode(IN3, OUTPUT); // pin 8 como salida
    pinMode(IN4, OUTPUT); // pin 9 como salida
    pinMode(ENB, OUTPUT); // pin 10 como salida
    lcd.init();
    lcd.backlight();
    lcd.clear();
    myServo.attach(servoPin);
while (true)
{
    start();
}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void start()
{
  int valor1;
    if (digitalRead(fdcInicial) == 1) { //si el fin de carrera inicial esta activado
        motorHigh(1);                     //se enciende el motor 1
        do{                               //Este ciclo while lee el sensor optico y almacena esa lectura en la variable "valor1"
            valor1 = digitalRead(opticS1);
        } while(valor1==0);             // se sale del bucle cuando la lectura da 1
        motorLow(1);                    //motorLow(1) apaga el motor 1
        motorHigh(2);                     // se enciende el motor 2
        do{                             //se inicia este ciclo que almacena el contador presente en el display
          count();
        } while(counter<5); //count==5
        motorLow(2);                     //se apaga el motor 2
        endingCounter();                    
        motorHigh(1);
        endingInstruction();
        }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void count(){
    int valor = digitalRead(opticS2);
    if (valor == 1 && metalDec(digitalRead(decMetal)) == 0) {
            counter++;
        }
}

int metalDec(int x) {
    int devuelve = 0;

    if (x == 1) {
        // Se detecto metal proceso detenido
        lcd.setCursor(0, 0);
        lcd.print("METAL DETECTADO!!");
        lcd.setCursor(0, 1);
        lcd.print("PROCESO DETENIDO!");
        myServo.write(servoPos);
        delay(servoDelay);
        devuelve=1;
    } 
    return devuelve;
}

void motorHigh(int c){ 
  if(c == 1)
  {
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else
  {
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void motorLow(int motor) {
    if(motor = 1){
      digitalWrite(ENA,LOW);  //int ifD = ENA; //Apagamos motor 1
    } else {
        digitalWrite(ENB,LOW); // apagamos motor 2
    }          
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void endingCounter()
{
    do
    {
        lcDisplay = opticS2;
        // mostrar por pantalla el cÃ³nteo
        lcd.setCursor(0, 0);
        lcd.print("==>ENCENDIDO!<==");
        lcd.setCursor(0, 1);
        lcd.print("PR:");
        lcd.setCursor(4, 1);
        lcd.print(counter);
    } while (opticS2 == 5);
}
//---------------------------------------------
void endingInstruction()
{
    do
    {
        digitalRead(fdcFinal);
    } while (fdcFinal == 0);
    motorLow(1);
}