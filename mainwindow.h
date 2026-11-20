
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calcular();

private:
    Ui::MainWindow *ui;

    // Funciones matemáticas
    double funcion1(double x);
    double funcion2(double x);
    double diferencia(double x);

    // Métodos numéricos
    double buscarRaiz(double a, double b);
    double calcularArea(double a, double b);

    // Gráfica
    void graficar();
};

#endif // MAINWINDOW_H


