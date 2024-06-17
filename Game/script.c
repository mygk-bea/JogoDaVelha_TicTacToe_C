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

struct player {
    char name[5];
    int points;
};

struct player pts_X    = {"X", 0};
struct player pts_O    = {"O", 0};
struct player pts_Draw = {"Draw", 0};

int playerTurn;
int changePlayerTurn() {
    playerTurn = !playerTurn;
    return playerTurn;
}

// -------------------------------------

void generateBoard(char matrix[3][3]) {
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            matrix[i][j] = '_';
        }
    }
}

void listBoard(char matrix[3][3]) {
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("------\n");
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
        printf("Insira as coordenadas da jogada (x, y) separadas por um espaco: ");
        scanf("%i %i", &x, &y);
    }

    struct coordinates move = {x, y};
    return move;
}

void updateBoard(char matrix[3][3], struct coordinates move, int player) {
    matrix[move.x][move.y] = (player) ? 'X' : 'O';
    listBoard(matrix);
}

int checkWinnerExists(char matrix[3][3]){
    for(int i=0; i<3; i++){
        int row = 0;
        for(int j=0; j<3; j++){
            char element[2] = { matrix[i][j] };
            if(strcmp(element, "X") == 0){
                row++;
            }else if (strcmp(element, "O") == 0){
                row--;
            }   
        }
        if(row == 3 || row == -3) {
            printf("valor linha = %i\n\n", row);
        }
    }
    return 0;
}

// -------------------------------------

int startGame(int type) {
    char board[3][3];
    int numOfMoves = 0;
    int player = changePlayerTurn();
    int isBot = false;
    generateBoard(board);
    listBoard(board);

    while(numOfMoves < 9 ) {

        if(type == 2) {
            isBot = (player) ? false : true;
        } else if (type == 3) {
            isBot = true;
        }

        struct coordinates move = getPlayCoordinates(isBot);
        if(board[move.x][move.y] == '_') {
            updateBoard(board, move, player);
            player = changePlayerTurn();
            numOfMoves++;
        }

        checkWinnerExists(board);
    }
    return 0;
}

// -------------------------------------

int main() {
    srand(time(NULL));
    int gamemode;
    while(true) {
        gamemode = getGameMode();
        printf("\n%s\n", options[gamemode].name);

        if (gamemode == 0){
            break;
        }

        startGame(gamemode);
    }

    return 0;
}