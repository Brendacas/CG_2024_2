#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int R = 0, G=0, B = 0;

void display(void);
void corpo();
void cabeca();
void olho();
void braco_esquerdo();
void braco_direito();
void perna_esquerda();
void perna_direita();
void boca();
void desenha_nuvem();
void sol();



int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  glutInitWindowSize (800,600); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (00, 00); //Estabelece o tamanho (em pixels) da janela a ser criada
  glutCreateWindow (argv[1]); //Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(0.8, 0.5, 1.0, 0.0); //selecionar cor de fundo (Azul)
  glOrtho (-1, 1,-1, 1, -1 ,1); //define as coordenadas do volume de recorte (clipping volume),
  glutDisplayFunc(display); //Função callback chamada para fazer o desenho
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  printf("\nTestando... \n");
  return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
    glBegin(GL_POLYGON);
    // Canto inferior esquerdo - Verde (R=0, G=255, B=0)
    glColor3ub(0, 255, 0);
    glVertex2f(-1.0f, -1.0f);

    // Canto superior esquerdo - Azul (R=0, G=0, B=255)
    glColor3ub(0, 0, 255);
    glVertex2f(-1.0f, 1.0f);

    // Canto superior direito - Azul (R=0, G=0, B=255)
    glColor3ub(0, 0, 255);
    glVertex2f(1.0f, 1.0f);

    // Canto inferior direito - Verde (R=0, G=255, B=0)
    glColor3ub(0, 255, 0);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    corpo();
    cabeca();
    braco_esquerdo();
    braco_direito();
    perna_esquerda();
    perna_direita();
    sol();
    desenha_nuvem();


    glutSwapBuffers();

    glFlush(); ////Executa os comandos OpenGL para renderização
}

float grausParaRadianos(float angulo)
{
    return (angulo * 2 * 3.14159265358979323846) / 360.0;
}
void Circulo(float raio, float x0, float y0, int def, float graus, int r, int g, int b)
{
    /* raio: define o tamanho do circulo.
        x0, y0: define a posição onde o circulo vai está.
        def: a quantidade de pontos, quanto maior mais perfeito o circulo
        a,b,c: define a cor do circulo
    */
    float passo = grausParaRadianos(graus / def);
    float x, y;
    float angulo = grausParaRadianos(0);

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // define a cor
    for (int i = 0; i < def; i++)
    {
        x = raio * cos(angulo) + x0;
        y = raio * sin(angulo) + y0;
        glVertex2f(x, y);
        angulo += passo;
    }
    glEnd();
}
void semi_Circulo(float raio, float x0, float y0, int def, float graus, int a, int b, int c)
{
    /* raio: define o tamanho do circulo.
        x0, y0: define a posição onde o circulo vai está.
        def: a quantidade de pontos, quanto maior mais perfeito o circulo
        a,b,c: define a cor do circulo
    */
    float passo = grausParaRadianos(graus / def);
    float x, y;
    float angulo = grausParaRadianos(0);

    glBegin(GL_POLYGON);
    glColor3ub(a,b,c); // define a cor
    for (int i = 0; i < def; i++)
    {
        x = raio * cos(angulo) + x0;
        y = raio * sin(angulo) + y0;
        glVertex2f(x, y);
        glColor3ub(a, b, c); // define a cor

        angulo += passo;
    }
    glEnd();
};
void torax()
{
    glBegin(GL_POLYGON);
    glColor3ub(245, 245, 220); // Define a cor do tórax

    // Definindo os vértices 
    glVertex2f(0.300, 0.3);       // ponto A 
    glVertex2f(0.395, -0.4);    // ponto B 
    glVertex2f(-0.395, -0.4);   // ponto C 
    glVertex2f(-0.300, 0.3);    // ponto D 

    glEnd();
}

void corpo()
{
    glPushMatrix();  // Salva a matriz de transformação atual

    // Aplicando as transformações para mover
    glTranslatef(-0.5, 0.0, 0.0); // Move o corpo para a esquerda
    glScalef(0.5, 0.5, 1.0);      

    // Desenhando o corpo 
    semi_Circulo(0.3, 0.0, 0.3, 20, 200,240,255,255);
    torax(); // Desenha o tórax
    semi_Circulo(0.400, 0.0, -0.4, 20, -189.6240, 240, 255,255);

    glPopMatrix();  // Restaura a matriz de transformação anterior
}

/*void olho()
{

    semi_Circulo_Olho(0.105, -0.10, 0.2, 30, 200, 0);

    glBegin(GL_POLYGON);
    glColor3ub(133, 133, 133); // define a cor

    glVertex2f(-0.120, 0.2);  // ponto A
    glColor3ub(133, 133, 133); // define a cor
    glVertex2f(-0.2, 0.17);   // ponto B
    glColor3ub(255, 255, 255); // define a cor
    glVertex2f(-0.04, 0.17);   // ponto C
    glColor3ub(255, 255, 255); // define a cor
    glVertex2f(-0.120, 0.28);  // ponto D
    glEnd();

    semi_Circulo_Olho(0.105, -0.10, 0.2, 30, -180, 0);

    // desenha a pupila
    Circulo(0.05, -0.13, 0.22, 20, 340);

    semi_Circulo_Olho(0.105, 0.14, 0.28, 30, -200, 180);

    glBegin(GL_POLYGON);
    glColor3ub(133, 133, 133); // define a cor

    glVertex2f(0.244, 0.26);   // ponto A
    glColor3ub(133, 133, 133); // define a cor
    glVertex2f(0.24, 0.17);    // ponto B
    glColor3ub(255, 255, 255); // define a cor
    glVertex2f(0.04, 0.17);    // ponto C
    glColor3ub(255, 255, 255); // define a cor
    glVertex2f(0.035, 0.28);   // ponto D
    glEnd();

    semi_Circulo_Olho(0.105, 0.14, 0.21, 30, 200, 180);

    // desenha a pupila
    Circulo(0.05, 0.13, 0.22, 20, 340);
}
*/

void cabeca(){
    glPushMatrix();  // Salva a matriz de transformação atual

    // Aplicando as transformações para mover
    glTranslatef(-0.55, 0.0, 0.0); // Move a cabeça para a esquerda
    glScalef(0.4, 0.4, 1.0);  
    Circulo(0.42, 0.160, 1.3, 200, 340, 255, 240, 245); // exterior da cabeça
    Circulo(0.35, 0.170, 1.3, 200, 340, 128, 128, 128); // interior da cabeça
    Circulo(0.06, 0.300, 1.4, 200, 340, 255, 255, 255); // olho esquerdo
    Circulo(0.06, 0.110, 1.4, 200, 340, 255, 255, 255); // olho direito
    boca();

    glPopMatrix();  // Restaura a matriz de transformação anterior

}
// Função para desenhar o braço com cantos arredondados
void braco_esquerdo( ) {
   
    semi_Circulo(0.027, -0.677, 0.18, 10, 200, 200,255,200); // Desenha a parte superior arredondada do braço
    glPushMatrix();

    // Desenha a parte retangular do braço
    glBegin(GL_QUADS);
    glColor3ub(200,255,200); // Cor do braço
    glVertex2f(-0.830f, -0.18f);    // Vértice inferior esquerdo
    glVertex2f(-0.750f, -0.18f);     // Vértice inferior direito
    glVertex2f(-0.650f, 0.18f);     // Vértice superior direito
    glVertex2f(-0.702f, 0.18f);    // Vértice superior esquerdo
    glEnd();

    glPopMatrix();
    semi_Circulo(0.04, -0.788, -0.18, 20, -200,200,255,200); // Desenha a parte inferior arredondada do braço
}
void braco_direito() { // falta alinhar os semicirculo
    // Desenha a parte superior arredondada do braço
    
    semi_Circulo(0.027, 0.377, 0.18, 20, 180, 200, 255, 200); // 180 graus para a parte superior
  
    glPushMatrix();
    glTranslatef(0.55, 0.0, 0.0); // Move pra direita
    //semi_Circulo(0.027, 0.377, 0.18, 20, 180, 200, 255, 200); // 180 graus para a parte superior
    // Desenha a parte retangular do braço
    glBegin(GL_QUADS);
    glColor3ub(200,255,200); // Cor do braço
    glVertex2f(-0.790f, -0.18f);    // Vértice inferior esquerdo
    glVertex2f(-0.700f, -0.18f);     // Vértice inferior direito
    glVertex2f(-0.890f, 0.18f);     // Vértice superior direito
    glVertex2f(-0.830f, 0.18f);    // Vértice superior esquerdo
    glEnd();

    
    glTranslatef(-0.25, 0.0, 0.0); // Move pra direita
    // Desenha a parte inferior arredondada do braço
    semi_Circulo(0.04, 0.05, -0.18, 20, -180, 200, 255, 200); // 180 graus para a parte inferior
    glPopMatrix();
} 

void perna_esquerda() {

    glBegin(GL_QUADS);
    glColor3ub(255,255,255); // Cor da perna
    glVertex2f(-0.660f, -0.58f);    // Vértice inferior esquerdo
    glVertex2f(-0.600f, -0.58f);     // Vértice inferior direito
    glVertex2f(-0.600f, -0.2f);     // Vértice superior direito
    glVertex2f(-0.660f, -0.2f);    // Vértice superior esquerdo
    glEnd();
}

void perna_direita(){

    glBegin(GL_QUADS);
    glColor3ub(255,255,255); // Cor da perna
    glVertex2f(-0.420f, -0.58f);    // Vértice inferior esquerdo
    glVertex2f(-0.360f, -0.58f);     // Vértice inferior direito
    glVertex2f(-0.360f, -0.2f);     // Vértice superior direito
    glVertex2f(-0.420f, -0.2f);    // Vértice superior esquerdo
    glEnd();
}

void boca()
{
    // Define a cor da boca
    glColor3ub(255, 255, 255); 

    // Define o raio e a posição central do semicírculo
    float raio = 0.15;
    float x_centro = 0.2;
    float y_centro = 1.2;

    // Define o número de pontos para o semicírculo
    int num_pontos = 30;

    // Calcula o ângulo de cada ponto no semicírculo
    float angulo;
    float passo_angulo = M_PI / num_pontos;

    // Desenha o semicírculo da boca
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_pontos; i++)
    {
        angulo = (i * passo_angulo) + M_PI; // Ajusta o ângulo para começar de baixo
        float x = x_centro + raio * cos(angulo);
        float y = y_centro + raio * sin(angulo);
        glVertex2f(x, y);
    }
    glEnd();
}

void desenha_nuvem() {
    // Círculo maior central (centralizado no topo direito)
    Circulo(0.12f, 0.08f, 0.63f, 50, 360, 255, 255, 255); 
    // Círculo à esquerda
    Circulo(0.12f, 0.20f, 0.63f, 50, 360, 255, 255, 255); 
    // Círculo menor central inferior
    Circulo(0.12f, 0.35f, 0.63f, 50, 360, 255, 255, 255);

    //Nuvem2    
    // Círculo maior central (centralizado no topo direito)
    Circulo(0.12f, 0.58f, 0.63f, 50, 360, 255, 255, 255); 
    // Círculo à esquerda
    Circulo(0.12f, 0.73f, 0.63f, 50, 360, 255, 255, 255); 
    // Círculo menor central inferior
    Circulo(0.12f, 0.85f, 0.63f, 50, 360, 255, 255, 255);

}
void sol(){
    Circulo(0.18f, 0.48f, 0.70f, 50, 360, 255, 255, 0); 
}



