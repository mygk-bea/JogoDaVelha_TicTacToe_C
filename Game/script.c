#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct menu {
    char name[20];
};

struct menu options[4];
void listMenu() {
    strcpy(options[1].name, "Jogador vs Jogador"); 
    strcpy(options[2].name, "Maquina vs Jogador"); 
    strcpy(options[3].name, "Maquina vs Maquina"); 
    strcpy(options[0].name, "Sair");

    for(int i=1; i<4; i++)
        printf("\n| %i | %s", i, options[i].name);
    printf("\n| %i | %s", 0, options[0].name);
}

int getGameMode() {
    int choice;
    printf("Escolha o modo de jogo:\n");
    listMenu();

    printf("\n\nDigite: ");
    scanf("%i", &choice);
    return choice;
}

// -------------------------------------

void generateBoard(char matrix[3][3]) {
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
            matrix[i][j] = '_';
    }
}

void listBoard(char matrix[3][3]) {
    printf("\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }
}

struct coordinates {
    int x;
    int y;
};

struct coordinates getPlayCoordinates(int isBotPlayer){
    int x, y;

    if(isBotPlayer) {
        x = rand() % 3;
        y = rand() % 3;
    } else {
        printf("\nInsira as coordenadas da jogada (x, y) separadas por um espaco: ");
        scanf("%i %i", &x, &y);
    }

    struct coordinates move = {x, y};
    return move;
}

void updateBoard(char matrix[3][3], struct coordinates move, int player) {
    matrix[move.x][move.y] = (player) ? 'X' : 'O';
    listBoard(matrix);
}

int checkWinnerExists(char matrix[3][3], int moves){
    if(moves >= 5) {
        char seq[4][4] = {"","","",""};
        for(int i=0, aux=2; i<3; i++, aux--){
            strcpy(seq[0], "");
            strcpy(seq[1], "");

            for(int j=0; j<3; j++){
                char rowElement[2] = { matrix[i][j] };
                char colElement[2] = { matrix[j][i] };
                strcat(seq[0], rowElement);
                strcat(seq[1], colElement);
            }

            char diagPriElement[2] = { matrix[i][i] };
            char diagSecElement[2] = { matrix[i][aux] };
            strcat(seq[2], diagPriElement);
            strcat(seq[3], diagSecElement);

            for(int j=0; j<4; j++){
                if(!strcmp(seq[j], "XXX")){
                    return 1;
                } else if (!strcmp(seq[j], "OOO")){
                    return 2;
                }
            }
        }
    }
    return 0;
}

// -------------------------------------

int playerTurn;
int changePlayerTurn() {
    playerTurn = !playerTurn;
    return playerTurn;
}

int startGame(int type) {
    char board[3][3];
    int numOfMoves = 0;
    int player = changePlayerTurn();
    int isBot = (type == 3) ? true : false;
    char winner = false;

    generateBoard(board);
    listBoard(board);

    while(!winner) {
        if(type == 2) {
            isBot = (player) ? false : true;
        }

        struct coordinates move = getPlayCoordinates(isBot);
        if(board[move.x][move.y] == '_') {
            updateBoard(board, move, player);
            player = changePlayerTurn();
            numOfMoves++;
            winner = checkWinnerExists(board, numOfMoves);

            if(numOfMoves == 9 && !winner) {
                winner = 3;
            }
        }
    }
    return winner;
}

// -------------------------------------

struct player {
    char name[7];
    int points;
};

int main() {
    srand(time(NULL));
    int gamemode;

    struct player p_pts[4] = {{"_", 0}, {"X", 0}, {"O", 0}, {"Empate", 0}};

    while(true) {
        gamemode = getGameMode();
        printf("\nModo | %s", options[gamemode].name);
        if(gamemode == 0) {
            break;
        }

        int result = startGame(gamemode);
        p_pts[result].points++;

        printf("\nVencedor: * %s *", p_pts[result].name);
        printf("\n+-----+--------+-----+");
        printf("\n|  X  | EMPATE |  O  |");
        printf("\n+-----+--------+-----+");
        printf("\n| %2i  |   %2i   | %2i  |" , p_pts[1].points, p_pts[3].points, p_pts[2].points);
        printf("\n+-----+--------+-----+\n\n");
    }
    return 0;
}