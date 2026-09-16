#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPolygonF>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    friend void Add_middle_dots(QPainter& painter, QPolygonF& snowflake,
                                QPointF firstd, QPointF secondd, int iter_num, double& min_dev_pixel);
    friend QPolygonF Kosh_snowflake(QPainter& painter,int iteration_num,
                                    double radius_, double centerX, double centerY, const double& min_dev_pixel);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void IterationChanged(int value);
    void SizeChanged(int value);

private:
    Ui::MainWindow *ui;
    double radius;
    int cur_iter;
    const double min_dev_pixel = 0.5; //размер пикселя экрана
};
#endif // MAINWINDOW_H
