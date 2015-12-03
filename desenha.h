#ifndef DESENHA_H
#define DESENHA_H

#include <QWidget>

class Desenha : public QWidget
{
    Q_OBJECT
private:
    bool animacaoAtiva;
    double t;
    double balaX;
    double balaY;
    double alvoX;
    double alvoY;
    double velocidadeX;
    double velocidadeY;
    double velocidadeChange;
    double anguloChange;
public:
    explicit Desenha(QWidget *parent = 0);
    void timerEvent(QTimerEvent *e);
    void paintEvent(QPaintEvent *e);
signals:
    void display_velocidadeX(double);
    void display_velocidadeY(double);
    void display_status(QString);
    void display_posX(double);
    void display_posY(double);
public slots:
    void muda_velocidade(QString x);
    void muda_angulo(QString x);
    void lancar();
};

#endif // DESENHA_H
