#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


/*!
 *  \mainpage Pagina principal
 * Este é um projeto com o objetivo da aprendizagem em prática da utilização do Qt Creator para
 * programação visual. Foi idealizado a construção de um jogo simples 2D para acerto ao alvo
 * de modo a incentivar o estudo e prática da fisica classica, mais precisamente do movimento parabólico.
 * O usuario tem com objetivo informar a velocidade inicial e o angulo, no qual supostamente deverá acertar
 * o alvo e ver a simulação acontecer para checar se sua resposta estava certa.
 */



namespace Ui {
class MainWindow;
}
/*!
 * \brief Classe para construção da tela principal.
 * \details Esta classe é responsável pela inicialização visual do programa e para construção dos demais objetos.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*! Construtor da tela principal */
    explicit MainWindow(QWidget *parent = 0);
    /*! Destrutor da tela principal */
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
