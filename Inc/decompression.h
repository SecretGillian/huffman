#ifndef __DECOMPRESSION_H__
#define __DECOMPRESSION_H__

	#include "compretion.h"

	#define DECODE_INDICE(j, NbrMax)	(j < NbrMax) ? j : j - 1

	void CpyEntete(T_ENTETE* entete1, T_ENTETE* entete2);
	void trieEntete(T_ENTETE* TabEntete, uint8_t TabSize);
	int8_t decompress(T_COMPRESS_CHAR* InputBuffer, uint8_t* OutputBuffer);

#endif
