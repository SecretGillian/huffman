#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "compretion.h"

uint32_t NbrFeuille = 0;

int main(void)
{
	/*FPU_Init();
	GPIO_Init();
	SYSTICK_Init();*/
	USART2_Init();

	uint8_t texte[] = "aaaaabbcccd";					//texte non compressé
	//uint8_t texteCompressé[TAILLE_MAX_COMPRESS];	//text compressé
	uint32_t tabCaractere[NBR_CARACTERE] = {0};				//tableau du nombre d'occurrence de chaque caractère
	//uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereTotal = 0;					//nombre de caractère totale dans le texte non compressé
	struct noeud* arbreHffman[NBR_CARACTERE] = {NULL};					//arbre de huffman

	printf("start occurence\n\r");
	occurence(texte, tabCaractere);
	printf("end occurence\n\r");
	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)
	{
		if(tabCaractere[i])
		{
			printf("%c = %u \n\r", i, tabCaractere[i]);
		}
	}

	printf("start creeFeuille\n\r");
	creeFeuille(arbreHffman, tabCaractere);
	printf("end creeFeuille\n\r");

	afficheTabArbreHuffman(arbreHffman);

	printf("start trie\n\r");
	triArbre(arbreHffman);
	printf("end trie\n\r");

	afficheTabArbreHuffman(arbreHffman);

	while(1);

	//}
}
