#∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
#∗ Authon : Paulo Mateus Moura da Silva
#∗ 
#∗ Run in:
#∗ Linux : GNU Make
#∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗/

# Como gerar um makefile simples
# https://aulasdec.wordpress.com/2011/07/28/utilitarios-make-makefiles-e-sua-importancia/
# Pseudo Wildcard recursivo
# http://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make#answer-2483203
# Detecção de sistema operacional
# http://stackoverflow.com/questions/714100/os-detecting-makefile
# Variáveis
# http://www.chemie.fu-berlin.de/chemnet/use/info/make/make_6.html

####################################
# Parâmetros principais
####################################
COMPILADOR = g++ -std=c++0x
NOME_PROGRAMA := MultiEffect

EXTENSAO_WINDOWS = exe
EXTENSAO_LINUX   = e
EXTENSAO_MAC	 = app

####################################
# Configurando programa
####################################
ifeq ($(OS), Windows_NT)
	ARQUITETURA := $(PROCESSOR_ARCHITECTURE)
	EXTENSAO := $(EXTENSAO_WINDOWS)

else
	SYSTEM := $(shell uname -s)

	ifeq ($(SYSTEM), Linux)
		EXTENSAO := $(EXTENSAO_LINUX)
	endif
	ifeq ($(SYSTEM), Darwin)
		EXTENSAO := $(EXTENSAO_MAC)
	endif

	ARQUITETURA := $(shell uname -p)
endif

NOME_PROGRAMA := $(NOME_PROGRAMA)_$(ARQUITETURA).$(EXTENSAO)


####################################
# Compilando e limpando
####################################

# Buscar todas as imagens que possuem... neste diretório
#HEADERS=$(wildcard *.h)
#FONTES=$(wildcard *.c)
#OBJECTS=$(wildcard *.o)

# Buscar todas as imagens que possuem... (recursivo: Neste e em outros subdiretórios)
HEADERS=$(shell find -type f -name '*.h')
FONTES=$(shell find -type f -name '*.c' -o -name "*.cpp")
OBJECTS=$(shell find -type f -name '*.o')

# Para cada arquivo .c encontrado, vai chamar o %.o
all: clean_executable $(FONTES:.cpp=.o) $(NOME_PROGRAMA) clean

$(NOME_PROGRAMA): $(OBJECTS)
	$(COMPILADOR) -o $(NOME_PROGRAMA) $(OBJECTS) -Wall

%.o: %.cpp $(HEADERS)
	$(COMPILADOR) -c $< -o $@ -Wall

clean:
	rm -f $(OBJECTS)

clean_executable:
	-rm -f $(NOME_PROGRAMA)