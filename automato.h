#ifndef _AUTOMATO_H_
#define _AUTOMATO_H_

typedef struct _automato_ Automato;

Automato *novoAutomato(int num_estados, char *simbolos);

int definirTransicao(Automato *automato, int estado_entrada, char simbolo, int estado_saida);

int definirEstadoFinal(Automato *automato, int estado);

int executar(Automato *automato, char *palavra);

#endif
