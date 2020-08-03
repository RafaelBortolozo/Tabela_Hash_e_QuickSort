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
int divideLista(int inicio, int fim);
void quicksort(int inicio, int fim);

main(){
	criaListas();
    readArquivoTXT();

	//Pesquisa e remocao de nomes    
        //char pesquisar[]="JOCELINE";
	    //pesquisaElemento(pesquisar);
        //removerElemento(pesquisar);
    //freeElementos();
    //imprimeListas();

    quicksort(1, chave[0]->size);
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
		aux= chave[i]->head;
        
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
    novo_elemento->id= chave[nHash]->size;
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
    printf("%i", numCaracteres);
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

//calculo do hash exclusivo para ordenacao
int hashSort(char letra){
    return letra;
}

int divideLista(int inicio, int fim){
    int esq= inicio;
    int dir= fim;
    Elemento *esquerda;
    Elemento *direita;
    Elemento *pivo;
    Elemento *aux= chave[0]->head;
    for(int i=1; i<=fim ;i++){
        if(aux->id==inicio){
            pivo=aux;
            esquerda=aux;
            for(i; i<=fim ;i++){
                if(aux->id==fim){
                    direita= aux; 
                    break; 
                }
                aux=aux->next;
            }
            break; 
        }
        aux=aux->next;
    }
    //esquerda= aponta para o elemento do inicio da particao
    //    pivo= aponta para o elemento do inicio da particao
    // direita= aponta para o elemento do final da particao
    Elemento *bEsquerda= esquerda;
    Elemento *bDireita= direita;

    while(esq<dir){
        while(hashSort(esquerda->nome[0]) <= hashSort(pivo->nome[0])){
            esquerda=esquerda->next;
            esq++;
        }
        while(hashSort(direita->nome[0]) > hashSort(pivo->nome[0])){
            direita=direita->prev;
            dir--;
        }
        if(esq < dir){
            //troca os dados dos elementos, o id nao eh alterado
            //salva os dados do elemento da esquerda em um ponteiro auxiliar
            Elemento *aux2;
            aux2->next= esquerda->next;
            aux2->prev= esquerda->next;
            for(int i=0; i<QTDCARACTERES; i++){
                aux2->nome[i]= esquerda->nome[i];
            }

            //troca os dados da esquerda pelos dados da direita
            esquerda->next= direita->next;
            esquerda->prev= direita->prev;
            for(int i=0; i<QTDCARACTERES ;i++){
                esquerda->nome[i]=direita->nome[i];
            }

            //troca os dados da direita pelos dados da esquerda, usando o auxiliar
            direita->next= aux2->next;
            direita->prev= aux2->prev;
            for(int i=0; i<QTDCARACTERES ;i++){
                direita->nome[i]=aux2->nome[i];
            }
        }
    }
    Elemento *aux2= chave[0]->head;
    for(int i=1; i<=fim ;i++){
        if(aux2->id==inicio){
            break;
        }
        aux2=aux2->next;
    }
    aux2->next= direita->next;
    aux2->prev= direita->prev;
    for(int i=0; i<QTDCARACTERES; i++){
        aux2->nome[i]= direita->nome[i];
    }
    
    Elemento *aux3=chave[0]->head;
    for(int i=1; i<=fim ;i++){
        if(aux3->id==dir){
            break;
        }
        aux3=aux3->next;
    }
    aux3->next= pivo->next;
    aux3->prev= pivo->prev;
    for(int i=0; i<QTDCARACTERES; i++){
        aux3->nome[i]= pivo->nome[i];
    }
    return dir;
}

void quicksort(int inicio, int fim){
	int pivo;
    if(fim>inicio){
        pivo= divideLista(inicio, fim);
        quicksort(inicio, pivo-1);
        quicksort(pivo+1, fim);
    }
}
