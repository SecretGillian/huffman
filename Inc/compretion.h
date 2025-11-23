#ifndef __COMPRETION_H__
#define __COMPRETION_H__

	#include <stdint.h>
	#include <stdio.h>
	#include "main.h"

	#define TAILLE_MAX_COMPRESS 500

	typedef union
	{
		uint8_t texteCompresse[TAILLE_MAX_COMPRESS];	//text compressé
		struct
		{
			uint16_t EnteteSize;//taile de l'entête
			uint16_t MsgSize;//taille du fichier compressé
			uint16_t NbrCaractereTotal;//nombre totall de caractère du fichier d'origine
			uint8_t Msg[TAILLE_MAX_COMPRESS - 6/*car 3*16 bite sois 3*2 octet*/];//emplacement pour entrer le reste du message
		};
	}T_COMPRESS_CHAR;

	typedef union
	{
	    uint8_t tamponTab[3];

	    struct
	    {
	        uint8_t CaractereInicial;
	        uint16_t CodeSize : 4;
	        uint16_t Code : 12;
	        // 12+4+8 = 24 | 24/8 = 3
	    };
	}T_ENTETE;

	void occurence (uint8_t* chaine, uint32_t* tab);
	void creeFeuille(struct noeud** arbre, uint32_t* tab);
	struct noeud* InitElement(void);
	void afficheTabArbreHuffman(struct noeud ** arbre);
	void triArbre(struct noeud** arbre);
	void CopyNoeud(struct noeud* noeud1, struct noeud* noeud2);
	void CreeNoeud(struct noeud** arbre);
	void CreeArbre(struct noeud** arbre);
	void parcourirArbre(struct noeud* ptrNoeud, struct noeud** arbre);
	void CreerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille);
	struct noeud* GetAddress(struct noeud* PtrNoeud, uint8_t caractere);
//	struct noeud* GetAddress(struct noeud** arbre, uint8_t caractere);
	void FillOutput(uint8_t* PtrTextOutput, struct noeud* ptrNoeud, uint8_t* PtrTextInput);
//	void FillOutput(uint8_t* PtrTextOutput, struct noeud** arbre, uint8_t* PtrTextInput);
	void FillEntete(T_COMPRESS_CHAR* StructCompress, struct noeud** arbre, uint16_t StrSize);

#endif
