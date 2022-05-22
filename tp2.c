#include "Renderizador.h"




int main(){
    FILE *file = fopen("papa.ppm", "r");
    pixel** matriz;
    char magic_var[2];
    int altura, largura, max_range, x, y, j = 200;

    if(file == NULL) printf("Erro, arquivo não encontrado.\n");
    else{

        fscanf(file, "%s", magic_var);
        if(strcmp(magic_var,"P3") != 0) printf("Erro na variavel magica\n");
        fscanf(file, "%d %d", &largura, &altura);
        fscanf(file, "%d ", &max_range); 

        matriz = registro(altura, largura, file, matriz);
        
    
    }
    

    
    if(1){
    calculador(altura, largura, matriz);
    while(j != 0){
        remocao(largura, altura, matriz);
        largura--;
        calculador(altura, largura, matriz);
        j--;
    }
    }
    if(1){
    gravador(altura, largura, matriz);
    }
    limpeza(altura, matriz);
    fclose(file);
    
    return 0;
}