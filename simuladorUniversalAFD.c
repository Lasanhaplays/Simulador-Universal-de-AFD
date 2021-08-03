#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void verificarCadeias(FILE *arquivo, FILE *saida){
    /*FILE *saida = fopen("saida.txt","w");

    //Verifica se houve algum problema ao criar o arquivo de saida
    if(!saida){
        printf("\n\nNao foi possivel criar o arquivo de saida");
        system("Pause");
        exit(1);
    }


    fclose(saida);*/
}

char *removeEspacos(char *saida, const char *entrada ){
    const char *p = entrada;
    int i = 0;

    while(*p){
        if(!isspace(*p)) saida[i++] = *p;
        p++;
    }
    saida[i] = 0;
    return saida;
}

void main(){
    //Variaveis auxiliares
    int linha = 5, aux =0, i;
    char buffer[50];

    //Variaveis construtoras
    int nmrEstados, qntdSimbolos, nmrEstadosIniciais, qntdEstadosAceitacao, nmrTransicoes, nmrCadeiasEntrada;
    char *simbolos, *estadosDeAceitacao;

    FILE *arquivo = fopen("entrada.txt","r");

    //Verifica se o arquivo existe
    if(!arquivo){
        printf("\n\nNao foi possivel ler o arquivo");
        system("Pause");
        exit(1);
    }

    //Salva e separa os dados do arquivo em variaveis
    fscanf(arquivo, "%d", &nmrEstados);                                         //Linha 1. Numero de estados
    fscanf(arquivo, "%d", &qntdSimbolos);                                       //Linha 2. Conjunto de simbolos terminais
    simbolos = fgets(buffer, qntdSimbolos*2+1, arquivo);
    simbolos = removeEspacos(simbolos, simbolos);
    fscanf(arquivo, "%d", &nmrEstadosIniciais);                                 //Linha 3. Numero de estados iniciais
    fscanf(arquivo, "%d", &qntdEstadosAceitacao);                               //Linha 4. Conjunto de estados de aceitacao
    estadosDeAceitacao = fgets(buffer, qntdEstadosAceitacao*2+1, arquivo);
    estadosDeAceitacao = removeEspacos(estadosDeAceitacao,estadosDeAceitacao);
    fscanf(arquivo, "%d", &nmrTransicoes);                                      //Linha 5. Numero de transicoes

    //Salva todas as transicoes em uma matriz
    char *transicao[4][nmrTransicoes];   //Matriz das transicoes

    for(i=0; i<nmrTransicoes; i++){
        fscanf(arquivo, "%i %c %i", &transicao[aux][i], &transicao[aux+1][i], &transicao[aux+2][i]);
    }

    fscanf(arquivo, "%d", &nmrCadeiasEntrada);  //Linha depois das transicoes. Numero de cadeias de entrada

    
    //------------------------DEBUG----------------------------------
    printf("Numero de estados: %d\n", nmrEstados);
    printf("Quantidade de simbolos: %d\n", qntdSimbolos);
    printf("Simbolos: %s\n",simbolos);
    printf("Numero de estados iniciais: %d\n", nmrEstadosIniciais);
    printf("Numero de estados de aceitacao: %d\n", qntdEstadosAceitacao);
    printf("Estados de aceitacao: %s\n",estadosDeAceitacao);
    printf("Numero de transicoes: %d\n", nmrTransicoes);
    for(i=0; i<nmrTransicoes; i++){
        printf("Transicao: %i %c %i\n", transicao[aux][i], transicao[aux+1][i], transicao[aux+2][i]);
    }
    printf("Numero de cadeias de entrada: %d\n", nmrCadeiasEntrada);
    //------------------------DEBUG----------------------------------

    fclose(arquivo);
}
