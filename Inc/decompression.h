#ifndef __DECOMPRESSION_H__
#define __DECOMPRESSION_H__

	#include "compretion.h"

	void CpyEntete(T_ENTETE* entete1, T_ENTETE* entete2);
	void trieEntete(T_ENTETE* TabEntete, uint8_t TabSize);
	void decompress(T_COMPRESS_CHAR* InputBuffer, uint8_t OutputBuffer);

#endif
