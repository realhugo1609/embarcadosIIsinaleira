#include <Arduino.h>

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
unsigned int timer = millis();
unsigned int duracao = 10000;
bool flagPedestre = false; //PRA VER SE O BOTAO DO PEDESTRE ESTA SENDO APERTADO
bool estadoDeAlerta = false;
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

  //PARA RECEBER ESTADO DE ALERTA DO SUPERVISORIO
  if (Serial.available() > 0)
  {
    indice = 0;
    while (Serial.available())
    {
      teste[indice] = Serial.read();
      indice++;
    }

    if (teste[0] == 105) 
    { 
      if (estadoDeAlerta) 
      {
        estadoDeAlerta = false;
        tempo = 0;  //PARA COMECAR DO ESTADO 1
      } else estadoDeAlerta = true;
      teste[0] = 0;   //PRA CONDICAO SER FALSA, PRA NAO SE REPETIR SEMPRE
    }

  }


  //HORA DE TROCAR DE TEMPO
  if (millis() > timer + duracao)
  {
    /*
    if ((flagPedestre) && ((tempo == 2) || (tempo == 4) || (tempo == 6))) //BOTAO DE PEDESTRE FOI APERTADO, E JA ESTA NA TRANSICAO COM AMARELO
    {
      tempo = 7; //PULA PRO ESTADO 7, COM OS SEMAFOROS FECHADOS
      flagPedestre = false; //PRA VOLTAR PRA NORMALIDADE
      //qtdIteracoes = 7; 
    } else 
    */
    if (tempo < qtdIteracoes) 
    {
      tempo++;
    } else tempo = 1;

    setaSinais();
    timer = millis();
  }

  //VERIFICA SE O BOTAO DO PEDESTRE ESTA SENDO APERTADO
  if (!digitalRead(BOTAO_PEDESTRE)) 
  {
    //Serial.println(digitalRead(BOTAO_PEDESTRE));
    flagPedestre = true;
    qtdIteracoes = 7;
  }



}


void setaSinais()
{

  if (estadoDeAlerta)  //ESTADOD E ALERTA LIGADO (2 OPCOES)
  {

    if (digitalRead(pinos1amarelo))  //TOGGLE NOS SINAIS AMARELOS
    {
      duracao = 500;
      digitalWrite(pinos1vermelho, LOW); //VERMELHO
      digitalWrite(pinos1amarelo, LOW); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, LOW); //AMARELO
      digitalWrite(pinos2verde, LOW); //VERDE
      digitalWrite(pinos3vermelho, LOW); //VERMELHO
      digitalWrite(pinos3amarelo, LOW); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, LOW); //VERMELHO
      digitalWrite(pinos4amarelo, LOW); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, LOW); //VERMELHO
      digitalWrite(pinos5amarelo, LOW); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      imprimeSinais();
    } else  //TOGGLE NOS SINAIS AMARELOS
    {
      duracao = 500;
      digitalWrite(pinos1vermelho, LOW); //VERMELHO
      digitalWrite(pinos1amarelo, HIGH); //AMARELO
      digitalWrite(pinos1verde, LOW); //VERDE
      digitalWrite(pinos2vermelho, LOW); //VERMELHO
      digitalWrite(pinos2amarelo, HIGH); //AMARELO
      digitalWrite(pinos2verde, LOW); //VERDE
      digitalWrite(pinos3vermelho, LOW); //VERMELHO
      digitalWrite(pinos3amarelo, HIGH); //AMARELO
      digitalWrite(pinos3verde, LOW); //VERDE
      digitalWrite(pinos4vermelho, LOW); //VERMELHO
      digitalWrite(pinos4amarelo, HIGH); //AMARELO
      digitalWrite(pinos4verde, LOW); //VERDE
      digitalWrite(pinos5vermelho, LOW); //VERMELHO
      digitalWrite(pinos5amarelo, HIGH); //AMARELO
      digitalWrite(pinos5verde, LOW); //VERDE
      imprimeSinais();
    }



  } else //ESTADO DE ALERTA DESLIGADO
  {

    switch(tempo)
    {
      case 1:                            //1º TEMPO
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
        imprimeSinais();
        break;
      case 2:                        //TRANSITORIO DO 1 PRO 2
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
        imprimeSinais();
        break;
      case 3:                             //2º TEMPO
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
        imprimeSinais();
        break;
      case 4:                             //TRANSITORIO DO 2 PRO 3
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
        imprimeSinais();
        break;
      case 5:                             //3º TEMPO
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
        imprimeSinais();
        break;
      case 6:                             //TRANSITORIO DO 3 PRO 1
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
        imprimeSinais();
        break;
  
      case 7:                             //CHAVE PEDESTRE
        duracao = 10000;
        qtdIteracoes = 6;
        flagPedestre = false;
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
        imprimeSinais();
        break;
    }
  }
}

//MANDAR UM i PELO SERIAL PRA VER TODOS OS ESTADOS DOS SEMAFOROS
void imprimeSinais()
{
  //Serial.println("1 0 1 0 0 1 1 1 0 0 1 0 1 1 0\n");

  Serial.print(digitalRead(pinos1vermelho));
  Serial.print(" ");
  Serial.print(digitalRead(pinos1amarelo));
  Serial.print(" ");
  Serial.print(digitalRead(pinos1verde));
  Serial.print(" ");

  Serial.print(digitalRead(pinos2vermelho));
  Serial.print(" ");
  Serial.print(digitalRead(pinos2amarelo));
  Serial.print(" ");
  Serial.print(digitalRead(pinos2verde));
  Serial.print(" ");

  Serial.print(digitalRead(pinos3vermelho));
  Serial.print(" ");
  Serial.print(digitalRead(pinos3amarelo));
  Serial.print(" ");
  Serial.print(digitalRead(pinos3verde));
  Serial.print(" ");

  Serial.print(digitalRead(pinos4vermelho));
  Serial.print(" ");
  Serial.print(digitalRead(pinos4amarelo));
  Serial.print(" ");
  Serial.print(digitalRead(pinos4verde));
  Serial.print(" ");

  Serial.print(digitalRead(pinos5vermelho));
  Serial.print(" ");
  Serial.print(digitalRead(pinos5amarelo));
  Serial.print(" ");
  Serial.println(digitalRead(pinos5verde));

}