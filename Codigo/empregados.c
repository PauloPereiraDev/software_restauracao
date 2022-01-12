#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
typedef struct emp *pemp;


pemp regemp(pemp empr){// funçao para registar empregados
	pemp novo,aux;
	char st[100],c;
	aux=empr;
	printf("\nIntroduza o nome: ");
	gets(st);
	while(aux!=NULL){//procura repetiçao de nome
		if(strcmp(st,aux->nome)==0){
			printf("\nNome existente\n");
			getchar();
			return empr;
		}
		aux=aux->prox;
	}
	printf("tem a certeza?\n('s' ou 'S' para sim, outro para cancelar)\n.:");
	scanf("%c",&c);
	getchar();
	if(c!='s'&&c!='S'){
		printf("\ncancelado\n");
		getchar();
		return empr;
	}
	novo=malloc(sizeof(struct emp));
	strcpy(novo->nome,st);
	novo->mesas=0;
	novo->prox=NULL;
	if(empr==NULL){//1º elemento
		novo->id=1;
		empr=novo;
	}
	else{//outro elemento
		aux=empr;
		while(aux->prox!=NULL){
			aux=aux->prox;
		}
		novo->id=aux->id+1;//incrementa ID
		aux->prox=novo;
	}
	printf("\nadicionado\n");
	printf("\nprima uma tecla para continuar....");
	getchar();
	return empr;
}

void veremp(pemp empr){
	pemp aux;
	//funçao para listar empregados
	aux=empr;
	if(aux==NULL){
		printf("\nsem empregados\n");
		printf("\nprima uma tecla para continuar....");
		getchar();
		return;
	}
	printf("\n   Empregados\n");
	printf("\nID\tMesas\tNome\n");
	while(aux!=NULL){//corre empregadose lista
		printf("\n%d\t%d\t%s",aux->id,aux->mesas,aux->nome);
		aux=aux->prox;
	}
	printf("\n\nprima uma tecla para continuar....");
	getchar();
}

pemp libemp(pemp empr){
	pemp aux,ant=NULL;
	int idp;
	char c;
	//funçao que nos premite libertar empregados
	aux=empr;
	printf("\nIntroduza o ID do empregado que deseja eleminar: ");
	scanf("%d",&idp);
	getchar();
	printf("tem a certeza?\n('s' ou 'S' para sim, outro para cancelar)\n.: ");
	scanf("%c",&c);
	getchar();
	if(c!='s'&&c!='S'){
		printf("\ncancelado\n");
		getchar();
		return empr;
	}

	while(aux!=NULL && aux->id!=idp){//procura empregado ate atingir o fim da lista
		ant = aux;
		aux=aux->prox;
	}
	if(aux==NULL){
		printf("\nempregado nao existe\n");
		getchar();
		return empr;
	}
	if(ant==NULL){ //1º elemento
		if(aux->mesas!=0){//flag de mesas activada, nao pode ser libertado
			printf("\neste empregado ainda esta encarregue de mesas\n");
			getchar();
			return empr;
		}
		printf("\nempregado libertado\n");
		getchar();
		empr=aux->prox;
		free(aux);
		return empr;
	}else{//outro elemento
		if(aux->mesas!=0){//flag de mesas activada, nao pode ser libertado
			printf("\neste empregado ainda esta encarregue de mesas\n");
			getchar();
			return empr;
		}
		ant->prox=aux->prox;
	}
	printf("\nempregado libertado\n");
	getchar();
	free(aux);
	return empr;
}
			
	