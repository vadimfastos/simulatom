#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      image_2d(nullptr),
      image_3d(nullptr)
{
    ui->setupUi(this);
    model = new AtomModel();
    QObject::connect(ui->model_3d, SIGNAL(viewChanged(long double,long double,long double,long double)), this, SLOT(on_model3d_viewChanged(long double,long double,long double,long double)));
    ui->statusbar->showMessage("Разработчик программы: студент группы ИВТ-12 НИУ МИЭТ Слесарев Вадим. Год разработки: 2021");
    ui->prob->setText("вероятность: |\u03A8|\u00B2*\u03C1\u00B2");
    ui->prob_dens->setText("плотность вероятности: |\u03A8|\u00B2");
    redraw();
}


MainWindow::~MainWindow()
{
    delete image_2d;
    delete image_3d;
    delete ui;
    delete model;
}


// Handle main quantum number changing
void MainWindow::on_input_n_valueChanged(int arg1)
{
    if (!model->set_n(arg1))
        return;
    ui->input_l->setMinimum(0);
    ui->input_l->setMaximum(model->get_n()-1);
    redraw();
}


// Handle orbital quantum number changing
void MainWindow::on_input_l_valueChanged(int arg1)
{
    if (!model->set_l(arg1))
        return;
    ui->input_m->setMinimum(-model->get_l());
    ui->input_m->setMaximum(model->get_l());
    redraw();
}


// Handle magnetic quantum number changing
void MainWindow::on_input_m_valueChanged(int arg1)
{
    if (!model->set_m(arg1))
        return;
    redraw();
}


// Handle model type changing
void MainWindow::on_prob_dens_toggled(bool checked)
{
    model->setProbabilityDensityStatus(checked);
    redraw();
}


// Handle model type changing
void MainWindow::on_prob_toggled(bool checked)
{
    model->setProbabilityDensityStatus(!checked);
    redraw();
}


// Handle view changing
void MainWindow::on_model3d_viewChanged(long double mov_x, long double mov_y, long double rot_x, long double rot_y)
{
    redraw_3d(mov_x, mov_y, rot_x, rot_y);
}


// Handle reset 3D view
void MainWindow::on_reset_3d_clicked()
{
    ui->model_3d->setView2Default();
    redraw_3d(ui->model_3d->getMovX(), ui->model_3d->getMovY(), ui->model_3d->getRotX(), ui->model_3d->getRotX());
}


// Redraw all models
void MainWindow::redraw()
{
    ui->quantum_state->setText("Состояние: " + model->getState());
    redraw_graphic();
    redraw_2d();
    ui->model_3d->setView2Default();
    redraw_3d(ui->model_3d->getMovX(), ui->model_3d->getMovY(), ui->model_3d->getRotX(), ui->model_3d->getRotX());
}


// Redraw graphic
void MainWindow::redraw_graphic()
{
    const int points_count = 1000;

// Compute model
    long double *p = new long double[points_count];
    model->modelGraphic(p, points_count);
    QVector<double> x(points_count), y(points_count);
    for (int i=0; i<points_count; i++) {
        x[i] = model->maxRelativeRadius() * i / points_count;
        y[i] = p[i];
    }
    delete[] p;

// Build graphic
    ui->model_graphic->addGraph();
    ui->model_graphic->graph(0)->setData(x, y);

// Set horizontal (r) axis
    ui->model_graphic->xAxis->setLabel("\u03C1 = r / r\u2080, r\u2080 = 0,529*10\u207B\u00B9\u2070 м - боровский радиус");
    ui->model_graphic->xAxis->setRange(0, model->maxRelativeRadius());

// Set vertical (phi^2*r^2 or phi^2) axis
    if (model->isProbabilityDensity()) {
        ui->model_graphic->yAxis->setLabel("|\u03A8|\u00B2");
    } else {
        ui->model_graphic->yAxis->setLabel("|\u03A8|\u00B2*\u03C1\u00B2");
    }
    ui->model_graphic->yAxis->setRange(0, 1);
    ui->model_graphic->yAxis->setTickLabels(false);

// Show results
    ui->model_graphic->replot();
}


// Redraw 2D atom model
void MainWindow::redraw_2d()
{

// Get size of image and create it
    int width = ui->model_2d->width();
    int height = ui->model_2d->height();
    if (image_2d == nullptr)
        image_2d = new QImage(width, height, QImage::Format_RGB32);

// Compute model
    long double *p = new long double[height * width];
    model->model2D(p, width, height);

// Per pixel drawing
    for (int yy=0; yy<height; yy++)
        for (int xx=0; xx<width; xx++)  {
            long double intensity = p[yy*width + xx];
        // Compute 8-bit color components
            int r = 255 * intensity;
            int g = 128 * intensity;
            int b = 0 * intensity;
            r = (r < 0) ? 0 : r; r = (r > 0xFF) ? 0xFF : r;
            g = (g < 0) ? 0 : g; g = (g > 0xFF) ? 0xFF : g;
            b = (b < 0) ? 0 : b; b = (b > 0xFF) ? 0xFF : b;
        // Draw pixel
            image_2d->setPixel(xx, yy, r<<16 | g<<8 | b);
        }

// Show results
    delete[] p;
    ui->model_2d->setPixmap(QPixmap::fromImage(*image_2d));
}


// Redraw 3D atom model
void MainWindow::redraw_3d(long double mov_x, long double mov_y, long double rot_x, long double rot_y)
{

// Get size of image and create it
    int width = ui->model_3d->width();
    int height = ui->model_3d->height();
    if (image_3d == nullptr)
        image_3d = new QImage(width, height, QImage::Format_RGB32);

// Compute model
    long double *p = new long double[height * width];
    model->model3D(p, width, height, mov_x, mov_y, rot_x, rot_y);

// Per pixel drawing
    for (int yy=0; yy<height; yy++)
        for (int xx=0; xx<width; xx++)  {
            long double intensity = p[yy*width + xx];
        // Compute 8-bit color components
            int r = 128 * intensity;
            int g = 10 * intensity;
            int b = 255 * intensity;
            r = (r < 0) ? 0 : r; r = (r > 0xFF) ? 0xFF : r;
            g = (g < 0) ? 0 : g; g = (g > 0xFF) ? 0xFF : g;
            b = (b < 0) ? 0 : b; b = (b > 0xFF) ? 0xFF : b;
        // Draw pixel
            image_3d->setPixel(xx, yy, r<<16 | g<<8 | b);
        }

// Show results
    delete[] p;
    ui->model_3d->setPixmap(QPixmap::fromImage(*image_3d));
}
