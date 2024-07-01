#include "object/invisibleobject/camera/camera.h"

Camera::Camera(const QVector3D& pos, const QVector3D& view, const double k):
    _view(view),
    _k(k)
{
    _center = pos;
    _update_view = (_view - _center).normalized();
    Camera::update();
}

void Camera::move(const QVector3D& d)
{
    _center += d;
    _update_view = (_view - _center).normalized();
    Camera::update();
}

void Camera::update()
{
    double h = 2 * std::tan(60 * M_PI / 180 / 2);
    double w = _k * h;
    _horizontal = (QVector3D::crossProduct(_update_view, _up)).normalized();
    _vertical = QVector3D::crossProduct(_horizontal, _update_view);

    _horizontal *= w;
    _vertical *= h;

    _lower_left = _update_view - (_horizontal + _vertical) / 2.0f;
}

bool Camera::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    return false;
}

QVector3D Camera::get_pos() const
{
    return _center;
}

QVector3D Camera::get_view() const
{
    return _view;
}

void Camera::rotate(const QVector3D& angle)
{
    double cosX = std::cos(angle.x());
    double sinX = std::sin(angle.x());
    double cosY = std::cos(angle.y());
    double sinY = std::sin(angle.y());
    double cosZ = std::cos(angle.z());
    double sinZ = std::sin(angle.z());

    double newDirY = cosX * _view.y() - sinX * _view.z();
    double newDirZ = sinX * _view.y() + cosX * _view.z();

    _view.normalize();
    _view[1] = newDirY;
    _view[2] = newDirZ;

    double newDirX = cosY * _view.x() + sinY * _view.z();
    newDirZ = -sinY * _view.x() + cosY * _view.z();

    _view[0] = newDirX;
    _view[2] = newDirZ;

    newDirX = cosZ * _view.x() - sinZ * _view.y();
    newDirY = sinZ * _view.x() + cosZ * _view.y();

    _view[0] = newDirX;
    _view[1] = newDirY;

    _view.normalize();

    newDirY = cosX * _update_view.y() - sinX * _update_view.z();
    newDirZ = sinX * _update_view.y() + cosX * _update_view.z();

    _update_view.normalize();
    _update_view[1] = newDirY;
    _update_view[2] = newDirZ;

    newDirX = cosY * _update_view.x() + sinY * _update_view.z();
    newDirZ = -sinY * _update_view.x() + cosY * _update_view.z();

    _update_view[0] = newDirX;
    _update_view[2] = newDirZ;

    newDirX = cosZ * _update_view.x() - sinZ * _update_view.y();
    newDirY = sinZ * _update_view.x() + cosZ * _update_view.y();

    _update_view[0] = newDirX;
    _update_view[1] = newDirY;

    _update_view.normalize();

    Camera::update();
}

Ray Camera::get_ray(const double i, const double j) const
{
    return Ray(_center, (_lower_left + i * _horizontal + j * _vertical).normalized());
}
