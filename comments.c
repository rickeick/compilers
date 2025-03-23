#include <stdio.h>

int position = 0;

typedef enum _token_ {
    COMMENT,
    ERRO,
    END
} Token;

Token getToken(char *string) {
    int state = 1;
    char character;
    while (state != 5 && state != 6) {
        character = string[position++];
        if (character == '\0') {
            return END;
        }
        switch (state) {
            case 1:
                if (character == '/') {
                    state = 2;
                } else {
                    state = 6;
                }
            break;
            case 2:
                if (character == '*') {
                    state = 3;
                } else {
                    state = 6;
                }
            break;
            case 3:
                if (character == '*') {
                    state = 4;
                }
            break;
            case 4:
                if (character == '/') {
                    state = 5;
                } else if (character != '*') {
                    state = 3;
                }
            break;
        }
    }
    if (state == 5) {
        return COMMENT;
    } else {
        return ERRO;
    }
}

int main(void) {
    Token token;
    char string[256];
    int start, found = 0;

    printf("String para ser analisada:\n");
    fgets(string, 256, stdin);
    printf("\n");

    while (token != END) {
        start = position;
        token = getToken(string);
        if (token == COMMENT) {
            if (!found) {
                printf("Comentário(s) encontrado(s):\n");
                found = 1;
            }
            for (int i=start; i<position; i++) {
                printf("%c", string[i]);
            }
            printf("\n");
        }
    }

    if (!found) {
        printf("Nenhum comentário encontrado!\n");
    }

    return 0;
}
