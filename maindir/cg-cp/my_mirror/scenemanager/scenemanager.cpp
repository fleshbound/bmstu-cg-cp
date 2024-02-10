#include "scenemanager/scenemanager.h"

SceneManager::SceneManager(std::shared_ptr<QPixmap> pixmap)
{
    qInfo( "scenemanager: create" );
    _scene = std::make_shared<Scene>(pixmap);
}

std::string SceneManager::draw()
{
    _scene->draw();
    _msg = "";
    return _msg;
}

std::string SceneManager::edit_object(std::string name, const double& radius_k, const double& angle_k, const double& height_k)
{
    if (!_scene->is_name_on_scene(name))
        _scene->change_object_and_mirror(name, "");

    std::string cur_name = _scene->get_object_name();

    if (std::abs(radius_k) > 1e-8)
        _scene->change_object_geometry(QVector3D(radius_k, radius_k, 1));

    if (std::abs(height_k) > 1e-8)
        _scene->change_object_geometry(QVector3D(1, 1, height_k));

    if (std::abs(angle_k) > 1e-8)
    {}

    _msg = "";
    return _msg;
}

std::string SceneManager::edit_mirror(std::string name, const double& radius_k, const QVector3D& reflective, const double& polish, const QVector3D& diffuse)
{
    if (!_scene->is_name_on_scene(name))
        _scene->change_object_and_mirror("", name);

    std::string cur_name = _scene->get_mirror_name();

    if (cur_name.find("con", 0, cur_name.size() - 1) > 0)
        if (std::abs(radius_k) > 1e-8)
            _scene->change_mirror_geometry(QVector3D(radius_k, 1, 1)); // меньше k - больше радиус крив.

    _scene->change_mirror_material(reflective, polish, diffuse);

    _msg = "";
    return _msg;
}

std::string SceneManager::edit_light(const QVector3D& d, const QVector3D& color)
{
    _scene->move_light(d);
    _scene->change_light_color(color);
    _msg = "";
    return _msg;
}

std::string SceneManager::move_and_rotate_camera(const QVector3D& d, const QVector3D& angle)
{
    if (std::abs(d.length()) > 1e-8)
        _scene->move_camera(d);

    if (std::abs(angle.length()) > 1e-8)
        _scene->rotate_camera(angle);

    _msg = "";
    return _msg;
}
