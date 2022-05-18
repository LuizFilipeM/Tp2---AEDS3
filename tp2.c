#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pixel{
    int R, G, B;
    float Intensidade, Energia, Caminho;
    char Direcao[2];
}pixel;

int main(){
    FILE *file = fopen("entrada.txt", "r");
    pixel** matriz;
    char magic_var[2], leitor[300];
    int altura, largura, max_range, n = 0, m = 0, valor, cont = 1;

    if(file == NULL) printf("Erro, arquivo não encontrado.\n");
    else{

        //**FUNÇAO REGISTRO*****
        fscanf(file, "%s", magic_var);
        if(strcmp(magic_var,"P3") != 0) printf("Erro na variavel magica\n");
        fscanf(file, "%d %d", &altura, &largura);
        fscanf(file, "%d ", &max_range); 
        printf("magica: %s alt: %d lar: %d Max: %d\n", magic_var, altura, largura, max_range);

        matriz = (pixel**) malloc(altura * sizeof(pixel*));
        matriz[n] = (pixel*) malloc(largura * sizeof(pixel));

        //percorre a linha em busca dos valores de R, G e B
        while(fgets(leitor, 100, file) != NULL){

            for(int i = 0; i < 100; i++){

                if((leitor[i] == '#') || (leitor[i] == '\n') || (leitor[i] == '\0')){
                    break; //para a busca na linha
                }
                else{
                    if((leitor[i-1] == ' ') && (leitor[i]) != ' '){
                        cont++;
                    }
                    if(cont > 3){
                            cont = 1;
                            m++; //avança uma coluna na matriz
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
        
        
            cont++; //avanca o registro entre R, G e B
            
            //avança uma linha na matriz e reinicia o contador da coluna da matriz
            if((m == largura-1) && (n < altura - 1)){
                cont = 1;
                m = 0;
                n++;
                matriz[n] = (pixel*) malloc(largura * sizeof(pixel));
            }
        }

        //***FUNCAO LEITOR****
        if(1){
        for(int i = 0; i < altura; i++){
            for(int j = 0; j < largura; j++){
                printf("+ %d %d %d +", matriz[i][j].R, matriz[i][j].G, matriz[i][j].B);
            }
            printf("\n");
            free(matriz[i]);
        }
        free(matriz);
        fclose(file);
        }
    }
}