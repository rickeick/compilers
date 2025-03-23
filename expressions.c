#include <stdio.h>
#include <stdlib.h>

// Constantes e Macros

#define TRUE 1
#define FALSE 0
#define isDigit(c) ((c>='0')&&(c<='9'))

// Estrutura de Dados

typedef enum _token_ {
    NUM,
    PLUS,
    MINUS,
    TIMES,
    RPAREN,
    LPAREN,
    ERROR,
    END
} Token;

// Protótipos

void expr();
void term();
void factor();
void match(Token);
void error_handler(int);
void panic_mode();

// Variáveis Globais

char string[256];
int error = FALSE;
int position = 0;
Token token;

// Análise Léxica

Token getToken() {
    char c;
    int state = 1;
    while (TRUE) {
        c = string[position++];
        switch (state) {
            case 1:
                if (c == '+') {
                    return PLUS;
                } else if (c == '-') {
                    return MINUS;
                } else if (c == '*') {
                    return TIMES;
                } else if (c == '(') {
                    return LPAREN;
                } else if (c == ')') {
                    return RPAREN;
                } else if (isDigit(c)) {
                    state = 2;
                } else if (c == '\n' || c == '\0') {
                    return END;
                } else {
                    return ERROR;
                }
            break;
            case 2:
                if (!(isDigit(c))) {
                    position--;
                    return NUM;
                }
            break;
        }
    }
}

// Análise Sintática

void expr() {
    term();
    while (token == PLUS || token == MINUS) {
        match(token);
        term();
    }
}

void term() {
    factor();
    while (token == TIMES) {
        match(TIMES);
        factor();
    }
}

void factor() {
    if (token == NUM) {
        match(NUM);
    } else if (token == LPAREN) {
        match(LPAREN);
        expr();
        match(RPAREN);
    } else {
        error_handler(2);
    }
}

void match(Token espected) {
    if (token == espected) {
        token = getToken();
    } else {
        error_handler(3);
    }
}

// Tratamento de Erros

void error_handler(int id_error) {
    if (id_error == 1) {
        printf("Erro sintático na posição %d: Esperando PLUS, MINUS ou TIMES.\n", position-1);
    } else if (id_error == 2) {
        printf("Erro sintático na posição %d: Esperando NUM ou LPAREN.\n", position-1);
    } else if (id_error == 3) {
        printf("Erro sintático na posição %d: Esperando RPAREN.\n", position-1);
    }
    panic_mode();
    error = TRUE;
}

void panic_mode() {
    while (token != NUM && token != LPAREN && token != END) {
        token = getToken();
    }
    if (token == NUM) {
        match(NUM);
    } else if (token == LPAREN) {
        match(LPAREN);
        expr();
        match(RPAREN);
    } else if (token == END) {
        exit(0);
    }
}

// Compilador

int main(void) {
    printf("String para ser Analisada: ");
    fgets(string, 256, stdin);

    do {
        token = getToken(); expr();
        if (token != END) {
            error_handler(1);
        }
    } while (token != END);
    
    if (error == FALSE) {
        printf("Não foram encontrados erros na expressão.\n");
        return 0;
    } else {
        return 1;
    }
}
