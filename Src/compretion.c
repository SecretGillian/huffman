#include "compretion.h"
#include "main.h"

void occurence (uint8_t* chaine, uint32_t tab[NBR_CARACTERE])
{
	uint8_t y = 0;



	for(uint8_t i = 0 ; i < NBR_CARACTERE ; i++)
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
