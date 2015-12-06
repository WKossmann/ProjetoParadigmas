#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "desenha.h"
#include "QPen"
#include "QPainter"
#include "QBrush"
#include "QImage"
using namespace std;

#define CONVERTE_GRAUS_P_RADIANO 0.0174532925

Desenha::Desenha(QWidget *parent) : QWidget(parent)
{
    srand(time(NULL));
    startTimer(1);
    animacaoAtiva = false;

    //Ler Recorde do arquivo:
    ifstream arquivoLeitura("recorde.txt");
    char leitura[100];
    if(arquivoLeitura.is_open()){
        arquivoLeitura.getline(leitura,100);
        pontuacaoRecorde = atoi(leitura);
    }else{
        pontuacaoRecorde = 0;
    }
}
void Desenha::timerEvent(QPaintEvent *e){
    if(animacaoAtiva){
        //Desabilitar botao de lancar
        desativar_botao();

        //Calculo da nova posicao da bala
        balaX += 5;
        t = (balaX-80)/(velocidadeX);
        balaY = 100 + velocidadeY*t - 5*pow(t,2);

        /*
        t=t+0.2;
        balaX = 80 + velocidadeX*t;
        balaY = 100 + velocidadeY*t - 5*pow(t,2);
        */
        //Checa se acertou o Alvo
        if(balaX<=alvoX+60 && balaX>=alvoX && balaY>=alvoY-65 && balaY<=alvoY+15){
            display_status("Acertou!\n <+100 pontos>");
            pontuacaoAtual+= 100;

            //Sorteia novo local para o alvo:
            alvoX = rand()%500 + 450;
            alvoY = rand()%500 + 100;

            //Mostrar informações:
            display_recorde(pontuacaoRecorde);
            display_pontuacao(pontuacaoAtual);
            display_posicaoX(alvoX);
            display_posicaoY(alvoY);

            animacaoAtiva = false;
            ativar_botao();
        }
        //Checa se chegou nos limites da fase
        if(balaX>1000 || balaY<0){
            //Perde uma vida:
            vidasRestantes--;

            //Checa se já chegou GameOver
            if(vidasRestantes<=-1){
                display_status("Game Over!");
                desativar_botao();

                //Checa se bateu o recorde:
                if(pontuacaoAtual>pontuacaoRecorde){
                    pontuacaoRecorde = pontuacaoAtual;

                    //Escreve no arquivo:
                    ofstream arquivoEscrita("recorde.txt");
                    if(arquivoEscrita.is_open()){
                        arquivoEscrita << pontuacaoRecorde;
                    }
                }

                //Sinal para mostrar o recorde:
                display_recorde(pontuacaoRecorde);
            }else{
                //Não chegou no GameOver
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
    //Grava em uma variavel auxiliar
    velocidadeChange = x.toDouble();
}
void Desenha::muda_angulo(QString x){
    //Grava em uma variavel auxiliar
    anguloChange = x.toDouble();
}
void Desenha::lancar(){
    //Ativar animação de lançamento:
    animacaoAtiva = true;
    balaX = 80;
    if(anguloChange==90){
        anguloChange = 89;
    }

    //Definir velocidades em cada eixo a partir do angulo e da velocidade total guardada nas variaveis auxiliares:
    velocidadeX = velocidadeChange*cos(anguloChange*CONVERTE_GRAUS_P_RADIANO);
    velocidadeY = velocidadeChange*sin(anguloChange*CONVERTE_GRAUS_P_RADIANO);
}
void Desenha::iniciarJogo(){
    //Checa se houve recorde na partida passada:
    if(pontuacaoAtual>pontuacaoRecorde){
        pontuacaoRecorde = pontuacaoAtual;

        //Escreve no arquivo:
        ofstream arquivoEscrita("recorde.txt");
        if(arquivoEscrita.is_open()){
            arquivoEscrita << pontuacaoRecorde;
        }
    }

    //Sortear local para o alvo:
    alvoX = rand()%500 + 450;
    alvoY = rand()%500 + 100;

    //Definir posição invalida para a bala
    balaX = 80;

    //Inicializar variaveis de partida:
    vidasRestantes = 3;
    pontuacaoAtual = 0;

    //Mostrar informações:
    display_vidas(vidasRestantes);
    display_pontuacao(pontuacaoAtual);
    display_recorde(pontuacaoRecorde);
    display_posicaoX(alvoX);
    display_posicaoY(alvoY);

    ativar_botao();

    repaint();
}


