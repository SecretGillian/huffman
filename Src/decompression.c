#include "decompression.h"

void decompress(T_COMPRESS_CHAR* InputBuffer, uint8_t OutputBuffer)
{
	uint8_t EnteteSize = InputBuffer->EnteteSize / sizeof(T_ENTETE);
	T_ENTETE EnteteBuffer[EnteteSize];
	T_ENTETE* CharInfo = InputBuffer->Msg;

	for(uint8_t i = 0 ; i < EnteteSize ; i++)
	{
		EnteteBuffer[i].CaractereInicial = CharInfo[i].CaractereInicial;
		EnteteBuffer[i].CodeSize = CharInfo[i].CodeSize;
		EnteteBuffer[i].Code = CharInfo[i].Code;
	}
}

/**
 * @brief  fontion permetant de triller l'entète les différant caractère en fonction de leur code
 *
 * @param TabEntete est un pointeur vers le tableau de contenant les code des différant caractère
 *
 * @param TabSize représante le nombre de case du tableau de codes
 */
void trieEntete(T_ENTETE* TabEntete, uint8_t TabSize)
{
	uint8_t IndexMin = 0;
	T_ENTETE EnteteBuffer = {.tamponTab = {0}};

	for(uint8_t i = 0 ; i < TabSize ; i++)
	{
		IndexMin = i;
		for(uint8_t j = i ; j < TabSize ; j++)
		{
			if(TabEntete[j].Code < TabEntete[IndexMin].Code)
			{
				IndexMin = j;
			}
		}

		CpyEntete(&EnteteBuffer, &TabEntete[i]);
		CpyEntete(&TabEntete[i], &TabEntete[IndexMin]);
		CpyEntete(&TabEntete[IndexMin], &EnteteBuffer);
	}
}

/**
 * @brief fonction permetant de copier entete2 dans entete1
 *
 * @param entete1 est le pointeur vers la structure dont la valeur va aitre remplacer
 *
 * @param entete2 est le pointeur vers la structure à copier
 */
void CpyEntete(T_ENTETE* entete1, T_ENTETE* entete2)
{
	entete1->CaractereInicial	= entete2->CaractereInicial;
	entete1->CodeSize			= entete2->CodeSize;
	entete1->Code				= entete2->Code;
}
