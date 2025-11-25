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
#include "decompression.h"

extern uint8_t const NbrChar;

int main(void)
{
	/*FPU_Init();
	GPIO_Init();
	SYSTICK_Init();*/
	USART2_Init();

	uint8_t texte[] 									= "aaaabbbccd";	//texte non compressé
	T_COMPRESS_CHAR texteCompresse = {.texteCompresse	= {0}};			//texte compressé
	uint32_t tabCaractere[NBR_CARACTERE] 				= {0};			//tableau du nombre d'occurrence de chaque caractère
	//uint32_t nbrCaractereDifferent = 0;								//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereDifferent = 0;								//nombre de caractère différent dans le texte nnon comprésé
	//uint32_t nbrCaractereTotal = 0;									//nombre de caractère totale dans le texte non compressé
	struct noeud* arbreHuffman[NBR_CARACTERE] 			= {NULL};		//arbre de huffman
	//variable permetant de
	uint32_t code 										= 0;
	uint32_t taille 									= 0;
	uint8_t TextDecompress[TAILLE_MAX_COMPRESS] 		= {0};			//texte decompresser
	int8_t ValReturn 									= 0;			//valeur de retour de la fonction de décompression

	printf("------------------------------------------start occurence\n\r");
	occurence(texte, tabCaractere);

	printf("\n\n\n");

	//affiche les caractère présant dans le text et leurs nombre d'occurance
	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)
	{
		if(tabCaractere[i])
		{
			printf("%c = %u \n\r", i, tabCaractere[i]);
		}
	}
	printf("---------------------end occurence\n\r");

	printf("\n\n\n");

	printf("---------------------start creeFeuille\n\r");
	creeFeuille(arbreHuffman, tabCaractere);

	afficheTabArbreHuffman(arbreHuffman);
	printf("---------------------end creeFeuille\n\r");

	printf("\n\n\n");

	printf("---------------------start triArbre\n\r");
	triArbre(arbreHuffman);

	afficheTabArbreHuffman(arbreHuffman);
	printf("---------------------end triArbre\n\r");

	printf("\n\n\n");

	printf("---------------------start CreeArbre\n\r");
	CreeArbre(arbreHuffman);

	printf("\n\n\n");

	afficheTabArbreHuffman(arbreHuffman);
	printf("---------------------end CreeArbre\n\r");

	printf("\n\n\n");

	printf("---------------------start parcourirArbre\n\r");
	parcourirArbre(arbreHuffman[0], arbreHuffman);

	afficheTabArbreHuffman(arbreHuffman);
	printf("---------------------end parcourirArbre\n\r");

	printf("\n\n\n");

	printf("---------------------start CreerCode\n\r");
	CreerCode(arbreHuffman[0], code, taille);
	printf("---------------------end CreerCode\n\r");

	printf("\n\n\n");

	printf("---------------------start GetAddress\n\r");
	arbreHuffman[NBR_CARACTERE - NbrChar - 1] = GetAddress(arbreHuffman[0], 'c');
	printf("%c \t code : %d \t taille : %d \n\r", arbreHuffman[NBR_CARACTERE - 1]->c, arbreHuffman[NBR_CARACTERE - 1]->code, arbreHuffman[NBR_CARACTERE - 1]->tailleCode);
	printf("---------------------end GetAddress\n\r");

	printf("\n\n\n");

	printf("---------------------start FillOutput\n\r");
	FillOutput(texteCompresse.Msg, arbreHuffman[0], texte);

	printf("---------------------start FillEntete\n\r");
	FillEntete(&texteCompresse, arbreHuffman, strlen(/*(char*)*/texte));
//	uint8_t i = 0;
//	while(texteCompresse.texteCompresse[i] != '\0')
//	{
//		printf("OutVal : %p\n\r", texteCompresse.texteCompresse[i]);
//		i++;
//	}

	printf("\n\n\n");

	for(uint16_t i = 0 ; i < TAILLE_MAX_COMPRESS / 2 ; i++)
	{
		printf("%d : "BYTE_TO_BINARY_PATTERN" | %02X \n\r", i, BYTE_TO_BINARY(texteCompresse.texteCompresse[i]), texteCompresse.texteCompresse[i]);
	}

	printf("---------------------end FillOutput\n\r");

	printf("\n\n\n");

	printf("---------------------start trieEntete\n\r");
	T_ENTETE TestEntete[NbrChar];
	T_ENTETE* PtrTestEntete = /*(T_ENTETE*)*/texteCompresse.Msg;

	for(uint8_t i = 0 ; i < NbrChar ; i++)
	{
		CpyEntete(&TestEntete[i], &PtrTestEntete[i]);
	}

	trieEntete(TestEntete, NbrChar);

	for(uint8_t i = 0 ; i < NbrChar ; i++)
	{
		printf("case %d : \n\r \t caractère : %c \n\r taille code : %d \n\r code : "BYTE_TO_BINARY_PATTERN"\n\r", i, TestEntete[i].CaractereInicial, TestEntete[i].CodeSize, BYTE_TO_BINARY(TestEntete[i].Code));
	}
	printf("---------------------end trieEntete\n\r");

	printf("\n\n\n");

	printf("---------------------start decompress\n\r");
	ValReturn = decompress(&texteCompresse, TextDecompress);

	printf("test fonction : %i \n\r", ValReturn);
//	for(uint16_t i = 0 ; i < TAILLE_MAX_COMPRESS / 2 ; i++)
//	{
//		printf("c : %02X \n\r", TextDecompress[i]);
//	}
	printf("%s \n\r", TextDecompress);

	while(1);

	//}
}
