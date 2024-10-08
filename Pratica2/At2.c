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
void corpo_interior();
void cabeca();
void olho();
void braco_esquerdo();
void braco_direito();
void perna_esquerda();
void perna_direita();
void boca();
void desenha_nuvem();
void sol();
void desenharGarra();
void fogo();
void robo();



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
    robo();
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
void semi_Circulo(float raio, float x0, float y0, int def, float graus, int r, int g, int b)
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
    glColor3ub(r,g,b); // define a cor
    for (int i = 0; i < def; i++)
    {
        x = raio * cos(angulo) + x0;
        y = raio * sin(angulo) + y0;
        glVertex2f(x, y);
        glColor3ub(r,g,b); // define a cor

        angulo += passo;
    }
    glEnd();
};
void torax(int r, int g, int b)
{
    glBegin(GL_POLYGON);
    glColor3ub(r,g,b); // Define a cor do tórax

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
    semi_Circulo(0.3, 0.0, 0.3, 20, 200,255,255,255);
    torax(255,255,255); // Desenha o tórax
    semi_Circulo(0.400, 0.0, -0.4, 20, -189.6240, 255, 255,255);

    glPopMatrix();  // Restaura a matriz de transformação anterior
}

void corpo_interior(){
    glPushMatrix();  // Salva a matriz de transformação atual

    glScalef(0.4f, 0.4f, 0.4f);
    glTranslatef(-1.25, 0.0, 0.0); // Move o corpo para a esquerda

    // Desenhando o corpo 
    semi_Circulo(0.3, 0.0, 0.3, 20, 200,100, 149, 220);
    torax(100, 149, 220); // Desenha o tórax
    semi_Circulo(0.400, 0.0, -0.4, 20, -189.6240, 100, 149, 220);
    
    glPopMatrix();  // Restaura a matriz de transformação anterior
}

void cabeca(){
    glPushMatrix();  // Salva a matriz de transformação atual
    
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); 
    glVertex2f(-0.50, 0.50f);    // Vértice inferior esquerdo
    glVertex2f(-0.48, 0.50f);     // Vértice inferior direito
    glVertex2f(-0.48f, 0.70f);     // Vértice superior direito
    glVertex2f(-0.50, 0.70f);    // Vértice superior esquerdo
    glEnd();

    Circulo(0.02, -0.484, 0.72, 200,340, 255,0,0);
    // Aplicando as transformações para mover
    glTranslatef(-0.55, 0.0, 0.0); // Move a cabeça para a esquerda
    glScalef(0.4, 0.4, 1.0);  
    Circulo(0.42, 0.160, 1.25, 200, 340, 255, 255, 255); // exterior da cabeça
    Circulo(0.35, 0.170, 1.25, 200, 340, 100, 149, 220); // interior da cabeça
    Circulo(0.06, 0.300, 1.35, 200, 340, 255, 255, 255); // olho esquerdo
    Circulo(0.06, 0.110, 1.35, 200, 340, 255, 255, 255); // olho direito
    boca();

    //pescoço
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); 
    glVertex2f(0.11, 0.74f);    // Vértice inferior esquerdo
    glVertex2f(0.15, 0.74f);     // Vértice inferior direito
    glVertex2f(0.15f, 0.83f);     // Vértice superior direito
    glVertex2f(0.11, 0.83f);    // Vértice superior esquerdo
    glEnd();

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
    //semi_Circulo(0.04, -0.788, -0.18, 20, -200,200,255,200); // Desenha a parte inferior arredondada do braço
}
void braco_direito() { 
    // Desenha a parte superior arredondada do braço
    
    semi_Circulo(0.027, -0.315, 0.18, 20, 189, 200, 255, 200); 
  
    glPushMatrix();
    glTranslatef(0.55, 0.0, 0.0); // Move pra direita
    // Desenha a parte retangular do braço
    glBegin(GL_QUADS);
    glColor3ub(200,255,200); // Cor do braço
    glVertex2f(-0.790f, -0.18f);    // Vértice inferior esquerdo
    glVertex2f(-0.710f, -0.18f);     // Vértice inferior direito
    glVertex2f(-0.840f, 0.18f);     // Vértice superior direito
    glVertex2f(-0.893f, 0.18f);    // Vértice superior esquerdo
    glEnd();
    glPopMatrix();

   // semi_Circulo(0.04, -0.201, -0.18, 20, -200,200,255,200);
} 

void perna_esquerda() {

    glBegin(GL_QUADS);
    glColor3ub(255,255,255); // Cor da perna
    glVertex2f(-0.660f, -0.58f);    // Vértice inferior esquerdo
    glVertex2f(-0.600f, -0.58f);     // Vértice inferior direito
    glVertex2f(-0.600f, -0.3f);     // Vértice superior direito
    glVertex2f(-0.660f, -0.3f);    // Vértice superior esquerdo
    glEnd();
}

void perna_direita(){

    glBegin(GL_QUADS);
    glColor3ub(255,255,255); // Cor da perna
    glVertex2f(-0.420f, -0.58f);    // Vértice inferior esquerdo
    glVertex2f(-0.360f, -0.58f);     // Vértice inferior direito
    glVertex2f(-0.360f, -0.3f);     // Vértice superior direito
    glVertex2f(-0.420f, -0.3f);    // Vértice superior esquerdo
    glEnd();
}

void boca()
{
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255); 
    glVertex2f(0.06, 1.02f);    // Vértice inferior esquerdo
    glVertex2f(0.32, 1.02f);     // Vértice inferior direito
    glVertex2f(0.32f, 1.1f);     // Vértice superior direito
    glVertex2f(0.06, 1.1);    // Vértice superior esquerdo
    glEnd();
}

void desenha_nuvem() {
    glPushMatrix();  // Salva a matriz de transformação atual
    glTranslatef(-0.4, 0.0, 0.0); // Move a nuvem para a esquerda
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
    glPopMatrix();  // Restaura a matriz de transformação anterior

}
void sol(){
    glPushMatrix();  // Salva a matriz de transformação atual
    glTranslatef(-0.4, 0.0, 0.0); // Move o sol para a esquerda
    Circulo(0.18f, 0.48f, 0.70f, 50, 360, 255, 255, 0); 
    glPopMatrix();  // Restaura a matriz de transformação anterior
}

void desenharGarra() { 
    //esquerda
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); 
    glVertex2f(-0.820f, -0.20f);    // Vértice inferior esquerdo
    glVertex2f(-0.760f, -0.20f);     // Vértice inferior direito
    glVertex2f(-0.760f, -0.18f);     // Vértice superior direito
    glVertex2f(-0.820f, -0.18f);    // Vértice superior esquerdo
    glEnd();
    // Desenhar a parte superior da garra
    semi_Circulo(0.05, -0.795f, -0.25f, 50, 180, 169,169,169); // Parte superior arredondada da garra

    // Desenhar a parte inferior da garra (semi-círculo invertido)
    semi_Circulo(0.03,-0.795f, -0.25f, 50, 180, 0, 255, 150); // Parte inferior arredondada da garra

    //direita
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); 
    glVertex2f(-0.23f, -0.18f);    // Vértice inferior esquerdo
    glVertex2f(-0.17f, -0.18f);     // Vértice inferior direito
    glVertex2f(-0.17f, -0.20f);     // Vértice superior direito
    glVertex2f(-0.23f, -0.20f);    // Vértice superior esquerdo
    glEnd();
    // Desenhar a parte superior da garra
    semi_Circulo(0.05, -0.20f, -0.25f, 50, 180, 169,169,169); // Parte superior arredondada da garra

    // Desenhar a parte inferior da garra (semi-círculo invertido)
    semi_Circulo(0.03,-0.20f, -0.25f, 50, 180, 0, 255, 150); // Parte inferior arredondada da garra
}

void fogo() {
    //direita
    glBegin(GL_TRIANGLES);  // Primeira camada da chama

    // Parte superior da chama - Vermelho (Agora o topo está acima)
    glColor3ub(255, 0, 0);  // Vermelho
    glVertex2f(-0.662f, -0.58f);  // Ponto esquerdo superior
    glVertex2f(-0.600f, -0.58f);  // Ponto direito superior

    // Parte inferior da chama - Amarelo
    glColor3ub(255, 255, 0);  // Amarelo
    glVertex2f(-0.635f, -0.78f);   // Ponto inferior (centro da chama)

    glEnd();

    glBegin(GL_TRIANGLES);  // Segunda camada da chama mais interna

    // Parte superior da chama interna - Laranja (Topo da parte interna)
    glColor3ub(255, 165, 0);  // Laranja
    glVertex2f(-0.652f, -0.58f);  // Ponto esquerdo superior
    glVertex2f(-0.614f, -0.58f);  // Ponto direito superior

    // Parte inferior da chama interna - Amarelo claro (Centro inferior)
    glColor3ub(255, 255, 100);  // Amarelo claro
    glVertex2f(-0.635f, -0.75f);  // Ponto inferior (centro da chama interna)

    glEnd();

    //esquerda
    glBegin(GL_TRIANGLES);  // Primeira camada da chama

    // Parte superior da chama - Vermelho (Agora o topo está acima)
    glColor3ub(255, 0, 0);  // Vermelho
    glVertex2f(-0.420f, -0.58f);  // Ponto esquerdo superior
    glVertex2f(-0.362f, -0.58f);  // Ponto direito superior
    
    // Parte inferior da chama - Amarelo 
    glColor3ub(255, 255, 0);  // Amarelo
    glVertex2f(-0.395f, -0.78f);   // Ponto inferior (centro da chama)

    glEnd();

    glBegin(GL_TRIANGLES);  // Segunda camada da chama mais interna

    // Parte superior da chama interna - Laranja (Topo da parte interna)
    glColor3ub(255, 165, 0);  // Laranja
    glVertex2f(-0.410f, -0.58f);  // Ponto esquerdo superior
    glVertex2f(-0.372f, -0.58f);  // Ponto direito superior
    
    // Parte inferior da chama interna - Amarelo claro (Centro inferior)
    glColor3ub(255, 255, 100);  // Amarelo claro
    glVertex2f(-0.395f, -0.75f);  // Ponto inferior (centro da chama interna)

    glEnd();
}

void robo(){
    glPushMatrix();  // Salva a matriz de transformação atual
    glScaled(0.6, 0.6, 0.6);  // Escala o robô
    glTranslatef(-0.55, 0.0, 0.0); // Move o robô para a esquerda
    cabeca();
    corpo();
    corpo_interior();
    braco_esquerdo();
    braco_direito();
    desenharGarra();
    perna_esquerda();
    perna_direita();
    fogo();
    glPopMatrix();  // Restaura a matriz de transformação anterior
}