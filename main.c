#include<arduino.h>
int opticS1 = A0;
int opticS2 = A1;
int SDA = A4;
int SCL = A5;
int FDCI = A3;
int FDCF = A2;
int V1;
int decMetal;
int counter;
int LCD;
int IN1 = 2;			// IN1 de L298N a pin digital 2
int IN2 = 3;			// IN2 de L298N a pin digital 3
int ENA = 5;			// ENA de L298N a pin digital 5
//motor2
int IN3 = 8;    
int IN4 = 9;
int ENB = 10;
int VELOCIDAD;			// variable para almacenar valor de velocidad
int VMotor = 255;
int VMotor2 = 255;

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
}
while(1){
do{
    V1 = analogRead(FDCI);
switch(V1){
    case 1:
    do{
        analogRead(opticS1)
    }while(opticS1 == 1);
    //apagado de cinta secundaria

    do{
        do{
        analogRead(decMetal)
        switch(decMetal){
            case 1:
            //Se detecto metal proceso detenido;
 for (VELOCIDAD = 0; VELOCIDAD < 10; VELOCIDAD++){	// bucle que incrementa de a uno
  analogWrite(ENA, VELOCIDAD);				// el valor de velocidad y aplica a ENA
  digitalWrite(IN1, LOW);				// IN1 en 0
  digitalWrite(IN2, HIGH);	
  }
            break;
            default: 
            counter = 0;
            counter++;
        }
        LCD = opticS2;
        //mostrar por pantalla el cónteo
        }while(opticS2 >= 5);
    }while(opticS2 == 5);
    //continua caja
    do{
        analogRead(FDCF);
    }while(FDCF == 1);
    //Se detiene hasta que el FDCF = 1
    FDCI = 0;
    break;
    default;

}while(FDCI == 1);

}
}