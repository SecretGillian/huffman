#include "compretion.h"
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
