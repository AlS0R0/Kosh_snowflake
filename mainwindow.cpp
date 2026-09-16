#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , radius(50.0) //радиус описанной окружности для 0 итерации
    , cur_iter(0) //начальное значение (треугольник)
{
    ui->setupUi(this);

    //привязываем слот изменения номера итерации
    connect(ui->iter_slider, &QSlider::valueChanged, this, &MainWindow::IterationChanged);
    //привязываем слот изменения размера снежинки
    connect(ui->size_slider, &QSlider::valueChanged, this, &MainWindow::SizeChanged);

    //название окна
    QString title_text = "Kosh snowflake, iteration: " + QString::number(cur_iter);
    setWindowTitle(title_text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//рекурсивно строим треугольник (шип) на отрезке
void Add_middle_dots(QPainter& painter, QPolygonF& snowflake,
                     QPointF& firstd, QPointF& secondd, int iter_num, const double& min_dev_pixel) {

    QPointF d1 = painter.deviceTransform().map(firstd); //значение в пикселях первой точки
    QPointF d2 = painter.deviceTransform().map(secondd); //значение в пикселях второй точки
    double deviceLength = QLineF(d1, d2).length(); //расстояние в пикселях

    if (iter_num <= 0 || deviceLength < min_dev_pixel) return;
    --iter_num;

    //ищем три точки нового треугольника на отрезке
    QPointF a((secondd.x() + 2*firstd.x())/3, (secondd.y() + 2*firstd.y())/3);
    QPointF c((2*secondd.x() + firstd.x())/3, (2*secondd.y() + firstd.y())/3);
    QPointF b((a.x()+c.x())/2 - sqrt(3)*(c.y()-a.y())/2, (a.y()+c.y())/2 + sqrt(3)*(c.x()-a.x())/2);

    //входим в рекурсию для новых отрезков
    Add_middle_dots(painter, snowflake, firstd, a, iter_num, min_dev_pixel);
    snowflake << a;
    Add_middle_dots(painter, snowflake, a, b, iter_num, min_dev_pixel);
    snowflake << b;
    Add_middle_dots(painter, snowflake, b, c, iter_num, min_dev_pixel);
    snowflake << c;
    Add_middle_dots(painter, snowflake, c, secondd, iter_num, min_dev_pixel);
}

//построение снежинки Коха
QPolygonF Kosh_snowflake(QPainter& painter, int iteration_num,
                         double radius_, double centerX, double centerY, const double& min_dev_pixel) {
    QPolygonF snowflake_dots;

    //радиус описанной окружности
    double R = radius_;

    //вычисляем координаты трех вершин для 1-ой итерации
    //верхняя вершина
    QPointF f(centerX, centerY - R);

    //правая нижняя вершина
    QPointF t(centerX + R * std::cos(30 * M_PI / 180.0), centerY + R * std::sin(30 * M_PI / 180.0));

    //левая нижняя вершина
    QPointF s(centerX - R * std::cos(30 * M_PI / 180.0), centerY + R * std::sin(30 * M_PI / 180.0));

    snowflake_dots << f;
    Add_middle_dots(painter, snowflake_dots, f, s, iteration_num, min_dev_pixel);
    snowflake_dots << s;
    Add_middle_dots(painter, snowflake_dots, s, t, iteration_num, min_dev_pixel);
    snowflake_dots << t;
    Add_middle_dots(painter, snowflake_dots, t, f, iteration_num, min_dev_pixel);

    return snowflake_dots;
}

//отрисовка фигуры (с нахождением центра экрана)
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //сглаживание линий

    painter.setPen(QPen(Qt::red, 1)); //выбор цвета и толщины

    //ищем координаты середины окна
    double centerX = width() / 2.0;
    double centerY = height() / 2.0;

    QPolygonF Kosh_snowflake_ = Kosh_snowflake(painter, cur_iter, radius, centerX, centerY, min_dev_pixel);

    painter.drawPolygon(Kosh_snowflake_);
}

//изменение номера итерации снежинки Коха
void MainWindow::IterationChanged(int value) {
    cur_iter = value;

    //изменяем название окна
    QString title_text = "Kosh snowflake, iteration: " + QString::number(cur_iter);
    setWindowTitle(title_text);

    update();
}

//изменение размера снежинки
void MainWindow::SizeChanged(int value) {
    radius = static_cast<double>(value);
    update();
}
