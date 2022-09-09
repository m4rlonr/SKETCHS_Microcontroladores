//--------------------------------------------------------------------------------------------------------------//
//Documentação completa da biblioteca IR remote em : https://github.com/Arduino-IRremote/Arduino-IRremote       //
//Simulação do exemplo oficial: https://wokwi.com/projects/338611596994544210                                   // 
//--------------------------------------------------------------------------------------------------------------//
#include <IRremote.hpp>                                                     // Importando a biblioteca necessária para usar o receptor

const byte IR_RECEIVE_PIN = 11;                                             // Setando o pino que receve os dados

void setup()
{
   Serial.begin(115200);                                                    // Iniciando o Serial para poder monitorar e armazenar os códigos
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);                   // Iniciando a IR para poder trabalhar com o sensor
   Serial.println("Pronto para receber código.");                           // Enviando um aviso sobre a prontidão do código para receber os arquivos
}

void loop()
{
   if (IrReceiver.decode())                                                 // Validando o sinal recebido
   {
      IrReceiver.printIRResultRawFormatted(&Serial, true);                  // Imprimindo em forma de sinal bruto os dados
      //Serial.println(IrReceiver.decodedIRData.decodedRawData);            
      IrReceiver.resume();                                                  // 
   }
}
