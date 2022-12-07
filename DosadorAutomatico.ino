//Bibliotecas
#include <Servo.h>
#include <LiquidCrystal.h>
#include <HX711.h>

//Pinagem de componentes
int interruptPin = 2;
int sensor = 3;
int pinDT = 4;
int pinSCK = 5;
Servo servio;
int botao = 7;
int bomba = 8;
int led[5]={9,10,11,12,13};

LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
HX711 scale;

//Variaveis auxiliares 
int c=0;
float medida=0;
int etapa=1;
int servoAberto=-90;
int servoFechado=90;
int pesoDose=40;
int peso;
bool aux=false;
bool aux2=false;
int aux3=5;

void setup() {
  
pinMode(botao,INPUT_PULLUP);

pinMode(bomba,OUTPUT);

pinMode(interruptPin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), contador, FALLING);

pinMode(sensor,INPUT_PULLUP);

scale.begin(pinDT, pinSCK); 
scale.set_scale(341800);
scale.tare();

servio.attach(6); 

// Vazio para os pinos 7 e 8

for (int i = 0; i<5; i++){
  pinMode(led[i],OUTPUT); 
}

lcd.begin(16,2);
Serial.begin(9600);

servio.write(servoFechado);
}

void loop() {
  scale.power_up(); 
  if(digitalRead(sensor)==HIGH){
  switch (etapa){
    case 1:    
      lcd.setCursor(4,0);
      lcd.print("Dosador");
      lcd.setCursor(3,1);
      lcd.print("Automatico");
      teste();
      VerificarBotao();
    break;
     
     case 2:
       lcd.print("Insira as fichas");
       delay(1000);
       lcd.clear();
       delay(500);
       teste();
       VerificarBotao();    
     break;
     
     case 3:
       lcd.setCursor(1,0);
       lcd.print("Aperte o botao");
       lcd.setCursor(2,1);
       lcd.print("para iniciar");
       teste();
       VerificarBotao();
     break;
     
     case 4:
     lcd.setCursor(2,0);
     lcd.print("Quantidade:");
     lcd.setCursor(13,0);
     lcd.print(c);
     lcd.setCursor(1,1);
     lcd.print("coloque o copo");
     delay(2000);
     teste();
     VerificarBotao(); 
     break;
     
     case 5:
     lcd.setCursor(1,0);
     lcd.print("Aperte o botao");
     lcd.setCursor(3,1);
     lcd.print("e aguarde");
     teste();
     VerificarBotao();
     break; 
      
     case 6:
     lcd.setCursor(0,0);
     lcd.print("Peso do liquido:");
     digitalWrite(bomba,HIGH);
     scale.tare();
     teste(); 
     //delay(2000);
     while(peso<(pesoDose*c)){
       peso = (scale.get_units(5))*1000;
       lcd.setCursor(5,1);
       lcd.print(peso);
       lcd.print("g");
       teste();
       delay(90);
       if (VerificarSensor()== false)
       {
        digitalWrite(bomba,LOW);
         while(aux2==false){
            lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("Equipamento");
            lcd.setCursor(4,1);
            lcd.print("esgotado");
            delay(3000);
            lcd.clear();
            lcd.setCursor(4,0);
            lcd.print("Chame o");
            lcd.setCursor(2,1);
            lcd.print("responsavel");
            delay(3000);
           if(VerificarSensor()== true){ 
            digitalWrite(bomba,HIGH);
            aux2=true;
            lcd.clear();
           }
         }
       }
     }
     
     digitalWrite(bomba,LOW);
     delay(2000);
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("Pode retirar");
     lcd.setCursor(4,1);
     lcd.print("seu copo");//acertar
     delay(2000);
     while(aux==false){
       peso = (scale.get_units(5))*1000;
       if(peso<-20){ 
        aux=true;
       }
     }
     lcd.clear();
     lcd.setCursor(4,0);
     lcd.print("Obrigado");
     lcd.setCursor(2,1);
     lcd.print("volte sempre");
     scale.tare();
     scale.power_down();
     delay(5000);
     teste();
     c=0;
     aux=LOW;
     etapa=1;
     lcd.clear();
     break;
     
  }//switch
  }else{
     lcd.setCursor(2,0);
     lcd.print("Equipamento");
     lcd.setCursor(1,1);
     lcd.print("em manutencao");
     delay(2000);
     lcd.clear();
  }
}//loop end  

void VerificarBotao(){
  if((digitalRead(botao)==LOW)&((etapa==1)||(etapa==3)||(etapa==5))){
    if(etapa==1){
      servio.write(servoAberto);
    }else if(etapa==3){
      servio.write(servoFechado);
    }else{
      for (int i = 0; i<5; i++){
     digitalWrite(led[i],LOW); 
     }
    }
    etapa++;
    lcd.clear(); 
    //scale.tare();
  }
  if((etapa==2 & c>0)){
    etapa++;
    lcd.clear();     
  }
  if(etapa==4){
  peso = (scale.get_units(5))*1000;
  if(peso>10){
    etapa++;
    lcd.clear(); 
  }
  delay(1000);
  }
   
}

void contador(){
  if((etapa==2)||(etapa==3)){
    digitalWrite(led[c],HIGH);
    c++;
    switch(c){
      case 6:
      c=5;
      break;
      case 5:
      servio.write(servoFechado);
    break;
    }
  }
}

void teste(){
  Serial.print("Etapa= ");
  Serial.print(etapa);
  Serial.print(" Botao= ");
  Serial.print(digitalRead(botao));
  Serial.print(" Contador= ");
  Serial.print(c);
  Serial.print(" Sensor= ");
  Serial.print(digitalRead(sensor));
  Serial.print(" Peso= ");
  Serial.println(peso);
}

bool VerificarSensor ()
{
  if (digitalRead (sensor)== LOW){
    return false;
  }
  else {
  return true;
  }
}
