#include <LedControl.h>
#include <SR04.h>

// Nombre de colores asociados con la salidas digitales correspondiente.
#define BUZZER 2
#define ECHO_PIN 3
#define TRIG_PIN 4

long a;

//SENSOR SR04, LEDCONTROL
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
LedControl lc=LedControl(12,11,10,1);

unsigned long delaytime=100;

void setup() {
  Serial.begin(9600);
 
  pinMode(BUZZER, OUTPUT);
 
  lc.shutdown(0,false);       // que inicie en power saving power-saving 
  lc.setIntensity(0,5);      // brillo maximo 15
  lc.clearDisplay(0);         // limpia el display
}
 
void loop() {   
  a=sr04.Distance();
  Serial.print(a);
  Serial.println("cm");

  if (a < 30) {  
    delay(a*10);   
    tone(BUZZER, 500); 
    delay(a*10);               
    noTone(BUZZER); 
    delay(a*10);   
  
    if (a >= 25) { pintaDisplay(5); 
    } else if ((a >= 20) and (a < 25 )){ pintaDisplay(4);
    } else if ((a >= 15) and (a < 20 )){ pintaDisplay(3);
    } else if ((a >= 10) and (a < 15 )){ pintaDisplay(2);
    } else if ((a >= 5) and (a < 10 )){ pintaDisplay(1);
    } else if (a < 5){ pintaDisplay(0);
    }     
  } else { pintaDisplay(99); }
}

void pintaDisplay(int iTipo) {
  byte CaraSmile[8] = { B00111100,B01000010,B10010101,B10100001,B10100001,B10010101,B01000010,B00111100};
  byte distancia4[8] = { B11000000,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}; 
  byte distancia3[8] = { B11000000,B11000000,B11110000,B11110000,B00000000,B00000000,B00000000,B00000000};
  byte distancia2[8] = { B11000000,B11000000,B11110000,B11110000,B11111100,B11111100,B00000000,B00000000};
  byte distancia1[8] = { B11000000,B11000000,B11110000,B11110000,B11111100,B11111100,B11111111,B11111111};
  byte caraSad[8] = { B00111100,B01000010,B10101001,B10100001,B10101001,B10100001,B01000010,B00111100};
  
  if (iTipo == 5) { for (int i=0; i<8; i++){ lc.setRow(0,i,CaraSmile[i]); } }
  if (iTipo == 4) { for (int i=0; i<8; i++){ lc.setRow(0,i,distancia4[i]); } }
  if (iTipo == 3) { for (int i=0; i<8; i++){ lc.setRow(0,i,distancia3[i]); } }
  if (iTipo == 2) { for (int i=0; i<8; i++){ lc.setRow(0,i,distancia2[i]); } }
  if (iTipo == 1) { for (int i=0; i<8; i++){ lc.setRow(0,i,distancia1[i]); } }
  if (iTipo == 0) { for (int i=0; i<8; i++){ lc.setRow(0,i,caraSad[i]); } }
  
  if (iTipo == 99) { for(int i=0; i<8; i++){ lc.setRow(0,i,0); } } // borra display
}


