#include <cmath>
#include "desenha.h"
#include "QPen"
#include "QPainter"
#include "QBrush"
#include "QImage"
#define CONVERTE_GRAUS_P_RADIANO 0.0174532925

Desenha::Desenha(QWidget *parent) : QWidget(parent)
{
    t=0;
    animacaoAtiva = false;
    velocidadeX = 0;
    velocidadeY = 0;
    alvoX = 500;
    alvoY = 100;
    startTimer(1);
}
void Desenha::timerEvent(QTimerEvent *e){
    if(animacaoAtiva){
        t=t+0.1;
        balaX = 80 + velocidadeX*t;
        display_posX(balaX);
        balaY = 100 + velocidadeY*t - 5*pow(t,2);
        display_posY(balaY);
        if(balaX<=alvoX+60 && balaX>=alvoX && balaY>=alvoY-80 && balaY<=alvoY){
            display_status("Acertou!!");
            animacaoAtiva = false;
        }
        if(balaX>1000 || balaY<0){
            display_status("Não Acertou!!");
            animacaoAtiva = false;
        }
        repaint();
    }else{
        balaX=80;
        balaY=100;
    }
}
void Desenha::paintEvent(QPaintEvent *e){
    QPainter p(this);
    QPen pen;
    QBrush brush;

    //Imagem de fundo(fixo):
    QImage fundo(":/images/fundo");
    p.drawImage(0,0,fundo,0,0,1000,600);
    //Imagem canhao(fixo):
    QImage canhao(":/images/canhao01");
    p.drawImage(0,520,canhao,0,0,80,65);
    //Imagem alvo(local-sorteado):
    QImage alvo(":/images/alvo");
    p.drawImage(alvoX,height()-alvoY,alvo,0,0,50,55);
    //Imagem bala(equação):
    QImage bala(":/images/bala1");
    p.drawImage(balaX,height()-balaY,bala,0,0,20,20);
}
void Desenha::muda_velocidade(QString x){
    velocidadeChange = x.toDouble();
}
void Desenha::muda_angulo(QString x){
    anguloChange = x.toDouble();
}
void Desenha::lancar(){
    animacaoAtiva = true;
    t=0;
    balaX=80;
    balaY=100;
    velocidadeX = velocidadeChange*cos(anguloChange*CONVERTE_GRAUS_P_RADIANO);
    display_velocidadeX(velocidadeX);
    velocidadeY = velocidadeChange*sin(anguloChange*CONVERTE_GRAUS_P_RADIANO);
    display_velocidadeY(velocidadeY);
}


