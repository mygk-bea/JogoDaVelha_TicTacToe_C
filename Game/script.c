// Online C compiler to run C program online
#include <stdio.h>

// Gerando e Listando Matrix do Tabuleiro
void generateMatrix(int matrix[3][3]) {
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            matrix[i][j] = 0;
        }
    }
}

void listMatrix(int matrix[3][3]) {
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Pedindo Jogadas e Atualizando o Tabuleiro
int updateMatrix(int matrix[3][3]){
    // Requests
    int x, y;
    printf("Digite as coordenadas da posição = ");
    scanf("%i %i", &x, &y);

    matrix[x][y] = 1;
    listMatrix(matrix);
    return 0;
}

int main() {
    int board[3][3];

    generateMatrix(board);
    listMatrix(board);

    updateMatrix(board);

    return 0;
}