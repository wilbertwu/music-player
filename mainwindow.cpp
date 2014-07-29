#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QMediaPlaylist>
#include <QMediaContent>
#include <QMediaResource>
#include<QDir>
#include<QFileDialog>
#include <QtWidgets>
#include <QMediaPlayer>
#include <QVideoWidget>
#include<QFile>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->shengyintiaojie->setMaximum(100);
    ui->shengyintiaojie->setMinimum(0);
    ui->shengyintiaojie->setValue(volume);
    player = new QMediaPlayer;
    playerList = new QMediaPlaylist;
    volume = 80;
    player->setVolume(volume);
    /*QFile file(tr("F:\\QT\\music\\music.txt"));
    QTextStream textstream(&file);
    stringlist=textstream.readAll();
    string temp;
    while(getline(textstream, temp, ';')) {
        QString path = QString::fromStdString(temp);
        playerList->addMedia(QUrl::fromLocalFile(path));
        QString fileName=path.split("\\").last();
        int rownum=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rownum);
        ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName.split(".").front()));
        ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(fileName.split(".").last()));
        ui->tableWidget->setItem(rownum, 2, new QTableWidgetItem(path));
    }
    file.close();*/
    //playerList->addMedia(QUrl::fromLocalFile("F:\\04.mp3"));
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->setPlaylist(playerList);
    playOrpause = true;
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete playerList;
}

void MainWindow::on_actionAbout_me_triggered()
{
  QMessageBox::about(this, tr("关于"),tr("coded by wilbert"));
}

void MainWindow::on_actionImport_song_triggered()
{
    this->addsongs();
}

void MainWindow::on_actionPrevious_triggered()
{
    this->previous();
}

void MainWindow::on_actionNext_triggered()
{
    this->next();
}

void MainWindow::on_actionPause_triggered()
{
    this->pauseOrplay();
}

void MainWindow::on_actionDanquxunhuang_triggered()
{
    this->setDanQu();
}

void MainWindow::on_actionShunxubofang_triggered()
{
    this->setShunXu();
}



void MainWindow::previous() {
    int currentindex = playerList->currentIndex();
    if (currentindex == 0) {
        player->pause();
        playOrpause = false;
    } else {
        currentindex--;
        playerList->setCurrentIndex(currentindex);
        playOrpause = true;
        player->play();
         ui->playing->setText(tr("正在播放: %1").arg(ui->tableWidget->item(playerList->currentIndex(), 0)->text()));
    }

}
void MainWindow::next() {
    int currentindex = playerList->currentIndex();
    if (currentindex == (playerList->mediaCount()-1)) {
        playOrpause = false;
        player->pause();
    }  else {
        currentindex++;
        playerList->setCurrentIndex(currentindex);
        playOrpause = true;
        player->play();
        ui->playing->setText(tr("正在播放: %1").arg(ui->tableWidget->item(playerList->currentIndex(), 0)->text()));
    }
}
void MainWindow::addsongs() {
    QString initialName=tr("F:\\库\\music");
    QStringList pathList=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr(".mp3"));
    for(int i=0; i<pathList.size(); ++i) {
        QString path=QDir::toNativeSeparators(pathList.at(i));
        if(!path.isEmpty()) {
            playerList->addMedia(QUrl::fromLocalFile(path));
            QString fileName=path.split("\\").last();
            int rownum=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rownum);
            ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName.split(".").front()));
            ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(fileName.split(".").last()));
            ui->tableWidget->setItem(rownum, 2, new QTableWidgetItem(path));
            /*QFile file(tr("F:\\QT\\music\\music.txt"));
            file.open(QIODevice::Append);
            QTextStream textstream = file.readAll();
            textstream << tr(";") << path;
            file.close();*/
        }
    }
}
void MainWindow::pauseOrplay() {
    if (playOrpause) {
        player->pause();
        playOrpause = false;
        return;
    }  else {
        player->play();
        playOrpause = true;
        return;
    }
}
void MainWindow::setDanQu() {
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void MainWindow::setShunXu() {
    playerList->setPlaybackMode(QMediaPlaylist::Sequential);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionRadom_triggered()
{
    playerList->setPlaybackMode(QMediaPlaylist::Random);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    playerList->setCurrentIndex(row);
    player->play();
    ui->playing->setText(tr("正在播放: %1").arg(ui->tableWidget->item(row, 0)->text()));
}

void MainWindow::on_jindutiaojie_sliderMoved(int position)
{
    volume = position;
    player->setVolume(volume);
}

void MainWindow::on_shengyintiaojie_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

}
