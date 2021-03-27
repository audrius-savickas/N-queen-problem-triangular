// Audrius Savickas 4gr
// 14 perrinkimo užduotis
// Rasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define M 7
#define N 5
//  10  3  7  10  13  14
//   7  2  5   8   3   9

int total_squares = 0;
int total_queens = 0;
int last_queen = 0;
long int bandymu_skaicius = 0;
FILE *output;

void initTriangle(char triangle[]);
void printTriangle(char triangle[]);
int rowToNumber(int row);
bool changeSquare(char triangle[], int row, int column, char symbol);
void changeToEights(char triangle[], int row, int column, int row_to_change);
bool solveTriangleUtil(char triangle[]);
bool solveTriangle(char triangle[]);
bool isSafe(char triangle[], int row, int column);
void printQueens(char triangle[]);

int main () {
    for (int i = 1; i <= M; i++) {
        total_squares += i;
    }

    char *triangle = (char *) malloc (total_squares * sizeof(char));
    initTriangle(triangle);
    
    output = fopen("protokolas.txt", "w");
    fprintf(output, "Audrius Savickas 1k. 4gr. 1pogr.\nAntroji pagrindinė užduotis. 14 variantas. \nRasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų.\n\n");
    fprintf(output, "Limitas: M - %d, N - %d.\n\n", 12, 8);
    fprintf(output, "%s", "1 DALIS.\n");
    fprintf(output, "M = %d, N = %d\n", M, N);
    fprintf(output, "Lenta buvo sunumeruota taip:\n");
    int tarpu_skaicius = (M-1) * 2;
    int counter = 0;

    for (int i = 0; i < M; i++){
        for (int o = 0; o < tarpu_skaicius; o++){
            fprintf(output, " ");
        }
        for (int o = 0; o < i + 1; o++){
            if (counter < 10){
                fprintf(output, " %d", counter++);
            }
            else {
                fprintf(output, "%d", counter++);
            }
            if (o != i) fprintf(output, "  ");
        }
        for (int o = 0; o < tarpu_skaicius; o++){
            fprintf(output, " ");
        }
        tarpu_skaicius -= 2;
        fprintf(output, "\n");
    }

    fprintf(output, "\n");
    if (N > M || N > floor((2*M + 1)/3)) {
        fprintf(output, "KLAIDA 1. Programa nutraukta, nes neįmanoma rasti %d valdovių pozicijų %d dydžio lentoje. ", N, M);
        fprintf(output, "Daugiausia galima rasti %d valdovių pozicijas.\n\n", (int)floor((2*M + 1)/3));
        fprintf(output, "3 DALIS. REZULTATAI\nDėl klaidos nebuvo galima rasti valdovių išdėstymo lentoje.\n");
        fclose(output);
        return 0;
    }
    if (M > 12 || N > 8) {
        fprintf(output, "KLAIDA 2. Programa nutraukta, nes per ilgai užtrunka rasti %d valdovių pozicijas %d dydžio lentoje. ", N, M);
        fprintf(output, "Didžiausias M gali būti 12, o N - 8\n\n");
        fprintf(output, "3 DALIS. REZULTATAI\nDėl klaidos nebuvo galima rasti valdovių išdėstymo lentoje.\n");
        fclose(output);
        return 0;
    }
    fprintf(output, "2 DALIS. VYKDYMAS\n");
    solveTriangle(triangle);
    fclose(output);
}

bool solveTriangle(char triangle[]){
    bool canSolve = false;
    if (solveTriangleUtil(triangle) == true) canSolve = true;
    
    fprintf(output, "\n3 DALIS. REZULTATAI\n");
    fprintf(output, "Bandymu skaicius: %d.\n", bandymu_skaicius);
    if (canSolve){
        fprintf(output, "Sprendinys: Q - valdove, 0 - tuscia.\n\n");
        printTriangle(triangle);
        return true;
    }
    else {
        fprintf(output, "\nSprendimas nerastas.\n");
    }
}

bool solveTriangleUtil(char triangle[]){
    if (total_queens == N) {
        return true;
    }
    bool res = false;

    for (int i = M; i >= 1; i--){
        for (int o = 1; o <= i; o++){
            if (isSafe(triangle, i, o)){
                if (last_queen > total_queens) fprintf(output, "Backtrack.\n");
                else fprintf(output, "\n");
                bandymu_skaicius++;
                fprintf(output, "%7d) ", bandymu_skaicius);
                for (int j = 0; j < total_queens + 1; j++){
                    fprintf(output, "-");
                }
                fprintf(output, " Bandome %d vieta. Valdoviu vietos: { ", rowToNumber(i) + o - 1);
                changeSquare(triangle, i, o, 'Q');
                printQueens(triangle);
                last_queen = total_queens;
                total_queens++;  
                res = res || solveTriangleUtil(triangle);
                if (res) {
                    return true;
                }
                changeSquare(triangle, i, o, '0');
                total_queens--;
            }
        }
    }
    return res;
}

void printQueens(char triangle[]) {
    for (int i = 0; i < total_squares; i++){
        if (triangle[i] == 'Q'){
            fprintf(output, "%d ", i);
        }
    }
    fprintf(output, "}. ");
    fprintf(output, "Valdoviu skaicius: %d. ", total_queens + 1);
    if (total_queens + 1 != N) {
        fprintf(output, "Negauta. ");

    }
    else fprintf(output, "Gauta.\n");
}

bool isSafe(char triangle[], int row, int column) {
    //printf("..%d %d - %d %d\n", row, column, rowToNumber(row), rowToNumber(row+1));
    int rowStart = rowToNumber(row);
    int rowEnd = rowToNumber(row+1);
    //printf("Start: %d end: %d\n", rowStart, rowEnd);
    //Horizontally
    for (int i = rowToNumber(row); i < rowToNumber(row + 1); i++){
        if (triangle[i] == 'Q') {
            return false;
        }
    }
    //North-west
    int curr_column = column - 1;
    int curr_row = row - 1;
    for (int i = 0; i < column - 1; i++){
        if (triangle[rowToNumber(curr_row) + curr_column - 1] == 'Q') return false;
        curr_column--;
        curr_row--;
    }
    curr_column = column + 1;
    curr_row = row + 1;
    for (int i = 0; i < M - row; i++){
        if (triangle[rowToNumber(curr_row) + curr_column - 1] == 'Q') return false;
        curr_column++;
        curr_row++;
    }

    //North-east
    curr_column = column;
    curr_row = row - 1;
    for (int i = 0; i < M - 1; i++){
        if (triangle[rowToNumber(curr_row) + curr_column - 1] == 'Q') return false;
        curr_row--;
    }
    curr_column = column;
    curr_row = row + 1;
    for (int i = 0; i < M - row + 1; i++){
        if (triangle[rowToNumber(curr_row) + curr_column - 1] == 'Q') return false;
        curr_row++;
    }

    return true;
}

void initTriangle(char triangle[]) {
    for (int i = 0; i < total_squares; i++) {
        triangle[i] = '0'; 
    }
}

void printTriangle(char triangle[]) {
    int curr_space = M - 1;
    int last_triangle = 0;
    for (int i = 0; i < M; i++){
        last_triangle += i;
        //Print spaces before first square in row
        for (int o = 0; o < curr_space; o++){
            fprintf(output, " ");
        }
        for (int o = 0; o < i + 1; o++){
            fprintf(output, "%c", triangle[last_triangle + o]);
            if (o < i) fprintf(output, " ");
        }
        fprintf(output, "\n");
        curr_space--;
    }
}

bool changeSquare(char triangle[], int row, int column, char symbol) {
    triangle[rowToNumber(row) + column - 1] = symbol;
    //if (symbol == '1') printf("Row: %d, column: %d placed Queen\n", row, column);
    //else printf("Row: %d, column: %d removed Queen\n", row, column);
    return true;
}

int rowToNumber(int row){
    int temp = 0;
    for (int i = 0; i < row; i++) {
        temp += i;
    }
    return temp;
}

void changeToEights(char triangle[], int row, int column, int row_to_change) {
    //Horizontally
    for (int i = row_to_change + 1; i < rowToNumber(row + 1) + 1; i++) {
        triangle[i] = 'x';
    }
    
    //North-west
    int curr_column = column - 1;
    int curr_row = row - 1;
    for (int i = 0; i < column - 1; i++){
        triangle[rowToNumber(curr_row) + curr_column] = 'x';
        curr_column--;
        curr_row--;
    }
    curr_column = column + 1;
    curr_row = row + 1;
    for (int i = 0; i < M - row; i++){
        triangle[rowToNumber(curr_row) + curr_column] = 'x';
        curr_column++;
        curr_row++;
    }

    //North-east
    curr_column = column;
    curr_row = row - 1;
    for (int i = 0; i < M - 1; i++){
        triangle[rowToNumber(curr_row) + curr_column] = 'x';
        curr_row--;
    }
    curr_column = column;
    curr_row = row + 1;
    for (int i = 0; i < M - row + 1; i++){
        triangle[rowToNumber(curr_row) + curr_column] = 'x';
        curr_row++;
    }
}
