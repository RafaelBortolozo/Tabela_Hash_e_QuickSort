#include <stdio.h>
#include <stdlib.h>
#define CHAVES 11 
#define QTDCARACTERES 16

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
	char nome[QTDCARACTERES];
}Elemento;

typedef struct sLista{ 
    struct sElemento *head;
    struct sElemento *tail; 
    int size;
}Lista;

Lista *chave[CHAVES];
void criaListas();
void imprimeListas();
int hash(char letra);
void insereElemento(char *nome);

main(){
	criaListas();
	
	FILE *file = fopen("nomes.txt", "r");
	char nome[QTDCARACTERES];
	while(fgets(nome, QTDCARACTERES, file) != NULL){
		insereElemento(nome);
	}

	imprimeListas();
}

void criaListas(){
    for(int i=0; i<CHAVES ;i++){
        chave[i] = (Lista*)malloc(sizeof(Lista));
        chave[i]->head=NULL;
        chave[i]->tail=NULL;
        chave[i]->size=0;
    }
}
	
void imprimeListas(){
	Elemento *aux;
	int total=0;
	//imprime os nomes
	for(int i=0; i<CHAVES; i++){
		aux= chave[i]->head;
		for(int x=0; x<chave[i]->size ;x++){
			printf("%i- %s",i,aux->nome);
			total++;
			aux= aux->next;
		}
		printf("\n\n");
    }

	//imprime o size de cada lista
	for(int i=0; i<CHAVES; i++){
		printf("%i- %i\n\n",i,chave[i]->size);
	}
	printf("total de nomes: %i", total);
}

int hash(char letra){
	int i= letra;
	i= i % CHAVES;
	return i;
}

void insereElemento(char *nome){
	int nHash= hash(nome[0]);
	Elemento *pivo= chave[nHash]->tail;
	
	Elemento *novo_elemento = (Elemento*)malloc(sizeof(Elemento));
    int i=0;
    while(i<QTDCARACTERES){
        novo_elemento->nome[i]= nome[i];
		++i;
    }
	
    if(chave[nHash]->size==0){
        chave[nHash]->head=novo_elemento;
        chave[nHash]->head->prev=NULL;
        chave[nHash]->head->next=NULL;
        chave[nHash]->tail=novo_elemento;
    }else{
        novo_elemento->next=pivo->next;
        novo_elemento->prev=pivo;

        if(pivo->next==NULL){
            chave[nHash]->tail= novo_elemento;
        }else{
            pivo->next->prev=novo_elemento;
        }
        pivo->next=novo_elemento;
    }
    chave[nHash]->size++;
}
