#ifndef SCENECOMMAND_H
#define SCENECOMMAND_H

#include <stdlib.h>
#include "command/basecommand.h"

class DrawScene: public BaseCommand
{
public:
    DrawScene() {}
    std::string execute()
    {
        return _scene_manager->draw();
    }
};

class EditLight: public BaseCommand
{
public:
    EditLight(const QVector3D& d, const QVector3D& color):
        _d(d),
        _color(color)
    {}

    std::string execute()
    {
        return _scene_manager->edit_light(_d, _color);
    }

private:
    QVector3D _d;
    QVector3D _color;
};

class EditObject: public BaseCommand
{
public:
    EditObject(std::string name, const QVector3D& scale_k, const QVector3D& angle_k):
        _scale_k(scale_k),
        _angle_k(angle_k),
        _name(name)
    {}

    std::string execute()
    {
        return _scene_manager->edit_object(_name, _scale_k, _angle_k);
    }

private:
    std::string _name;
    QVector3D _angle_k;
    QVector3D _scale_k;
};

class EditMirror: public BaseCommand
{
public:
    EditMirror(std::string name, const double& radius_k, const QVector3D& reflective, const double& polish, const QVector3D& diffuse):
        _radius_k(radius_k),
        _name(name),
        _reflective(reflective),
        _polish(polish),
        _diffuse(diffuse)
    {}

    std::string execute()
    {
        return _scene_manager->edit_mirror(_name, _radius_k, _reflective, _polish, _diffuse);
    }

private:
    QVector3D _reflective;
    double _polish;
    QVector3D _diffuse;
    std::string _name;
    double _radius_k;
};

class MoveAndRotateCamera: public BaseCommand
{
public:
    MoveAndRotateCamera(const QVector3D& d, const QVector3D& angle):
        _d(d),
        _angle(angle)
    {}

    std::string execute()
    {
        return _scene_manager->move_and_rotate_camera(_d, _angle);
    }

private:
    QVector3D _d;
    QVector3D _angle;
};


#endif // SCENECOMMAND_H
