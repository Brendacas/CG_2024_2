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



int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  glutInitWindowSize (800, 600); //Posição inicial do canto superior esquerdo da janela a ser criada
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
  corpo();

  glutSwapBuffers();

  glFlush(); ////Executa os comandos OpenGL para renderização
}

float grausParaRadianos(float angulo)
{
    return (angulo * 2 * 3.14159265358979323846) / 360.0;
}

void semi_Circulo_Corpo(float raio, float x0, float y0, int def, float graus)
{
    /* raio: define o tamanho do circulo.
        x0, y0: define a posição onde o circulo vai está.
        def: a quantidade de pontos, quanto maior mais perfeito o circulo
    */
    float passo = grausParaRadianos(graus / def);
    float x, y;
    float angulo = grausParaRadianos(0);

    glBegin(GL_POLYGON);
    glColor3ub(255, 205, 250); // define a cor
    for (int i = 0; i < def; i++)
    {
        x = raio * cos(angulo) + x0;
        y = raio * sin(angulo) + y0;
        glVertex2f(x, y);
        glColor3ub(255, 205, 250); // define a cor

        angulo += passo;
    }
    glEnd();
}
void torax()
{
    glBegin(GL_POLYGON);
    glColor3ub(255, 205, 250); // Define a cor do tórax

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
    semi_Circulo_Corpo(0.3, 0.0, 0.3, 20, 200);
    torax(); // Desenha o tórax
    semi_Circulo_Corpo(0.400, 0.0, -0.4, 20, -189.6);

    glPopMatrix();  // Restaura a matriz de transformação anterior
}


