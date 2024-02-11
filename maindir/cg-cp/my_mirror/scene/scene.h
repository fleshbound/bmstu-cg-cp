#ifndef SCENE_H
#define SCENE_H

#undef emit
#include <cmath>
#include <mutex>
#include <random>
#include <tbb/tbb.h>
#include "builder/cone/cone.h"
#include "builder/cylinder/cylinder.h"
#include "builder/mirror/concave/mirrorconcave.h"
#include "builder/mirror/convex/mirrorconvex.h"
#include "builder/mirror/plane/mirrorplane.h"
#include "builder/prysm/tri/prysmtri.h"
#include "builder/prysm/tetra/prysmtetra.h"
#include "builder/prysm/penta/prysmpenta.h"
#include "builder/pyramide/tri/pyramidetri.h"
#include "builder/pyramide/tetra/pyramidetetra.h"
#include "builder/pyramide/penta/pyramidepenta.h"
#include "builder/sphere/sphere.h"
#include "object/invisibleobject/camera/camera.h"
#include "object/invisibleobject/kdtree/kdtree.h"
#include "object/invisibleobject/light/light.h"
#define emit

#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include "factory/qtdrawerfactory/qtdrawerfactory.h"

class Scene
{
public:
    Scene(std::shared_ptr<QPixmap>);
    ~Scene() = default;
    void draw();
    void rotate_camera(const QVector3D& angle);
    void move_light(const QVector3D& d);
    void move_camera(const QVector3D& d);
    void change_object_and_mirror(std::string obj_name, std::string mir_name);
    void change_light_color(const QVector3D& color);
    void change_object_geometry(const QVector3D& k, const QVector3D& a = QVector3D(0, 0, 0));
    void change_mirror_geometry(const QVector3D& k);
    void change_mirror_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse);
    bool is_name_on_scene(std::string name);
    std::string get_object_name();
    std::string get_mirror_name();
    void update_models();
    void start();

private:
    int _get_builder_id_by_name(std::string);
    QVector3D trace(const Ray& r, const int depth, HitInfo& hitdata);

    std::vector<std::shared_ptr<Object>> _objects;
    std::vector<int> _builder_ids = {2, 9}; // 0: object, 1: mirror
    std::vector<BaseBuilder> _builders;
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Light> _light;
    std::shared_ptr<KDtree> _models;
    std::shared_ptr<QPixmap> _pixmap;
};

#endif // SCENE_H
