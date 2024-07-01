#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene/scene.h"

class SceneManager
{
public:
    SceneManager(std::shared_ptr<QPixmap> pixmap);
    ~SceneManager() = default;
    explicit SceneManager(const SceneManager &);
    SceneManager(SceneManager &&) noexcept;

    std::string draw();
    std::string edit_object(std::string name, const QVector3D& scale_k, const QVector3D& angle_k);
    std::string edit_mirror(std::string name, const double& radius_k, const QVector3D& reflective, const double& polish, const QVector3D& diffuse);
    std::string edit_light(const QVector3D& d, const QVector3D& color);
    std::string move_and_rotate_camera(const QVector3D& d, const QVector3D& angle);

private:
    std::shared_ptr<Scene> _scene;
    std::string _msg;
};

#endif // SCENEMANAGER_H
