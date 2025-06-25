#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    installProcess(new QProcess(this))
{
    ui->setupUi(this);

    // Настройка процесса
    installProcess->setProcessChannelMode(QProcess::MergedChannels);

    connect(installProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = QString::fromUtf8(installProcess->readAllStandardOutput());
        qDebug() << "DPKG output:" << output;

        if (output.contains("Unpacking") || output.contains("Распаковывается")) {
            ui->progressBar->setValue(30);
        }
        else if (output.contains("Setting up") || output.contains("Настраивается")) {
            ui->progressBar->setValue(70);
        }
    });

    connect(installProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &MainWindow::on_installFinished);
}

MainWindow::~MainWindow()
{
    if (installProcess && installProcess->state() == QProcess::Running) {
        installProcess->terminate();
        installProcess->waitForFinished();
    }
    delete installProcess;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString debFile = QFileDialog::getOpenFileName(this, "Выберите .deb файл", "",
                                                   "Debian Package (*.deb)");
    if (debFile.isEmpty()) return;

    ui->progressBar->setValue(0);
    installProcess->start("pkexec", {"dpkg", "-i", "--force-all", debFile});
}

void MainWindow::on_installFinished(int exitCode)
{
    ui->progressBar->setValue(100);
    if (exitCode == 0) {
        QMessageBox::information(this, "Успех", "Пакет успешно установлен!");
    } else {
        QMessageBox::critical(this, "Ошибка",
                              "Ошибка установки: " + installProcess->errorString());
    }
}
