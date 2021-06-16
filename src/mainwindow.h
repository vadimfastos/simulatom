#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include "atommodel.h"
#include "qcustomplot.h"
#include "viewer3d.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_input_n_valueChanged(int arg1);
    void on_input_l_valueChanged(int arg1);
    void on_input_m_valueChanged(int arg1);
    void on_prob_dens_toggled(bool checked);
    void on_prob_toggled(bool checked);
    void on_model3d_viewChanged(long double mov_x, long double mov_y, long double rot_x, long double rot_y);
    void on_reset_3d_clicked();

private:
    Ui::MainWindow *ui;
    AtomModel *model;
    QImage *image_2d, *image_3d;

// Model redraw
    void redraw();
    void redraw_graphic();
    void redraw_2d();
    void redraw_3d(long double mov_x, long double mov_y, long double rot_x, long double rot_y);
};


#endif // MAINWINDOW_H
