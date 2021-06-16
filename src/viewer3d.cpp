#include "viewer3d.h"
#include "vectormatrix.h"


Viewer3D::Viewer3D(QWidget *parent) :
    QLabel(parent),
// All mouse buttons is released
    isLeftMouseButtonPressed(false),
    isRightMouseButtonPressed(false),
// Set view to default
    raw_mov_x(0),
    raw_mov_y(0),
    raw_rot_x(0),
    raw_rot_y(0) {

// Set move limits
    raw_mov_x_min = -width();
    raw_mov_x_max = width();
    raw_mov_y_min = -height();
    raw_mov_y_max = height();

// Set rotation limits
    raw_rot_x_min = -width();
    raw_rot_x_max = width();
    raw_rot_y_min = -height();
    raw_rot_y_max = height();
}


// Set view to default
void Viewer3D::setView2Default() {
    raw_mov_x = 0; raw_mov_y = 0;
    raw_rot_x = 0; raw_rot_y = 0;
}


// Compute relative horizontal movement
long double Viewer3D::getMovX() const {
    long double mx_coeff = 2.0l / (raw_mov_x_max - raw_mov_x_min);
    return mx_coeff * raw_mov_x;
}


// Compute relative vertical movement
long double Viewer3D::getMovY() const {
    long double my_coeff = -2.0l / (raw_mov_y_max - raw_mov_y_min);
    return my_coeff * raw_mov_y;
}


// Compute relative horizontal rotation
long double Viewer3D::getRotX() const {
    long double rx_coeff = 2.0l / (raw_rot_x_max - raw_rot_x_min) * M_PI;
    return rx_coeff * raw_rot_x;
}


// Compute relative vertical rotation
long double Viewer3D::getRotY() const {
    long double ry_coeff = 1.0l / (raw_rot_y_max - raw_rot_y_min) * M_PI;
    return ry_coeff * raw_rot_y;
}


void Viewer3D::mousePressEvent(QMouseEvent *event) {
    isLeftMouseButtonPressed = event->buttons() & Qt::LeftButton;
    isRightMouseButtonPressed = event->buttons() & Qt::RightButton;
    mouse_pos = event->pos();
}


void Viewer3D::mouseReleaseEvent(QMouseEvent *event) {
    isLeftMouseButtonPressed = event->buttons() & Qt::LeftButton;
    isRightMouseButtonPressed = event->buttons() & Qt::RightButton;
    mouse_pos = event->pos();
}


void Viewer3D::mouseMoveEvent(QMouseEvent *event) {
    if (!isLeftMouseButtonPressed && !isRightMouseButtonPressed)
        return;

// Get mouse move
    QPoint delta = event->pos();
    delta -= mouse_pos;
    mouse_pos = event->pos();

// Get mouse movement on each axis
    int dx = delta.x();
    int dy = delta.y();

    if (isLeftMouseButtonPressed) {
    // Process horizontal movement
        raw_mov_x += dx;
        if (raw_mov_x < raw_mov_x_min)
            raw_mov_x = raw_mov_x_min;
        if (raw_mov_x > raw_mov_x_max)
            raw_mov_x = raw_mov_x_max;
     // Process vertical movement
        raw_mov_y += dy;
        if (raw_mov_y < raw_mov_y_min)
            raw_mov_y = raw_mov_y_min;
        if (raw_mov_y > raw_mov_y_max)
            raw_mov_y = raw_mov_y_max;
    } else {
    // Process horizontal rotation
        raw_rot_x += dx;
        if (raw_rot_x < raw_rot_x_min)
            raw_rot_x = raw_rot_x_min;
        if (raw_rot_x > raw_rot_x_max)
            raw_rot_x = raw_rot_x_max;
     // Process vertical rotation
        raw_rot_y += dy;
        if (raw_rot_y < raw_rot_y_min)
            raw_rot_y = raw_rot_y_min;
        if (raw_rot_y > raw_rot_y_max)
            raw_rot_y = raw_rot_y_max;
    }

// Call handler
    emit viewChanged(getMovX(), getMovY(), getRotX(), getRotY());
}
