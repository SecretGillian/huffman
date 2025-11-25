#include <stdlib.h>
#include "compretion.h"

static uint32_t NbrFeuille 	= 0;
uint8_t NbrChar				= 0;

/**
 * @brief fonction permetant de compter le nombre d'occurence de chaque carractère
 *
 * @param chaine est la chaine de carractère à compressé
 * @param tab est le tableau qui stock le nombre d'occurence de chaque carractère
 */
void occurence (uint8_t* chaine, uint32_t* tab)
{
	uint8_t y = 0;



	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)//boucle permetant de parcourire tout les caractère
	{
		y = 0;
		tab[i] = 0;

		while(chaine[y] != '\0')//boucle permetant de vérifier le nombre d'occurence de chaque carractère
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
void creeFeuille(struct noeud** arbre, uint32_t* tab)
{
	for(uint32_t i = 0 ; i < NBR_CARACTERE ; i++)
	{
		if(tab[i] != 0)
		{
			arbre[NbrFeuille]				= InitElement();
			arbre[NbrFeuille]->c			= i;
			arbre[NbrFeuille]->occurence	= tab[i];
			NbrFeuille++;
		}
	}
}


/**
 * @brief fonction permetant de crée et d'initialier un élément de type noeud
 *
 * @return retourne un pointeur vers l'élément créer
 */
struct noeud* InitElement(void)
{
	struct noeud* ElementBuffer = (struct noeud*)malloc(sizeof(struct noeud));

	ElementBuffer->c			= 0;
	ElementBuffer->occurence	= 0;
	ElementBuffer->code			= 0;
	ElementBuffer->tailleCode	= 0;
	ElementBuffer->droite		= NULL;
	ElementBuffer->gauche		= NULL;

	return ElementBuffer;
}


/**
 * @breaf afficheTabArbreHuffman permet d'afficher la totaliter de l'arbre de huffman
 *
 * @param arbre est un tableau de pointeurs vers l'arbre de huffman
 */
void afficheTabArbreHuffman(struct noeud** arbre)
{
	for(uint32_t i = 0 ; i < NbrFeuille ; i++)
	{
		printf("feuille %u :\n\r", i);
		printf("\t c = %c \n \r", arbre[i]->c);
		printf("\t occurence = %u \n \r", arbre[i]->occurence);
	}

	printf("\n\n\n");

	for(uint8_t i = 0 ; i < NbrChar ; i++)
	{
		printf("feuille %u :\n\r", i);
		printf("\t c = %c \n \r", arbre[NBR_CARACTERE - i - 1]->c);
		printf("\t occurence = %u \n \r", arbre[NBR_CARACTERE - i - 1]->occurence);
	}
}


/**
 * @breaf triArbre trie l'arbre de huffman
 *
 * @param arbre est un tableau de pointeurs vers l'arbre de huffman
 */
void triArbre(struct noeud** arbre)
{
	struct noeud CpyArbre;	//tructure de stockage
	uint32_t IndexMax = 0;	//indice du carractère avec le plus d'occurence

	for(uint32_t i = 0 ; i < NbrFeuille - 1 ; i++)	//boucle permetant de parcourire l'arbre de huffman
	{
		IndexMax = i;
		for(uint32_t j = i ; j < NbrFeuille ; j++)	//boucle permetant de sélectioner le carractère avec le plus grad nombre occurence à chaque itération

		{
			if(arbre[j]->occurence > arbre[IndexMax]->occurence)
			{
				IndexMax = j;
			}
		}

		CopyNoeud(arbre[i], &CpyArbre);
		CopyNoeud(arbre[IndexMax], arbre[i]);
		CopyNoeud(&CpyArbre, arbre[IndexMax]);
	}
}


/**
 * @breaf CopyNoeud copie la structure noeud1 dans la structure noeud2
 *
 * @param noeud1 est le noeud ou la feuille à copier
 *
 * @param noeud2 est le noeud ou la feuille dont on écrase la valeur
 */
void CopyNoeud(struct noeud* noeud1, struct noeud* noeud2)
{
	noeud2->c			= noeud1->c;
	noeud2->occurence	= noeud1->occurence;
	noeud2->code		= noeud1->code;
	noeud2->tailleCode	= noeud1->tailleCode;
	noeud2->gauche		= noeud1->gauche;
	noeud2->droite		= noeud1->droite;
}


/**
 * @brief fonction permetant de réunire les deux dernier élément de l'arbre de huffman
 *
 * @param arbre est un tableau de pointeurs vers l'arbre de huffman
 */
void CreeNoeud(struct noeud** arbre)
{
	struct noeud* ElementBuffer = InitElement();//création d'un nouvelle élément de type noeud

	ElementBuffer->c = '!';
	ElementBuffer->occurence	= arbre[NbrFeuille - 1]->occurence + arbre[NbrFeuille - 2]->occurence;
	ElementBuffer->gauche		= arbre[NbrFeuille - 1];
	ElementBuffer->droite		= arbre[NbrFeuille - 2];
	arbre[NbrFeuille - 2]		= ElementBuffer;
	NbrFeuille--;
}


/**
 * @brief fonction permetant de crée l'arbre de huffman
 *
 * @param arbre est un tableau de pointeurs vers l'arbre de huffman
 */
void CreeArbre(struct noeud** arbre)
{
	while(NbrFeuille > 1)
	{
		triArbre(arbre);
		CreeNoeud(arbre);
	}
}


/**
 * @brief fonction permetant de parcourire l'arbre de huffman
 *
 * @param ptrNoeud est un pointeurs vers la racine de l'arbre de huffman
 *
 * @param arbre est un tableau de pointeurs vers l'arbre de huffman
 */
void parcourirArbre(struct noeud* ptrNoeud, struct noeud** arbre)
{
	if(ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL)
	{
		printf("je suis une feuille\n\r\tc:%c\n\r", ptrNoeud->c);
		arbre[NBR_CARACTERE - NbrChar - 1] = ptrNoeud;//réorganisation pour faciliter leur récupération
		NbrChar++;//incrémente un compteur pour connaitre le nombre de caractère
	}else
	{
		printf("je suis un neud\n\r");
		parcourirArbre(ptrNoeud->gauche, arbre);//on va à gauche
		parcourirArbre(ptrNoeud->droite, arbre);//on va à droite
	}
}

/**
 * @brief fonction permetant de parcourire l'arbre de huffman et de crée le code de chaque carractère
 *
 * @param ptrNoeud est un pointeurs vers la racine de l'arbre de huffman
 *
 * @param code permet de rensaigner le code du caractère
 *
 * @param taille permet de rensaigner la taille du code
 */
void CreerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille)
{
	if(ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL)
	{
		ptrNoeud->tailleCode	= taille;
		ptrNoeud->code			= code;
		printf("%c \t code : %d \t taille : %d \n\r", ptrNoeud->c, ptrNoeud->code, ptrNoeud->tailleCode);
	}else
	{
		printf("je suis un neud\n\r");
		CreerCode(ptrNoeud->gauche, (code << 1), taille+1);//on va à gauche(on injecte un 0 à droite dans le code)
		CreerCode(ptrNoeud->droite, (code << 1) + 1, taille+1);//on va à droite(on injecte un 1 à droite dans le code)
	}
}

/**
 * @brief fonction permetant de retourner l'adresse de la structure corespondant au caractère ransaigner
 *
 * @param ptrNoeud est un pointeur vers la racine de l'arbre de huffman
 *
 * @param caractere permet de resegner le caractère que l'on recherche
 */
struct noeud* GetAddress(struct noeud* ptrNoeud, uint8_t caractere)
{
	struct noeud* ElementBuffer = NULL;

	if(ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL)
	{
		if(ptrNoeud->c == caractere)
		{
			return ptrNoeud;
		}

		return NULL;
	}else
	{
		ElementBuffer = GetAddress(ptrNoeud->gauche, caractere);//on va à gauche
		if(ElementBuffer != NULL)
		{
			return ElementBuffer;
		}

		ElementBuffer = GetAddress(ptrNoeud->droite, caractere);//on va à droite
		if(ElementBuffer != NULL)
		{
			return ElementBuffer;
		}

		return NULL;
	}
}

//struct noeud* GetAddress(struct noeud** arbre, uint8_t caractere)
//{
//	for(uint8_t i = 0 ; i < NbrChar ; i++)
//	{
//		if(arbre[NBR_CARACTERE - i - 1]->c == caractere)
//			return arbre[i];
//	}
//	return NULL;
//}


/**
 * @brief rempli le buffer de sorti
 *
 * @param PtrOutputVal est le pinteur vers le tableau où est stocké le text compressé
 *
 * @param PtrNoeud est un pointeurs vers la racine de l'arbre de huffman
 *
 * @param PtrTextInput est un pointeurs vers la chaine de caractère d'entré
 */
void FillOutput(uint8_t* PtrTextOutput, struct noeud* ptrNoeud, uint8_t* PtrTextInput)
{
	uint8_t CptBit						= 0;
	uint16_t IndexIn					= 0;
	uint16_t IndexOut					= 0;
	struct noeud* ElementBuffer			= NULL;
	const uint8_t EnteteStructSize		= sizeof(T_ENTETE);
//	uint8_t new 						= 1;

	while(PtrTextInput[IndexIn] != '\0')//parcoure le text d'entée
	{
		ElementBuffer = GetAddress(ptrNoeud, PtrTextInput[IndexIn]);//récupère les information du caractère

		for(uint8_t i = 0 ; i < ElementBuffer->tailleCode ; i++)
		{
			if(CptBit >= 8)//vérifi si on a dépasser la taille de la case actuel
			{
				IndexOut++;
				CptBit = 0;
			}
			if(ElementBuffer->code & (1 << (ElementBuffer->tailleCode - 1 - i)))
			{
				PtrTextOutput[IndexOut + EnteteStructSize * NbrChar] |= (1 << (7 - CptBit));
				printf("1\n\r");
			}else
			{
				PtrTextOutput[IndexOut + EnteteStructSize * NbrChar] &= ~(1 << (7 - CptBit));
				printf("0\n\r");
			}

			CptBit++;
		}

		IndexIn++;
	}
}

//void FillOutput(uint8_t* PtrTextOutput, struct noeud** arbre, uint8_t* PtrTextInput)
//{
//	uint8_t CptBit						= 0;
//	uint16_t IndexIn					= 0;
//	uint16_t IndexOut					= 0;
//	struct noeud* ElementBuffer			= NULL;
////	uint8_t new 						= 1;
//
//	while(PtrTextInput[IndexIn] != '\0')//parcoure le text d'entée
//	{
//		ElementBuffer = GetAddress(arbre, PtrTextInput[IndexIn]);//récupère les information du caractère
//
//		for(uint8_t i = 0 ; i < ElementBuffer->tailleCode ; i++)
//		{
//			if(CptBit >= 8)//vérifi si on a dépasser la taille de la case actuel
//			{
//				IndexOut++;
//				CptBit = 0;
//			}
//			if(ElementBuffer->code & (1 << (ElementBuffer->tailleCode - 1 - i)))
//			{
//				PtrTextOutput[IndexOut] |= (1 << (7 - CptBit));
//				printf("1\n\r");
//			}else
//			{
//				PtrTextOutput[IndexOut] &= ~(1 << (7 - CptBit));
//				printf("0\n\r");
//			}
//
//			CptBit++;
//		}
//
//		IndexIn++;
//	}
//}


/**
 * @brief rempli l'entète du message
 *
 * @param StructCompress est un pointeur vers l'union représentant le buffer de sorti
 *
 * @param arbre est un tableau de pointeurs vers l'arbre de huffman
 *
 * @param StrSize est le nombre de caratère contenu dans le message à compresser
 */
void FillEntete(T_COMPRESS_CHAR* StructCompress, struct noeud** arbre, uint16_t StrSize)
{
	uint8_t EnteteStructSize	= sizeof(T_ENTETE);
	T_ENTETE* CharInfo 			= /*(T_ENTETE*)*/StructCompress->Msg;


	StructCompress->EnteteSize			= EnteteStructSize * NbrChar;//0x1122;
	StructCompress->MsgSize				= 6 + StructCompress->EnteteSize + StrSize;//0x3344;
	StructCompress->NbrCaractereTotal	= StrSize;//0x5566;

	//création de la parti de l'entète permetant le décodage en bougent un pointeur de type T_ENTETE
	for(uint8_t i = 0 ; i < NbrChar ; i++)
	{
		CharInfo[i].CaractereInicial	= arbre[NBR_CARACTERE - i - 1]->c;//0xAA;
		CharInfo[i].CodeSize			= arbre[NBR_CARACTERE - i - 1]->tailleCode;//0b1100;
		CharInfo[i].Code				= arbre[NBR_CARACTERE - i - 1]->code;//0b111000111000;
	}
	printf("test union : %0X\n\r", CharInfo[0].Code);
}
