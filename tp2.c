#include "Renderizador.h"





int main(){
    FILE *file = fopen("anders.ppm", "r");
    pixel** matriz;
    char magic_var[2];
    int altura, largura, max_range, x, y;

    if(file == NULL) printf("Erro, arquivo não encontrado.\n");
    else{

        fscanf(file, "%s", magic_var);
        if(strcmp(magic_var,"P3") != 0) printf("Erro na variavel magica\n");
        fscanf(file, "%d %d", &largura, &altura);
        fscanf(file, "%d ", &max_range); 

        matriz = registro(altura, largura, file, matriz);
        printf("----\n");
    
    }

    calculador(altura, largura, matriz);
    gravador(altura, largura, matriz);


    limpeza(altura, matriz);
    fclose(file);
    return 0;
}