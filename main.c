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
typedef struct l {
  struct l * prox;
  struct g * amigo;
  char *matricula;
} amigo;

//vértice do grafo
typedef struct g {
    char *nome;
    char *matricula;
    amigo *amigos;
} aluno;



aluno grafo_alunos[NV];

//protótipos de funções
int preencherGrafo();
char **str_split(char *, const char);
void menu();
aluno * buscaVertice(char *);
void novaAresta(amigo*, aluno *, char *);


//função que busca um vértice através de sua matrícula
aluno * buscaVertice(char * target){
  aluno *retorno = NULL;
  //varre a lista
  for (int i = 0; i < NV; i++) {
    if (strcmp((grafo_alunos[i].matricula), target) == 0){
      retorno = &grafo_alunos[i];
      //se encontra o vértice retorna o endereço do vértice
      //printf("achou\n");
      return retorno;
    }
  }
  //se não retorna um ponteiro nulo
  //printf("não achou\n");
  return retorno;
}

void novaAresta(amigo * lista, aluno * amigo, char *matricula){
  struct l novo;
  novo.amigo = (aluno*) &amigo;
  novo.matricula = matricula;

  if (lista == NULL) {
    lista = &novo;
  }
  else{
    novo.prox = (struct l *) &lista;
    lista = &novo;
  }
}

//invoca o menu
void menu(){
  int escape = 1, opt;

  do {
      printf("\t====================================================\n");
      printf("\t======================= Menu =======================\n");
      printf("\t====================================================\n");
      printf("\t========== 1) Imprimir em ordem de grau  ===========\n");
      printf("\t========== 2) Imprimir todos os vertices ===========\n");
      printf("\t========== 3) Sair                       ===========\n");
      printf("\t====================================================\n");
      printf("\t====================================================\n");
      printf("\t====================================================\n\t>>>");
      scanf("%d", &opt);
      switch (opt) {
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
  } while (escape);
}



int preencherGrafo() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    int i,j=0;

    //abre-se o arquivo
    fp = fopen("amigos_tag20171.txt", "r");
    if (fp == NULL) {
        return -1;
    }


    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        tokens = str_split(line, ',');

        if (tokens) {
            //inicializando a lista de amigos como uma lista vazia
            grafo_alunos[j].amigos = NULL;
            //inserindo nome do aluno no grafo
            grafo_alunos[j].nome = *(tokens);
            printf("Nome=%s\n",grafo_alunos[j].nome);
            //inserindo matricula do aluno
            grafo_alunos[j].matricula = *(tokens + 1);
            printf("Matricula=%s\n",grafo_alunos[j].matricula);
            // /inserindo matricula de amigos
            for (i = 2; *(tokens + i); i++) {
                printf(" %s - ", *(tokens + i));
                free(*(tokens + i));
            }
            printf("\n");
            free(tokens);
        }
        j++;
    }
    fclose(fp);
    return 0;
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
    int escape = 1, opt;
    preencherGrafo();
    //buscaVertice("kiko");
    //buscaVertice("130028959");
    menu();

    return 0;
}
