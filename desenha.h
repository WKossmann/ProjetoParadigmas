#ifndef DESENHA_H
#define DESENHA_H

#include <QWidget>
/*!
 * \brief Classe para desenho dos objetos.
 * \details Esta classe é responsável pelo processo dos dados de entrada ( velocidade e angulo ), para desenhar e dar movimento
 * aos objetos do jogo (tela de fundo, canhao, alvo e bala) de acordo com os botôes de ativação.
 */
class Desenha : public QWidget
{
    Q_OBJECT
public:
    //Variavies:
    /*! Define se há movimento da bala a ser feito */
    bool animacaoAtiva;
    /*! (Tempo) Variável auxiliar para calculo da altura da bala em cada instante */
    double t;
    /*! Posição x a ser desenhada a Bala */
    double balaX;
    /*! Posição y a ser desenhada a Bala */
    double balaY;
    /*! Posição x a ser desenhado o Alvo */
    double alvoX;
    /*! Posição y a ser desenhado o Alvo */
    double alvoY;
    /*! Velocidade em x para calculo da posição */
    double velocidadeX;
    /*! Velocidade em y para calculo da posição */
    double velocidadeY;
    /*! Variavel auxiliar que é atualizada de acordo com a mudança do LineEdit Velocidade */
    double velocidadeChange;
    /*! Variavel auxiliar que é atualizada de acordo com a mudança do LineEdit Angulo*/
    double anguloChange;
    /*! Variavel de controle de vidas restantes para game over */
    int vidasRestantes;
    /*! Variavel de controle da pontuação durante um partida */
    int pontuacaoAtual;
    /*! Variavel de controle da pontuação recorde (gravada em um arquivo) */
    int pontuacaoRecorde;

    /*! Construtor do objeto, com algumas pré-configurações em sua estrutura*/
    explicit Desenha(QWidget *parent = 0);
    /*! Membro da classe que controla o timerEvent, disparado a cada 1ms */
    void timerEvent(QPaintEvent *e);
    /*! Membro da classe que controla o desenho na tela */
    void paintEvent(QPaintEvent *e);
signals:
    /*! Sinal para mostrar a posição atual do alvo, em X */
    void display_posicaoX(double);
    /*! Sinal para mostrar a posição atual do alvo, em Y */
    void display_posicaoY(double);
    /*! Sinal para amostrar a situação atual do jogador */
    void display_status(QString);
    /*! Sinal para controle do desparecimento do botão de lançar */
    void desativar_botao();
    /*! Sinal para controle do aparecimento do botão de lançar */
    void ativar_botao();
    /*! Sinal para mostrar a pontuação atual da jogada */
    void display_pontuacao(int);
    /*! Sinal para mostrar a pontuação recorde do jogo */
    void display_recorde(int);
    /*! sinal para mostrar a quantidade de vidas restantes que o jogador possui */
    void display_vidas(int);
public slots:
    /*! Recebe o texto (QString x) do lineEdit Velocidade a medida que ele vai sendo editado */
    void muda_velocidade(QString x);
    /*! Recebe o texto (QString x) do lineEdit Angulo a medida que ele vai sendo editado */
    void muda_angulo(QString x);
    /*! Recebe o click do botao de lançamento */
    void lancar();
    /*! Recebe o click do botao de incio de jogo */
    void iniciarJogo();
};

#endif // DESENHA_H
