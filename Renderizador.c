#include "Renderizador.h"


pixel** registro(int altura, int largura, FILE *file, pixel** matriz){
    //**FUNÇAO REGISTRO*****
        int  valor, n = 0, m = 0, cont = 1, k = 0;
        char leitor[500];
        matriz = (pixel**) malloc(altura * sizeof(pixel*));
        matriz[n] = (pixel*) malloc(largura * sizeof(pixel));

        printf("btf\n");
        //percorre a linha em busca dos valores de R, G e B
        while(fgets(leitor, 500, file) != NULL){
            k++;

            for(int i = 0; i < 500; i++){

                if((leitor[i] == '#') || (leitor[i] == '\n') || (leitor[i] == '\0')){
                    break; //para a busca na linha
                }
                else{
                    if((leitor[i-1] == ' ') && (leitor[i]) != ' '){
                        cont++;
                    }
                    if(cont > 3){
                        matriz[n][m].Intensidade = 0.30 * matriz[n][m].R + 0.59 * matriz[n][m].G + 0.11 * matriz[n][m].B;
                        if((n == altura - 1) && (m == largura - 1)){
                            printf("Cont: %d -- %s\n", k, leitor);
                            break;
                        }
                        if((m == largura-1) && (n < altura - 1)){
                            printf("i: %d j: %d\n", n, m);
                            printf("%d %d %d\n", matriz[n][m].R,matriz[n][m].G, matriz[n][m].B);
                            cont = 1;
                            m = 0;
                            n++;
                            matriz[n] = (pixel*) malloc(largura * sizeof(pixel));
                        }
                        else{
                            m++; //avança uma coluna na matriz
                        }
                        cont = 1;
                    }
                    if(leitor[i] != ' '){
                        if(leitor[i] == '0'){
                            valor = 0;
                        }
                        if(leitor[i] == '1'){
                            valor = 1;
                        }
                        if(leitor[i] == '2'){
                            valor = 2;
                        }
                        if(leitor[i] == '3'){
                            valor = 3;
                        }
                        if(leitor[i] == '4'){
                            valor = 4;
                        }
                        if(leitor[i] == '5'){
                            valor = 5;
                        }
                        if(leitor[i] == '6'){
                            valor = 6;
                        }
                        if(leitor[i] == '7'){
                            valor = 7;
                        }
                        if(leitor[i] == '8'){
                            valor = 8;
                        }
                        if(leitor[i] == '9'){
                            valor = 9;
                        }
                        switch (cont){
                            case 1:
                                matriz[n][m].R = matriz[n][m].R * 10 + valor;
                                break;
                            case 2:
                                matriz[n][m].G = matriz[n][m].G * 10 + valor;
                                break;
                            case 3:
                                matriz[n][m].B = matriz[n][m].B * 10 + valor;
                                break;
                        }
                    }
                }
            }
            printf("i: %d j: %d\n", n, m);
            printf("%d %d %d\n", matriz[n][m].R,matriz[n][m].G, matriz[n][m].B);

            cont++; //avanca o registro entre R, G e B

            if(cont > 3){
                matriz[n][m].Intensidade = 0.30 * matriz[n][m].R + 0.59 * matriz[n][m].G + 0.11 * matriz[n][m].B;
                if((n == altura - 1) && (m == largura - 1)){
                break;
            }
            }
            
            //avança uma linha na matriz e reinicia o contador da coluna da matriz
            if((m == largura-1) && (n < altura - 1)){
                cont = 1;
                m = 0;
                n++;
                matriz[n] = (pixel*) malloc(largura * sizeof(pixel));
            }
        }
        n = 3;
        m = 13;
        printf("%d %d %d\n", matriz[n][m].R,matriz[n][m].G, matriz[n][m].B);
        return matriz;
}





void leitor(int altura, int largura, pixel** matriz){
    int cont = 0;
    //***FUNCAO LEITOR****
        for(int i = 0; i < altura; i++){
            for(int j = 0; j < largura; j++){
                printf("%d %d %d ", matriz[i][j].R, matriz[i][j].G, matriz[i][j].B);
            }
            printf("\n");
        }
}


void limpeza(int altura, pixel** matriz){
    //***FUNCAO LIMPEZA****
    for(int i = 0; i < altura; i++){
        free(matriz[i]);
    }
    free(matriz);
}


void remocao(int largura, pixel** matriz, int y, int x){
    //***FUNCAO REMOCAO****
    for(x; x < largura - 1; x++){
        matriz[y][x] = matriz[y][x+1];
    }
}

float Operador_de_Sobel(float sup_esq, float sup, float sup_dir, float esq, float dir, float inf_esq, float inf, float inf_dir){
    int m, n;
    float mascara_x, mascara_y, energia_do_pixel;
    mascara_x = (1 * sup_esq) + (-1 * sup_dir) + (2 * esq) + (-2 * dir) + (1 * inf_esq) + (-1 * inf_dir); 
    mascara_y = (1 * sup_esq) + (2 * sup) + (1 * sup_dir) + (-1 * inf_esq) + (-2 * inf) + (-1 * inf_dir);
    mascara_x = sqrt(mascara_x * mascara_x);
    mascara_y = sqrt(mascara_y * mascara_y);
    energia_do_pixel = atan2(mascara_y, mascara_x);
    return energia_do_pixel;
}

void gravador(int altura, int largura, pixel** matriz){
    FILE *file = fopen("saida.ppm", "w");
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", largura, altura);
    fprintf(file, "255\n");
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            fprintf(file, "%d %d %d ", matriz[i][j].R, matriz[i][j].G, matriz[i][j].B);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    file = fopen("saida.pgm", "w");
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", largura, altura);
    fprintf(file, "255\n");
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura ; j++){
            fprintf(file, "%.4f ", matriz[i][j].Energia);
        }
        fprintf(file, "\n");
    }
}

void calculador(int altura, int largura, pixel** matriz){
    int x = 0, y = 0;
    printf("%.2f %.2f %.2f\n%.2f *** %.2f\n%.2f %.2f %.2f\n", matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);

    //***SUPERIOR
    //superior lateral esquerdo
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
    x++;
    for(x ; x < largura - 1; x++){
    //superior meio
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
    }
    //superior lateral direito
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade);
    y++;
    x = 0;

    //***MEIO
    for(y; y < altura - 1; y++){
    //meio lateral esquerdo
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
    printf("y: %d x: %d ", y, x);
    x++;
    for(x ; x < largura - 1; x++){
    //meio
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x + 1].Intensidade);
    }
    //meio lateral direito
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y + 1][x - 1].Intensidade, matriz[y + 1][x].Intensidade, matriz[y + 1][x].Intensidade);
    printf("y: %d x: %d\n", y, x);
    x = 0;
    }

    //***INFERIOR
    //inferior lateral esquerdo
    printf("%d\n", y);
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade);
    x++;
    for(x ; x < largura - 1; x++){
    //inferior meio
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x + 1].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x + 1].Intensidade);
    }
    //inferior lateral direito
    matriz[y][x].Energia =  Operador_de_Sobel(matriz[y - 1][x - 1].Intensidade, matriz[y - 1][x].Intensidade, matriz[y - 1][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x - 1].Intensidade, matriz[y][x].Intensidade, matriz[y][x].Intensidade);

}