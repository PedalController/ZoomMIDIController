//
//   ZOOM G3 Pedal State Change using MIDI over USB
//           (c)2013, Paulo Mateus
//            mateus.moura@hotmail.com
//
// Library Used:
// https://github.com/YuuichiAkagawa/USBH_MIDI
// Basede in:
// https://github.com/vegos/ArduinoMIDI

//http://blog.petrockblock.com/2012/05/19/usb-keyboard-with-arduino-and-v-usb-library-an-example/
//http://labdegaragem.com/profiles/blogs/tutorial-conhe-a-o-conversor-usb-serial-ft232rl
//http://vusb.wikidot.com/hardware

// Midi
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-midi-output-using-an-arduino/
//https://github.com/FortySevenEffects/arduino_midi_library
//http://shiftmore.blogspot.com.br/2010/01/quick-and-dirty-arduino-midi-over-usb.html
//http://forum.arduino.cc/index.php?topic=22336.0
//http://moddersandrockers.com/littlebits/2.php

//http://www.embarcados.com.br/arduino-comunicacao-serial/
/*
O sinal de comunicação na placa Arduino UNO, é um sinal TTL de 5V.
Para comunicação com um computador ou outro dispositivo que não tenha
o mesmo nível de tensão é necessário um conversor de nível.
Existem várias opções de conversores, como por exemplo TTL/ RS232,
TTL/RS485, TTL/USB, entre outros.
*/

//http://arduino.cc/en/reference/serial
/*
To use these pins to communicate with your personal computer,
you will need an additional USB-to-serial adaptor, as they
are not connected to the Mega's USB-to-serial adaptor. 
*/


// C++
//http://liveblue.files.wordpress.com/2009/07/treinamento_standard_c.pdf
//http://www-usr.inf.ufsm.br/~pozzer/disciplinas/cg_5_oo_c++.pdf

#include <iostream>
#include "lib/multiEffect/ZoomGSeries.h"
#include "lib/comunicator/ZoomGSeriesComunicator.h"
#include "lib/pedalComunication/Sender.h"
#include "lib/dao/MultiEffectDao.h"

#include "lib/arduinoUtils/SimuleArduino.h"

#define TOTAL_PEDALS 3

/////////////////////////////////////////////////////////////////////////////////////
// Button.c
/////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream &stream, Button& button) {
	std::string retorno("");

	if (button.isActived())
		retorno += "Actived";
	else
		retorno += "Disabled";

	return stream << retorno;
}

std::ostream& operator<<(std::ostream &stream, Pedal pedal) {
	//return stream << ((Button) pedal);
	std::string retorno("");

	if (pedal.isActived())
		retorno += "Actived";
	else
		retorno += "Disabled";

	return stream << retorno;
}

/////////////////////////////////////////////////////////////////////////////////////
// MultiEffect.c
/////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream &stream, MultiEffect& multiStomp) {
	std::string retorno("");
	std::string currentPatch = std::to_string(((unsigned int) multiStomp.getCurrentPatch()));
	std::string maxPatch     = std::to_string(((unsigned int) multiStomp.getTotalPatch()));

	retorno += "MultiEffect\n";
	retorno += " - Current Patch: " + currentPatch + "\n";
	retorno += " - Max Patch: " + maxPatch + "\n";
	retorno += " Effects:\n";
	
	int count=0;
	for (Pedal& pedal: *multiStomp.getPedals()) {
        //retorno += "  " + std::to_string(count) + " - " << pedal + "\n";
		retorno += "  " + std::to_string(pedal.getPosition()) + " - ";
		retorno += pedal.isActived() ? "Actived" : "Disabled";
		retorno += " (Pin " + std::to_string(pedal.getPin()->getPin()) + ")";
		retorno += "\n";
		count++;
	}

	return stream << retorno;
}

/////////////////////////////////////////////////////////////////////////////////////
// Button.c
/////////////////////////////////////////////////////////////////////////////////////
void Button::update() {
	int currentState = digitalRead(this->pin->getPin());

	if (this->state != currentState) {
		this->setState(currentState);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// Main.cpp
/////////////////////////////////////////////////////////////////////////////////////
MultiEffectComunicator * comunicator;

MultiEffect * zoom;
std::list<Button *> buttons;

void setup() {
	// Initialize MultiStomp
	Pin * firstPin = new Pin(0x03);
  	zoom = new ZoomGSeries(TOTAL_PEDALS, *firstPin);

	// Get all components to verific an change
	buttons = zoom->getAllButtons();

	// Inicialize the Comunicator
	comunicator = new ZoomGSeriesComunicator(zoom, new Sender());
}

void loop() {
	// Verif any button state change
	for (Button* button: buttons)
        button->update();
}


/////////////////////////////////////////////////////////////////////////////////////
// Para poder testar
/////////////////////////////////////////////////////////////////////////////////////
void test() {
	std::cout << *zoom;

	zoom->beforePatch();
	std::cout << *zoom;

	zoom->toPatch(99);
	std::cout << *zoom;
	zoom->nextPatch();
	std::cout << *zoom;
}

int main() {
	setup();

	std::cout << "=========================================\n";
	std::cout << "Inicializando\n";
	std::cout << "=========================================\n";
	test();

	std::cout << "=========================================\n";
	std::cout << "Execução\n";
	std::cout << "=========================================\n";
	while (true) {
		loop();
		break;
	}

	std::cout << "=========================================\n";
	std::cout << "Após execução\n";
	std::cout << "=========================================\n";
	test();

	MultiEffectDao::save(zoom);
	
	MultiEffect * testador = MultiEffectDao::load();
	std::cout << std::to_string(testador->getCurrentPatch()) + "___\n";
	return 0;
}