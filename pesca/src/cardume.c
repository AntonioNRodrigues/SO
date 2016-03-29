#include <unistd.h>

#include <stdbool.h>
#include <stdlib.h>

#include "cardume.h"
#include "parametros.h"
#include "mundo.h"

#include "semaphore.h"
#include "shared.h"
#include "util.h"

const char *EPS[] = {"NAD", "REP", "PES", "MRT", "FIM"};

Cardume *cardumes;

static bool esta_vivo (int id);
static void apanhado_rede (int id);
static void nadar (int id);
static bool proximo_outro_cardume (int id);
static void reproduzir (int id);

static void iniciar_cardume (Cardume *cardume)
{
	int x, y;
	cardume->estado = P_NADAR;
	cardume->tamanho = TAMANHO_INICIAL_CARDUME;
	do {
		x = random () % DIMENSAO_MAR;
		y = random () % DIMENSAO_MAR;
	} while (mundo->mar [x][y].cardume != VAZIO);
	cardume->posicao.x = x;
	cardume->posicao.y = y;
}

void iniciar_cardumes ()
{

	/* Criar a memória partilhada para os barcos */
	//retorna um discritor de um ficheiro
	int fd = shm_open("/cardume", O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

	if(fd == -1){
		perror("shm");
		exit(1);
	}else{
		printf("Memoria partilhada-->Cardume criada %d\n", fd);
	}

	int ret = ftruncate(fd, (sizeof(cardume) * num_cardumes));
	if (ret == -1){
		perror("shm");
		exit(2);
	}else{
		printf("O espaco-->Cardume foi criado %d\n", ret);

	/* Inicializar a memória partilhada dos barcos */
	int i;

	cardumes = mmap(0, (sizeof(Cardume) * num_cardumes), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);

	if (cardumes==MAP_FAILED){
		perror("shm-mmap");
		exit(3);
	}else{
		printf("O espaço de memoria foi criado e associado ah variavel cardumes");
	}
}

void destruir_cardumes ()
{
	//INSERIR CÓDIGO
}

void imprimir_cardume (FILE *ficheiro, const Cardume *cardume)
{
	fprintf (ficheiro, "%s ", EPS [cardume->estado]);
	if (cardume->estado == P_PESCADO || cardume->estado == P_REPRODUZIR || cardume->estado == P_NADAR)
		fprintf (ficheiro, "%2d%2d", cardume->posicao.x, cardume->posicao.y);
	else
		fprintf (ficheiro, "----");
	fprintf (ficheiro, " %5d", cardume->tamanho);
}

void main_cardume (int id)
{
	while (esta_vivo (id)) {
		apanhado_rede (id);
		nadar (id);
		if (proximo_outro_cardume (id)) {
			reproduzir (id);
		}
	}
}

bool esta_vivo (int id)
{
	return false;
}

void apanhado_rede (int id)
{
}

void nadar (int id)
{
}

bool proximo_outro_cardume (int id)
{
	return false;
}

void reproduzir (int id)
{
}
