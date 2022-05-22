#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



typedef struct pixel{
    int R, G, B, Direcao;
    float Intensidade, Energia;
    double Caminho;
}pixel;



pixel** registro(int ,int ,FILE* ,pixel**);
void leitor(int, int, pixel**);
void limpeza(int , pixel**);
void remocao(int , int, pixel**);
float Operador_de_Sobel(float, float, float, float, float, float, float, float);
void gravador(int, int, pixel**);
void calculador(int, int, pixel**);
pixel calculador_de_caminho(double, double, double, pixel);