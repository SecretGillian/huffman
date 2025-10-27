#ifndef __COMPRETION_H__
#define __COMPRETION_H__

	#include <stdint.h>
	#include <stdio.h>
	#include "main.h"

	void occurence (uint8_t* chaine, uint32_t* tab);
	void creeFeuille(struct noeud** arbre, uint32_t* tab);
	struct noeud* InitElement(void);
	void afficheTabArbreHuffman(struct noeud ** arbre);
	void triArbre(struct noeud** arbre);
	void CopyNoeud(struct noeud* noeud1, struct noeud* noeud2);
#endif
