#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Funcao que verifica se determinado estado eh um estado final
bool ehEstadoFinal(int valor, int qntdEstadosAceitacao, char *estadosDeAceitacao){
    for(int i=0; i<qntdEstadosAceitacao; i++){
        if(valor == estadosDeAceitacao[i]) return true;
    }return false;
}

//Funcao que verifica se determinado simbolo existe no alfabeto
bool pertenceAlfabeto(char ch, char *simbolos, int qntdSimblos){
    for(int i=0; i<qntdSimblos; i++){
        if(ch == simbolos[i]) return true;
    }return false;
}

//Funcao que verifica se ha uma transicao existente para determinado simbolo
bool verificaTransicao(int *estadoAtualP,int estadoAtual, char simbAtual, char **transicao, int nmrTransicoes){
    int novoEstado;

    //Percorre toda a matriz
    for(int i=0; i<nmrTransicoes; i++){
        for(int j=0; j<4; j++){
            //Se o simbolo e o estado forem compativeis com alguma linha da matriz
            if(simbAtual == transicao[1][i] && estadoAtual == transicao[0][i]){
                //Atualiza o estado atual e retona true
                novoEstado = transicao[2][i];
                *estadoAtualP = novoEstado;
                return true;
            }
        }
    }

    //Se nenhuma linha for compativel, retorna false
    return false;
}

//Funcao que verifica se determinada cadeia eh aceita ou nao no AFD
bool verificarCadeias(char **transicao, int nmrTransicoes, char *simbolos, int qntdSimblos, int nmrEstadosIniciais, int qntdEstadosAceitacao, char *estadosDeAceitacao, char *cadeia){
    char simbAtual;
    int estadoAtual, i;

    estadoAtual = nmrEstadosIniciais-1; //Como foi solicitado, somente eh aceito AFD

    for(i=0; i<strlen(cadeia); i++){
        simbAtual = cadeia[i];   //Recebe o simbolo

        //Quando houver somente o lambda na cadeia
        if(simbAtual == '-'){
            if(ehEstadoFinal(estadoAtual,qntdEstadosAceitacao, estadosDeAceitacao)) return true;
            else return false;
        }

        //Verifica se o simbolo eh pertecente ao alfabeto
        if(!pertenceAlfabeto(simbAtual, simbolos, qntdSimblos)) return false;

        //Quando for o ultimo simbolo a ser analisado
        if(i == (strlen(cadeia)-1)){
            //Se nao for uma transicao valida ou nao for o estado final, retorna falso
            if(!verificaTransicao(&estadoAtual, estadoAtual, simbAtual, transicao, nmrTransicoes) || !ehEstadoFinal(estadoAtual, qntdEstadosAceitacao, estadosDeAceitacao)) return false;
        }

        //Se nao for uma transicao valida, retorna falso
        if(!verificaTransicao(&estadoAtual, estadoAtual, simbAtual, transicao, nmrTransicoes)) return false;
    }
    //Com todas as validacoes confirmadas, retorna true
    return true;
}

//Funcao que remove os espacos de uma string
char *removeEspacos(char *saida, const char *entrada ){
    const char *p = entrada;
    int i = 0;

    while(*p){
        if(!isspace(*p)) saida[i++] = *p;
        p++;
    }
    saida[i] = 0;
    p == NULL;
    return saida;
}

void main(){
    //Variaveis auxiliares
    int linha = 5, aux =0, i;
    char bufferA[25], bufferB[25], bufferC[25];

    //Variaveis construtoras
    int nmrEstados, qntdSimbolos, nmrEstadosIniciais, qntdEstadosAceitacao, nmrTransicoes, nmrCadeiasEntrada;
    char **transicao = NULL, *simbolos, *estadosDeAceitacao, *cadeia;

    FILE *arquivo = fopen("entrada.txt","r");

    //Verifica se o arquivo existe
    if(!arquivo){
        printf("\n\nNao foi possivel ler o arquivo");
        system("Pause");
    }


    //Salva e separa os dados do arquivo em variaveis
    fscanf(arquivo, "%d", &nmrEstados);                                         //Linha 1. Numero de estados
    fscanf(arquivo, "%d", &qntdSimbolos);                                       //Linha 2. Conjunto de simbolos terminais
    simbolos = fgets(bufferA, qntdSimbolos*2+1, arquivo);
    simbolos = removeEspacos(simbolos, simbolos);
    fscanf(arquivo, "%d", &nmrEstadosIniciais);                                 //Linha 3. Numero de estados iniciais
    fscanf(arquivo, "%d", &qntdEstadosAceitacao);                               //Linha 4. Conjunto de estados de aceitacao
    estadosDeAceitacao = fgets(bufferB, qntdEstadosAceitacao*2+1, arquivo);
    estadosDeAceitacao = removeEspacos(estadosDeAceitacao,estadosDeAceitacao);
    fscanf(arquivo, "%d", &nmrTransicoes);                                      //Linha 5. Numero de transicoes

    //Aloca dinamicamente a matriz de transicao
    transicao = (char **)malloc(nmrTransicoes*sizeof(char *));

    if(!transicao){
        printf("\n\nErro ao criar a matriz de transicao");
        system("Pause");
    }
    for(i=0; i<nmrTransicoes; i++){
        transicao[i] = (char *)malloc(4*sizeof(char *));
    }

    //Salva as transicoes na matriz
    for(i=0; i<nmrTransicoes; i++){
        fscanf(arquivo, "%i %c %i", &transicao[aux][i], &transicao[aux+1][i], &transicao[aux+2][i]);
    }

    fscanf(arquivo, "%d", &nmrCadeiasEntrada);  //Linha depois das transicoes. Numero de cadeias de entrada

    //Cria arquivo de saida
    FILE *saida = fopen("saida.txt","w");

    //Verifica se houve algum erro na criacao do arquivo
    if(!saida){
        printf("\n\nNao foi possivel criar o arquivo de saida");
        system("Pause");
    }

    //Verifica se cada uma das cadeias eh aceitada ou rejeitada
    for(i=0; i<nmrCadeiasEntrada; i++){
        cadeia = fgets(bufferC, 21, arquivo);

        //Escreve no arquivo de saida
        if(verificarCadeias(transicao, nmrTransicoes, simbolos, qntdSimbolos, nmrEstadosIniciais, qntdEstadosAceitacao, estadosDeAceitacao, cadeia)){
            fprintf(saida, "aceita\n");
        }else fprintf(saida, "rejeita\n");
    }

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

    fclose(saida);
    fclose(arquivo);
}
