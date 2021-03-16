#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Declarando as variáveis para o calculo da frequência. 

unsigned int cont_pulsos=0;
unsigned int frequencia=0;

//Declarando os ponteiros que apontarão para a porta D 

unsigned char *p_portd;
unsigned char *p_ddrd;

//Declarando os ponteiros que apontarão para a porta c 

unsigned char *p_portc;
unsigned char *p_pinc;
unsigned char *p_ddrc;

//Declarando os ponteiros que apontarão para a interrupção! 
unsigned char *p_cmask1;
unsigned char *p_cicr;

//Função que estima a frequência
void estimativa(){
  frequencia =(cont_pulsos*60000)/((48)*(500));
}

//Função que rege a interrupção

ISR(PCINT1_vect){
  if((*p_pinc & 0x01)== 1){ //Comparação para garantir que o incremento seja dado apenas na borda de descida 
cont_pulsos++; 
  }
}

// Inicialização dos periféricos que serão utilizados no sistema

void setup(void){
  
  //Inicializando os ponteiros de interrupção
  cli();
  p_cmask1 = (unsigned char*)0x6C;
  p_cicr= (unsigned char *)0x68;
  
 //Primeiramente, iniciaizando a porta de entrada D 
  
  p_portd = (unsigned char *)0x2B;
  p_ddrd= (unsigned char *) 0x2A;
  
 //Agora, inicializando a porta de saída D 
  
  p_portc = (unsigned char *)0x28;
  p_pinc = (unsigned char *)0x26;
  p_ddrc = (unsigned char *)0x27;
  
  //Configurando as mascaras do pin
  *p_cicr |= 2;
  *p_cmask1 |= 1;
    
 // Definindo as saídas (de PD0 a PD7)
    
  *p_ddrd |= 0xFF; // 1111 1111 é como ficara os ddr'sD, logo, todos são registradores de saída!
  
  //Definindo PC0 como entrada 
  
  *p_ddrc &= 0x01; // 1111 1110 é como ficara os ddr'sC, logo, o único registrador de entrada é PC0
  
  
  // Ativar o resitor de pull-up em A0
  
  *p_portc |= 0x01; // 0000 0001
  
   //Led's' inicialmente apagados 
  
  *p_portd &=0xFF; // 0000 0000, lembrando que os Leds são ativo alto
  sei();
}

// Criando uma função que manipula o display de acordo com o valor da frequência

  void display(void)
  {
    
    *p_portd &= 0x01;
    if (frequencia<100){*p_portd = 0x7E;}
  else if ((frequencia>= 100) & (frequencia < 200)){*p_portd = 0x0C;}
  else if ((frequencia>= 200) & (frequencia < 300)){*p_portd = 0xB6;}
  else if ((frequencia>= 300) & (frequencia < 400)){*p_portd = 0x9E;}
  else if ((frequencia>= 400) & (frequencia < 500)){*p_portd = 0xCC;}
  else if ((frequencia>= 500) & (frequencia < 600)){*p_portd = 0xDA ;}
  else if ((frequencia>= 600) & (frequencia < 700)){*p_portd =0xFA;}
  else if ((frequencia>= 700) & (frequencia < 800)){*p_portd = 0x0E;}
  else if ((frequencia>= 800) & (frequencia < 900)){*p_portd = 0xFE;}
  else if ((frequencia>= 900) & (frequencia < 1000)){*p_portd = 0xCE;}
    
  }
int main(){
  
  // Inicializo os periféricos (regs e display)
  
  setup();
  
  //Loop Infinito
  
  while (1){
    
   _delay_ms(5); 			// Para correção do BUG do ThinkerCad
   cont_pulsos=0; 			// Zerando a variável que conta os pulsos para garantir que ao final do laço seja contabilizado um "intervalo"
    sei(); 				// Inicio as Interrupções que foram paradas no fim do setup
    _delay_ms(500);			 // Paro o programa por 500 ms (Aqui as interrupções não são paradas. Então a contagem será continuada durante os 500ms)
    cli();	 			// Paro a interrupção para garantir que cont_pulsos seja apenas o contabilizado durante o periodo de tempo proposto acima 
   estimativa(); 
    display();			 // Mostro o resultado da função estimativa no display (a função display foi pensada para os valores de RPM da funçaõ estimativa)
  }
  return 0;
}
