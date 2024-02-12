#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qInfo( "mainwindow create" );
    ui->setupUi(this);
    ui->drawLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWindowTitle("Bad Mirror");

    this->setGeometry(0, 0, 1400, 900);
    _scene = std::make_shared<QPixmap>(1000, 900);
    qInfo( "start creating facade" );
    _facade = std::unique_ptr<Facade>(new Facade(_scene));
    qInfo( "facade: done" );
    _add_variants();
    ui->drawLabel->setPixmap(*_scene);
    qInfo( "end mainwindow" );
}

bool MainWindow::_execute_with_wait(BaseCommand *command)
{
    QFutureWatcher<std::string> watcher;
    LoadDialog dialog;
    connect(&watcher, SIGNAL(finished()), &dialog, SLOT(close()));
    QFuture runner = QtConcurrent::run(&Facade::execute, *_facade.get(), command);
    watcher.setFuture(runner);
    dialog.exec();
    watcher.waitForFinished();

    if (runner.result() != "")
    {
        QMessageBox messageBox(this);
        messageBox.critical(0, "Ошибка", runner.result().c_str());
        return false;
    }

    return true;
}

void MainWindow::_draw()
{
    DrawScene *draw = new DrawScene();
    _execute_with_wait(draw);
    delete draw;
    ui->drawLabel->setPixmap(*_scene);
}

MainWindow& MainWindow::_add_variants()
{
    ui->comboBox_object_type->addItem("Шар");
    ui->comboBox_object_type->addItem("Цилиндр");
    ui->comboBox_object_type->addItem("Конус");
    ui->comboBox_object_type->addItem("Призма");
    ui->comboBox_object_type->addItem("Пирамида");

    ui->comboBox_object_edge->addItem("3");
    ui->comboBox_object_edge->addItem("4");
    ui->comboBox_object_edge->addItem("5");

    ui->comboBox_mirror_type->addItem("Плоское");
    ui->comboBox_mirror_type->addItem("Выпуклое");
    ui->comboBox_mirror_type->addItem("Вогнутое");

    ui->comboBox_object_type->setCurrentIndex(0);
    ui->comboBox_object_edge->setCurrentIndex(0);
    ui->comboBox_mirror_type->setCurrentIndex(0);

    last_light_color = Qt::white;
    last_mirror_color = Qt::gray;

    return *this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_edit_mirror_clicked()
{
    double ref_x = ui->spinBox_mirror_diffuse->value();
    QVector3D reflective = QVector3D(1, 1, 1) - QVector3D(ref_x, ref_x, ref_x);
    double polish = ui->spinBox_mirror_polish->value();
    QVector3D mirror_color(double(last_mirror_color.red()) / 255,
                           double(last_mirror_color.green()) / 255,
                           double(last_mirror_color.blue()) / 255);
    std::string mirror_name = "";

    switch (ui->comboBox_mirror_type->currentIndex())
    {
    case 0:
        mirror_name = "mirrorplane";
        break;
    case 1:
        mirror_name = "mirrorconvex";
        break;
    case 2:
        mirror_name = "mirrorconcave";
        break;
    }

    double radius_k = ui->spinBox_mirror_radius_k->value();

    EditMirror *command = new EditMirror(mirror_name, radius_k, reflective, polish, mirror_color);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}


void MainWindow::on_pushButton_edit_object_clicked()
{
    std::string object_name = "";

    switch (ui->comboBox_object_type->currentIndex())
    {
    case 0:
        object_name = "sphere";
        break;
    case 1:
        object_name = "cylinder";
        break;
    case 2:
        object_name = "cone";
        break;
    case 3:
        switch (ui->comboBox_object_edge->currentIndex())
        {
        case 0:
            object_name = "prysmtri";
            break;
        case 1:
            object_name = "prysmtetra";
            break;
        case 2:
            object_name = "prysmpenta";
            break;
        }
        break;
    case 4:
        switch (ui->comboBox_object_edge->currentIndex())
        {
        case 0:
            object_name = "pyramidetri";
            break;
        case 1:
            object_name = "pyramidetetra";
            break;
        case 2:
            object_name = "pyramidepenta";
            break;
        }
        break;
    }

    double radius_k = ui->spinBox_object_radius_k->value();
    double height_k = ui->spinBox_object_height_k->value();
    double angle_kx = ui->spinBox_object_angle_kx->value();
    double angle_ky = ui->spinBox_object_angle_ky->value();

    if (radius_k == 0)
        radius_k = 1;

    if (height_k == 0)
        height_k = 1;

    QVector3D scale_k(radius_k, radius_k, height_k);
    QVector3D angle_k(angle_kx, angle_ky, 0);

    EditObject *command = new EditObject(object_name, scale_k, angle_k);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}

void MainWindow::on_pushButton_object_color_clicked()
{
    QString title = "Выбор цвета зекрала";
    QColor color = QColorDialog::getColor(last_mirror_color, this, title, QColorDialog::DontUseNativeDialog);

    if (color.isValid())
    {
        QPalette sample_palette;
        sample_palette.setColor(QPalette::Window, color);
        ui->label_mirror_color->setAutoFillBackground(true);
        ui->label_mirror_color->setPalette(sample_palette);
        last_mirror_color = color;
    }
}

void MainWindow::on_pushButton_edit_light_clicked()
{
    QVector3D light_color(double(last_light_color.red()) / 255,
                          double(last_light_color.green()) / 255,
                          double(last_light_color.blue()) / 255);
    double dx = ui->spinBox_light_dx->value();
    double dy = ui->spinBox_light_dy->value();
    double dz = ui->spinBox_light_dz->value();

    EditLight *command = new EditLight(QVector3D(dx, dy, dz), light_color);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}

void MainWindow::on_pushButton_light_color_clicked()
{
    QString title = "Выбор интенсивности точечного источника света";
    QColor color = QColorDialog::getColor(last_light_color, this, title, QColorDialog::DontUseNativeDialog);

    if (color.isValid())
    {
        QPalette sample_palette;
        sample_palette.setColor(QPalette::Window, color);
        ui->label_light_color->setAutoFillBackground(true);
        ui->label_light_color->setPalette(sample_palette);
        last_light_color = color;
    }
}

void MainWindow::on_pushButton_edit_camera_clicked()
{
    double ax = double(ui->spinBox_camera_angle_x->value()) * M_PI / 180.0f;
    double ay = double(ui->spinBox_camera_angle_y->value()) * M_PI / 180.0f;
    double az = double(ui->spinBox_camera_angle_z->value()) * M_PI / 180.0f;

    QVector3D d(ui->spinBox_camera_dx->value(), ui->spinBox_camera_dy->value(), ui->spinBox_camera_dz->value());
    QVector3D angle(ax, ay, az);

    MoveAndRotateCamera *command = new MoveAndRotateCamera(d, angle);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}

