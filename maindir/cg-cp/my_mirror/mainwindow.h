#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QColor>
#include <QColorDialog>
#include <QFuture>
#include <QFutureWatcher>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QPalette>
#include <QProgressDialog>
#include <QRgb>
#include <QScreen>
#include <QString>
#include <QtConcurrent/QtConcurrent>
#include <QWidget>
#include "command/scenecommand.h"
#include "facade/facade.h"
#include "loaddialog/loaddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_edit_light_clicked();
    void on_pushButton_edit_mirror_clicked();
    void on_pushButton_edit_object_clicked();
    void on_pushButton_light_color_clicked();
    void on_pushButton_object_color_clicked();

    void on_pushButton_edit_camera_clicked();

private:
    MainWindow& _load_models() { return *this; }
    MainWindow& _update_scene() { return *this; }
    MainWindow& _make_connects();
    MainWindow& _add_variants();
    bool _execute_with_wait(BaseCommand *command);
    void _draw();
    Ui::MainWindow *ui;
    std::shared_ptr<QPixmap> _scene;
    std::unique_ptr<Facade> _facade;
    QColor last_mirror_color;
    QColor last_light_color;
};
#endif // MAINWINDOW_H
