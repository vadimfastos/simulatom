#ifndef VIEWER3D_H
#define VIEWER3D_H


#include <Qt>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>


class Viewer3D : public QLabel
{
    Q_OBJECT

private:
    bool isLeftMouseButtonPressed;
    bool isRightMouseButtonPressed;
    QPoint mouse_pos;

    int raw_mov_x, raw_mov_x_min, raw_mov_x_max;
    int raw_mov_y, raw_mov_y_min, raw_mov_y_max;
    int raw_rot_x, raw_rot_x_min, raw_rot_x_max;
    int raw_rot_y, raw_rot_y_min, raw_rot_y_max;

public:
    explicit Viewer3D(QWidget *parent = nullptr);

// Set view to default
    void setView2Default();

// Get current move and rotation
    long double getMovX() const;
    long double getMovY() const;
    long double getRotX() const;
    long double getRotY() const;

signals:
    void viewChanged(long double mov_x, long double mov_y, long double rot_x, long double rot_y);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

};

#endif // VIEWER3D_H
