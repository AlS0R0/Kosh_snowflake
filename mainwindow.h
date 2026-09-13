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
    friend QPolygonF Kosh_snowflake(int iteration_num, double centerX, double centerY);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    int it_num;
};
#endif // MAINWINDOW_H
