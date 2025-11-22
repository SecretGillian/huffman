
#ifndef MAIN_H_
#define MAIN_H_

	#define INPUT_MODE 	0
	#define OUTPUT_MODE	1
	#define ALT_MODE 	2
	#define ANALOG_MODE	3

	#define BITMASK_1BITS	0b1
	#define BITMASK_2BITS	0b11
	#define BITMASK_3BITS	0b111
	#define BITMASK_4BITS	0b1111
	#define BITMASK_5BITS	0b11111

	#define NBR_CARACTERE		256

	struct noeud
	{
		uint8_t c;						//carractère initial
		uint32_t occurence;				//nombre d'occurences
		uint32_t code;					//conde binaire dans l'arbre
		uint32_t tailleCode;			//nombre de bits du code
		struct noeud *gauche, *droite;	//lien vers les neuds suivants
	};

#endif
