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
void readArquivoTXT();
void imprimeListas();
int hash(char letra);
void insereElemento(char *nome);
int qtdCaracteres(char *nome);
void pesquisaElemento(char *nome);
void removerElemento(char *nome);
void freeElementos();

main(){
	criaListas();
    readArquivoTXT();

	imprimeListas();
	//Pesquisa e remocao de nomes    
        //char pesquisar[]="MIQUAELI";
	    //pesquisaElemento(pesquisar);
        //removerElemento(pesquisar);
    freeElementos();
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

void readArquivoTXT(){
    FILE *file = fopen("nomes.txt", "r");
	char nome[QTDCARACTERES];
	while(fgets(nome, QTDCARACTERES, file) != NULL){
		insereElemento(nome);
	}
}

void imprimeListas(){
	Elemento *aux;
	int total=0;
	//imprime os nomes
	/*for(int i=0; i<CHAVES; i++){
		aux= chave[i]->head;
        
		for(int x=0; x<chave[i]->size ;x++){
			printf("%i- %s",i,aux->nome);
			aux= aux->next;
		}
		printf("\n\n");
    }*/

	//imprime o size de cada lista
	for(int i=0; i<CHAVES; i++){
		printf("\n%i- %i\n",i,chave[i]->size);
        total= total + chave[i]->size;
	}
	printf("\ntotal de nomes: %i\n", total);
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

int qtdCaracteres(char *nome){
    int cont=0;
    while(nome[cont] != '\0'){
        ++cont;
    }
    return cont;
}

void pesquisaElemento(char *nome){
    int y= hash(nome[0]);
    int numCaracteres= qtdCaracteres(nome);
    int i;
    Elemento *aux= chave[y]->head;
    for(int x=0; x<chave[y]->size; x++){
		i=0;
        while(i<numCaracteres){
            if(aux->nome[i]==nome[i]){
                i++;
            }else{
            	break;
			}
            if(i==numCaracteres){
                printf("\n\nO nome (%s) foi encontrado na chave[%i]", nome, y);
                return;
            } 
        }
    aux=aux->next;
    }
    printf("\n\nO nome (%s) nao existe na tabela", nome);
}

void removerElemento(char *nome){
    int y= hash(nome[0]);
    int numCaracteres= qtdCaracteres(nome);
    int i;
    Elemento *aux= chave[y]->head;
    for(int x=0; x<chave[y]->size; x++){
		i=0;
        while(i<numCaracteres){
            if(aux->nome[i]==nome[i]){
                i++;
            }else{
            	break;
			}
            
            if(i==numCaracteres){
                if(aux==chave[y]->head){
                    chave[y]->head = aux->next;
                    if(chave[y]->head==NULL){
                        chave[y]->tail=NULL;
                    }else{
                        aux->next->prev=NULL;
                    }
                }else{
                    aux->prev->next = aux->next;
                    if(aux->next==NULL){
                        chave[y]->tail= aux->prev;
                    }else{
                        aux->next->prev = aux->prev;
                    }
                }
                free(aux);
                chave[y]->size--;
                printf("\n\nO nome (%s) foi removido da chave[%i]", nome, y);
                return;
            } 
        }
    aux=aux->next;
    }
    printf("\n\n nao foi possivel remover o nome (%s), pois nao existe na tabela", nome);
}

void freeElementos(){
    Elemento *aux;
    for(int x=0; x<CHAVES ;x++){
        while(chave[x]->size>0){
            aux= chave[x]->head;
            chave[x]->head = aux->next;
            if(chave[x]->head==NULL){
                chave[x]->tail=NULL;
            }else{
                aux->next->prev=NULL;
            }
            free(aux);
            chave[x]->size--;
        }
        free(chave[x]);
    }
}
