#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



typedef struct pixel{
    int R, G, B;
    float Intensidade, Caminho;
    double Energia;
    char Direcao[2];
}pixel;



pixel** registro(int ,int ,FILE* ,pixel**);
void leitor(int, int, pixel**);
void limpeza(int , pixel**);
void remocao(int , pixel** , int, int);
float Operador_de_Sobel(float, float, float, float, float, float, float, float);
void gravador(int, int, pixel**);
void calculador(int, int, pixel**);