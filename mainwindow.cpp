

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVector>
#include <QPen>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectar el botón con el cálculo
    connect(ui->btnCalcular, &QPushButton::clicked,
            this, &MainWindow::calcular);

    // Dibujar las funciones al abrir el programa
    graficar();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// FUNCIONES MATEMÁTICAS


double MainWindow::funcion1(double x)
{
    return x*x - 0.5*x - 3;
}

double MainWindow::funcion2(double x)
{
    return -x*x + 8;
}

// Diferencia entre las funciones



double MainWindow::diferencia(double x)
{
    return funcion1(x) - funcion2(x);
}

// MÉTODO DE BISECCIÓN

double MainWindow::buscarRaiz(double a, double b)
{
    double medio;

    for(int i = 0; i < 100; i++)
    {
        medio = (a + b) / 2.0;

        if(diferencia(a) * diferencia(medio) < 0)
        {
            b = medio;
        }
        else
        {
            a = medio;
        }
    }

    return (a + b) / 2.0;
}


// MÉTODO DE SIMPSON


double MainWindow::calcularArea(double a, double b)
{
    int n = 10000;

    double h = (b - a) / n;

    double suma = diferencia(a) + diferencia(b);

    for(int i = 1; i < n; i++)
    {
        double x = a + i*h;

        if(i % 2 == 0)
        {
            suma += 2 * diferencia(x);
        }
        else
        {
            suma += 4 * diferencia(x);
        }
    }

    return std::abs((h / 3.0) * suma);
}


// GRAFICAR LAS DOS FUNCIONES


void MainWindow::graficar()
{
    QVector<double> x;
    QVector<double> y1;
    QVector<double> y2;

    for(double i = -4; i <= 4; i += 0.01)
    {
        x.append(i);

        y1.append(funcion1(i));
        y2.append(funcion2(i));
    }

    // Limpiar gráficas anteriores
    ui->customPlot->clearGraphs();

    // Primera función
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y1);
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue, 2));
    ui->customPlot->graph(0)->setName("f(x)");

    // Segunda función
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(x, y2);
    ui->customPlot->graph(1)->setPen(QPen(Qt::red, 2));
    ui->customPlot->graph(1)->setName("g(x)");

    // Configuración de los ejes
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");

    ui->customPlot->xAxis->setRange(-4, 4);
    ui->customPlot->yAxis->setRange(-5, 10);

    // Mostrar leyenda
    ui->customPlot->legend->setVisible(true);

    ui->customPlot->replot();
}


// CALCULAR Y MOSTRAR RESULTADOS


void MainWindow::calcular()
{
    // Buscar las dos intersecciones
    double x1 = buscarRaiz(-3, 0);
    double x2 = buscarRaiz(0, 3);

    // Calcular el área
    double area = calcularArea(x1, x2);

    // Mostrar resultados
    ui->labelRaiz1->setText(
        QString("Primera intersección: x1 = %1")
            .arg(x1, 0, 'f', 4));

    ui->labelRaiz2->setText(
        QString("Segunda intersección: x2 = %1")
            .arg(x2, 0, 'f', 4));

    ui->labelArea->setText(
        QString("Área entre las curvas: %1")
            .arg(area, 0, 'f', 4));

    // Dibujar nuevamente las funciones
    graficar();

    // Marcar los puntos de intersección
    QVector<double> puntosX;
    QVector<double> puntosY;

    puntosX.append(x1);
    puntosX.append(x2);

    puntosY.append(funcion1(x1));
    puntosY.append(funcion1(x2));

    ui->customPlot->addGraph();

    ui->customPlot->graph(2)->setData(puntosX, puntosY);

    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);

    ui->customPlot->graph(2)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::black, 8));

    ui->customPlot->replot();
}