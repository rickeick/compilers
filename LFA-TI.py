class Estado:
    def __init__(self, id: int, isFinal: bool) -> None:
        self.id = id
        self.isFinal = isFinal
    def __str__(self) -> str:
        if self.isFinal == True:
            return f'qf{self.id}'
        return f'q{self.id}'


class Automato:
    def __init__(self, sigma: str, estados: list, delta: list) -> None:
        self.sigma = sigma
        self.estados = estados
        self.delta = delta
    def __str__(self) -> str:
        string = str()
        for (entrada, simbolo, saida) in self.delta:
            string += f'δ({entrada}, {simbolo}) = {saida}\n'
        return string


def transformar(AFN: Automato) -> Automato:
    # Definindo Sigma
    sigma = AFN.sigma
    # Definindo o Conjunto das Partes de Q
    conjuntos = [set()]
    for elemento in AFN.estados:
        for i in range(len(conjuntos)):
            conjunto = set(conjuntos[i])
            conjunto.add(elemento)
            conjuntos.append(conjunto)
    conjuntos.remove(set())
    # Definindo delta' estendindo
    funcao = list()
    for entradas in conjuntos:
        for simbolo in sigma:
            saidas = set()
            for entrada in entradas:
                for (qE, s, qS) in AFN.delta:
                    if (qE == entrada and s == simbolo):
                        saidas.add(qS)
            funcao.append((entradas, simbolo, saidas))
    # Definindo Q'
    estados = list()
    for i in range(len(conjuntos)):
        isFinal = False
        for estado in conjuntos[i]:
            if (estado.isFinal == True):
                isFinal = True; break
        estados.append(Estado(i, isFinal))
    print('Estados Equivalentes')
    for i in range(len(conjuntos)):
        print(f'{estados[i]}: <', end='')
        for estado in conjuntos[i]:
            print(estado, end='')
        print('>')
    print()
    # Definindo delta'
    delta = list()
    for (entradas, simbolo, saidas) in funcao:
        if saidas == set(): continue
        saida = estados[conjuntos.index(saidas)]
        entrada = estados[conjuntos.index(entradas)]
        delta.append((entrada, simbolo, saida))
    # Definindo e Retornando o AFD
    AFD = Automato(sigma, estados, delta)
    del conjuntos, funcao
    return AFD


if __name__ == '__main__':
    # Definindo Sigma
    sigma = input('Símbolos do Alfabeto: ').replace(' ','')
    # Definindo Q e q0
    estados = list()
    for i in range(int(input('\nQuantidade de Estados: '))):
        estados.append(Estado(i, False))
        print(f'Estado q{i} Criado!')
    print('\nEstado Inicial: q0\n')
    # Definindo F
    for id in input('Estado(s) Final(is): ').replace('q','').split(' '):
        estados[int(id)].isFinal = True
    print()
    # Definindo delta
    delta = list()
    for i in range(int(input('Quantidade de Transições: '))):
        transicao = input(f'{i+1}° Transição: ').replace('q', '').split(' ')
        simbolo = transicao[1]
        if (simbolo in sigma):
            saida = estados[int(transicao[2])]
            entrada = estados[int(transicao[0])]
        delta.append((entrada, simbolo, saida))
    print()
    # Definindo os Autômatos
    AFN = Automato(sigma, estados, delta)
    AFD = transformar(AFN)
    print(AFD)
