#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ficheiros.h"
#include "structs.h"


int main(){
	pmenu menu=NULL,auxm;			//declaraçao d ponteiros para listas
	pmesa mesas=NULL,auxme;
	pemp empr=NULL,auxe;
	pesp le=NULL,auxle;
	qiten auxi,ant;
	phist auxh,anth;

	mesas=carregabackup(mesas); // funçao para ver se tem backup, se tiver carrega-o com autorizaçao 
	if(mesas==NULL){     // se mesas ainda estiver vazio(sem backup) podera alterar-s as configuraçoes
		gernt();             //chama menu inicial ond se altera a configuraçao
		mesas=abremesas(mesas);   //inicia a lsita mesas
	}
	else{
		empr=backupemp(empr);//carrega empr do ficheiro e a le
		le=backuple(le);
	}
	menu=abremenu(menu);		//inicia o menu
	menuprinc(menu,mesas,empr,le);  //chama menu do dia
	imprime(mesas);  //imprime ficheiro com dados do dia
	


	//***************** liberta memoria de todas as listas ***************
	while(menu->prox!=NULL){
		auxm=menu;
		menu=menu->prox;
		free(auxm);
	}
	free(menu);
	while(mesas!=NULL){
		while(mesas->registo!=NULL){
			auxh=mesas->registo;
			while(mesas->registo->itens!=NULL){
				auxi=mesas->registo->itens;
				mesas->registo->itens=mesas->registo->itens->prox;
				free(auxi);
			}
			mesas->registo=mesas->registo->prox;
			free(auxh);
		}
		while(mesas->itens!=NULL){
			auxi=mesas->itens;
			mesas->itens=mesas->itens->prox;
			free(auxi);
		}
		auxme=mesas;
		mesas=mesas->prox;
		free(auxme);
	}
	while(empr!=NULL){
		auxe=empr;
		empr=empr->prox;
		free(auxe);
	}
	while(le!=NULL){
		auxle=le;
		le=le->prox;
		free(auxle);
	}


}