#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , iter_num(3) //тестовое значение
{
    ui->setupUi(this);

    setWindowTitle("Kosh snowflake"); //название окна
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPolygonF Kosh_snowflake(int iteration_num, double centerX, double centerY) {
    QPolygonF snowflake_dots;

    //радиус описанной окружности
    double R = 200.0;

    //вычисляем координаты трех вершин для 1-ой итерации
    //верхняя вершина
    snowflake_dots << QPointF(centerX, centerY - R);

    //правая нижняя вершина
    snowflake_dots << QPointF(centerX + R * std::cos(330 * M_PI / 180.0),
                              centerY - R * std::sin(330 * M_PI / 180.0));

    //левая нижняя вершина
    snowflake_dots << QPointF(centerX + R * std::cos(210 * M_PI / 180.0),
                              centerY - R * std::sin(210 * M_PI / 180.0));

    return snowflake_dots;
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //сглаживание линий

    painter.setPen(QPen(Qt::red, 2)); //выбор цвета и толщины

    //ищем координаты середины окна
    double centerX = width() / 2.0;
    double centerY = height() / 2.0;

    QPolygonF Kosh_snowflak = Kosh_snowflake(iter_num, centerX, centerY);

    painter.drawPolygon(Kosh_snowflak);
}
