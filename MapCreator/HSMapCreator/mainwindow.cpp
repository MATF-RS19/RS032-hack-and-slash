#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include "animator.h"
#include "map.h"
#include "mapitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m = new Map(this);
    ui->graphicsView->setScene(m);

    QFile fileTiles(":/Assets/tiles.hsa");
    fileTiles.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileTiles.atEnd()){
        QString line = fileTiles.readLine();
        assetsTiles.push_back(QPixmap(line.trimmed()));
        namesTiles.push_back(line);
    }

    qDebug() << namesTiles;

    fileTiles.close();

    QTransform transform;
    transform.scale(1.04, 0.52);
    transform.rotate(-45);

    for(int i = 0; i < assetsTiles.size(); i++){
        assetsTiles[i] = assetsTiles[i].scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        assetsTiles[i] = assetsTiles[i].transformed(transform);
    }

    QFile fileAnim(":/Assets/anim.hsa");
    fileAnim.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileAnim.atEnd()){
        QString line = fileAnim.readLine();
        QStringList args = line.split(" ");
        QString name = args[0];
        int dimX = args[1].toInt();
        int dimY = args[2].toInt();
        int frameWidth = args[3].toInt();
        int frameHeight = args[4].toInt();
        int offsetX = args[5].toInt();
        int offsetY = args[6].toInt();
        int animCount = args[7].toInt();
        int distinctCount = args[8].toInt();

        assetsAnims.push_back(Animator(QPixmap(name).scaled(frameWidth * dimX, frameHeight * dimY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), dimX, dimY, offsetX, offsetY));
        for(int i = 0; i < distinctCount; i++){
            line = fileAnim.readLine();
            args = line.split(" ");
            int begin = args[0].toInt();
            int end = args[1].toInt();
            int duration = args[2].toInt();
            bool looping = args[3].toInt();

            for(int j = 0; j < animCount/distinctCount; j++)
                assetsAnims[assetsAnims.size()-1].addAnimation(dimX * j + begin, dimX * j + end, duration, looping);
        }

        namesAnims.push_back(name);

    }

    qDebug() << namesAnims;

    fileAnim.close();

    QFile fileEnv(":/Assets/env.hsa");
    fileEnv.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileEnv.atEnd()){
        QString line = fileEnv.readLine().trimmed();
        QStringList args = line.split(" ");
        QString name = args[0];
        int dimX = args[1].toInt();
        int dimY = args[2].toInt();
        int width = args[3].toInt();
        int begin = args[4].toInt();
        int end = args[5].toInt();
        int duration = args[6].toInt();
        if(args.size() == 7)
            assetsEnv.push_back(Animator(QPixmap(name).scaledToWidth(width * dimX, Qt::SmoothTransformation), dimX, dimY));
        if(args.size() == 9){
            int offsetX = args[7].toInt();
            int offsetY = args[8].toInt();
            assetsEnv.push_back(Animator(QPixmap(name).scaledToWidth(width * dimX, Qt::SmoothTransformation), dimX, dimY, offsetX, offsetY));
        }
        assetsEnv[assetsEnv.size() - 1].addAnimation(begin, end, duration, true);
        namesEnv.push_back(name);


    }

    qDebug() << namesEnv;

    fileEnv.close();

    QFile fileChar(":/Assets/chars.hsa");
    fileChar.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileChar.atEnd()){
        QString line = fileChar.readLine().trimmed();
        QStringList args = line.split(" ");
        int animIndex = args[0].toInt();
        assetsChars.push_back(animIndex);
    }

    for(int i = 0; i < namesTiles.size(); i++)
        ui->comboBox_2->addItem(namesTiles[i]);
    //m->loadMap(":/Levels/test.hsl");
    //m->saveMap("shaggy_doo.hsl");
    //m->loadMap(20, 20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::getPixmap(MapItem::Type t, int i) {
    switch(t) {
    case MapItem::Type::tile:
        return assetsTiles[i];
    case MapItem::Type::env:
        return assetsEnv[i].getCurrentFrame();
    case MapItem::Type::chr:
        return assetsAnims[assetsChars[i]].getCurrentFrame();
    }
}

int MainWindow::getMode() {
    return ui->comboBox->currentIndex();
}

int MainWindow::getAssetIdx() {
    return ui->comboBox_2->currentIndex();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox_2->clear();
    switch(index) {
    case 0:
        for(int i = 0; i < namesTiles.size(); i++)
            ui->comboBox_2->addItem(namesTiles[i]);
        break;
    case 1:
        for(int i = 0; i < namesEnv.size(); i++)
            ui->comboBox_2->addItem(namesEnv[i]);
        break;
    case 2:
        for(int i = 0; i < assetsChars.size(); i++)
            ui->comboBox_2->addItem(namesAnims[assetsChars[i]]);
        break;
    case 4:
        // player, etc
        break;
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    qDebug() << index;
    if(index < 0)
        return;

    switch(ui->comboBox->currentIndex()) {
    case 0:
        ui->label->setPixmap(assetsTiles[index]);
        break;
    case 1:
        ui->label->setPixmap(assetsEnv[index].getCurrentFrame());
        break;
    case 2:
        ui->label->setPixmap(assetsAnims[assetsChars[index]].getCurrentFrame());
        break;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString line = ui->lineEdit_2->text();
    QStringList dimstr = line.trimmed().split("x");
    int w = dimstr.at(0).toInt();
    int h = dimstr.at(1).toInt();
    m->loadMap(w, h);
}


void MainWindow::on_pushButton_2_clicked()
{
    m->saveMap(ui->lineEdit->text());
}
