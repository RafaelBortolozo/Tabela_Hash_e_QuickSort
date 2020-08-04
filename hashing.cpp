#include <stdio.h>
#include <stdlib.h>
#define CHAVES 11 
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

Lista *chave[CHAVES];
void criaListas();
void readArquivoTXT();
void imprimeListas();
int hash(char letra1, char letra2, char letra3);
void insereElemento(char *nome);
int qtdCaracteres(char *nome);
void pesquisaElemento(char *nome);
void removerElemento(char *nome);
void freeElementos();

int hashSort(char letra);
int particiona(char nomes[][QTDCARACTERES], int inicio, int fim);
void inicializa_quicksort(int numchave);
void quicksort(char nomes[][QTDCARACTERES], int inicio, int fim);
void atualizaLista(char nomes[][QTDCARACTERES], int numChave);

main(){
	criaListas();
    	readArquivoTXT();

	//Pesquisa e remocao de nomes    
            //char pesquisar[]="JOCELINE";
	    //pesquisaElemento(pesquisar);
            //removerElemento(pesquisar);
    	//freeElementos();
    	//imprimeListas();
    
	//Ordenacao de elementos
	//inicializa_quicksort(0);
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
    	fclose(file);
}

void imprimeListas(){
	Elemento *aux;
	int total=0;
    	int i=0;
	//imprime os nomes
	//for(int i=0; i<CHAVES; i++){
		aux= chave[0]->head;
		
		for(int x=0; x<chave[i]->size ;x++){
			printf("%i- %s",aux->id,aux->nome);
			aux= aux->next;
		}
		printf("\n\n");
    //}

	//imprime o size de cada lista
	for(int i=0; i<CHAVES; i++){
		printf("%i\n",chave[i]->size);
        	total= total + chave[i]->size;
	}
	printf("\ntotal de nomes: %i\n", total);
}

int hash(char *nome){
	int l1= nome[0];
    	int l2= nome[1];
    	int l3= nome[2];
	int i= (l1+l2+l3) % CHAVES;
	return i;
}

void insereElemento(char *nome){
	int nHash= hash(nome);
	Elemento *pivo= chave[nHash]->tail;
	Elemento *novo_elemento = (Elemento*)malloc(sizeof(Elemento));
    	novo_elemento->id= chave[nHash]->size;
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
    int y= hash(nome);
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
    int y= hash(nome);
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
                //ajusta o id de todos os elementos
		Elemento *aux2= aux->next;
                while(aux2 != NULL){
                	aux2->id--;
                	aux2=aux2->next;
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

void atualizaLista(char nomes[][QTDCARACTERES], int numChave){
	Elemento *aux= chave[numChave]->head;
	for(int i=0; i<chave[numChave]->size; i++){
		for(int x=0; x<QTDCARACTERES; x++){
			aux->nome[x]=nomes[i][x];
		}
		aux=aux->next;
	}
}

void inicializa_quicksort(int numChave){
	//vetor de nomes, nesse caso, vetor de vetor de caracteres (matriz)
	char nomes[chave[numChave]->size][QTDCARACTERES];
	
	//copia os nomes da lista para ordenar
	Elemento *aux= chave[numChave]->head;
	for(int i=0; i<chave[numChave]->size; i++){
        for(int x=0; x<=QTDCARACTERES; x++){
            nomes[i][x]= aux->nome[x];
        }
        aux=aux->next;
    }	
    
    //define o inicio e o fim da matriz
    int inicio=0;
    int fim= (chave[numChave]->size);
    quicksort(nomes, inicio, fim);
    
    atualizaLista(nomes, numChave);
}

//calculo do hash exclusivo para ordenacao
int hashSort(char letra){
    return letra;
}

int particiona(char nomes[][QTDCARACTERES], int inicio, int fim){
    int esq= inicio;
    int dir= fim;
    char aux[QTDCARACTERES];
    int pivo= hashSort(nomes[inicio][0]);
    while(esq < dir){
    	while(hashSort(nomes[esq][0]) <= pivo){
    		esq++;
		}
		while(hashSort(nomes[dir][0]) > pivo){
			dir--;
		}
		if(esq < dir){
			for(int i=0; i<QTDCARACTERES; i++){
				aux[i]= nomes[esq][i];
			}
			for(int i=0; i<QTDCARACTERES; i++){
				nomes[esq][i]=nomes[dir][i];
			}
			for(int i=0; i<QTDCARACTERES; i++){
				nomes[dir][i]= aux[i];
			}
		}
	}
	for(int i=0; i<QTDCARACTERES; i++){
		nomes[inicio][i]= nomes[dir][i];
	}
	for(int i=0; i<QTDCARACTERES; i++){
		nomes[dir][i]= nomes[inicio][i];
	}
	return dir;
}

void quicksort(char nomes[][QTDCARACTERES], int inicio, int fim){
	int pivo;
	if(fim>inicio){
        	pivo= particiona(nomes,inicio, fim);
        	quicksort(nomes,inicio, pivo-1);
        	quicksort(nomes,pivo+1, fim);
    	}
}
