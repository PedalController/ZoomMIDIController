#include "Sender.h"
#include "../arduinoUtils/SimuleArduino.h"

#include <stdio.h>

static void log(byte * message, int size);


void Sender::take(void * message, va_list args) {
	byte * midiMessage = (byte*) message;
	int sizeMessage = va_arg(args, int);

	log(midiMessage, sizeMessage);
};


static void log(byte * message, int size) {
	printf("[LOG] Enviando mensagem: Tamanho %d\n", size);
	printf(" > ");
	for (int i=0; i<size; i++) {
		printf("0x%02x ", *(message+i));
		if (i%4 == 3)
			printf("\n   ");
	}
	printf("\n");
}