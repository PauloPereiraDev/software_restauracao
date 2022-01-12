typedef struct mitem  *pmenu; /* declaraçao do ponteiro para menu*/
typedef struct mesa *pmesa; //declaraçao do ponteiro pa mesas
typedef struct qitem *qiten; //dec. d pont pa itens com quant
typedef struct hist *phist; //pont para historico da mesa
typedef struct emp *pemp;//pont para lista empregados
typedef struct espera *pesp; //ponteiro pa lista de espera
typedef struct fact *pno; //ponteiro auxiliar para facturar empregados

struct mitem{   /* para criar lista do menu*/
	char nome[100]; /* nome do item */
	int id; /* identificador numérico */
	float preço; /* preço unitário do item */
	pmenu prox; //apontador para porximo
};
struct qitem{   /* para criar lista do menu*/
	char nome[100]; /* nome do item */
	int id,qua; /* identificador numérico */
	float preço; /* preço unitário do item */
	qiten prox; //apontador para porximo
};
struct item{   //para ler do ficheiro
	char nome[100]; /* nome do item */
	int id; /* identificador numérico */
	float preço; /* preço unitário do item */
};
struct mesa{
	int id,cap,livre,idemp; //identificador,capacidade, flag para mesa livre ou ocupada
	qiten itens; //lista para itens na mesa se ocupada
	phist registo; //lista para historico da mesa
	pmesa prox; //ponteiro para proxima mesa
};

struct hist{
	char st[100];//nome
	qiten itens;//lista d itens consuidos
	float total;//total conta
	phist prox;//ponteiro para prox
};


struct emp{
	char nome[100];//nome
	int id;//identificador
	int mesas;//nro mesas a atender
	pemp prox;//pont para proximo
};

struct espera{
	int pessoas,id;//nro pessoas
	char nome[100];//nome  de quem esta em espera
	pesp prox;//pont para proximo elemento
};

struct fact{
	char nome[100];//nome empregado
	float factu;//quant d facturaçao
	pno prox;//pont para proximo empr
};

//*************Estruturas auxiliares pa fazer backup,escrever no ficheiro sem ocupar o espaço do ponteiro ?!!?******************//

struct fichmesa{
	int cap,id,idemp,livre,it,reg;
};

struct fichemp{
	int id,mesas;
	char nome[100];
};

struct fichesp{
	int pessoas,id;
	char nome[100];
};

struct fichhist{
	char st[100];
	float total;
	int idmesa,it;
};

struct fichitens{
	int id,qua;
	char nome[100];
	float preco;
	int idmesa,reg;
};