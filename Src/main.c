#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"

struct noeud
{

};

int main(void)
{
	/*FPU_Init();
	GPIO_Init();
	SYSTICK_Init();*/
	USART2_Init();

	uint8_t texte[] = "hello word\n\r";//"aaaabbbccd";					//texte non compressé
	//uint8_t texteCompressé[TAILLE_MAX_COMPRESS];	//text compressé
	//uint32_t tabCaractere[NBR_CARACTERE] = {0};				//tableau du nombre d'occurrence de chaque caractère
	//uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereTotal = 0;					//nombre de caractère totale dans le texte non compressé
	//struct noeud* arbreHffman[NBR_CARACTERE];					//arbre de huffman

	uint8_t i = 0;


		while(texte[i] != '\0')
		{
			USART2->DR = texte[i];
			while((USART2->SR & USART_SR_TXE) == 0);
			i++;
		}

		printf("hello2\n");
	/*while(1){
		//SYSTICK_Delay(100);
		//GPIOA->ODR ^= 1<<5;
		//printf("Hello\r\n");

	}*/
}
