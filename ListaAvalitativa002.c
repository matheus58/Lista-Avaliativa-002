#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ESTUD_TOTAL 15

// Espaço para criação das Structs
struct Professor {
  char nome[50];
  char funcional[20];
  char titulacao[20];
  char id_codigo[20];
};

struct Estudante {
  char nome[50];
  char matricula[20];
  char cursa_disciplina[50];
  int idade;
  /*menção disciplina*/
};

struct Disciplina {
  char nome[50];
  char ch[20];
  char id_codigo[20];
  char professor_responsavel[70]; /*meção professor*/
  struct Estudante estudante[ESTUD_TOTAL];
};

void le_valida_idade(struct Estudante estudante[], int i) {
  printf("\n\tInforme a Idade:");
  scanf("%d", &estudante[i].idade);

  while (estudante[i].idade < 16 || estudante[i].idade > 26) {
    printf("\n!! INAPTO !!\n");
    printf("Informe novamente a idade do aluno :");
    scanf("%d", &estudante[i].idade);
  }
}

void bubble_sort_crescente(struct Estudante estudante[], int qntd) { // vai deixar na forma decrescente
  int i, j;
  struct Estudante aux;

  for (i = 0; i < qntd - 1; i++) {
    for (j = 0; j < qntd - i - 1; j++) {
      if (estudante[j].idade > estudante[j + 1].idade) {
        aux = estudante[j];
        estudante[j] = estudante[j + 1];
        estudante[j + 1] = aux;
      }
    }
  }
}

void bubble_sort_decrescente(struct Estudante estudante[], int qntd) { // vai deixar na forma decrescente
  int i, j;
  struct Estudante aux;

  for (i = 0; i < qntd - 1; i++) {
    for (j = 0; j < qntd - i - 1; j++) {
      if (estudante[j].idade < estudante[j + 1].idade) {
        aux = estudante[j];
        estudante[j] = estudante[j + 1];
        estudante[j + 1] = aux;
      }
    }
  }
}

int main(void) {
  int i, ret1, ret2;
  int qntd = 0, primeira_turma = 0, segunda_turma = 0;

  struct Professor professor[3];
  struct Disciplina disciplina[2];
  struct Estudante estudante[15];

  strcpy(professor[0].nome, "Antonio Cleber da Silva");
  strcpy(professor[0].funcional, "UC001");
  strcpy(professor[0].titulacao, "Mestrado");
  strcpy(professor[0].id_codigo, "p1");

  strcpy(professor[1].nome, "Bernardo Moreira de Jesus");
  strcpy(professor[1].funcional, "UC002");
  strcpy(professor[1].titulacao, "Mestrado");
  strcpy(professor[1].id_codigo, "p2");

  strcpy(professor[2].nome, "Carlos Alberto Goncalves");
  strcpy(professor[2].funcional, "UC003");
  strcpy(professor[2].titulacao, "Doutorado");
  strcpy(professor[2].id_codigo, "p3");

  strcpy(disciplina[0].nome, "Programacao Estruturada");
  strcpy(disciplina[0].ch, "80h"); 
  strcpy(disciplina[0].id_codigo, "d1"); 
  strcpy(disciplina[0].professor_responsavel,
         "Antonio Cleber da Silva & Bernardo Moreira de Jesus");

  strcpy(disciplina[1].nome, "Sistemas Operacionais");
  strcpy(disciplina[1].ch, "120h");
  strcpy(disciplina[1].id_codigo, "d2");
  strcpy(disciplina[1].professor_responsavel, "Carlos Alberto Goncalves");

  printf("+------------------------INICIO------------------------+\n");
  printf("\nDIGITE UMA QUANTIDADE ENTRE 0 A 15 ESTUDANTES\n");
  printf("\n\tValor: ");
  scanf("%d", &qntd);

  while (qntd < 0 || qntd > 15) {
    printf("\n\tInsira um valor valido entre 0 a 15!");
    printf("\n\t>Valor: ");
    scanf("%d", &qntd);
  }

  printf("\nDIGITE A QUANTIDADE DE ESTUDANTES INGRESSADOS NA TURMA DE "
         "PROGRAMACAO ESTRUTURADA\n");
  printf("\n\tLimite entre 0 a 10 estudantes por turma!!");
  printf("\n\tEstudantes restantes (%d)\n", qntd);

  do {
    printf("\n\tValor: ");
    scanf("%d", &primeira_turma); // TURMA DE PROGRAMACAO ESTRUTURADA

    if (primeira_turma < 0 || primeira_turma > 10) {
      printf("\n\tLimite de estudantes atingido! (0-10)");
    }
  } while (primeira_turma < 0 || primeira_turma > 10);

  printf(
      "\nO RESTANTE FOI REDIRECIONADO PARA TURMA DE SISTEMAS OPERACIONAIS\n");

  segunda_turma = qntd - primeira_turma;

  printf("\n\t!Estudantes registrados (Programacao Estruturada): %d !",
         primeira_turma);
  printf("\n\t!Estudantes registrados (Sistemas Operacionais): %d !\n\n",
         segunda_turma);

  /*--------------------------------------------------------------------------------*/
  for (int a = 0; a < primeira_turma; a++) {
    printf("\n+-------------------------------+\n");
    printf("|    Cadastro do %do estudante   |\n", a + 1);
    printf("|    Programacao Estruturada    |\n");
    printf("+-------------------------------+\n");
    printf("\n\tInforme o nome: ");
    scanf(" %[^\n]s", &estudante[a].nome);

    le_valida_idade(estudante, a);
  }
  
  printf("\n");
  printf("+-+-+-+-+-+-SEGUNDA-TURMA-+-+-+-+-+-+\n");
  //  for (int b = primeira_turma, c = primeira_turma; b + 1 < segunda_turma ||
  //  c > segunda_turma; //b++, c--) {
  int d = 0;
  for (int b = primeira_turma; b < qntd; b++) {
    printf("\n+-------------------------------+\n");
    printf("|    Cadastro do %do estudante   |\n", d + 1);
    printf("|    Sistemas Operacionais      |\n");
    printf("+-------------------------------+\n");
    printf("\n\tInforme o nome: ");
    scanf(" %[^\n]s", &estudante[b].nome);

    le_valida_idade(estudante, b);
    d++;
  }

  printf("\n+----------------------------------------------------+\n");
  printf("| 1o RELATORIO - DISCIPLINA: Programacao Estruturada|\n");
  printf("+----------------------------------------------------+\n");

  for (int e = 0; e < primeira_turma; e++) {
    bubble_sort_crescente(estudante, primeira_turma);

    strcpy(estudante[e].cursa_disciplina, disciplina[0].nome);
    

    ret1 = strcmp(estudante[e].cursa_disciplina, disciplina[0].nome); // comparacao de strings

    if (ret1 == 0) {
      // codigo disciplina , nome professor, nome estudante, idade estudante
      printf("\tNome do estudante: %s\n", estudante[e].nome);
      printf("\tIdade: %d\n", estudante[e].idade); // correto
      printf("\tCodigo da disciplina: %s\n", disciplina[0].id_codigo);
      printf("\tNome do professor: %s", disciplina[0].professor_responsavel);
    }
    printf("\n----------------------------------------------------\n");
  }

  
  printf("\n+----------------------------------------------------+\n");
  printf("|  2o RELATORIO - DISCIPLINA: Sistemas Operacionais  |\n");
  printf("+----------------------------------------------------+\n");
  printf("\n");

  for (int f = 0; f < segunda_turma; f++){
    bubble_sort_decrescente(estudante, segunda_turma);
  
    strcpy(estudante[f].cursa_disciplina, disciplina[1].nome);
    ret2 = strcmp(estudante[f].cursa_disciplina, disciplina[1].nome);

    if(ret2==0){
      printf("\tNome do estudante: %s\n", estudante[f].nome);
      printf("\tIdade: %d\n", estudante[f].idade); 
      printf("\tCodigo da disciplina: %s\n", disciplina[1].id_codigo);
      printf("\tNome do professor: %s", disciplina[1].professor_responsavel);
      
    }
    printf("\n----------------------------------------------------\n");
  }
  return 0;
}