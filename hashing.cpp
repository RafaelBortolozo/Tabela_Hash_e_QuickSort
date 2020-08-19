#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAVES 59
#define QTDCARACTERES 16

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
	char nome[QTDCARACTERES];
    int id;
}Elemento;

typedef struct sLista{ 
    struct sElemento *head;
    struct sElemento *tail; 
    int size;
}Lista;

Lista *criaListas();
void readArquivoTXT(Lista *chave);
void imprimeListas(Lista *chave);
void imprimePesquisa(Elemento *pesquisa);
void imprimeRemove(Elemento *remove);
int hash(char *nome);
int ascii(char letra);
void insereElemento(Lista *chave, char *nome);
Elemento *alocaMemoriaNovo_elemento(Lista *chave,char *nome, int nHash);
Elemento *pesquisaElemento(Lista *chave, char *nome);
void removerElemento(Lista *chave, Elemento *nome);
void ajustarID(Elemento *aux);
void freeElementos(Lista *chave);

void inicializa_quicksort(Lista *chave);
int particiona(Lista *chave, int inicio, int fim, int numChave);
int ordenar_pivo_quicksort(int esquerda,int direita,char *vetPivo,Elemento *elementoDireita,Elemento *elementoEsquerda);
Elemento *troca_pivo_direita(int *esq,int *dir,char *vetPivo, Elemento *elementoDireita, Elemento *elementoEsquerda);
Elemento *troca_pivo_esquerda(int *esq,int *dir,char *vetPivo, Elemento *elementoDireita, Elemento *elementoEsquerda);
void quicksort(Lista *chave, int inicio, int fim, int numChave);

main(){
	Lista *chave= criaListas();
    readArquivoTXT(chave);

	//Pesquisa e remocao de nomes    
        char pesquisar[]="ADALVINO";
		//imprimePesquisa(pesquisaElemento(chave, pesquisar));
        //imprimeRemove(pesquisaElemento(chave, pesquisar));
        //removerElemento(chave, pesquisaElemento(chave, pesquisar));
    //freeElementos(chave);
    //imprimeListas();
    
	//Ordenacao de elementos
	inicializa_quicksort(chave);
	imprimeListas(chave);
}

Lista* criaListas(){
    Lista *vetListas= (Lista*)malloc(CHAVES * sizeof(Lista));
	for(int i=0; i<CHAVES; i++){
        vetListas[i].head=NULL;
        vetListas[i].tail=NULL;
        vetListas[i].size=0;
    }
    return vetListas;
}

void readArquivoTXT(Lista *chave){
    FILE *file = fopen("nomes.txt", "r");
	char nome[QTDCARACTERES];
	while(fgets(nome, QTDCARACTERES, file) != NULL){
		nome[strcspn(nome, "\n")]='\0';
		insereElemento(chave, nome);
	}
    fclose(file);
}

void imprimeListas(Lista *chave){
	Elemento *aux;
	int total=0;
    int i=0;
	//imprime os nomes
	for(int i=0; i<CHAVES; i++){
		aux= chave[i].head;
		
		for(int x=0; x<chave[i].size ;x++){
			printf("[%i]- %i - %s\n",i, aux->id, aux->nome);
			aux= aux->next;
		}
		printf("\n");
    }

	//imprime o size de cada lista
	for(int i=0; i<CHAVES; i++){
		printf("%i\n",chave[i].size);
        total= total + chave[i].size;
	}
	printf("\ntotal de nomes: %i\n", total);
}

void imprimePesquisa(Elemento *pesquisa){
	if(pesquisa!=NULL){
		printf("O nome (%s) foi encontrado na chave[%i]\n", pesquisa->nome, hash(pesquisa->nome));
	}else{
		printf("Nome inexistente\n");
	}
}

void imprimeRemove(Elemento *remove){
	if(remove!=NULL){
		printf("O nome (%s) foi removido da chave[%i]\n", remove->nome, hash(remove->nome));
	}else{
		printf("Nome inexistente\n");
	}
}

int ascii(char letra){
	return letra;
}

int hash(char *nome){
	int x=0;
	for(int i=0; i<strlen(nome) ;i++){
		x= x+ascii(nome[i]);
	}
	x= x % CHAVES;
	return x;
}

void insereElemento(Lista *chave, char *nome){
	int nHash= hash(nome);
	Elemento *pivo= chave[nHash].tail;
	Elemento *novo_elemento= alocaMemoriaNovo_elemento(chave, nome, nHash);
    
	if(chave[nHash].size==0){
        chave[nHash].head=novo_elemento;
        chave[nHash].head->prev=NULL;
        chave[nHash].head->next=NULL;
        chave[nHash].tail=novo_elemento;
    }else{
        novo_elemento->next=pivo->next;
        novo_elemento->prev=pivo;

        if(pivo->next==NULL){
            chave[nHash].tail= novo_elemento;
        }else{
            pivo->next->prev=novo_elemento;
        }
        pivo->next=novo_elemento;
    }
    chave[nHash].size++;
}

Elemento *alocaMemoriaNovo_elemento(Lista *chave,char *nome, int nHash){
	Elemento *novo_elemento = (Elemento*)malloc(sizeof(Elemento));
    novo_elemento->id= chave[nHash].size;
    strcpy(novo_elemento->nome, nome);
	return novo_elemento;
}

Elemento *pesquisaElemento(Lista *chave, char *nome){
    int nHash= hash(nome);
    Elemento *aux= chave[nHash].head;
    for(int x=0; x<chave[nHash].size; x++){
        if(strcmp(aux->nome, nome)==0){
	        return aux;
		}
    	aux=aux->next;
    }
    return NULL;
}

void removerElemento(Lista *chave, Elemento *aux){
	if(aux!=NULL){
		int nHash= hash(aux->nome);
		if(aux==chave[nHash].head){
            chave[nHash].head = aux->next;
            if(chave[nHash].head==NULL){
                chave[nHash].tail=NULL;
            }else{
                aux->next->prev=NULL;
            }
        }else{
            aux->prev->next = aux->next;
            if(aux->next==NULL){
                chave[nHash].tail= aux->prev;
            }else{
                aux->next->prev = aux->prev;
            }
        }
		ajustarID(aux);	
        free(aux);
        chave[nHash].size--;
    }
}

void ajustarID(Elemento *aux){
	Elemento *aux2= aux->next;
    while(aux2 != NULL){
        aux2->id--;
        aux2=aux2->next;
	}
}

void freeElementos(Lista *chave){
    Elemento *aux;
    for(int i=0; i<CHAVES; i++){
		while(chave[i].size>0){
            aux= chave[i].head;
            chave[i].head = aux->next;
            if(chave[i].head==NULL){
                chave[i].tail=NULL;
            }else{
                aux->next->prev=NULL;
            }
            free(aux);
            chave[i].size--;
        }
    }
    free(chave);
}

void inicializa_quicksort(Lista *chave){
    int inicio;
    int fim;
	for(int i=0; i<CHAVES; i++){
    	inicio= 0;
		fim= (chave[i].size-1);
		quicksort(chave, inicio, fim, i);
	}
}

int particiona(Lista *chave, int inicio, int fim, int numChave){
    int esq= inicio;
    int dir= fim;
    char vetPivo[QTDCARACTERES];
	
	Elemento *pesquisa= chave[numChave].head;
	while(pesquisa->id != esq){
		pesquisa= pesquisa->next;
	}
	strcpy(vetPivo, pesquisa->nome);
	
	Elemento* elementoEsquerda= pesquisa;
	Elemento* elementoDireita= chave[numChave].tail;
	while(elementoDireita->id != dir){
		elementoDireita=elementoDireita->prev;
	}
	
	dir= ordenar_pivo_quicksort(esq, dir, vetPivo, elementoDireita, elementoEsquerda);
	return dir;
}

int ordenar_pivo_quicksort(int esquerda,int direita,char *vetPivo,Elemento *elementoDireita,Elemento *elementoEsquerda){
	int *esq= &esquerda; int *dir= &direita;
	
	while(*esq < *dir){
		//compara o pivo com o elemento da DIREITA, ate encontrar alguem MENOR
		while((strcmp(vetPivo, elementoDireita->nome) < 0) && *esq < *dir){
			*dir= *dir-1;
			elementoDireita= elementoDireita->prev;
		}
		//troca os nomes
		elementoEsquerda= troca_pivo_direita(esq, dir, vetPivo, elementoDireita, elementoEsquerda);
		
		//compara o pivo com o elemento da ESQUERDA, ate encontrar alguem MAIOR
		while((strcmp(vetPivo, elementoEsquerda->nome) >= 0) && *esq<*dir){
    		*esq= *esq+1;
    		elementoEsquerda= elementoEsquerda->next;
		}
		//troca os nomes
		elementoDireita= troca_pivo_esquerda(esq, dir, vetPivo, elementoDireita, elementoEsquerda);
	}
	return *dir;
}

Elemento *troca_pivo_direita(int *esq,int *dir,char *vetPivo, Elemento *elementoDireita, Elemento *elementoEsquerda){
	if(*esq < *dir){
		strcpy(elementoEsquerda->nome, elementoDireita->nome);
		strcpy(elementoDireita->nome, vetPivo);
		*esq= *esq+1;
		elementoEsquerda=elementoEsquerda->next;
	}
	return elementoEsquerda;
	
}

Elemento *troca_pivo_esquerda(int *esq,int *dir,char *vetPivo, Elemento *elementoDireita, Elemento *elementoEsquerda){
	if(*esq < *dir){
		strcpy(elementoDireita->nome, elementoEsquerda->nome);
		strcpy(elementoEsquerda->nome, vetPivo);
		*dir= *dir-1;
		elementoDireita=elementoDireita->prev;
	}
	return elementoDireita;
}

void quicksort(Lista *chave, int inicio, int fim, int numChave){
	int pivo;
    if(fim>inicio){
        pivo= particiona(chave, inicio, fim, numChave);
        quicksort(chave, inicio, pivo-1, numChave);
        quicksort(chave, pivo+1, fim, numChave);
    }
}
