/*
@jeffvfa
@renanlr
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NV 39

//elemento da lista de adjacência, aresta
typedef struct amg {
    struct amg *prox;
    struct aln *amigo;
    char *matricula;
} amigo;

//vértice do grafo
typedef struct aln {
    char *nome;
    char *matricula;
    int numAmigos;
    amigo *amigos;
} aluno;


aluno grafo_alunos[NV];

//protótipos de funções
int preencherGrafo();

void strip(char *);

void ligarAmigos();

void imprimirPorGrau();

char **str_split(char *, const char);

void menu();

aluno *buscaVertice(char *);

int contaMaxAmigos();

aluno *maisAmigos();

int maiorClique();

int achaCLique(aluno); 

int eAmigo(aluno, aluno);

//
/*
int eAmigo(aluno alvo, aluno duvida){ 
	if(strcmp(alvo.matricula, duvida.matricula) == 0){ 
		return 0; 	
	} 
	else if ()	
}*/

/*int maiorClique(aluno * noinicio){ 
	int cliqueMaior = 0, parcial; 
	for(int i = 0; i < NV; i++){ 
		parcial = achaCLique(grafo_alunos[1]);
		parcial > cliqueMaior? parcial : cliqueMaior;
	} 
	return cliqueMaior;
} */

aluno *maisAmigos() {
    int i, maisAmigos = 0;
    aluno *aluno = NULL;
    for (i = 0; i < NV; i++) {
        maisAmigos = grafo_alunos[i].numAmigos > maisAmigos ? grafo_alunos[i].numAmigos : maisAmigos;
        aluno = grafo_alunos[i].numAmigos > maisAmigos ? &grafo_alunos[i] : aluno;
    }
    return aluno;
}

//retorna a maior quantidade de amigos
int contaMaxAmigos() {
    int i, maisAmigos = 0;
    for (i = 0; i < NV; i++) {
        maisAmigos = (grafo_alunos[i].numAmigos) > maisAmigos ? grafo_alunos[i].numAmigos : maisAmigos;
    }
    return maisAmigos;
}

//função que busca um vértice através de sua matrícula
aluno *buscaVertice(char *target) {
    aluno *retorno = NULL;
    //varre a lista
    int i;
    for (i = 0; i < NV; i++) {
        if (strcmp((grafo_alunos[i].matricula), target) == 0) {
            //se encontra o vértice retorna o endereço do vértice
            retorno = &grafo_alunos[i];
            return retorno;
        }
    }
    //se não retorna um ponteiro nulo
    return retorno;
}

//invoca o menu
void menu() {
    int escape = 1, opt;

    do {
        system("clear||cls");
        printf("\t====================================================\n");
        printf("\t======================= Menu =======================\n");
        printf("\t====================================================\n");
        printf("\t========= 1) Imprimir em ordem de grau    ==========\n");
        printf("\t========= 2) Imprimir o maior clique      ==========\n");
        printf("\t========= 3) Sair                         ==========\n");
        printf("\t====================================================\n");
        printf("\t====================================================\n");
        printf("\t====================================================\n\t>>>");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                system("clear||cls");
                imprimirPorGrau();
                break;
            case 2:
                system("clear||cls");
                maiorClique();
                break;
            case 3:
                system("clear||cls");
                escape = 0;
                break;
            default:
                break;
        }
    } while (escape);
}

void maiorClique(){
    printf("Cliquezão");
}

void imprimirPorGrau() {
    int i = 0, j = 0, k = 0, l = 0;
    aluno grafo_alunos_ordenado[NV];
    aluno temp, aux;
    grafo_alunos_ordenado[0] = grafo_alunos[0];
    ++k;
    for (i = 1; i < NV; ++i) {
        for (j = 0; j < k; ++j) {
            if (grafo_alunos[i].numAmigos >= grafo_alunos_ordenado[j].numAmigos) {
                ++k;
                temp = grafo_alunos_ordenado[j];
                grafo_alunos_ordenado[j] = grafo_alunos[i];
                for (l = j + 1; l < k; ++l) {
                    aux = grafo_alunos_ordenado[l];
                    grafo_alunos_ordenado[l] = temp;
                    temp = aux;
                }
                break;
            } else if (j == (k - 1)) {
                grafo_alunos_ordenado[j + 1] = grafo_alunos[i];
                ++k;
                break;
            }
        }
    }
    for (i = 0; i < NV; ++i) {
        printf("\t%s %s %d amigos\n", grafo_alunos_ordenado[i].matricula, grafo_alunos_ordenado[i].nome,
               grafo_alunos_ordenado[i].numAmigos);
    }
    printf("\n\tPressione uma tecla para voltar ao menu\n");
    getchar();
    getchar();
}


int preencherGrafo() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    int i, j = 0;
    aluno *alvo;

    //abre-se o arquivo
    fp = fopen("amigos_tag20171.txt", "r");
    if (fp == NULL) {
        return -1;
    }


    while ((read = getline(&line, &len, fp)) != -1) {
        strip(line);
        // Separando linha por virgulas
        tokens = str_split(line, ',');
        if (tokens) {
            //inicializando a lista de amigos como uma lista vazia
            grafo_alunos[j].amigos = NULL;
            //inserindo nome do aluno no grafo
            grafo_alunos[j].nome = *(tokens);
            //inserindo matricula do aluno
            grafo_alunos[j].matricula = *(tokens + 1);

            // inserindo matricula de amigos

            /*
            a ideia aqui está certa, porém temos que fazer 2 passadas, pois podemos
            querer referenciar algúem que não está no vetor ainda
            */
            amigo *ultimoDaLista;
            grafo_alunos[j].amigos = malloc(sizeof(amigo));
            ultimoDaLista = grafo_alunos[j].amigos;
            for (i = 2; *(tokens + i); i++) {

                //alvo = buscaVertice(*(tokens + i));

                //novaAresta(grafo_alunos[j].amigos, alvo, *(tokens + i));
                ultimoDaLista->matricula = *(tokens + i);
                ultimoDaLista->prox = malloc(sizeof(amigo));
                ultimoDaLista = ultimoDaLista->prox;

            }

            grafo_alunos[j].numAmigos = i - 2;

            printf("\n");
        }
        j++;
    }
    fclose(fp);
    ligarAmigos();
    return 0;
}

// Este método deve relacionar a lista de amigos com o seu respectivo nó
void ligarAmigos() {
    int k;
    amigo *elementoLista;
    for (k = 0; k < NV; k++) {
        elementoLista = grafo_alunos[k].amigos;
        while (elementoLista->matricula != NULL) {
            elementoLista->amigo = buscaVertice(elementoLista->matricula);
            elementoLista = elementoLista->prox;
        }
    }
}

void strip(char *s) {
    char *p2 = s;
    while (*s != '\0') {
        if (*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
}

char **str_split(char *a_str, const char a_delim) {
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result) {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main() {
    preencherGrafo();
    menu();

    return 0;
} 


