#include <cmath>
#include <cstdlib>
#include <ctime>
//#include <fstream>
#include "desenha.h"
#include "QPen"
#include "QPainter"
#include "QBrush"
#include "QImage"

#define CONVERTE_GRAUS_P_RADIANO 0.0174532925

Desenha::Desenha(QWidget *parent) : QWidget(parent)
{
    srand(time(NULL));
    animacaoAtiva = false;
    //TODO-LER RECORDE
    startTimer(1);

    //Inicia uma jogada no inicio
    alvoX = rand()%500 + 450;
    alvoY = rand()%500 + 100;
    balaX = 1000;
    balaY = 100;
    vidasRestantes = 3;
    pontuacaoAtual = 0;

    display_vidas(vidasRestantes);
    display_pontuacao(pontuacaoAtual);
    display_posicaoX(alvoX);
    display_posicaoY(alvoY);

    //atribuições testes
    pontuacaoRecorde = 300;
}
void Desenha::timerEvent(QTimerEvent *e){
    if(animacaoAtiva){
        //Desabilitar botao de lancar
        desativar_botao();

        //Calculo da nova posicao da bala
        t=t+0.2;
        balaX = 80 + velocidadeX*t;
        balaY = 100 + velocidadeY*t - 5*pow(t,2);

        //Checa se acertou o Alvo
        if(balaX<=alvoX+60 && balaX>=alvoX && balaY>=alvoY-80 && balaY<=alvoY){
            display_status("Acertou! <+100 pontos>");
            animacaoAtiva = false;
            pontuacaoAtual+= 100;
            display_pontuacao(pontuacaoAtual);
            alvoX = rand()%500 + 450;
            alvoY = rand()%500 + 100;
            display_posicaoX(alvoX);
            display_posicaoY(alvoY);
            ativar_botao();
        }
        //Checa se chegou nos limites da fase
        if(balaX>1000 || balaY<0){
            vidasRestantes--;
            if(vidasRestantes<=-1){
                display_status("Game Over!");
                desativar_botao();
                if(pontuacaoAtual>pontuacaoRecorde){
                    //TODO-ESCREVER RECORDE
                }
            }else{
                display_status("Não Acertou!");
                display_vidas(vidasRestantes);
                ativar_botao();
            }
            animacaoAtiva = false;
        }
        repaint();
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
    //ativar animação de lançamento
    animacaoAtiva = true;
    t=0;

    //Definir velocidades em cada eixo a partir do angulo e da velocidade total
    velocidadeX = velocidadeChange*cos(anguloChange*CONVERTE_GRAUS_P_RADIANO);
    velocidadeY = velocidadeChange*sin(anguloChange*CONVERTE_GRAUS_P_RADIANO);
}
void Desenha::iniciarJogo(){
    alvoX = rand()%500 + 450;
    alvoY = rand()%500 + 100;
    balaX = 1000;
    balaY = 100;
    vidasRestantes = 3;
    pontuacaoAtual = 0;

    display_vidas(vidasRestantes);
    display_pontuacao(pontuacaoAtual);
    display_posicaoX(alvoX);
    display_posicaoY(alvoY);

    ativar_botao();

    repaint();
}


