#include <stdlib.h>
#include "compretion.h"

extern uint32_t NbrFeuille;

/**
 * @brief fonction permetant de compter le nombre d'occurence de chaque carractère
 *
 * @param chaine est la chaine de carractère à compressé
 * @param tab est le tableau qui stock le nombre d'occurence de chaque carractère
 */
void occurence (uint8_t* chaine, uint32_t tab[NBR_CARACTERE])
{
	uint8_t y = 0;



	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)
	{
		y = 0;
		tab[i] = 0;

		while(chaine[y] != '\0')
		{
			if(chaine[y] == i)
			{
				tab[i]++;
			}

			y++;
		}
	}
}


/**
 * @brief fonction permetant d'initialiser l'arbre de huffman
 *
 * @param arbre est un tableau de pointeur afin de stocker les feuille de l'arbre crée
 *
 * @param tab est les nombre d'itération de chaque caractère
 */
void creeFeuille(struct noeud* arbre[NBR_CARACTERE], uint32_t tab[NBR_CARACTERE])
{
	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)
	{
		if(tab[i] != 0)
		{
			arbre[NbrFeuille] = (struct noeud*)malloc(sizeof(struct noeud));
			arbre[NbrFeuille]->c = i;
			arbre[NbrFeuille]->occurence = tab[i];
			arbre[NbrFeuille]->code = 0;
			arbre[NbrFeuille]->tailleCode = 0;
			arbre[NbrFeuille]->droite = NULL;
			arbre[NbrFeuille]->gauche = NULL;
			NbrFeuille++;
		}
	}
}


/**
 * @breaf afficheTabArbreHuffman permet d'afficher la totaliter de l'arbre de huffman
 *
 * @param arbre pointeur vers l'arbre de huffman
 */
void afficheTabArbreHuffman(struct noeud* arbre[NBR_CARACTERE])
{
	for(uint32_t i = 0 ; i < NbrFeuille ; i++)
	{
		printf("feuille %u :\n\r", i);
		printf("\t c = %c \n \r", arbre[i]->c);
		printf("\t occurence = %u \n \r", arbre[i]->occurence);
	}
}
