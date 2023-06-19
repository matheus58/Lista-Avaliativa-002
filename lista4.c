#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Fabrica{
  char marca[100];//Alocação dinamica
  char site[40];
  char uf[2];
  char telefone[30];
  char marcaProvisoria[100];
};

struct Produto{
  char descricao[100];//Alocação dinamica
  float peso;
  float compra;
  float venda;
  float lucro;
  float percentual;
  struct Fabrica fabricante;
  char descricaoProvisoria[100];//Alocação dinamica
};

//Prototipaçao Funcoes :
int QuantidadeFabricante (int qnt); //quantidade de fabricas;
int QuantidadeProduto(int qnt);
//todos os menus/relatorio :
int MenuPrincipal(int *seletor, int qnt_produto, int qnt_fabricante, struct Fabrica *fabrica[], struct Produto *produto[]);
void ufs_escolhidas_pelo_fabricante(struct Fabrica *fabrica, int con);
//void ufs_disoniveis_para_pesquisa(struct Fabrica*fabrica); // deve ser colocado dentro do menu principal na opcao 3
void Opcao1(struct Fabrica* fabrica, int qnt_fabricante);
void Opcao2(struct Produto* fabrica, int qnt_produto);
void Opcao3(struct Fabrica* fabrica, struct Produto* produto, int qnt_fabrica,int qnt_produto);
void Opcao4(struct Produto* produto, int qnt_produto);
void Opcao5(struct Produto* produto, int qnt_produto);
void Opcao6(struct Produto* produto, int qnt_produto);
void Opcao7(struct Produto* produto, int qnt_produto);
void Opcao8(struct Produto* produto, int qnt_produto);
void Opcao9(struct Produto* produto, int qnt_produto);
void Opcao10(struct Produto* produto,int qnt_produto);
void Opcao11 (struct Fabrica* fabrica, int qnt_fabricante);
void ODENA(int qnt_produto, int produto, int x);
double ValidaPeso(void);
float ValidaCompra(void);
float ValidaVenda(void);

//fim da funcoa 

int main (void){//Inicio main
//Area de variaveis geras:
  int qnt_fabricante;
  int qnt_produto;
  int seletorUF;
  int seletorFabrica;
  int seletorRelatori;
  int ret;
  int retorno;
  
            //cadastro fabricante :
            struct Fabrica* fabrica;
            struct Produto* produto;
            
            // Obtenção da quantidade de fabricantes e produtos
            qnt_fabricante = QuantidadeFabricante(qnt_fabricante);
            qnt_produto = QuantidadeProduto(qnt_produto);
            
            // Alocação dinâmica dos arrays
            fabrica = malloc(qnt_fabricante * sizeof(struct Fabrica));
            produto = malloc(qnt_produto * sizeof(struct Produto));
            
            // Verificação se a alocação foi bem-sucedida
            if (fabrica == NULL || produto == NULL) {
              printf("Erro ao alocar memória.\n");
              exit(1);  // ou retorne um código de erro adequado
            }
  
            for(int con=0; con < qnt_fabricante;con++){//inicio for
                printf("+---------------------------------------------------+\n");
                printf("Cadastro Fabricante (%d)\n\n", con+1);
                printf("Informe o nome do Fabricante: ");
                scanf(" %[^\n]s", &fabrica[con].marca);
                printf("\nInforme o site do Fabricante: ");
                scanf(" %[^\n]s", &fabrica[con].site);
                printf("\nInforme o telefone do Fabricante: ");
                scanf(" %[^\n]s", &fabrica[con].telefone);
                printf("\n");
                ufs_escolhidas_pelo_fabricante(fabrica, con);
                printf("\n\t>Fabricante UF (%d): %s\n",con+1, fabrica[con].uf);
                }//Fechamento do FOR   //fim do cadastro do fabricante ;

              
            //cadastro produto:
            for(int con=0; con < qnt_produto;con++){//incio for: 
                printf("+---------------------------------------------------+\n");
                printf("Cadastro Produto (%d)\n\n", con+1);
                printf("Informe o nome do produto: ");
                scanf(" %[^\n]s", &produto[con].descricao);
              
                produto[con].peso = ValidaPeso();
                produto[con].compra = ValidaCompra();
                produto[con].venda = ValidaVenda();
              
                produto[con].lucro = produto[con].venda - produto[con].compra;
                produto[con].percentual = produto[con].lucro * 100 / produto[con].venda;
              
                printf("\nLucro: %.2f\nPercentual: %.2f%%\n", produto[con].lucro, produto[con].percentual);//Referencia provisória (TESTE)
                printf("\nEscolha entre as opcoes abaixo: \n");

                //FOR para imprimir as fabricas
                for(int i = 0 ; i < qnt_fabricante ; i++){
                  printf("\t[%i] %s\n",i+1,fabrica[i].marca);
                } 

                //DO WHILE para verificar
                do {
                    //Ta tendo erro com o CHAR, repetição infinita;
                  printf("\n Digite: ");
                  scanf("%d", &seletorFabrica);
                
                  if (seletorFabrica < 1 || seletorFabrica > qnt_fabricante) {
                    printf("\n\t!Opcao incorreta. Digite novamente!\n");
                  } 
                } while (seletorFabrica < 1 || seletorFabrica > qnt_fabricante);
                
                strcpy(produto[con].fabricante.marca, fabrica[seletorFabrica - 1].marca);
                strcpy(produto[con].fabricante.uf, fabrica[seletorFabrica - 1].uf);
                
                printf("\nMarca do produto (%s): %s\n", produto[con].descricao, produto[con].fabricante.marca);
                printf("\nUF do produto (%s): %s\n", produto[con].descricao, produto[con].fabricante.uf);
                } //Fechamento do FOR produto; //fim do cadastro do produto; 
  
                //Função para o relatório
                do{
                  retorno = MenuPrincipal(&seletorRelatori, qnt_produto, qnt_fabricante, fabrica, produto);
                   // printf("\nretorno = %d", retorno);
                }while(retorno != 0);
        
return 0;
}//Fim main;


// funçoes :
double ValidaPeso(void) {
  double peso;
    do {
        printf("\nInforme o peso do produto em gramas entre 50 a 50000: ");
        scanf("%lf", &peso);
        if(peso < 50){
          printf(">O peso digitado foi menor que 50 gramas, digite novamente!\n");
        }
        else if(peso > 50000){
            printf(">O peso digitado foi maior que 50000 gramas, digite novamente!\n");
        }
    } while (peso < 50 || peso > 50000);
return peso;
}

float ValidaCompra(void){
  float compra;
    do{
        printf("\nInforme o valor de compra do produto entre R$0,50 a R$8.000: ");
        scanf(" %f", &compra);
        if(compra < 0.5){
          printf(">O valor de compra foi menor que R$0,50, digite novamente!\n");
        }
        if(compra > 8000){
            printf(">O valor de compra foi maior que R$8.000, digite novamente!\n");
          }
    }while(compra < 0.5 || compra > 8000);
return compra;
}

float ValidaVenda(void){
  float venda;
    do{
        printf("\nInforme o valor de venda do produto entre R$1,00 a R$10.000: ");
        scanf(" %f", &venda);
        if(venda < 1){
          printf(">O valor de venda foi menor que R$1,00, digite novamente!\n");
        }
        if(venda > 10000){
          printf(">O valor de venda foi maior que R$10.000, digita novamnte!\n");
        }
    }while(venda < 1 || venda > 10000
      );
return venda;
}

int QuantidadeFabricante (int qnt){//inicio funçoes:
 //quantidade de fabricantes:
    printf("+---------------------------------------------------+\n");
    printf("Informe o numero de fabricantes a serem registrados \n");
    printf("Entre 2 a 5 fabricantes \n\n");
    do {
        while (1) {
          printf(" Digite: ");
          if (scanf("%d", &qnt) == 1) {//incio if
              break;
          } else {//fim if //inicio elese
              printf("\n\t!Digite um numero. Tente novamente!.\n\n");
              // Limpar o buffer de entrada para evitar repetições infinitas
              while (getchar() != '\n');
          }//fim else 
        }//Fechamento While
  
        if(qnt < 2 || qnt > 5){
               printf("\n\t!Numero invalido. Tente novamente!.\n\n");
        }
        else{}
    } while (qnt < 2 || qnt > 5);
    //fim do quantidade fabricante ;
return qnt;
}//fim funcoe

int QuantidadeProduto (int qnt){//inicio funçoes:
 //quantidade de fabricantes:
    printf("+---------------------------------------------------+\n");
    printf("Informe o numero de produto a serem registrados \n");   
    printf("Entre 5 a 50 produtos \n\n");
    do {
        while (1) {
          printf(" Digite: ");
          if (scanf("%d", &qnt) == 1) {//incio if
              break;
          } else {//fim if //inicio elese
              printf("\n\t!Digite um numero. Tente novamente!.\n\n");
              // Limpar o buffer de entrada para evitar repetições infinitas
              while (getchar() != '\n');
          }//fim else 
        }//Fechamento While
  
        if(qnt < 5 || qnt > 50){
               printf("\n\t!Numero invalido. Tente novamente!.\n\n");
        }
        else{}
    } while (qnt < 5 || qnt > 50);
    //fim do quantidade fabricante ;
return qnt;
}//Função Quantidade 

int MenuPrincipal(int *seletor, int qnt_produto, int qnt_fabricante, struct Fabrica *fabrica[], struct Produto *produto[]) {//abertura Menu:
    do{
        printf("+---------------------------------------------------+\n");
        printf("Relatorio\n\n");
        printf("Escolha uma opcao:\n");
        printf("[1] Listar todas as marcas\n");//funcionando
        printf("[2] Listar todos os produtos\n");//funcionando
        printf("[3] Listar os produtos de um determinado estado (Nao esta funcionando!!)\n");//Não está funcionando, tentamos ao maximo!!
        printf("[4] Listar os produtos de uma determinada marca\n");//funcionando
        printf("[5] Apresentar o(s) estado(s) onde esta resgistrado o produto mais caro\n");//funcionando
        printf("[6] Apresentar o(s) fabricante(s) onde esta resgitrado o produto mais barato\n");//funcionando
        printf("[7] Listar todos os produtos em ordem crescente de valor\n");//funcionando
        printf("[8] Listar todos os produtos em ordem crescente de maior valor de lucro\n");//funcionando
        printf("[9] Listar todos os produtos em ordem crescente de maior percentual de lucro\n");//funcionando
        printf("[10] Lista os produto em ordem crescente de A-Z\n");
        printf("[11] Lista as marcas em ordem decresente de Z-A\n");
        printf("[0] Para sair\n");//funcionando
        printf("\nOpcao selecionada: ");
        scanf("%d",seletor);
      
        switch (*seletor) {
        case 1:
          Opcao1(fabrica ,qnt_fabricante);
          break;
        case 2:
          Opcao2(produto,qnt_produto);
          break;
        case 3:
          Opcao3(fabrica,produto,qnt_fabricante,qnt_produto);
          break;
        case 4:
          Opcao4(produto,qnt_produto);
          break;
        case 5:
          Opcao5(produto,qnt_produto);
          break;
        case 6:
          Opcao6(produto, qnt_produto);
          break;
        case 7:
          Opcao7(produto, qnt_produto);
          break;
        case 8:
          Opcao8(produto, qnt_produto);
          break;
        case 9:
            Opcao9(produto, qnt_produto);
          break;
        case 10:
            Opcao10(produto, qnt_produto);
          break;
        case 11:
            Opcao11(fabrica ,qnt_fabricante);
          break;
        
         }//fim  SWITCH
    }while(*seletor>11||*seletor<0);
return *seletor;
}//fim menu 
//todos os relatorios;
void Opcao1(struct Fabrica* fabrica, int qnt_fabricante){
  printf("\n+---------------------------------------------------+\n");
  printf("Relatorio das marcas:\n");
  
  for(int i=0; i<qnt_fabricante;i++){
    printf("- Nome: %s | Site: %s. | Telefone: %s | UF: %s\n", fabrica[i].marca, fabrica[i].site, fabrica[i].telefone, fabrica[i].uf);
    }
}//fim função

void Opcao2(struct Produto* produto, int qnt_produto){
  printf("\n+---------------------------------------------------+\n");
  printf("Relatorio dos produtos:\n");
  
  for(int i=0; i<qnt_produto;i++){
    printf("- Nome: %s | Peso: %.2f | Valor: %.2f | Fabricante: %s\n", produto[i].descricao, produto[i].peso, produto[i].venda, produto[i].fabricante.marca);
    }
}//fim função
void Opcao3(struct Fabrica* fabrica, struct Produto* produto, int qnt_fabrica, int qnt_produto) {
    printf("\n+---------------------------------------------------+\n");
    printf("Relatorio dos produtos de um determinado estado:\n");
    char validaUf[5];
    int Retencao;
    bool encontrado = false;

    printf("Digite a UF desejada: ");
    scanf(" %[^\n]%*c", validaUf);

    printf("UF selecionada: %s\n", validaUf);

    for (int i = 0; i < qnt_produto; i++) {
        Retencao = strcmp(produto[i].fabricante.uf, validaUf);
        printf("\n\tRetencao: %d\n", Retencao);
        printf("\n\tProduto uf: %s\n", produto[i].fabricante.uf);
        printf("\n\tValida uf: %s\n", validaUf);

        if (Retencao == 0) {
            printf("- %s\n", produto[i].descricao);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Nenhum produto encontrado para a UF especificada.\n");
    }
}

void Opcao4(struct Produto* produto, int qnt_produto){
  printf("\n+---------------------------------------------------+\n");  
  printf("Relatorio dos produtos de uma determinada marca:\n");
  char ValidaMarca[100];//Variavel pra validar a marca
  int ret;//variavel para reter o inteiro da função STRCMP
  int ValidaDowhile;

    do{ //For para verificar se o VALIDA é igual ao nome, se caso for igual ele vai PRINTAR 
      printf("Digite a marca desejada existente!: ");
      scanf(" %[^\n]s", ValidaMarca);
      getchar(); // Limpa o caractere de nova linha (\n) do buffer de entrada
      printf("\n");
      
      for(int i = 0; i<qnt_produto ;i++){
          ret = strcmp(produto[i].fabricante.marca, ValidaMarca);
            if(ret == 0){
              printf("- %s\n",produto[i].descricao);
            }
            else{
              ret=0; //else para reinicializar o ret e não conflitar no do while  
            }
        }//Fechamento FOR
   }while(ret != 0);//fechamento DO WHILE
}

void Opcao5(struct Produto* produto, int qnt_produto){
  printf("\n+---------------------------------------------------+\n");  
  printf("Relatorio do estado que possui o produto mais caro: \n");

        for(int j=0;j<qnt_produto;j++){
        strcpy(produto[j].descricaoProvisoria, produto[j].fabricante.uf);
        }

  for(int i=0;i<qnt_produto;i++){
    for(int j=0;j<(qnt_produto-1);j++){

        if(produto[j].venda > produto[j+1].venda){//Maior para crescente e Menor para descresente
          float temp = produto[j].venda;
          produto[j].venda = produto[j+1].venda;
          produto[j+1].venda = temp;

          char temp2[100];
          strcpy(temp2, produto[j].descricaoProvisoria);
          strcpy(produto[j].descricaoProvisoria, produto[j+1].descricaoProvisoria);
          strcpy(produto[j+1].descricaoProvisoria, temp2);
        }//Fevhamento IF
    }//Fechamento for J
  }//Fechamento for I
    printf("- Estado com o produto mais caro (R$%.2f): %s\n",produto[qnt_produto-1].venda, produto[qnt_produto-1].fabricante.uf);
}//fechamento função

void Opcao6(struct Produto* produto, int qnt_produto){
  printf("\n+---------------------------------------------------+\n");  
  printf("Relatorio do fabricante que possui o produto mais barato: \n");

        for(int j=0;j<qnt_produto;j++){
        strcpy(produto[j].descricaoProvisoria, produto[j].fabricante.marca);
        }//fechamento for

  for(int i=0;i<qnt_produto;i++){
    for(int j=0;j<(qnt_produto-1);j++){

        if(produto[j].venda < produto[j+1].venda){//Maior para crescente e Menor para descresente
          float temp = produto[j].venda;
          produto[j].venda = produto[j+1].venda;
          produto[j+1].venda = temp;

          char temp2[100];
          strcpy(temp2, produto[j].descricaoProvisoria);
          strcpy(produto[j].descricaoProvisoria, produto[j+1].descricaoProvisoria);
          strcpy(produto[j+1].descricaoProvisoria, temp2);
        }//Fevhamento IF
    }//Fechamento for J
  }//Fechamento for I

    printf("- Fabricante com o produto mais barato (R$%.2f): %s\n",produto[qnt_produto-1].venda, produto[qnt_produto-1].fabricante.marca);

}//fechamento função

void Opcao7(struct Produto* produto, int qnt_produto){
  //qnt_produto pra avaliar a quantidade de vetores na condição
  //produto[i].venda pra printar o valor de venda
  printf("\n+---------------------------------------------------+\n");  
  printf("Relatorio em ordem cresente do valor de venda: \n");

  for(int i=0;i<qnt_produto;i++){
    for(int j=0;j<(qnt_produto-1);j++){

        if(produto[j].venda > produto[j+1].venda){//Maior para crescente e Menor para descresente
          float temp = produto[j].venda;
          produto[j].venda = produto[j+1].venda;
          produto[j+1].venda = temp;
        }//Fevhamento IF
    }//Fechamento for J
  }//Fechamento for I

  for(int i=0;i<qnt_produto;i++){
    printf("%d- Valor do produto: R$%.2f\n", i+1,produto[i].venda);
  }//fechamento for que ta servindo pra printar
}//fechamento função

void Opcao8(struct Produto* produto, int qnt_produto){
  //qnt_produto pra avaliar a quantidade de vetores na condição
  //produto[i].lucro pra printar o valor de lucro
  printf("\n+---------------------------------------------------+\n");  
  printf("Relatorio em ordem cresente do valor de lucro: \n");

  for(int i=0;i<qnt_produto;i++){
    for(int j=0;j<(qnt_produto-1);j++){

        if(produto[j].lucro > produto[j+1].lucro){//Maior para crescente e Menor para descresente
          float temp = produto[j].lucro;
          produto[j].lucro = produto[j+1].lucro;
          produto[j+1].lucro = temp;
        }//Fevhamento IF

    }//Fechamento for J
}//Fechamento for I

  for(int i=0;i<qnt_produto;i++){
    printf("%d- lucro do produto: R$%.2f\n", i+1,produto[i].lucro);
  }//fechamento for que ta servindo pra printar

}//fechamento função

void Opcao9(struct Produto* produto, int qnt_produto){
  //qnt_produto pra avaliar a quantidade de vetores na condição
  //produto[i].percentual pra printar o percentual
  printf("\n+---------------------------------------------------+\n");  
  printf("Relatorio em ordem cresente do percentual de lucro: \n");

        for(int j=0;j<qnt_produto;j++){
        strcpy(produto[j].descricaoProvisoria, produto[j].descricao);
        }//Esse for ta servindo pra resolver um  problema que altera o valor do produto.descricao, pra evitar eu resolvi criar uma descricao feita pra ser alterada

  for(int i=0;i<qnt_produto;i++){
    for(int j=0;j<(qnt_produto-1);j++){

        if(produto[j].percentual > produto[j+1].percentual){//Maior para crescente e Menor para descresente

          float temp = produto[j].percentual;
          produto[j].percentual = produto[j+1].percentual;
          produto[j+1].percentual = temp;
        }//Fevhamento IF

    }//Fechamento for J
}//Fechamento for I

  for(int i=0;i<qnt_produto;i++){
    printf("%d- Percentual de lucro do produto: %.2f%%\n", i+1,produto[i].percentual);
  }//fechamento for que ta servindo pra printar
}//Fechamento void

void ufs_escolhidas_pelo_fabricante(struct Fabrica *fabrica, int con){

    char ufs[27 /*nm_ufs*/][50] =
        {" AC", " AL", " AP", " AM", " BA",
         " CE", " DF", " ES", " GO", "MA",
         "MT", "MS", "MG", "PA", "PB",
         "PR", "PE", "PI", "RJ", "RN",
         "RS", "RO", "RR", "SC", "SP",
         "SE", "TO"};
    int op = 0;
    int count = 0;

    // imprimindo as ufs em formato de tabela
    for (int i = 0; i < 6 /*nm_linhas*/; i++)
    {
        for (int j = 0; j < 5 /*nm_colunas*/; j++)
        {
            if (count < 10 /*num_ufs*/)
            {
                printf("[%d]%-9s", count + 1, ufs[count]);
            }
            else if (count > 9 && count < 27)
            {
                printf("[%d]%-8s", count + 1, ufs[count]); // para um melhor alinhamento
            }
            count++;
        }
        printf("\n");
    }

    // recebe os nomes das ufs escolhidas pela marca/fabricante
    for (int i = 0; i < 1; i++)
    { // laço de validacao do intervalo
        printf("\nSelecione uma UF valida para o fabricante: ");
        scanf("%d", &op);
        if (op > 0 && op < 28)
        {
            strcpy(fabrica[con].uf, ufs[op - 1]);
        }
        else
        {
            printf("!Opcao invalida. Tente novamente!\n");
            i--;
        }
    }
}
//teste /////////////////////////////////
// Função de comparação para a ordenação em ordem alfabética A-Z

void Opcao10 (struct Produto* produto, int qnt_produto){
    printf("\n+---------------------------------------------------+\n");  
    printf("Relatorio em ordem alfabetica crescente dos produtos de A-Z: \n");    

        for(int j=0;j<qnt_produto;j++){
        strcpy(produto[j].descricaoProvisoria, produto[j].descricao);
        }//fechamento for

  char temporario[100];
  int r;
  for(int i=0;i<=qnt_produto;i++){
    for(int j= i+1;j<=qnt_produto;j++){
        r = strcmp(produto[i].descricaoProvisoria, produto[j].descricaoProvisoria);
        if(r > 0){//Maior para crescente e Menor para descresente
          strcpy(temporario, produto[i].descricaoProvisoria);
          strcpy(produto[i].descricaoProvisoria, produto[j].descricaoProvisoria);
          strcpy(produto[j].descricaoProvisoria, temporario);
        }//Fevhamento IF
    }//Fechamento for J
  }//Fechamento for I

    for(int i=0; i<qnt_produto; i++){
      printf("- %s \n", produto[i].descricaoProvisoria);
    }

          for(int j=0;j<qnt_produto;j++){
        strcpy(produto[j].descricaoProvisoria, produto[j].descricao);
        }//fechamento for
}

void Opcao11 (struct Fabrica* fabrica, int qnt_fabricante){
    printf("\n+---------------------------------------------------+\n");  
    printf("Relatorio em ordem alfabetica decrescente dos fabricantes de Z-A: \n");    

        for(int j=0;j<qnt_fabricante;j++){
        strcpy(fabrica[j].marcaProvisoria, fabrica[j].marca);
        }//fechamento for

  char temporario[100];
  int r;
  for(int i=0;i<=qnt_fabricante;i++){
    for(int j= i+1;j<=qnt_fabricante;j++){
        r = strcmp(fabrica[i].marcaProvisoria, fabrica[j].marcaProvisoria);
        if(r < 0){//Maior para crescente e Menor para descresente
          strcpy(temporario, fabrica[i].marcaProvisoria);
          strcpy(fabrica[i].marcaProvisoria, fabrica[j].marcaProvisoria);
          strcpy(fabrica[j].marcaProvisoria, temporario);
        }//Fevhamento IF
    }//Fechamento for J
  }//Fechamento for I

    for(int i=0; i<qnt_fabricante; i++){
      printf("- %s \n", fabrica[i].marcaProvisoria);
    }
          for(int j=0;j<qnt_fabricante;j++){
        strcpy(fabrica[j].marcaProvisoria, fabrica[j].marca);
        }//fechamento for
}
