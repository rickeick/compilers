#ifndef _AUTOMATO_C_
#define _AUTOMATO_C_

#include <stdlib.h>
#include <string.h>
#include "automato.h"

#define UNDEFINED -1
#define FALSE 0
#define TRUE 1

typedef struct _automato_ {
    int **delta;
    int *estados;
    char *simbolos;
    int num_estados;
    int num_simbolos;
} Automato;

Automato *novoAutomato(int num_estados, char *simbolos) {
    int **delta;
    int *estados;
    Automato *automato;
    if (num_estados > 0 && simbolos != NULL) {
        int num_simbolos = strlen(simbolos);
        estados = (int *)malloc(sizeof(int)*num_estados);
        if (estados != NULL) {
            delta = (int **)malloc(sizeof(int *)*num_estados);
            if (delta != NULL) {
                for (int i=0; i<num_estados; i++) {
                    estados[i] = FALSE;
                    delta[i] = (int *)malloc(sizeof(int)*num_simbolos);
                    if (delta[i] != NULL) {
                        for (int j=0; j<num_simbolos; j++) {
                            delta[i][j] = UNDEFINED;
                        }
                    } else {
                        for (int j=i-1; j>=0; j--) {
                            free(delta[j]);
                        }
                        free(estados);
                        free(delta);
                        return NULL;
                    }
                }
                automato = (Automato *)malloc(sizeof(Automato));
                if (automato != NULL) {
                    automato->delta = delta;
                    automato->estados = estados;
                    automato->simbolos = simbolos;
                    automato->num_estados = num_estados;
                    automato->num_simbolos = num_simbolos;
                    return automato;
                }
            }
        }
        
    }
    return NULL;
}

int pegarPosicao(char simbolo, char *string) {
    int posicao = 0;
    int encontrado = FALSE;
    int tamanho = strlen(string);
    for (posicao; posicao<tamanho; posicao++) {
        if (string[posicao] == simbolo) {
            encontrado = TRUE;
            break;
        }
    }
    return encontrado ? posicao : UNDEFINED;
}

int definirTransicao(Automato *automato, int estado_entrada, char simbolo, int estado_saida) {
    if (automato != NULL) {
        if (estado_entrada >= 0 && estado_entrada < automato->num_estados) {
            if (estado_saida >= 0 && estado_saida < automato->num_estados) {
                int posicao = pegarPosicao(simbolo, automato->simbolos);
                if (posicao != UNDEFINED) {
                    automato->delta[estado_entrada][posicao] = estado_saida;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

int definirEstadoFinal(Automato *automato, int estado) {
    if (automato != NULL) {
        if (estado >= 0 && estado < automato->num_estados) {
            automato->estados[estado] = TRUE;
            return TRUE;
        }
    }
    return FALSE;
}

int executar(Automato *automato, char *palavra) {
    int posicao;
    int estado = 0;
    if (automato != NULL && palavra != NULL) {
        int tamanho = strlen(palavra);
        for (int i=0; i<tamanho; i++) {
            posicao = pegarPosicao(palavra[i], automato->simbolos);
            if (posicao == UNDEFINED) {
                return FALSE;
            }
            estado = automato->delta[estado][posicao];
            if (estado == UNDEFINED) {
                return FALSE;
            }
        }
        return automato->estados[estado];
    }
    return UNDEFINED;
}

#endif
