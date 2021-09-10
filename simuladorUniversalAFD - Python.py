#Simulador AFD
#-------------------------------------------------------------------------------------------------
#Leitura dos componentes

#Linha 1 -> Numero de estados
nmrEstados = input()

#Linha 2 -> Conjunto de símbolos terminais
linhaSimbolos = input()
linhaSimbolos = linhaSimbolos.split(' ')            #Separa os simbolos
qntdSimbolos = linhaSimbolos[0]     #Recebe a quantidade de simbolos
simbolos = linhaSimbolos[1:]        #Recebe os simbolos

#Linha 3 -> Numero de estados Iniciais
nmrEstadosIniciais = input()

#Linha 4 -> Conjunto de estados de aceitacao
linhaEstdAceitacao = input()
linhaEstdAceitacao = linhaEstdAceitacao.split(' ')  #Separa os estados de aceitacao
qntdEstadosAceitacao = linhaEstdAceitacao[0]        #Recebe o numero de estados de aceitacao
estados = linhaEstdAceitacao[1:]                    #Recebe os estados de aceitacao
estadosDeAceitacao = list(map(int,estados))         #Converte os estados de aceitacao para int

#Linha 5 -> O numero de transicoes
nmrTransicoes = input()

#A partir da linha 6 -> As transicoes
#Recebe em cada posicao uma transicao contendo 
#o estado inicial, final e o simbolo da transicao
Transicao = []
while len(Transicao) < int(nmrTransicoes):
    linhaTransicao = input()
    linhaTransicao = linhaTransicao.split(' ')   #Separa os 3 elementos da transicao
    Transicao.append(linhaTransicao)

#Linha depois das transicoes -> Numero de cadeias
nmrCadeiasDeEntrada = input()

#Proximas linhas -> Cadeias de entrada
#Recebe em cada posicao uma cadeia
Cadeias = []
while len(Cadeias) < int(nmrCadeiasDeEntrada):
    cadeia = input()
    cadeia = list(cadeia)   #Transforma uma string em lista
    Cadeias.append(cadeia)

#-------------------------------------------------------------------------------------------------
#Verifica se o simbolo pertence ao alfabeto
def alfabeto(simboloAtual):
        if(simboloAtual in simbolos):
            return True
        else:
            return False

#Verifica se a cadeia e compativel com o automato descrito
def verificarCadeia(cadeia, estadoAtual):

    #Se o simbolo for '-'   
    if(cadeia == ['-']):
        if(estadoAtual in estadosDeAceitacao):
            return True
        else:
            return False
    
    #Verifica se o ultimo simbolo da cadeia e um estado de aceitacao
    if(cadeia == []):
        if(estadoAtual in estadosDeAceitacao):
            return True
        return False

    simboloAtual = cadeia[0]

    #Verfica se o simbolo esta no alfabeto
    if(alfabeto(simboloAtual) == False):
        return False

    #Verifica se tem alguma transicao que se encaixa com o simbolo e o estado atual
    for i in range(int(nmrTransicoes)):
        transicaoAtual = Transicao[i]

        estdInicialTransicao = int(transicaoAtual[0])       #Recebe o estado inicial da transicao
        simbTransicao = transicaoAtual[1]                   #Recebe o simbolo da transicao
        estdFinalTransicao = int(transicaoAtual[2])         #Recebe o estado final da transicao
        
        if((estdInicialTransicao == estadoAtual) and (simbTransicao == simboloAtual)):
            estado = estdFinalTransicao     #Atualiza o estado atual   

            #Parte recursiva, chama novamente a funcao menos o simbolo testado     
            cadeiaNova = cadeia[1:]               
            if(verificarCadeia(cadeiaNova,estado)):
                return True
    return False

for i in range(int(nmrCadeiasDeEntrada)):
    cadeia = Cadeias[i]
    #Como foi definido no trabalho somente AFD, o estado inicial sempre sera 0
    if(verificarCadeia(cadeia, 0)):
        print("aceita")
    else:
        print("rejeita")