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

    // int w = this->frameGeometry().width();
    // int h = this->frameGeometry().height();
    this->setGeometry(0, 0, 1200, 900);
    _scene = std::make_shared<QPixmap>(1000, 900);
    qInfo( "start creating facade" );
    _facade = std::unique_ptr<Facade>(new Facade(_scene));
    qInfo( "facade: done" );
    _add_variants();
    _make_connects();
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

MainWindow& MainWindow::_make_connects()
{
    connect(ui->pushButton_edit_light, &QPushButton::clicked, this, &MainWindow::on_pushButton_edit_light_clicked);
    connect(ui->pushButton_edit_mirror, &QPushButton::clicked, this, &MainWindow::on_pushButton_edit_mirror_clicked);
    connect(ui->pushButton_edit_object, &QPushButton::clicked, this, &MainWindow::on_pushButton_edit_object_clicked);
    return *this;
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
    case 1:
        mirror_name = "mirrorconvex";
    case 2:
        mirror_name = "mirrorconcave";
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
    case 1:
        object_name = "cylinder";
    case 2:
        object_name = "cone";
    case 3:
        switch (ui->comboBox_object_edge->currentIndex())
        {
        case 0:
            object_name = "prysmtri";
        case 1:
            object_name = "prysmtetra";
        case 2:
            object_name = "prysmpenta";
        }
    case 4:
        switch (ui->comboBox_object_edge->currentIndex())
        {
        case 0:
            object_name = "pyramidetri";
        case 1:
            object_name = "pyramidetetra";
        case 2:
            object_name = "pyramidepenta";
        }
    }

    double radius_k = ui->spinBox_object_radius_k->value();
    double height_k = ui->spinBox_object_height_k->value();
    double angle_k = ui->spinBox_object_angle_k->value();

    EditObject *command = new EditObject(object_name, radius_k, angle_k, height_k);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}


void MainWindow::on_pushButton_object_color_clicked()
{
    QString title = "Выбор цвета зекркала";
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

