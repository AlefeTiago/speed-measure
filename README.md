O desafio foi desenvolver um programa que estime a frequência de rotação de um motor CC com codificador (encoder). No circuito apresentado na Figura 2, o encoder produz
aproximadamente 49 bordas de subida e de descida (pulsos) no canal B a cada volta do eixo do motor (os pulsos podem ser vistos no osciloscópio). A estimativa da frequência, em rotações por minuto (rpm), deve ser feita através da contagem do número de pulsos produzidos pelo canal B do encoder durante um intervalo de tempo, através da equação:

frpm = número de pulsos/ número de pulsos por volta ∗ intervalo , em que o intervalo é medido em minutos.

Para uma contagem precisa do número de pulsos, utilizei a interrupção do tipo pin change associada ao terminal A0. Além disso, utilizei a função _delay_ms() da biblioteca util/delay.h para definir o intervalo de tempo da contagem de bordas.O algarismo correspondente à centena da estimativa deve ser exibido no display de sete segmentos.

![alt text](https://github.com/AlefeTiago/speed-measure/blob/main/Montagem.PNG)
