
#include <stdio.h>
#include "structs.h"

char menuinicial(){
	char op;
	printf("\n [Menu Inicial]\n\n");
	printf("1 - Inserir Mesa\n");
	printf("2 - Eleminar Mesa\n");
	printf("3 - consultar Mesas\n");
	printf("4 - Inserir Item\n");
	printf("5 - Alterar Item\n");
	printf("6 - Remover Item\n");
	printf("7 - Consultar Itens\n");
	printf("\n8 - Iniciar Dia\n");
	do{
		printf("\nOpcao: ");
		scanf("%c", &op);
		getchar();
	}while(op!='1' && op!='2' && op!='3' && op!='4' && op!='5' && op!='6' && op!='7' && op!='8');
	return op;
}

char menuprincipal(){
	char op;
	printf("\n [Menu Principal]\n\n");
	printf("1 - Menu Mesas\n");
	printf("2 - Menu Empregados\n");
	printf("3 - Consultar MENU\n");
	printf("4 - Consultar mesas\n");
	printf("5 - Consultar registo mesa\n");
	printf("\n6 - FAZER BACKUP!\n");
	printf("\n7 - Fechar Dia\n");
	do{
		printf("\nOpcao: ");
		scanf("%c", &op);
		getchar();
	}while(op!='1' && op!='2' && op!='3' && op!='4' && op!='5' && op!='6' && op!='7');
	return op;
}

char menumesas(){
	char op;
	printf("\n [Menu Mesas]\n\n");
	printf("1 - Adicionar Mesa(manual)\n");
	printf("2 - Associar Mesa(auto)\n");
	printf("3 - Adiconar Itens\n");
	printf("4 - Remover Itens\n");
	printf("5 - Pagamento\n");
	printf("6 - Libertar Mesa\n");
	printf("7 - Consultar Mesas\n");
	printf("8 - Menu Espera\n");
	printf("\n9 - Voltar\n");
	do{
		printf("\nOpcao: ");
		scanf("%c", &op);
		getchar();
	}while(op!='1' && op!='2' && op!='3' && op!='4' && op!='5' && op!='6' && op!='7' && op!='8' && op!='9');
	return op;
}

char menuempregados(){
	char op;
	printf("\n [Menu Empregados]\n\n");
	printf("1 - Registar Empregado\n");
	printf("2 - Libertar Empregado\n");
	printf("3 - Visualizar Empregados\n");
	printf("\n4 - Voltar\n");
	do{
		printf("\nOpcao: ");
		scanf("%c", &op);
		getchar();
	}while(op!='1' && op!='2' && op!='3' && op!='4');
	return op;
}


int menuprinc(pmenu menu, pmesa mesas, pemp empr,pesp le){
	char op;
	do{
		system("cls");
		op=menuprincipal();
		switch(op){
			case '1': le=menumes(mesas,empr,menu,le);break;
			case '2': empr=menuemp(empr);break;
			case '3': mostramen(menu);break;
			case '4': mostramesa(mesas);break;
			case '5': histmesa(mesas);break;
			case '6': backup(le,mesas,empr);break;
			case '7': op=questao(mesas);break;
		}
	}while(op!='8');
}


int menuemp(pemp empr){
	char op;
	do{
		system("cls");
		op=menuempregados();
		switch(op){
			case '1': empr=regemp(empr); break;
			case '2': empr=libemp(empr); break;
			case '3': veremp(empr); break;
		}
	}while(op!='4');
	return empr;
}

int menumes(pmesa mesas,pemp empr,pmenu menu,pesp le){
	char op;
	do{
		system("cls");
		op=menumesas();
		switch(op){
			case '1': sentar(mesas,empr);break;
			case '2': associar(mesas,empr);break;
			case '3': adicionaitens(mesas,empr,menu);break;
			case '4': removeitens(mesas,menu,empr);break;
			case '5': pagamento(mesas,empr);break;
			case '6': libertar(mesas,empr);le=testle(le,mesas,empr); break;
			case '7': visualiza(mesas,empr); break;
			case '8': le=menulista(le,mesas); break;
		}
	}while(op!='9');
	return le;
}

char listaespera(){
	char op;
	printf("\n [Menu Lista de espera]\n\n");
	printf("1 - Adicionar grupo\n");
	printf("2 - Desistencia\n");
	printf("3 - Ver lista\n");
	printf("\n4 - Voltar\n");
	do{
		printf("\nOpcao: ");
		scanf("%c", &op);
		getchar();
	}while(op!='1' && op!='2' && op!='3' && op!='4');
	return op;
}
int menulista(pesp le,pmesa mesas){
	char op;
	do{
		system("cls");
		op=listaespera();
		switch(op){
			case '1': le=inserele(le,mesas);break;
			case '2': le=desitle(le,0);break;
			case '3': mostrale(le);break;
		}
	}while(op!='4');
	return le;
}



int questao(pmesa mesas){
	char c;
	pmesa auxm;
	// questao para sair e alertar, pois isto sera o fim 
	auxm=mesas;
	while((auxm!=NULL)&&(auxm->idemp==0))
		auxm=auxm->prox;
	if(auxm!=NULL){
		printf("ainda tem mesas ocupadas");
		getchar();
		return '0';
	}
	printf("\ntem a certeza que deseja fechar o dia?\n\nESTA ACCAO E IRREVERSIVEL!!!\n\n('s' ou 'S' para sim, outro para nao)\n.: ");
	scanf("%c",&c);
	getchar();
	if((c!='s')&&(c!='S'))
		return '0';
	return '8';
}