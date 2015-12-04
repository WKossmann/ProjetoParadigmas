#ifndef DESENHA_H
#define DESENHA_H

#include <QWidget>

class Desenha : public QWidget
{
    Q_OBJECT
private:
    bool animacaoAtiva;
    double t;
    double balaX, balaY;
    double alvoX, alvoY;
    double velocidadeX, velocidadeY;
    double velocidadeChange;
    double anguloChange;
    int vidasRestantes;
    int pontuacaoAtual;
    int pontuacaoRecorde;
public:
    explicit Desenha(QWidget *parent = 0);
    void timerEvent(QTimerEvent *e);
    void paintEvent(QPaintEvent *e);
signals:
    void display_posicaoX(double);
    void display_posicaoY(double);
    void display_status(QString);
    void desativar_botao();
    void ativar_botao();
    void display_pontuacao(int);
    void display_recorde(int);
    void display_vidas(int);
public slots:
    void muda_velocidade(QString x);
    void muda_angulo(QString x);
    void lancar();
    void iniciarJogo();
};

#endif // DESENHA_H
