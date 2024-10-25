#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>

void InicializaVGA(void);
void PontosCirculo(int, int, int, int, int);
void Circulo5(int, int, int, int);
void DesenhaFatiaTomate(int, int, int, int, int);
void DesenhaIconeBandeiraItaliana(int, int, int);

void InicializaVGA() {
    int Gd, Gm;
    char GrErr;

    Gd = DETECT;
    initgraph(&Gd, &Gm, "k:\\bgi");

    GrErr = graphresult();
    if (GrErr != grOk) {
        printf("Erro gráfico: %s\n", grapherrormsg(GrErr));
        exit(1);
    }
}

void PontosCirculo(int xc, int yc, int x, int y, int cor) {
    putpixel(xc + x, yc - y, cor); // 1º octante
    putpixel(xc + y, yc - x, cor); // 2º octante
    putpixel(xc + y, yc + x, cor); // 3º octante
    putpixel(xc + x, yc + y, cor); // 4º octante
    putpixel(xc - x, yc + y, cor); // 5º octante
    putpixel(xc - y, yc + x, cor); // 6º octante
    putpixel(xc - y, yc - x, cor); // 7º octante
    putpixel(xc - x, yc - y, cor); // 8º octante
}

void Circulo5(int xc, int yc, int raio, int cor) {
    int x = 0, y = raio - 1;
    int d = 1 - raio;
    PontosCirculo(xc, yc, x, y, cor);
    while (y > x) {
        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        PontosCirculo(xc, yc, x, y, cor);
    }
}

void DesenhaFatiaTomate(int centroX, int centroY, int raioPizza, int numeroRodelas, int raioRodela) {
    int i;

    // Desenha a pizza
    for (i = 0; i <= raioPizza; i++) {
        Circulo5(centroX, centroY, i, YELLOW); // Pizza
    }

    // Desenha as rodelas de tomate
    for (i = 0; i < numeroRodelas; i++) {
        int angulo = 360 / numeroRodelas * i;
        int xRodela = centroX + (raioPizza - raioRodela) * cos(angulo * M_PI / 180);
        int yRodela = centroY - (raioPizza - raioRodela) * sin(angulo * M_PI / 180);
        Circulo5(xRodela, yRodela, raioRodela, RED); // Rodela de tomate
    }
}

void DesenhaIconeBandeiraItaliana(int x, int y, int tamanho) {
    // Retângulo verde
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(x, y, x + tamanho, y + tamanho);
    floodfill(x + tamanho / 2, y + tamanho / 2, GREEN);

    // Retângulo branco
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(x + tamanho, y, x + 2 * tamanho, y + tamanho);
    floodfill(x + 3 * tamanho / 2, y + tamanho / 2, WHITE);

    // Retângulo vermelho
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    rectangle(x + 2 * tamanho, y, x + 3 * tamanho, y + tamanho);
    floodfill(x + 5 * tamanho / 2, y + tamanho / 2, RED);
}

void main(void) {
    int centroX = 320;
    int centroY = 240;
    int raioPizza = 150;
    int numeroRodelas = 10;
    int raioRodela = 20;
    int tamanhoIconeBandeira = 20;

    randomize();
    InicializaVGA();

    // Desenha a pizza e as fatias de tomate
    DesenhaFatiaTomate(centroX, centroY, raioPizza, numeroRodelas, raioRodela);

    // Desenha o texto no topo do círculo amarelo (Pizza)
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(centroX - textwidth("Pizza Portuguesa") / 2, centroY - raioPizza - textheight("Pizza Portuguesa") - 10, "Pizza Portuguesa");

    // Desenha o ícone da bandeira italiana
    DesenhaIconeBandeiraItaliana(centroX + raioPizza + 10, centroY - tamanhoIconeBandeira / 2, tamanhoIconeBandeira);

    // Desenha novamente a pizza e as fatias de tomate
    DesenhaFatiaTomate(centroX, centroY, raioPizza, numeroRodelas, raioRodela);

    // Desenha três círculos vermelhos no meio
    int centroX1 = centroX;
    int centroY1 = centroY;
    int centroX2 = centroX - 30; // Ajuste as posições conforme necessário
    int centroY2 = centroY + 30;
    int centroX3 = centroX + 30;
    int centroY3 = centroY + 30;

    // Desenha cinco círculos verdes no meio
    int centroX4 = centroX - 20;
    int centroY4 = centroY - 20;
    int centroX5 = centroX + 20;
    int centroY5 = centroY - 20;
    int centroX6 = centroX - 20;
    int centroY6 = centroY + 20;
    int centroX7 = centroX + 20;
    int centroY7 = centroY + 20;
    int centroX8 = centroX;
    int centroY8 = centroY;

    Circulo5(centroX4, centroY4, 10, GREEN);
    Circulo5(centroX5, centroY5, 10, GREEN);
    Circulo5(centroX6, centroY6, 10, GREEN);
    Circulo5(centroX7, centroY7, 10, GREEN);
    Circulo5(centroX8, centroY8, 10, GREEN);

    getch();
    closegraph();
}

