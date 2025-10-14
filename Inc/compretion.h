#ifndef __COMPRETION_H__
#define __COMPRETION_H__

	#include <stdint.h>
	#include <stdio.h>
	#include "main.h"

	void occurence (uint8_t* chaine, uint32_t tab[NBR_CARACTERE]);
	void creeFeuille(struct noeud* arbre[NBR_CARACTERE], uint32_t tab[NBR_CARACTERE]);
	void afficheTabArbreHuffman(struct noeud * arbre[NBR_CARACTERE]);
#endif
