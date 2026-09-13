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

    friend void Add_middle_dots(QPolygonF& snowflake, QPointF firstd, QPointF secondd, int iter_num);
    friend QPolygonF Kosh_snowflake(int iteration_num, double radius_, double centerX, double centerY);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void IterationChanged(int value);
    void SizeChanged(int value);

private:
    Ui::MainWindow *ui;
    double radius;
    int cur_iter;
};
#endif // MAINWINDOW_H
