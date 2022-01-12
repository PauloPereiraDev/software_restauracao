typedef struct mitem  *pmenu;
typedef struct mesa  *pmesa;
typedef struct emp *pemp;
typedef struct espera *pesp;

pmenu abremenu(pmenu menu);
pmesa abremesas(pmesa mesas);
void imprime(pmesa mesas);
void backup(pesp le,pmesa mesas,pemp empr);
int carregabackup(pmesa mesas);
int backupemp(pemp empr);
int backuple(pesp le);