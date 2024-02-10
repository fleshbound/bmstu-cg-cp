#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMovie>

#ifndef LOAD_PATH
#define LOAD_PATH "./data/gif/load.gif"
#endif

class LoadDialog: public QDialog
{
public:
    explicit LoadDialog(QObject *parent = nullptr);
};

#endif // LOADDIALOG_H
