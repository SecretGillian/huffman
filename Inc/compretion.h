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
	void CreeNoeud(struct noeud** arbre);
	void CreeArbre(struct noeud** arbre);
	void parcourirArbre(struct noeud* ptrNoeud);
	void CreerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille);
	struct noeud* GetAddress(struct noeud* PtrNoeud, uint8_t caractere);
	void FillOutput(uint8_t* PtrTextOutput, struct noeud* ptrNoeud, uint8_t* PtrTextInput);

	#define TAILLE_MAX_COMPRESS 500

	typedef union
	{
		uint8_t texteCompresse[TAILLE_MAX_COMPRESS];	//text compressé
		struct
		{
			uint16_t EnteteSize;
			uint16_t MsgSize;
			uint16_t NbrCaractereTotal;
			uint8_t Msg[TAILLE_MAX_COMPRESS - 6/*car 3*16 bite sois 3*2 octet*/];
		};
	}T_ENTETE;

#endif
