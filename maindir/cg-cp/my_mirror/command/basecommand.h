#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <memory>
#include "scenemanager/scenemanager.h"

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual std::string execute() = 0;

    void set_manager(const std::shared_ptr<SceneManager>& manager)
    {
        _scene_manager = manager;
    }

protected:
    std::shared_ptr<SceneManager> _scene_manager = nullptr;
};

#endif // BASECOMMAND_H
