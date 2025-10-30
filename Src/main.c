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



int main(void)
{
	/*FPU_Init();
	GPIO_Init();
	SYSTICK_Init();*/
	USART2_Init();

	uint8_t texte[] = "aaaabbbccd";					//texte non compressé
	//uint8_t texteCompressé[TAILLE_MAX_COMPRESS];	//text compressé
	uint32_t tabCaractere[NBR_CARACTERE] = {0};				//tableau du nombre d'occurrence de chaque caractère
	//uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereDifferent = 0;				//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereTotal = 0;					//nombre de caractère totale dans le texte non compressé
	struct noeud* arbreHffman[NBR_CARACTERE] = {NULL};					//arbre de huffman
	uint32_t code = 0;
	uint32_t taille = 0;

	printf("start occurence\n\r");
	occurence(texte, tabCaractere);
	printf("end occurence\n\r");

	printf("\n\n\n");

	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)
	{
		if(tabCaractere[i])
		{
			printf("%c = %u \n\r", i, tabCaractere[i]);
		}
	}

	printf("\n\n\n");

	printf("start creeFeuille\n\r");
	creeFeuille(arbreHffman, tabCaractere);
	printf("end creeFeuille\n\r");

	printf("\n\n\n");

	afficheTabArbreHuffman(arbreHffman);

	printf("\n\n\n");

	printf("start trie\n\r");
	triArbre(arbreHffman);
	printf("end trie\n\r");

	printf("\n\n\n");

	afficheTabArbreHuffman(arbreHffman);

	printf("\n\n\n");

	printf("strat création neud\n\r");
	CreeArbre(arbreHffman);
	printf("end création neud\n\r");

	printf("\n\n\n");

	afficheTabArbreHuffman(arbreHffman);

	printf("\n\n\n");

	parcourirArbre(arbreHffman[0]);

	printf("\n\n\n");

	CreerCode(arbreHffman[0], code, taille);

	while(1);

	//}
}
