#ifndef FACADE_H
#define FACADE_H

#include "command/basecommand.h"

class Facade
{
public:
    Facade() = delete;
    Facade(std::shared_ptr<QPixmap> pixmap):
        _manager(std::make_shared<SceneManager>(pixmap))
    {}
    ~Facade() = default;
    std::string execute(BaseCommand *command);
private:
    std::shared_ptr<SceneManager> _manager;
};

#endif // FACADE_H
