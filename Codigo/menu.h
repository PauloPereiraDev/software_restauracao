typedef struct emp *pemp;
typedef struct mitem  *pmenu;
typedef struct mesa *pmesa;
typedef struct espera *pesp;

char menuinicial();
int menuprinc(pmenu menu, pmesa mesas, pemp empr,pesp le);
pemp menuemp(pemp empr);
int menumes(pmesa mesas,pemp empr,pesp le);
