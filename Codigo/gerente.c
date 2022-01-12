#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "menu.h"


void eleminaitem(){
	FILE *f,*g;
	struct item aux;
	int id,x=0,y=0;
	char c;
	//funçao para eleminar itens 
	if((f=fopen("menu.dat", "rb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	if((g=fopen("temp.dat", "wb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	printf("introduza o id do item que quer eleminar: ");
	scanf("%d",&id);
	getchar();
	printf("\ntem a certeza que deseja eleminar o item associado ao ID: %d?\n('s' ou 'S' para sim, outro para nao)\n.: ",id);
	scanf("%c",&c);
	getchar();
	if(c=='s'||c=='S'){
		while(fread(&aux, sizeof(struct item), 1, f) == 1){
			if(aux.id!=id){
				fwrite(&aux, sizeof(struct item), 1, g);
				x++;
			}else
			y++;
		}
		if(y!=x){
			printf("\neleminado com exito\n");
		}else
			printf("\nitem enexistente\n");
		fclose(f);
		fclose(g);
		remove("menu.dat");
		rename("temp.dat","menu.dat");
	}
	else
		printf("\ncancelado\n");
	printf("prima uma tecla para continuar....");
	getchar();
	return;
}


void alteraitem(){
	FILE *f,*g;
	struct item aux;
	int id,x=0;
	float pre;
	char st[100],st2[4]="0",c;
	//funçao para alterar itens 

	
	printf("introduza o id do item que quer alterar: ");
	scanf("%d",&id);
	getchar();
	printf("\ntem a certeza que deseja alterar o item associado ao ID: %d?\n('s' ou 'S' para sim, outro para nao)\n.: ",id);
	scanf("%c",&c);
	getchar();
	if(c=='s'||c=='S'){
		if((f=fopen("menu.dat", "rb"))==NULL){
			printf("Erro no acesso ao ficheiro\n");
			return;
		}
		if((g=fopen("temp.dat", "wb"))==NULL){
			printf("Erro no acesso ao ficheiro\n");
			return;
		}
		while(fread(&aux, sizeof(struct item), 1, f) == 1){
			if(aux.id==id){
				printf("introduza o novo nome(0=antigo): ");
				gets(st);
				if(strcmp(st,st2)!=0)
					strcpy(aux.nome,st);			
				printf("introduza o novo preço: ");
				do{
					scanf("%f",&pre);
					getchar();
				}while(pre<0);
				x++;
				aux.preço=pre;
			}
			fwrite(&aux, sizeof(struct item), 1, g);
		}
		if(x==0)
			printf("\nitem inexistente\n");
		fclose(f);
		fclose(g);
		
		remove("menu.dat");
		rename("temp.dat","menu.dat");
	}
	else
		printf("\ncancelado\n");
	printf("prima uma tecla para continuar....");
	getchar();
	return;
}

void mostraitem(){
	FILE *f;
	struct item aux;
	//funçao para mostrar itens 
	if((f=fopen("menu.dat", "rb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	printf("      [Itens Menu]");
	printf("\n ID\tCusto\tDescricao\n\n");
	while(fread(&aux, sizeof(struct item), 1, f) == 1){
		printf(" %d\t %.2f\t %s\n",aux.id,aux.preço,aux.nome);
	}
	fclose(f);
	printf("prima uma tecla para continuar....");
	getchar();
	return;
}



void insereitem(){
	FILE *f,*g;
	struct item aux,aux2;
	int id,x=0;
	float pre;
	//funçao para inserir itens 
	if((f=fopen("menu.dat", "rb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	printf("introduza o id para o item que quer inserir: ");
	do{
		scanf("%d",&id);
		getchar();
	}while(id<=0);
	while(fread(&aux, sizeof(struct item), 1, f) == 1){
		if(aux.id==id){
			x=1;
		}
	}
	fclose(f);
	if(x==1){
		printf("\nid ja esta atribuido\n");
	}else{
		x=0;
		if((f=fopen("menu.dat", "rb"))==NULL){
			printf("Erro no acesso ao ficheiro\n");
			return;
		}
		if((g=fopen("temp.dat", "wb"))==NULL){
			printf("Erro no acesso ao ficheiro\n");
			return;
		}
		while(fread(&aux, sizeof(struct item), 1, f) == 1){
			if(x==0){
				if(aux.id<id){
					fwrite(&aux, sizeof(struct item), 1, g);
				}else{
					x=1;
					
					printf("introduza o nome do produto: ");
					gets(aux2.nome);
					printf("introduza o preco do produto: ");
					do{
						scanf("%f",&pre);
						getchar();
					}while(pre<0);
					aux2.id=id;
					aux2.preço=pre;
					fwrite(&aux2, sizeof(struct item), 1, g);
					fwrite(&aux, sizeof(struct item), 1, g);
				}
			}else
				fwrite(&aux, sizeof(struct item), 1, g);

		}
		if(x==0){
			printf("introduza o nome do produto: ");
			gets(aux2.nome);
			printf("introduza o preco do produto: ");
			do{
				scanf("%f",&pre);
				getchar();
			}while(pre<0);
			aux2.id=id;
			aux2.preço=pre;
			fwrite(&aux2, sizeof(struct item), 1, g);
		}
		fclose(f);
		fclose(g);
		remove("menu.dat");
		rename("temp.dat","menu.dat");
	}
	printf("prima uma tecla para continuar....");
	getchar();
	return;
}


void mostramesas(){
	FILE *f;
	//funçao para mostrar mesas
	int total,i,id,cap;
	f = fopen("config.txt", "r");
	if(f==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return NULL;
	}
	fscanf(f,"Total: %d\n",&total);
	printf("  [Mesas]");
	printf("\n ID\tCap.\n\n");
	for(i=0;i<total;i++){
		fscanf(f,"Mesa: %d\n",&id);
		fscanf(f,"Capacidade: %d\n",&cap);
		printf(" %d\t%d\n",id,cap);
	}
	

	fclose(f);
	printf("\nprima uma tecla para continuar....");
	getchar();
}

void inseremesas(){
	FILE *f, *g;
	//funçao para inserir mesas
	int total,i,id,cap,idp,capp,x;
	char c;
	printf("introduza o id para a mesa k deseja introduzir\n(se 0 vai ser adicionada em ultimo)\n.:");
	do{
		scanf("%d",&idp);
	}while(idp<0);
	printf("introduza a capacidade da mesa: ");
	getchar();
	do{
		scanf("%d",&capp);
	}while(capp<1);
	getchar();
	printf("tem a certeza que quer adicionar a mesa?\n('s' ou 'S' para sim, outro para cancelar)\n.:");
	scanf("%c",&c);
	getchar();
	if(c!='s'&&c!='S'){
		printf("\ncancelado\n");
		getchar();
		return;
	}
	if((f = fopen("config.txt", "r"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	if((g=fopen("temp.dat", "w"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	fscanf(f,"Total: %d\n",&total);
	fprintf(g,"Total: %d\n",total+1);
	if(idp==0)
		idp=total+1;
	x=0;
	for(i=0;i<total;i++){
		fscanf(f,"Mesa: %d\n",&id);
		fscanf(f,"Capacidade: %d\n",&cap);
		if((id>=idp)&&(x==0)){
			fprintf(g,"Mesa: %d\n",idp);
			fprintf(g,"Capacidade: %d\n",capp);
			x=1;
			fprintf(g,"Mesa: %d\n",id+1);
			fprintf(g,"Capacidade: %d\n",cap);
		}else{
			if(x==1)
				fprintf(g,"Mesa: %d\n",id+1);
			else
				fprintf(g,"Mesa: %d\n",id);
			fprintf(g,"Capacidade: %d\n",cap);
		}
	}
	if(x==0){
		fprintf(g,"Mesa: %d\n",total+1);
		fprintf(g,"Capacidade: %d\n",capp);
	}
	printf("\nadicionada com sucesso\n");
	fclose(f);
	fclose(g);
	remove("config.txt");
	rename("temp.dat","config.txt");
	printf("\nprima uma tecla para continuar....");
	getchar();
}

void eleminamesas(){
	FILE *f, *g;
	//funçao para eleminar mesas 
	int total,i,id,cap,idp,x;
	char c;
	if((f = fopen("config.txt", "r"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		return;
	}
	fscanf(f,"Total: %d\n",&total);
	printf("introduza o id para a mesa que deseja eleminar\n(se 0 vao ser eleminadas todas as mesas\n.:");
	do{
		do{
			scanf("%d",&idp);
		}while((idp>total));
	}while((idp<0));
	getchar();
	if(idp==0)
		printf("\nATENCAO VAI ELEMINAR TODAS AS MESAS!!!! \n\n");
	printf("tem a certeza?\n('s' ou 'S' para sim, outro para cancelar)\n.:");
	scanf("%c",&c);
	getchar();
	if(c!='s'&&c!='S'){
		printf("\ncancelado\n");
		getchar();
		fclose(f);
		return;
	}
	else{
		if((g=fopen("temp.dat", "w"))==NULL){
			printf("Erro no acesso ao ficheiro\n");
			return;
		}
		if(idp==0){
			fprintf(g,"Total: 0\n");
		
		}else{
			fprintf(g,"Total: %d\n",total-1);
			x=0;
			for(i=0;i<total;i++){
				fscanf(f,"Mesa: %d\n",&id);
				fscanf(f,"Capacidade: %d\n",&cap);
				if(idp==id){
					x=1;
					fscanf(f,"Mesa: %d\n",&id);
					fscanf(f,"Capacidade: %d\n",&cap);
				}
				if(x==0){
					fprintf(g,"Mesa: %d\n",id);
					fprintf(g,"Capacidade: %d\n",cap);
				}else{
					fprintf(g,"Mesa: %d\n",id-1);
					fprintf(g,"Capacidade: %d\n",cap);
				}	
			}
		}
		printf("\neleminado com exito\n");
		fclose(f);
		fclose(g);
		remove("config.txt");
		rename("temp.dat","config.txt");
		printf("\nprima uma tecla para continuar....");
		getchar();
	}
}


void gernt(){
	//funçao pa chamar funçoes
	char op;
	do{
		system("cls");
		op=menuinicial();
		switch(op){
			case '1': inseremesas();break;
			case '2': eleminamesas();break;
			case '3': mostramesas();break;
			case '4': insereitem();break;
			case '5': alteraitem();break;
			case '6': eleminaitem();break;
			case '7': mostraitem();break;
			case '8': op=test();break;
		}
	}while(op!='9');
}

int test(){
	FILE *f;
	int total;
	struct item aux;
	//funçao que abre ficheiro d configuraçao e de menu, se nao existir mesas ou menu o dia nao pode começar
	f = fopen("config.txt", "r");
	if(f==NULL){
		printf("Erro no acesso ao ficheiro\n");
		getchar();
		return '0';
	}
	fscanf(f,"Total: %d\n",&total);
	fclose(f);
	if(total==0){
		printf("Erro: Nao pode começar o dia sem mesas\n");
		getchar();
		return '0';
	}
	
	if((f=fopen("menu.dat", "rb"))==NULL){
		printf("Erro no acesso ao ficheiro\n");
		getchar();
		return '0';
	}
	if(fread(&aux, sizeof(struct item), 1, f) == 0){
		printf("Erro: Nao pode começar o dia sem menu\n");
		getchar();
		fclose(f);
		return '0';
	}
	fclose(f);
	return '9';
}