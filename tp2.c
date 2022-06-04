#include "Grafo.h"





int main(int argc, char *argv[]){
    parametros param;
    char magic_var[2], tipo_de_remocao[3], estrategia[5];
    int altura, largura, aux_de_trans, max_range;
    retorna_parametros(argc, argv, &param);
    FILE *file = fopen(param.file, "r");
    if(file == NULL){
        printf("Erro, arquivo não encontrado.\n");
        return 0;
    }
    else{

        fscanf(file, "%s", magic_var);
        if(strcmp(magic_var,"P3") != 0) printf("Erro na variavel magica\n");
            fscanf(file, "%d %d", &largura, &altura);
            fscanf(file, "%d ", &max_range); 
            if((param.colunas > largura-2) || (param.linhas > altura - 2)){
                printf("Erro, remocao invalida, tente um numero menor");
                return 0;
            } 

    
        if(param.estrategia[0] == 'D'){
            pixel** matriz;
            matriz = registro_de_matriz_dinamica(altura, largura, file, matriz);
            calculador_de_matriz_dinamica(altura, largura, matriz);


            if(param.colunas != 0){
                while(param.colunas != 0){
                    remocao_de_matriz_dinamica(largura, altura, matriz);
                    largura--;
                    calculador_de_matriz_dinamica(altura, largura, matriz);
                    param.colunas--;
                }
            }
            if(param.linhas != 0){
                matriz = transpor_de_matriz_dinamica(altura, largura, matriz);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_matriz_dinamica(altura, largura, matriz);

                while(param.linhas != 0){
                    remocao_de_matriz_dinamica(largura, altura, matriz);
                    largura--;
                    calculador_de_matriz_dinamica(altura, largura, matriz);
                    param.linhas--;
                }
                
                matriz = transpor_de_matriz_dinamica(altura, largura, matriz);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
            }

            gravador_de_matriz_dinamica(altura, largura, matriz);
            limpeza_de_matriz_dinamica(altura, matriz);
        }
        if(param.estrategia[0] == 'G'){
            grafo* Grafo;
            Grafo = registro_de_grafo(altura, largura, file, Grafo);
            calculador_de_grafo(altura, largura, Grafo);

            if(param.colunas != 0){
                while(param.colunas != 0){
                    remocao_de_grafo(largura, altura, Grafo);
                    largura--;
                    calculador_de_grafo(altura, largura, Grafo);
                    param.colunas--;
                }
            }
            if(param.linhas != 0){
                Grafo = transpor_de_grafo(altura, largura, Grafo);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
                calculador_de_grafo(altura, largura, Grafo);
                while(param.linhas != 0){
                    remocao_de_grafo(largura, altura, Grafo);
                    largura--;
                    calculador_de_grafo(altura, largura, Grafo);
                    param.linhas--;
                }
                Grafo = transpor_de_grafo(altura, largura, Grafo);
                aux_de_trans = altura;
                altura = largura;
                largura = aux_de_trans;
            }
            gravador_de_grafo(altura, largura, Grafo);
            limpeza_de_grafo(altura, largura, Grafo);
        }
    }
    fclose(file);
    
    return 0;
}