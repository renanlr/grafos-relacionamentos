#include <stdio.h>

typedef struct g{
    char * nome;
    char * matricula;
    void * amigos;
}aluno;

int main() {
    int escape,opt = 1;
    do{
        printf("====================================================\n");
        printf("======================= Menu =======================\n");
        printf("====================================================\n");
        printf("\t 1) Imprimir em ordem de grau\n");
        printf("\t 2) Imprimir todos os vertices\n");
        printf("\t 3) Sair\n>>>");
        scanf("%d", &opt);
        switch(opt){
            case 1:
                break;
            case 2:
                break;
            case 3:
                escape = 0;
                break;
            default:
                break;
        }
    }while(escape);
    return 0;
}