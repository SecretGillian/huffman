#include "decompression.h"

/**
 * @brief fonction permetant de décompresser le text ressu
 *
 * @param InputBuffer est un pointeur vers la structure contenent le message compresser
 *
 * @param OutputBuffer est un pointeur vers le tableau dans le quel nous stockerons le message decompresser
 *
 * @return -1 si la fonction n'a pas pue reconnetre un caractère. 0 si non
 */
int8_t decompress(T_COMPRESS_CHAR* InputBuffer, uint8_t* OutputBuffer)
{
	uint8_t EnteteSize	= InputBuffer->EnteteSize / sizeof(T_ENTETE);
	T_ENTETE EnteteBuffer[EnteteSize];
	T_ENTETE* CharInfo	= InputBuffer->Msg;
	uint16_t IndexIn	= 0;
	uint8_t CptBit		= 0;
	uint16_t InputChar	= 0;
//	uint8_t OutputBufferTest[TAILLE_MAX_COMPRESS] 		= {0};			//texte decompresser


	for(uint8_t i = 0 ; i < EnteteSize ; i++)
	{
		CpyEntete(&EnteteBuffer[i], &CharInfo[i]);
	}

	trieEntete(EnteteBuffer, EnteteSize);

	for(uint16_t i = 0 ; i < InputBuffer->NbrCaractereTotal ; i ++)
	{
		for(uint8_t j = 0 ; j < EnteteSize ; j++)
		{
//			if(CptBit < 8)
//			{
//				CptBit++;
//			}else
//			{
//				IndexIn++;
//				CptBit = 0;
//			}
//
//			if
//			(
//				((InputBuffer->Msg[InputBuffer->EnteteSize + IndexIn] & (1 << (7 - CptBit)))  !=
//							0)   ==
//				((EnteteBuffer[j].Code & (1 << (EnteteBuffer[j].CodeSize - 1 - DECODE_INDICE(j, EnteteSize)))) !=
//							0)
//			)
//			{
//				OutputBuffer[i] = EnteteBuffer[j].CaractereInicial;
//				CptBit++;
//				break;
//			}
//
//			if(j >= EnteteSize - 1)
//				return -1;
//
//			if(j < EnteteSize - 2)
//				CptBit++;


			for(uint8_t k = 0 ; k < EnteteBuffer[j].CodeSize ; k++)
			{
				if(InputBuffer->Msg[InputBuffer->EnteteSize + IndexIn] & (1 << (7 - CptBit - k)))
				{
					InputChar |= (1 << (EnteteBuffer[j].CodeSize - 1 - k)) ;
				}else
				{
					InputChar &= ~(1 << (EnteteBuffer[j].CodeSize - 1 - k));
				}
			}

			if(InputChar == EnteteBuffer[j].Code)
			{
				OutputBuffer[i] = EnteteBuffer[j].CaractereInicial;

				if(CptBit + EnteteBuffer[j].CodeSize < 8)
				{
					CptBit += EnteteBuffer[j].CodeSize;
				}else
				{
					IndexIn++;
					CptBit = (CptBit + EnteteBuffer[j].CodeSize) % 8;
				}

				break;
			}

			if(j >= EnteteSize - 1)
				return -1;
		}
	}

	return 0;
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
