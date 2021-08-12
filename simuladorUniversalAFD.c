#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NAME_SZ 256

//Funcao que verifica se determinado estado eh um estado final
bool ehEstadoFinal(int valor, int qntdEstadosAceitacao, char *estadosDeAceitacao){
    for(int i=0; i<qntdEstadosAceitacao; i++){
        if(valor == estadosDeAceitacao[i] - '0')return true;
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
            if(simbAtual == transicao[1][i] && estadoAtual == (int)transicao[0][i]-48){
                //Atualiza o estado atual e retona true
                novoEstado = (int)transicao[2][i]-48;
                *estadoAtualP = novoEstado;
                return true;
            }
        }
    }

    //Se nenhuma linha for compativel, retorna false
    printf("Transicao Invalida\n");
    return false;
}

//Funcao que verifica se determinada cadeia eh aceita ou nao no AFD
bool verificarCadeias(char **transicao, int nmrTransicoes, char *simbolos, int qntdSimblos, int nmrEstadosIniciais, int qntdEstadosAceitacao, char *estadosDeAceitacao, char *cadeia){
    char simbAtual;
    int estadoAtual, i;

    estadoAtual = nmrEstadosIniciais-1; //Como foi solicitado, somente eh aceito AFD

    for(i=0; i<strlen(cadeia)-1; i++){
        simbAtual = cadeia[i];   //Recebe o simbolo

        //Quando houver somente o lambda na cadeia
        if(simbAtual == '-'){
            if(ehEstadoFinal(estadoAtual,qntdEstadosAceitacao, estadosDeAceitacao)) return true;
            else return false;
        }

        //Verifica se o simbolo eh pertecente ao alfabeto
        if(!pertenceAlfabeto(simbAtual, simbolos, qntdSimblos)) return false;

        //Quando for o ultimo simbolo a ser analisado
        if(i == (strlen(cadeia)-2)){
            //Se nao for uma transicao valida ou nao for o estado final, retorna falso
            if(!verificaTransicao(&estadoAtual, estadoAtual, simbAtual, transicao, nmrTransicoes) || !ehEstadoFinal(estadoAtual, qntdEstadosAceitacao, estadosDeAceitacao)){
                return false;
            }
        }

        //Se nao for uma transicao valida, retorna falso
        if(!verificaTransicao(&estadoAtual, estadoAtual, simbAtual, transicao, nmrTransicoes))return false;
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
    p = NULL;
    return saida;
}

int main(){
    //Variaveis auxiliares
    int linha = 5, aux =0, i;

    //Variaveis construtoras
    int nmrEstados, qntdSimbolos, nmrEstadosIniciais, qntdEstadosAceitacao, nmrTransicoes, nmrCadeiasEntrada;
    char **transicao = NULL, *simbolos, *estadosDeAceitacao, *cadeia;

    //Alocando as variaveis
    simbolos = malloc(MAX_NAME_SZ);
    estadosDeAceitacao = malloc(MAX_NAME_SZ);
    cadeia = malloc(MAX_NAME_SZ);
    if(!simbolos || !estadosDeAceitacao || !cadeia) return 0;

    //Salva e separa os dados do arquivo em variaveis
    scanf("%d", &nmrEstados);                                         //Linha 1. Numero de estados
    scanf("%d", &qntdSimbolos);                                       //Linha 2. Conjunto de simbolos terminais
    simbolos = fgets(simbolos, MAX_NAME_SZ, stdin);
    simbolos = removeEspacos(simbolos, simbolos);
    scanf("%d", &nmrEstadosIniciais);                                 //Linha 3. Numero de estados iniciais
    scanf("%d", &qntdEstadosAceitacao);                               //Linha 4. Conjunto de estados de aceitacao
    estadosDeAceitacao = fgets(estadosDeAceitacao, MAX_NAME_SZ, stdin);
    estadosDeAceitacao = removeEspacos(estadosDeAceitacao,estadosDeAceitacao);
    scanf("%d", &nmrTransicoes);                                      //Linha 5. Numero de transicoes

    //Aloca dinamicamente a matriz de transicao
    transicao = (char **)malloc(nmrTransicoes*sizeof(char *));

    if(!transicao){
        printf("\n\nErro ao criar a matriz de transicao");
        return 0;
    }
    for(i=0; i<nmrTransicoes; i++)transicao[i] = (char *)malloc(4*sizeof(char *));

    //Salva as transicoes na matriz
    for(i=0; i<nmrTransicoes; i++) scanf(" %c  %c  %c ", &transicao[aux][i], &transicao[aux+1][i], &transicao[aux+2][i]);

    scanf("%d", &nmrCadeiasEntrada);  //Linha depois das transicoes. Numero de cadeias de entrada

    //Verifica se cada uma das cadeias eh aceitada ou rejeitada
    cadeia = fgets(cadeia, MAX_NAME_SZ, stdin);
    for(i=0; i<nmrCadeiasEntrada; i++){
        cadeia = fgets(cadeia, MAX_NAME_SZ, stdin);

        //Escreve no arquivo de saida
        if(verificarCadeias(transicao, nmrTransicoes, simbolos, qntdSimbolos, nmrEstadosIniciais, qntdEstadosAceitacao, estadosDeAceitacao, cadeia)){
            printf("aceita\n");
        }else printf("rejeita\n");
    }
}
