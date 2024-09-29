// Brenda Castro da Silva (202121125)
// Lavínia Souza Caló de Figueiredo (202220033)

#include <stdio.h>
#include <stdlib.h>

FILE *fpin1, *fpin2, *fpout;
int **imagemR1,**imagemG1, **imagemB1; 
int **imagemR2, **imagemG2, **imagemB2; 
int ncol, nlin, quantizacao;

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(void);
void ler_imagem(void);
void gravar_imagem(FILE *fpout, int **, int **, int **, int **, int **, int **, int, int, int, float);
void fechar_arquivos(void);

void abrir_arquivos(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Modo correto de uso: <prog> <imagemIn1> <imagemIn2>\n");
        exit(0);
    }
    if ((fpin1 = fopen(argv[1], "r")) == NULL) {
        printf("Nao foi possivel abrir o arquivo de imagem %s\n", argv[1]);
        exit(1);
    }
    if ((fpin2 = fopen(argv[2], "r")) ==  NULL) {
        printf("Nao foi possivel abrir o arquivo de imagem %s\n", argv[2]);
        exit(1);
    }
}

void ler_cabecalho(void) {
    char controle1[4], controle2[4]; 
    int ncol1, nlin1, quantizacao1;

    fscanf(fpin1, "%s\n", controle1);
    fscanf(fpin1,"%d %d\n", &ncol1, &nlin1);
    fscanf(fpin1, "%d\n", &quantizacao1);

    fscanf(fpin2, "%s\n", controle2);
    fscanf(fpin2,"%d %d\n", &ncol, &nlin); 
    fscanf(fpin2, "%d\n", &quantizacao);

    if (ncol1 != ncol || nlin1 != nlin || quantizacao1 != quantizacao) {
        printf("As imagens tem tamanhos ou quantizacoes diferentes.\n");
        exit(1);
    }

    ncol = ncol1;
    nlin = nlin1;
    quantizacao = quantizacao1;
}


void ler_imagem(void) {
    int cont, col, lin;

    imagemR1 = (int **)malloc((nlin+1)*sizeof(int *));
    imagemG1 = (int **)malloc((nlin+1)*sizeof(int *));
    imagemB1 = (int **)malloc((nlin+1)*sizeof(int *));
    
    imagemR2 = (int **)malloc((nlin+1)*sizeof(int *));
    imagemG2 = (int **)malloc((nlin+1)*sizeof(int *));
    imagemB2 = (int **)malloc((nlin+1)*sizeof(int *));
    
    for(cont = 0; cont < nlin; cont++) {
        imagemR1[cont] = (int *)malloc(ncol*sizeof(int));
        if (imagemR1[cont] == NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }

        imagemG1[cont] = (int *)malloc(ncol*sizeof(int));
        if (imagemG1[cont] == NULL) {
            printf("Falha na alocacao de momoria - 1\n");
            exit(1);
        }

        imagemB1[cont] = (int *)malloc(ncol*sizeof(int));
        if (imagemB1[cont] == NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }

        imagemR2[cont] = (int *)malloc(ncol*sizeof(int));
        if (imagemR2[cont] == NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }

        imagemG2[cont] = (int *)malloc(ncol*sizeof(int));
        if (imagemG2[cont] == NULL) {
            printf("Falha na alocacao de momoria - 1\n");
            exit(1);
        }

        imagemB2[cont] = (int *)malloc(ncol*sizeof(int));
        if (imagemB2[cont] == NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
    }
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fscanf(fpin1, "%d ", &imagemR1[lin][col]);
            fscanf(fpin1, "%d ", &imagemG1[lin][col]);
            fscanf(fpin1, "%d ", &imagemB1[lin][col]);
            fscanf(fpin2, "%d ", &imagemR2[lin][col]);
            fscanf(fpin2, "%d ", &imagemG2[lin][col]);
            fscanf(fpin2, "%d ", &imagemB2[lin][col]);
        }
    }
}

void gravar_imagem(FILE *fpout, int **imagemR1, int **imagemG1, int **imagemB1, int **imagemR2, int **imagemG2, int **imagemB2, int nlin, int ncol, int quantizacao, float cont) {
    int lin, col;

    fprintf(fpout, "P3\n");
    fprintf(fpout, "%d %d\n", ncol, nlin);
    fprintf(fpout, "%d\n", quantizacao); 

    for(lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            int pixelR = (int)(imagemR1[lin][col] * (1.0 - cont) + imagemR2[lin][col] * cont);
            int pixelG = (int)(imagemG1[lin][col] * (1.0 - cont) + imagemG2[lin][col] * cont);
            int pixelB = (int)(imagemB1[lin][col] * (1.0 - cont) + imagemB2[lin][col] * cont);

            fprintf(fpout, "%d %d %d ", pixelR, pixelG, pixelB); 
        }
        fprintf(fpout, "\n"); 
    }
}

void fechar_arquivos(void) {
    fclose(fpin1);
    fclose(fpin2);
    fclose(fpout);
}

int main(int argc, char *argv[]) {
    abrir_arquivos(argc, argv);
    ler_cabecalho();
    ler_imagem();
    
    for (float cont = 0.0; cont <= 1.0; cont += 0.05) { 
    char nomeArquivo[50];
    sprintf(nomeArquivo, "imagem_morph_%.1f.ppm", cont);
    FILE *fpout = fopen(nomeArquivo, "w");
    if (fpout == NULL) {
        printf("Erro ao abrir o arquivo de saída: %s\n", nomeArquivo);
        exit(1);
    }
    gravar_imagem(fpout, imagemR1, imagemG1, imagemB1, imagemR2, imagemG2, imagemB2, nlin, ncol, quantizacao, cont);
    fclose(fpout);
    }
    return 0;
}