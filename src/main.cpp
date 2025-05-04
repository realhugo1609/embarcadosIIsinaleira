#include <Arduino.h>
#include "funcoes.h"

#define BOTAO_PEDESTRE    32
#define pinos1vermelho    4
#define pinos1verde       5
#define pinos1amarelo     15
#define pinos2vermelho    18
#define pinos2amarelo     19
#define pinos2verde       21
#define pinos3vermelho    22
#define pinos3amarelo     23
#define pinos3verde       13
#define pinos4vermelho    12
#define pinos4amarelo     14
#define pinos4verde       27
#define pinos5vermelho    26
#define pinos5amarelo     25
#define pinos5verde       33


uint8_t s1[3]; //vermelho, amarelo, verde
uint8_t s2[3]; //vermelho, amarelo, verde
uint8_t s3[3]; //vermelho, amarelo, verde
uint8_t s4[3]; //vermelho, amarelo, verde
uint8_t s5[3]; //vermelho, amarelo, verde
uint8_t tempo = 1;
unsigned int timer = millis();;
unsigned int duracao = 10000;
bool flagPedestre = false; //PRA VER SE O BOTAO DO PEDESTRE ESTA SENDO APERTADO
uint8_t qtdIteracoes = 6; //6 EH SEM SEMAFOROS DO PEDESTRE... 8 EH COM


void setaSinais();
void imprimeSinais();

void setup() {
  Serial.begin(115200);
  pinMode(BOTAO_PEDESTRE, INPUT);

  pinMode(pinos1vermelho, OUTPUT);
  pinMode(pinos1verde, OUTPUT);
  pinMode(pinos1amarelo, OUTPUT);
  pinMode(pinos2vermelho, OUTPUT);
  pinMode(pinos2amarelo, OUTPUT);
  pinMode(pinos2verde, OUTPUT);
  pinMode(pinos3vermelho, OUTPUT);
  pinMode(pinos3amarelo, OUTPUT);
  pinMode(pinos3verde, OUTPUT);
  pinMode(pinos4vermelho, OUTPUT);
  pinMode(pinos4amarelo, OUTPUT);
  pinMode(pinos4verde, OUTPUT);
  pinMode(pinos5vermelho, OUTPUT);
  pinMode(pinos5amarelo, OUTPUT);
  pinMode(pinos5verde, OUTPUT);

  timer = millis();
  setaSinais();

}

char teste[32];
int indice = 0;

void loop() {

  //PARA LER ESTADOS ATUAIS DOS LEDS
  if (Serial.available() > 0)
  {
    indice = 0;
    while (Serial.available())
    {
      teste[indice] = Serial.read();
      indice++;
    }
    Serial.print("recebi: ");
    Serial.println(teste);
  }
  if (teste[0] == 105) 
  { 
    imprimeSinais(); //105 = letra i
    teste[0] = 0;
  }
  
  


  //HORA DE TROCAR DE TEMPO
  if (millis() > timer + duracao)
  {
    if (tempo < qtdIteracoes) tempo++;
    else tempo = 1;
    Serial.print("Tempo: ");
    Serial.println(tempo);
    setaSinais();
    timer = millis();
  }

  //VERIFICA SE O BOTAO DO PEDESTRE ESTA SENDO APERTADO
  if (!digitalRead(BOTAO_PEDESTRE)) 
  {
    Serial.println(digitalRead(BOTAO_PEDESTRE));
    flagPedestre = true;
    qtdIteracoes = 8;
  }
/*
  Serial.println(  digitalRead(BOTAO_PEDESTRE)   );
  //delay(500);
*/


}


void setaSinais()
{
  switch(tempo)
  {
    case 1:                            //1º TEMPO
      Serial.println("Caso 1");
      duracao = 10000;
      digitalWrite(pinos1vermelho, LOW); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, HIGH); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, HIGH); //VERDE
      digitalWrite(pinos3vermelho, HIGH); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, HIGH); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, HIGH); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      break;
    case 2:                        //TRANSITORIO DO 1 PRO 2
      Serial.println("Caso 2");
      duracao = 2000;
      digitalWrite(pinos1vermelho, LOW); //VERMELHO
      digitalWrite(pinos1amarelo, HIGH); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, HIGH); //VERDE
      digitalWrite(pinos3vermelho, HIGH); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, HIGH); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, HIGH); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      break;
    case 3:                             //2º TEMPO
      Serial.println("Caso 3");
      duracao = 10000;
      digitalWrite(pinos1vermelho, HIGH); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, HIGH); //VERDE
      digitalWrite(pinos3vermelho, LOW); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, HIGH); //VERDE
      digitalWrite(pinos4vermelho, HIGH); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, LOW); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, HIGH); //VERDE
      break;
    case 4:                             //TRANSITORIO DO 2 PRO 3
      Serial.println("Caso 4");
      duracao = 2000;
      digitalWrite(pinos1vermelho, HIGH); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, HIGH); //AMARELO
      digitalWrite(pinos2verde, LOW); //VERDE
      digitalWrite(pinos3vermelho, LOW); //VERMELHO
      digitalWrite(pinos3amarelo, HIGH); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, HIGH); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, LOW); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, HIGH); //VERDE
      break;
    case 5:                             //3º TEMPO
      Serial.println("Caso 5");
      duracao = 10000;
      digitalWrite(pinos1vermelho, HIGH); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, HIGH); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, LOW); //VERDE
      digitalWrite(pinos3vermelho, HIGH); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, LOW); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, HIGH); //VERDE
      digitalWrite(pinos5vermelho, LOW); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, HIGH); //VERDE
      break;
    case 6:                             //TRANSITORIO DO 3 PRO 1
      Serial.println("Caso 6");
      duracao = 2000;
      digitalWrite(pinos1vermelho, HIGH); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, HIGH); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, LOW); //VERDE
      digitalWrite(pinos3vermelho, HIGH); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, LOW); //VERMELHO
      digitalWrite(pinos4amarelo, HIGH); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, LOW); //VERMELHO
      digitalWrite(pinos5amarelo, HIGH); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      break;
 
    case 7:                             //CHAVE PEDESTRE
      Serial.println("Caso 7");
      duracao = 10000;
      digitalWrite(pinos1vermelho, HIGH); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, HIGH); //VERDE
      digitalWrite(pinos3vermelho, HIGH); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, HIGH); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, HIGH); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      break;

    case 8:                             //TRANSITORIO DA CHAVE PEDESTRE PRO 1
      Serial.println("Caso 8");
      duracao = 2000;
      qtdIteracoes = 6; //DEPOIS DO SEMAFORO DO PEDESTRE, VOLTAR PROS ESTADOS NORMAIS, SEM O SEMAFORO DO PEDESTRE
      digitalWrite(pinos1vermelho, HIGH); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, HIGH); //AMARELO
      digitalWrite(pinos2verde, LOW); //VERDE
      digitalWrite(pinos3vermelho, HIGH); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, HIGH); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, HIGH); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      break;
  }
}

//MANDAR UM i PELO SERIAL PRA VER TODOS OS ESTADOS DOS SEMAFOROS
void imprimeSinais()
{
  Serial.print("s1: " );
  Serial.print(s1[0]);
  Serial.print(", ");
  Serial.print(s1[1]);
  Serial.print(", ");
  Serial.println(s1[2]);
  Serial.print("s2: " );
  Serial.print(s2[0]);
  Serial.print(", ");
  Serial.print(s2[1]);
  Serial.print(", ");
  Serial.println(s2[2]);
  Serial.print("s3: " );
  Serial.print(s3[0]);
  Serial.print(", ");
  Serial.print(s3[1]);
  Serial.print(", ");
  Serial.println(s3[2]);
  Serial.print("s4: " );
  Serial.print(s4[0]);
  Serial.print(", ");
  Serial.print(s4[1]);
  Serial.print(", ");
  Serial.println(s4[2]);
  Serial.print("s5: " );
  Serial.print(s5[0]);
  Serial.print(", ");
  Serial.print(s5[1]);
  Serial.print(", ");
  Serial.println(s5[2]);


}