//http://sourcemaking.com/design_patterns/observer/cpp/3

#ifndef _Comunicator_INCLUDED__
#define _Comunicator_INCLUDED__

#include <cstdarg>
#include "../utils/Subject.h"
#include "Destination.h"

class Destination;

/** 
 *  Responsável por tratar (processar) qualquer notificação do 'subject'
 *  e notificar o 'destination' enviando os dados processados.
 *  
 *
 *  Comunicator comunica uma mudança do 'subject' para o 'destination'.
 *  A difereça do padrão de projeto Observer, é que comunicator
 *  prepara o subject e notifica o destination com a informação já
 *  tratada, do jeito que este espera receber.
 *
 *  Ou seja, Comunicator processa a informação.
 *
 *  Você pode também trocar, em tempo de compilação o tipo de processamento
 *  utilizando outro Comunicator
 *
 *  Resumindo, ele é uma mistura do Observer e Suject do 
 *  design pattern Observer
 */
class Comunicator : public Observer {
	public:
		Comunicator(Subject * subject, Destination * destination);

	protected:
		virtual void notify(void * message, ...) final;

	private:
		Destination * destination;

};

#endif