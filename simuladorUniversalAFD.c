#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivo(){
    FILE *arquivo = NULL;

    arquivo = fopen("entrada.txt","r");

    //Verifica se o arquivo existe
    if(!arquivo){
        printf("\n\nNao foi possivel ler o arquivo");
        system("Pause");
        exit(1);
    }

    
}

void main(){

}