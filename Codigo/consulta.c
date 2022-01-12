#include "structs.h"
#include <stdio.h>
void mostramen(pmenu menu){
	pmenu aux;
	aux=menu;
	printf("      [Itens Menu]");
	printf("\n ID\tCusto\tDescricao\n\n");
	while(aux != NULL){//funçao para consultar lsita de itens
		printf(" %d\t %.2f\t %s\n",aux->id,aux->preço,aux->nome);
		aux=aux->prox;
	}
	getchar();
}
void histmesa(pmesa mesas){
	pmesa auxm;
	qiten auxi;
	phist auxh;
	int idp;
	//funçao para nos mostrar o historico da mesa escolhida

	printf("\nIntroduza o ID da mesa que deseja visualizar historico: ");
	do{
		scanf("%d",&idp);
	}while(idp<1);
	getchar();
	auxm=mesas;
	while((auxm!=NULL)&&(auxm->id!=idp))//corre mesa ate ao fim ou encontrar mesa desejada
		auxm=auxm->prox;
	if(auxm==NULL){
		printf("\nID invalido");
		getchar();
		return;
	}
	if(auxm->registo==NULL){//registo nao foi ainda adicionado
		printf("\nmesa %d ainda nao tem registos\n",idp);
		getchar();
		return;
	}
	auxh=auxm->registo;
	printf("\n\nMesa: %d\n\n",idp);
	while(auxh!=NULL){//corre registos da mesa
		printf("\nEmpregado: %s\n",auxh->st);//mostra info
		auxi=auxh->itens;
		printf("Itens\n");
		printf("qnt\tpreco(unit)\tnome\n\n");
		while(auxi!=NULL){// corre itens do registo
			printf("%d\t%.2f\t%s\n",auxi->qua,auxi->preço,auxi->nome);
			auxi=auxi->prox;
		}
		printf("\nTotal: %.2f\n\n",auxh->total);//total pago
		auxh=auxh->prox;
		getchar();
	}
}
void mostramesa(pmesa mesas){
	pmesa auxm;
	auxm=mesas;
	printf("\n\n  [Mesas]");
	printf("\n ID\tCap.\tEstado\n\n");
	while(auxm!=NULL){//funçao pa mostrar as mesas todas, ID cap e o seu estado
		printf(" %d\t%d",auxm->id,auxm->cap);
		if(auxm->livre==0)
			printf("\tLivre\n");
		else
			printf("\tOcupada\n");
		auxm=auxm->prox;
	}
	getchar();
}









void mostrale(pesp le){
	pesp aux;

	//funçao pa mostrar le
	aux=le;
	if(aux==NULL){
		printf("\n\nlista de espera vazia\n\n");
		getchar();
		return;
	}
	printf("\n\nlista de espera\n\n");
	printf("ID\tPessoas\t\tNome\n");
	while(aux!=NULL){//corre lista le... e faz printf
		printf("\n%d\t%d\t\t%s",aux->id,aux->pessoas,aux->nome);
		aux=aux->prox;
	}
	getchar();

}

int inserele(pesp le,pmesa mesas){// inserir pessoas na lista d espera
	pesp aux,novo;
	pmesa auxm;
	int cap,x=0;

	aux=le;
	auxm=mesas;
	printf("\n\nIntroduza o nro de pessoas: ");
	do{
		scanf("%d",&cap);
	}while(cap<0);
	getchar();
	while(auxm!=NULL){//corre mesas e procura se ha mesas livres
		if(auxm->cap>=cap){
			if(auxm->livre==0){
				printf("\n\nExistem mesas livres com capacidade\n\n");
				getchar();
				return le;
			}
			x=1;
		}
		auxm=auxm->prox;
	}
	if(x==0){//flag para falta de capacidade das mesas
		printf("\n\nMesas sem capacidade\n");
		getchar();
		return le;
	}
	novo=malloc(sizeof(struct espera));
	novo->pessoas=cap;
	novo->prox=NULL;
	printf("\nIntroduza o nome do grupo: ");
	gets(novo->nome);
	if(le==NULL){
		novo->id=1;
		return novo;//lista vazia 
	}
	else{
		while(aux->prox!=NULL)//corre lista ate ao fim
			aux=aux->prox;
		novo->id=aux->id+1;//incrementa ID
		aux->prox=novo;
		return le;
	}
}



int desitle(pesp le,int id){// funçao para desistencia
	pesp aux,ant=NULL;
	int idi;
	if(id==0){
		if(le==NULL){
			printf("\nLista vazia\n");
			getchar();
			return le;
		}
		printf("\nIntroduza o ID do grupo a desistir: ");
		do{
			scanf("%d",&idi);
		}while(idi<0);
	}
	else
		idi=id;
	aux=le;
	while((aux!=NULL)&&(aux->id!=idi)){//procura ID do grupo ate ao fim da lista
		ant=aux;
		aux=aux->prox;
	}
	if(aux==NULL){
		printf("\nID invalido\n");
		getchar();
		return le;
	}
	if(ant==NULL){// 1º elemento
		aux=aux->prox;// avança 
		free(le);
		getchar();
		return aux;
	}
	ant->prox=aux->prox;//retira a desistencia
	free(aux);
	getchar();
	return le;
}

int testle(pesp le,pmesa mesas,pemp empr){
	pmesa auxm;
	pesp aux;
	pemp auxe;
	int ide,me;
	char st[100];
	//funçao para sentar pessoas apos mesa libertada
	aux=le;
	while(aux!=NULL){//corre lista de espera
		auxm=mesas;
		while(auxm!=NULL){//corre mesas
			
			if((auxm->livre==0)&&(auxm->cap>=aux->pessoas)){// restriçao para mesa livre e capacidade
				auxe=empr;
				me=auxe->mesas;
			
				while(auxe!=NULL){//atribui empregado
					if(auxe->mesas<=me){
						ide=auxe->id;
						me=auxe->mesas;
						strcpy(st,auxe->nome);
					}
					auxe=auxe->prox;
				}
	
				auxe=empr;
				while(auxe->id!=ide)//corre empregados ate empregado atribuido
					auxe=auxe->prox;

				auxe->mesas++;//incrementa o nro d mesas do empregado escolhido
				auxm->idemp=ide;

				auxm->livre=1;//mesa passa a ocupada
				printf("\no grupo %s vao para a mesa %d e foi selecionado o %s",aux->nome,auxm->id,st);
				getchar();
				le=desitle(le,aux->id);
				return le;
			}
			auxm=auxm->prox;
		}
		aux=aux->prox;
	}
	return le;
}