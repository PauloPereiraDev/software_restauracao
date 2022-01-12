#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

pmenu abremenu(pmenu menu){
	FILE *f;
	struct item aux;
	pmenu paux,novo;

	f = fopen("menu.dat", "rb");
	
	if(f==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	// le do ficheiro e preenche o ponteiro inicial
	if(fread(&aux, sizeof(struct item), 1, f) == 1){
		novo=malloc(sizeof(struct mitem));
		novo->id=aux.id;
		novo->preço=aux.preço;
		novo->prox=NULL;
		strcpy(novo->nome,aux.nome);
		menu=novo;
		paux=novo;
	}
	//le do ficheiro e preenche o resto da lista com ajuda do paux;
	while(fread(&aux, sizeof(struct item), 1, f) == 1){
		novo=malloc(sizeof( struct mitem));
		novo->id=aux.id;
		novo->preço=aux.preço;
		novo->prox=NULL;
		strcpy(novo->nome,aux.nome);
		paux->prox=novo;
		paux=paux->prox;
	}
	fclose(f);
	return menu;//devolve o ponteiro
}
pmesa abremesas(pmesa mesas){
	FILE *f;
	pmesa paux,novo;
	int total,i;

	f = fopen("config.txt", "r");
	if(f==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	fscanf(f,"Total: %d\n",&total);
	for(i=0;i<total;i++){
		//le do ficheiro e preenche as flags
		novo=malloc(sizeof(struct mesa));
		fscanf(f,"Mesa: %d\n",&novo->id);
		fscanf(f,"Capacidade: %d\n",&novo->cap);

		novo->livre=0;
		novo->idemp=0;
		novo->itens=NULL;
		novo->registo=NULL;
		novo->prox=NULL;
		if(mesas==NULL){//se o ponteiro da lista ainda estiver a NULL inicia-o
			mesas=novo;
			paux=mesas;
		}else{// senao usa uma variavel auxiliar para preencher a lista
			paux->prox=novo;
			paux=paux->prox;
		}
	
	}
	fclose(f);
	return mesas;
}

void imprime(pmesa mesas){  // fucçao para criar o registo do dia
	pno empf=NULL,auxf,novo;
	phist auxh;
	qiten auxi;
	FILE *f;
	float total=0;
	f=fopen("fact.txt","w");
	if(f==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return ;
	}	
	fprintf(f,"REGISTO DO DIA\n");
	while(mesas!=NULL){// corre as mesas
		auxh=mesas->registo;
		while(auxh!=NULL){// corre os registos
			fprintf(f,"\nMesa: %d\n",mesas->id);
			fprintf(f,"\nEmpregado: %s\n",auxh->st);
			auxi=auxh->itens;
			fprintf(f,"\nqnt\tpreco(unit)\tnome\n\n");
			while(auxi!=NULL){// corre os itens
				fprintf(f,"%d\t%.2f\t%s\n",auxi->qua,auxi->preço,auxi->nome);
				auxi=auxi->prox;
			}
			fprintf(f,"\nTotal: %.2f\n\n",auxh->total);
			auxf=empf;
			while((auxf!=NULL)&&(strcmp(auxf->nome,auxh->st)!=0))// core a lista de empregados auxiliar procurando
				auxf=auxf->prox;							//o empregado ou o fim da lista
				if(auxf==NULL){// se nao estiver ja na lista alloca espaço e inseree-o la
					novo=malloc(sizeof(struct fact));
					novo->prox=NULL;
					strcpy(novo->nome,auxh->st);
					novo->factu=auxh->total;
					if(empf==NULL)//se a lista estiver vazia inicia-a
						empf=novo;
					else{//senao insere no fim
						auxf=empf;
						while(auxf->prox!=NULL)
							auxf=auxf->prox;
						auxf->prox=novo;
					}	
				}else{//se o empregado ja existir soma-lh o total
					auxf->factu=auxh->total+auxf->factu;
				}
			auxh=auxh->prox;
		}
		mesas=mesas->prox;
	}
	auxf=empf;
	//imprime a facturaçao dos empregados
	fprintf(f,"\n\nFacturaçao de Empregados\n\n");
	while(auxf!=NULL){
		fprintf(f,"%s\t\t%.2f\n",auxf->nome,auxf->factu);
		total=total+auxf->factu;
		auxf=auxf->prox;
	}
	//liberta memoria 
	while(empf!=NULL){
		auxf=empf;
		empf=empf->prox;
		free(auxf);
	}
	fprintf(f,"\nFacturacao do DIA: %.2f",total);
	fclose(f);
}
		

void backup(pesp le,pmesa mesas,pemp empr){
	FILE *f,*g,*h;
	
	pesp auxle;
	pmesa auxm;
	pemp auxe;
	qiten auxi;
	phist auxh;

	struct fichmesa fmesa;
	struct fichemp femp;
	struct fichesp fesp;
	struct fichhist fhis;
	struct fichitens fiten;
	
	int x,r,i,ii;

	auxm=mesas;
	//abre ficheiros
	if((f=fopen("mesas.dat", "wb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	if((g=fopen("registo.dat", "wb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	if((h=fopen("itens.dat", "wb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	while(auxm!=NULL){// corre mesas
		x=1;
		fmesa.cap=auxm->cap;// copia dados pa estrutura
		fmesa.id=auxm->id;
		fmesa.idemp=auxm->idemp;
		fmesa.livre=auxm->livre;
		auxi=auxm->itens;
		i=0;// flag pa itens
		while(auxi!=NULL){//corre itens
			i++;
			fiten.idmesa=auxm->id;
			fiten.reg=0;
			fiten.id=auxi->id;
			strcpy(fiten.nome,auxi->nome);
			fiten.preco=auxi->preço;
			fiten.qua=auxi->qua;
			fwrite(&fiten, sizeof(struct fichitens), 1, h);// grava itens
			auxi=auxi->prox;
		}
		auxh=auxm->registo;
		r=0;
		while(auxh!=NULL){// corre registo
			r++;// flag pa nro d registos
			fhis.idmesa=auxm->id;
			fhis.total=auxh->total;
			strcpy(fhis.st,auxh->st);
			auxi=auxh->itens;
			ii=0;

			while(auxi!=NULL){// corre itens de registo
				ii++;//flag pa nro d itens do registo
				fiten.idmesa=auxm->id;
				fiten.reg=x;
				fiten.id=auxi->id;
				strcpy(fiten.nome,auxi->nome);
				fiten.preco=auxi->preço;
				fiten.qua=auxi->qua;
				fwrite(&fiten, sizeof(struct fichitens), 1, h);// grava em itens
				auxi=auxi->prox;
			}
			fhis.it=ii;
			fwrite(&fhis, sizeof(struct fichhist), 1, g);
			auxh=auxh->prox;
		}
		fmesa.it=i;
		fmesa.reg=r;
		fwrite(&fmesa, sizeof(struct fichmesa), 1, f);
		auxm=auxm->prox;
	}
	fclose(f);
	fclose(g);
	fclose(h);
	if((f=fopen("empregados.dat", "wb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	auxe=empr;// corre empregados
	while(auxe!=NULL){
		femp.id=auxe->id;
		femp.mesas=auxe->mesas;
		strcpy(femp.nome,auxe->nome);
		fwrite(&femp, sizeof(struct fichemp), 1, f);
		auxe=auxe->prox;
	}
	fclose(f);
	if((f=fopen("espera.dat", "wb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	auxle=le;
	while(auxle!=NULL){//corre lista d espera
		fesp.pessoas=auxle->pessoas;
		fesp.id=auxle->id;
		strcpy(fesp.nome,auxle->nome);
		fwrite(&fesp, sizeof(struct fichesp), 1, f);
		auxle=auxle->prox;
	}
	fclose(f);
	printf("\n\nBackup feito!!!\n\n");
	getchar();
}



int carregabackup(pmesa mesas){
	FILE *f,*g,*h;
	pmesa auxm=NULL,novom;
	qiten auxi=NULL,novoi;
	phist auxh=NULL,novoh;


	struct fichmesa fmesa;
	struct fichhist fhis;
	struct fichitens fiten;
	
	int x,i,j;
	char c;

	auxm=mesas;
	
	if((f=fopen("mesas.dat","rb"))==NULL){

		return NULL;
	}
	printf("\nexiste um BACKUP, deseja carregalo?\n('s' ou 'S' para sim, outro para nao e sera apagado o backup!)\n.: ");
	scanf("%c",&c);
	getchar();
	if((c!='s')&&(c!='S')){
		fclose(f);
		remove("mesas.dat");
		remove("empregados.dat");
		remove("espera.dat");
		remove("registo.dat");
		remove("itens.dat");
		return NULL;
	}
	if((g=fopen("registo.dat","rb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		getchar();
		return NULL;
	}
	if((h=fopen("itens.dat","rb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		getchar();
		return NULL;
	}
	//le do ficheiro todas as mesas
	while(fread(&fmesa, sizeof(struct fichmesa),1,f)==1){
		novom=malloc(sizeof(struct mesa));
		novom->cap=fmesa.cap;
		novom->id=fmesa.id;
		novom->idemp=fmesa.idemp;
		novom->livre=fmesa.livre;
		novom->itens=NULL;
		novom->prox=NULL;
		novom->registo=NULL;
		

		//com base na flag fmesa.it le itens desta mesa
		for(i=0;i<fmesa.it;i++){
			fread(&fiten, sizeof(struct fichitens),1,h);
			
			if((novoi=malloc(sizeof(struct qitem)))==NULL){
				printf("erro");
			}
			novoi->id=fiten.id;
			strcpy(novoi->nome,fiten.nome);
			novoi->preço=fiten.preco;
			novoi->qua=fiten.qua;
			novoi->prox=NULL;
			
			if(novom->itens==NULL){
				novom->itens=novoi;
				auxi=novoi;
			}else{
				auxi->prox=novoi;
				auxi=auxi->prox;
			}
			
		}
		
		//com base na flag fmesa.reg le os registos desta mesa
		for(i=0;i<fmesa.reg;i++){
			fread(&fhis, sizeof(struct fichhist),1,g);
			novoh=malloc(sizeof(struct hist));
			novoh->total=fhis.total;
			novoh->prox=NULL;
			novoh->itens=NULL;
			strcpy(novoh->st,fhis.st);
			//com base na flag fhis.it le os itens deste registo
			for(j=0;j<fhis.it;j++){
				fread(&fiten, sizeof(struct fichitens),1,h);
				novoi=malloc(sizeof(struct qitem));
				novoi->id=fiten.id;
				strcpy(novoi->nome,fiten.nome);
				novoi->preço=fiten.preco;
				novoi->qua=fiten.qua;
				novoi->prox=NULL;
				if(novoh->itens==NULL){
					novoh->itens=novoi;
					auxi=novoi;
				}else{
					auxi->prox=novoi;
					auxi=auxi->prox;
				}
			}

			if(novom->registo==NULL){
				novom->registo=novoh;
				auxh=novoh;
			}else{
				auxh->prox=novoh;
				auxh=auxh->prox;
			}
		}

		if(mesas==NULL){
			mesas=novom;
			auxm=mesas;
		}
		else{
			auxm->prox=novom;
			auxm=auxm->prox;
		}

	}
	fclose(f);
	fclose(g);
	fclose(h);
	remove("mesas.dat");
	remove("registo.dat");
	remove("itens.dat");
	getchar();
	return mesas;
}

int backupemp(pemp empr){
	FILE *f;
	pemp novo,aux;
	struct fichemp femp;
	if((f=fopen("empregados.dat","rb"))==NULL){
		return NULL;
	}
	//le todos os empregados do ficheiro
	while(fread(&femp, sizeof(struct fichemp),1,f)==1){
		novo=malloc(sizeof(struct fichemp));
		novo->id=femp.id;
		novo->mesas=femp.mesas;
		strcpy(novo->nome,femp.nome);
		novo->prox=NULL;
		if(empr==NULL){
			empr=novo;
			aux=empr;
		}
		else{
			aux->prox=novo;
			aux=aux->prox;
		}
	}
	fclose(f);
	remove("empregados.dat");
	return empr;
}

int backuple(pesp le){
	FILE *f;
	pesp novo,aux;
	struct fichesp fesp;
	if((f=fopen("espera.dat","rb"))==NULL){
		return NULL;
	}
	//le toda a fila de espera
	while(fread(&fesp, sizeof(struct fichesp),1,f)==1){
		novo=malloc(sizeof(struct fichesp));
		novo->id=fesp.id;
		novo->pessoas=fesp.pessoas;
		strcpy(novo->nome,fesp.nome);
		novo->prox=NULL;
		if(le==NULL){
			le=novo;
			aux=le;
		}
		else{
			aux->prox=novo;
			aux=aux->prox;
		}
	}
	fclose(f);
	remove("espera.dat");
	return le;
}