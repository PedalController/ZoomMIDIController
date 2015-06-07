#include <stdio.h>
#include <stdlib.h>
#include "MultiEffectDao.h"

/******************************
 * Read
 ******************************/
static void loadMultiStompStuct(MultiEffectTableStruct * multiStomp);

MultiEffect * MultiEffectDao::load() {
	MultiEffectTableStruct multiStompStruct;
	loadMultiStompStuct(&multiStompStruct);

	MultiEffect * multiStomp = NULL;
	MultiEffectDao::loadMultiEffect(multiStomp, &multiStompStruct);

	return multiStomp;
}

void MultiEffectDao::loadMultiEffect(MultiEffect * multiStomp, MultiEffectTableStruct * multiStompStruct) {
	Pin * firstPin = new Pin(multiStompStruct->firstPin);

	multiStomp = new MultiEffect(
		multiStompStruct->totalPatch,
		multiStompStruct->totalPedals,
		*firstPin
	);

	multiStomp->toPatchNotNotify(multiStompStruct->currentPatch);
}

static void loadMultiStompStuct(MultiEffectTableStruct * const multiStomp) {
	FILE * file = fopen("save.txt", "rb");
	fread(multiStomp, sizeof(MultiEffectTableStruct), 1, file);
	fclose(file);
}

/******************************
 * Save
 ******************************/
void MultiEffectDao::save(MultiEffect * multiStomp) {
	std::list<Pedal> * pedals = multiStomp->getPedals();
	int totalPedals = pedals->size();

	unsigned int sizeMultiStomp = sizeof(MultiEffectTableStruct);
	unsigned int sizePedals = sizeof(PedalTableStruct) * totalPedals;

	MultiEffectTableStruct * multiStompToSave = (MultiEffectTableStruct*) malloc(sizeMultiStomp);
	PedalTableStruct * pedalsToSave = (PedalTableStruct*) malloc(sizePedals);

	MultiEffectDao::convertMultiEffect(multiStomp, multiStompToSave);
	MultiEffectDao::convertPedals(pedals, pedalsToSave);

	//arquivo errado
	FILE * file = fopen("save.txt", "wb");
	fwrite(multiStompToSave, sizeMultiStomp, 1, file);
	//fwrite(file, *pedalsToSave, totalPedals);

	//super saveStructs(multiStompToSave, sizeof(*multiStompToSave))
	//super saveStructs(cada pedal)
	fclose(file);
	//fim de arquivo errado

	free(multiStompToSave);
	free(pedalsToSave);
}

void MultiEffectDao::convertMultiEffect(MultiEffect * multiStomp, MultiEffectTableStruct * multiStompStruct) {
	multiStompStruct->totalPatch = multiStomp->getTotalPatch();
	multiStompStruct->currentPatch = multiStomp->getCurrentPatch();
	
	std::list<Pedal> * pedals = multiStomp->getPedals();
	Pedal pedal = pedals->front();

	multiStompStruct->firstPin = pedal.getPin()->getPin();
	multiStompStruct->totalPedals = pedals->size();

	printf("Current Patch: %d\n", multiStompStruct->currentPatch);
	printf("Total Patch: %d\n",   multiStompStruct->totalPatch);
	printf("Total Pedals: %d\n",  multiStompStruct->totalPedals);
	printf("FirstPin: 0x%02x\n",  multiStompStruct->firstPin);
}

/** Convert the 'MultiEffect std::list<Pedal>' of 'Pedal's in
 *  an vector list of 'PedalTableStruct's and put in
 *  '@param pedals'
 */
void MultiEffectDao::convertPedals(std::list<Pedal> * pedals, PedalTableStruct * pedalsStruct) {
	int i = 0;
	for (Pedal pedal: *pedals) {
		MultiEffectDao::convertPedal(&pedal, pedalsStruct+i);
		i++;
	}
}

/** Convert an 'Pedal' in 'PedalTableStruct'
 */
void MultiEffectDao::convertPedal(Pedal * pedal, PedalTableStruct * pedalStruct) {
	pedalStruct->isActived = pedal->isActived();
	pedalStruct->isButtonActived = pedalStruct->isActived; // Fixme - Read in arduino!
}