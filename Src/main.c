#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
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
	USART2_Init();
	SYSTICK_Init();*/

	uint8_t texte[] = "aaaabbbccd";					//texte non compressé
	uint8_t texteCompressé[TAILLE_MAX_COMPRESS];	//text compressé
	uint32_t tabCaractere[NBR_CARACTERE] = {0};				//tableau du nombre d'occurrence de chaque caractère
	uint32_t nbrCaractereTotal = 0;					//nombre de caractère totale dans le texte non compressé
	uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	struct noeud* arbreHffman[NBR_CARACTERE];					//arbre de huffman


	while(1){
		SYSTICK_Delay(100);
		GPIOA->ODR ^= 1<<5;
		printf("Hello\r\n");
	}
}
