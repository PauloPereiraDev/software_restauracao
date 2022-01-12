#include <stdio.h>
#include "structs.h"

void sentar(pmesa mesas,pemp empr){
	int idp,x=0,me,ide;
	char st[100];
	pemp auxe;
	pmesa auxm;
	//funçao para adicionar pessoas  a mesas manual
	printf("\nIntroduza o ID da mesa que quer ocupar: ");
	do{
		scanf("%d",&idp);
	}while(idp<0);
	getchar();
	if(empr==NULL){//tem que haver alguem para servir as pessoas
		printf("\nnao existem empregados\n");
		getchar();
		return;
	}
	auxm=mesas;
	auxe=empr;
	while(auxm!=NULL){//corre mesas
		if(idp==auxm->id){//procura mesa
			x=1;
			if(auxm->livre==0){//mesa livre
				auxm->livre=1;
				ide=auxe->id;
				me=auxe->mesas;
				while(auxe!=NULL){//corre empregados
					if(auxe->mesas<=me){//escolhe empregado com menos mesas
						ide=auxe->id;
						me=auxe->mesas;
						auxm->idemp=ide;
						strcpy(st,auxe->nome);
					}
					auxe=auxe->prox;
				}
			}
			else{//mesa pretendida ocupada
				printf("\nmesa ocupada\n");
				getchar();
				return;
			}
		}
		auxm=auxm->prox;
	}
	if(x==0){//id mesa invalido
		printf("\nID invalido\n");
		getchar();
		return;
	}
	auxe=empr;
	while(auxe!=NULL){//corre empregados
		if(auxe->id==ide){
			auxe->mesas++;//incrementa flag d mesas responsavel
		}
		auxe=auxe->prox;
	}
	printf("\nmesa adicionada com sucesso e foi selecionado o %s\n",st);
	getchar();
	return;
}

void associar(pmesa mesas,pemp empr){
	int pes,x=0,me,ide,cap,idm;
	char st[100];
	pemp auxe;
	pmesa auxm;
	//funçao para adicionar pessoas  a mesas automatico
	printf("\nIntroduza o nro de pessoas a sentar: ");
	do{
		scanf("%d",&pes);
	}while(pes<1);
	getchar();
	if(empr==NULL){//alguem ha-de servir
		printf("\nnao existem empregados\n");
		getchar();
		return;
	}
	auxm=mesas;
	auxe=empr;
	while(auxm!=NULL){//corre mesas
		if((auxm->cap>=pes)&&(auxm->livre==0)){//procura mesa com restriçao d capacidade e livre
			if((x==1)&&(cap>auxm->cap)){//procura mesa mais economica se ja tiver alguma
				cap=auxm->cap;
				idm=auxm->id;
			}
			if(x==0){// atribui mesa
				idm=auxm->id;
				cap=auxm->cap;
				x=1;
			}
		}
		auxm=auxm->prox;
	}
	if(x==1){// corre empregados e atribui um empregado se tiver encontrado mesa
		me=auxe->mesas;
		while(auxe!=NULL){
			if(auxe->mesas<=me){
				ide=auxe->id;
				me=auxe->mesas;
				strcpy(st,auxe->nome);
			}
			auxe=auxe->prox;
		}
		auxm=mesas;
		auxe=empr;
		while(auxe->id!=ide)
			auxe=auxe->prox;
		auxe->mesas++;// incrementa mesas responsavel
		while(auxm->id!=idm)
			auxm=auxm->prox;//corre mesas 
		auxm->idemp=ide;//activa flags
		auxm->livre=1;
		printf("\nsentados na mesa %d e foi selecionado o %s",auxm->id,st);
		getchar();
	}
	if(x==0){//nao encontrou mesa
		printf("\nmesas sem capacidade ou ocupadas\n");
		printf("\nverifique a capacidade introduzida,se estiver correta adicione a lista d espera\n");
		getchar();
	}
}

int visualiza(pmesa mesas,pemp empr){
	int idp;
	float subtotal;
	pmesa auxm;
	pemp auxe;
	qiten auxi;
	//funçao para vizualizar itens da mesa
	printf("\nIntroduza o ID da mesa que deseja visualizar: ");
	do{
		scanf("%d",&idp);
	}while(idp<1);
	getchar();
	
	auxm=mesas;
	while((auxm!=NULL)&&(auxm->id!=idp))//procura mesa
		auxm=auxm->prox;
	
	if(auxm==NULL){
		printf("\nID invalido");//ID introduzido invalido
		getchar();
		return;
	}
	if(auxm->livre==0){
		printf("\nMesa %d livre\n",idp);//mesa livre
		getchar();
		return;
	}
	if((auxm->livre!=0)&&(auxm->idemp==0)){//mesa com conta tirada
		printf("\nmesa ainda ocupada\n");
		getchar();
		return;
	}
	auxe=empr;
	printf("\nMesa: %d\n\n",idp);
	while(auxe->id!=auxm->idemp)//procura empregado da mesa
		auxe=auxe->prox;
	printf("Empregado: %s\n\n",auxe->nome);
	if(auxm->itens==NULL){
		printf("\nSem Itens\n");
		getchar();
		return;
	}
	printf("Itens\n");
	printf("qnt\tpreco(unit)\tnome\n\n");
	auxi=auxm->itens;
	subtotal=0;
	while(auxi!=NULL){//corre itens
		printf("%d\t%.2f\t%s\n",auxi->qua,auxi->preço,auxi->nome);
		subtotal=auxi->qua*auxi->preço+subtotal;
		auxi=auxi->prox;
	}
	printf("\n\nSubtotal: %.2f",subtotal);//subtotal da mesa
	getchar();
	return;
}

void libertar(pmesa mesas,pemp empr){
	int id;
	pmesa auxm;
	pemp auxe;
	//funçao que liberta mesa se conta tirada ou sem itens
	printf("\nIntroduza o ID da mesa que deseja libertar: ");
	do{
		scanf("%d",&id);
	}while(id<1);
	getchar();
	auxm=mesas;
	while((auxm->id!=id)&&(auxm!=NULL))//procura mesa
		auxm=auxm->prox;
	if(auxm==NULL){
		printf("\nID invalido\n");
		getchar();
		return;
	}
	if(auxm->livre==0){//mesa ja estava livre
		printf("\nA mesa ja esta livre\n");
		getchar();
		return;
	}
	if(auxm->itens!=NULL){//mesa ainda conte registos, logo nao fica livre
		printf("\nA mesa ainda tem itens registados\n");
		getchar();
		return;
	}
	auxe=empr;
	while((auxe!=NULL)&&(auxe->id!=auxm->idemp))//procura empregado
		auxe=auxe->prox;
	if(auxe!=NULL)
		auxe->mesas--;//decrementa mesa
	printf("\nMesa libertada\n");
	auxm->livre=0;//flags d ocupada postas a zero
	auxm->idemp=0;
	getchar();
}

void adicionaitens(pmesa mesas,pemp empr,pmenu menu){
	pmesa auxm;
	pemp auxe;
	pmenu p;
	qiten auxi,novo;
	//funçao para adicionar itens a uma mesa
	int x,id,idi,mul;
	char opc;

	printf("\nIntroduza o ID da mesa que deseja adicionar itens: ");
	do{
		scanf("%d",&id);
	}while(id<1);
	getchar();
	auxm=mesas;
	while((auxm!=NULL)&&(auxm->id!=id))//procura mesa
		auxm=auxm->prox;
	if(auxm==NULL){
		printf("\nID invalido\n");
		getchar();
		return;
	}
	if(auxm->livre==0){//mesa vazia
		printf("\nMesa Livre\n");
		getchar();
		return;
	}
	if((auxm->livre!=0)&&(auxm->idemp==0)){// ja pagaram que vao embora
		printf("\nMesa ja tem a conta tirada\n");
		getchar();
		return;
	}
	auxe=empr;
	while(auxm->idemp!=auxe->id)//procura empregado responsavel
		auxe=auxe->prox;
	printf("\nEsta mesa está atribuida ao : %s\ndeseja continuar?('s' ou 'S' para sim, outro para cancelar)\n .: ",auxe->nome);
	scanf("%c",&opc);
	getchar();
	if((opc!='s')&&(opc!='S')){
		printf("\nCancelado\n");
		getchar();
		return;
	}
	printf("\nIntroduza o codigo do Item\n(0---sair)\t(-1---introduzir multiplo para item)\n.:");
	do{
		scanf("%d",&idi);
		mul=1;
		if(idi==-1){//opçao multiplo
			printf("\nIntroduza o nro d vezes  deseja: ");
			scanf("%d",&mul);
			printf("\nIntroduza o codigo do Item\n");
			scanf("%d",&idi);
		}
		p=menu;
		while((p!=NULL)&&(p->id!=idi))//procura iten no menu
			p=p->prox;
		if(( p == NULL )&&( idi!=0 )){
			printf("\nID item invalido\n");
			getchar();
		}
		if(( p != NULL )&&( idi!=0 )){//adiciona
			
			if(auxm->itens==NULL){//1ºelemento
				novo=alloca();//chamada de funçao para malloc
				novo->id=p->id;//copia dados
				novo->qua=mul;
				novo->preço=p->preço;
				novo->prox=NULL;
				strcpy(novo->nome,p->nome);
				auxm->itens=novo;
			}else{//outro elemento
				auxi=auxm->itens;
				while((auxi->prox!=NULL)&&(auxi->id!=p->id))//corre itens da mesa a ver se ja existe
					auxi=auxi->prox;
				if(auxi->id==p->id)//ja existe
					auxi->qua=auxi->qua+mul;
				else{//novo iten
					novo=alloca();//chamada de funçao para malloc
					novo->id=p->id;//copia dados
					novo->qua=mul;
					novo->preço=p->preço;
					novo->prox=NULL;
					strcpy(novo->nome,p->nome);
					auxi->prox=novo;
				}
			}
			
			printf("\n\nAdicionado\n\n");
		}
	}while(idi!=0);
	getchar();
	return;
}

int alloca(){
	qiten novo;
	novo=malloc(sizeof(struct qitem));
	return novo;
}

void  removeitens(pmesa mesas,pmenu menu,pemp empr){
	pmesa auxm;
	pemp auxe;
	pmenu p;
	qiten auxi,ant=NULL;
	int id,idi,mul;
	char opc;

	//funçao para remover itens, pode-se activar a opçao d quantdade a remover

	printf("\nIntroduza o ID da mesa que deseja remover itens: ");
	do{
		scanf("%d",&id);
	}while(id<1);
	getchar();
	auxm=mesas;
	while((auxm!=NULL)&&(auxm->id!=id))
		auxm=auxm->prox;
	if(auxm==NULL){
		printf("\nID invalido\n");
		getchar();
		return;
	}
	if(auxm->livre==0){
		printf("\nMesa Livre\n");
		getchar();
		return;
	}
	if((auxm->livre!=0)&&(auxm->idemp==0)){
		printf("\nMesa ja tem a conta tirada\n");
		getchar();
		return;
	}
	auxe=empr;
	while(auxm->idemp!=auxe->id)
		auxe=auxe->prox;
	printf("\nEsta mesa está atribuida ao : %s\ndeseja continuar?('s' ou 'S' para sim, outro para cancelar)\n .: ",auxe->nome);
	scanf("%c",&opc);
	getchar();
	if((opc!='s')&&(opc!='S')){
		printf("\nCancelado\n");
		getchar();
		return;
	}
	printf("\nIntroduza o codigo do Item a remover\n(0---sair)\t(-1---introduzir multiplo para item)\n.:");
	scanf("%d",&idi);
	mul=1;
	if(idi==-1){//opçao de remover varios
		printf("\nIntroduza o nro d vezes  deseja: ");
		scanf("%d",&mul);
		printf("\nIntroduza o codigo do Item\n");
		scanf("%d",&idi);
	}
	p=menu;
	while((p!=NULL)&&(p->id!=idi))//procura item no menu
		p=p->prox;
	if(( p == NULL )&&( idi!=0 )){//nao exite item
		printf("\nID item invalido\n");
		getchar();
	}
	if(( p != NULL )&&( idi!=0 )){//encontrou o iten no menu
		auxi=auxm->itens;
		while((auxi->id!=NULL)&&(auxi->id!=idi)){//procura iten na mesa
			ant=auxi;
			auxi=auxi->prox;
		}
		if(auxi==NULL){
			printf("\nItem nao registado na mesa\n");
			getchar();
		}
		else{
			if(auxi->qua>mul)//se houver mais registados k a remover
				auxi->qua=auxi->qua-mul;
			else{//se quantidade a remover maior ou igual
				if(ant==NULL){//1º elemento
					ant=auxm->itens;
					auxm->itens=auxm->itens->prox;
					free(ant);
				}
				else{//outro elemento
					ant->prox=auxi->prox;
					free(auxi);
				}
			}
		}
		printf("\nremovido\n");
	}
	getchar();
	return;
}

void pagamento(pmesa mesas,pemp empr){
	pmesa auxm;
	pemp auxe;
	qiten auxi;
	phist auxh,novo;
	
	int id,idi;
	float total;
	char opc;
	//funçao para pagamento de mesa

	printf("\nIntroduza o ID da mesa que deseja a conta: ");
	do{
		scanf("%d",&id);
	}while(id<1);
	getchar();
	auxm=mesas;
	while((auxm!=NULL)&&(auxm->id!=id))//corre mesa ate ao fim ou encontrar mesa desejada
		auxm=auxm->prox;
	if(auxm==NULL){
		printf("\nID invalido\n");
		getchar();
		return;
	}
	if(auxm->livre==0){
		printf("\nMesa Livre\n");
		getchar();
		return;
	}
	if((auxm->livre!=0)&&(auxm->idemp==0)){//flag idemp=0 e livre=1, seja conta foi tirada mas a mesa ta ocupada ainda
		printf("\nMesa ja tem a conta tirada\n");
		getchar();
		return;
	}
	if(auxm->itens==NULL){// sem itens nao ha conta
		printf("\nMesa nao tem itens registados\n");
		getchar();
		return;
	}
	auxe=empr;
	while(auxm->idemp!=auxe->id)
		auxe=auxe->prox;
	printf("\nEsta mesa está atribuida ao : %s\ndeseja continuar?('s' ou 'S' para sim, outro para cancelar)\n .: ",auxe->nome);
	scanf("%c",&opc);
	getchar();
	if((opc!='s')&&(opc!='S')){
		printf("\nCancelado\n");
		getchar();
		return;
	}
	//imprmime para o ecra um tipo d factura
	printf("\n\nFactura eletronica\n");
	printf("\nMesa: %d\n\n",id);
	printf("Empregado: %s\n\n",auxe->nome);
	printf("Itens\n");
	printf("qnt\tpreco(unit)\tnome\n\n");
	auxi=auxm->itens;
	total=0;
	novo=malloc(sizeof(struct hist));
	novo->itens=auxm->itens;//manda itens para o registo
	while(auxi!=NULL){//corre lista itens e guarda total
		printf("%d\t%.2f\t%s\n",auxi->qua,auxi->preço,auxi->nome);
		total=auxi->qua*auxi->preço+total;
		auxi=auxi->prox;
	}
	printf("\n\ntotal: %.2f",total);
	printf("\n\nObrigado pela sua visita\n");
	getchar();
	novo->total=total;//total para registo
	strcpy(novo->st,auxe->nome);//empregado responsavel pel atendimento
	novo->prox=NULL;
	if(auxm->registo==NULL)//linka lista
		auxm->registo=novo;
	else{
		auxh=auxm->registo;
		while(auxh->prox!=NULL)//corre registos linka lista
			auxh=auxh->prox;
		auxh->prox=novo;
	}
	auxm->itens=NULL;
	auxm->idemp=0;//flag
	auxe->mesas-1;//flag
}