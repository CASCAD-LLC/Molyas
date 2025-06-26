#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "distrodetector.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    installProcess(new QProcess(this))
{
    ui->setupUi(this);

    DistroDetector::PackageType distro = DistroDetector::detectDistro();
    currentPackageManager = DistroDetector::packageManagerCommand(distro);
    currentPackageTypeFilter = DistroDetector::packageTypeName(distro);

    ui->label->setText(QString("Вас приветствует Molyas Installer - мастер установки %1 пакетов")
                           .arg(DistroDetector::packageTypeName(distro).split(' ').first()));

    // Настройка процесса
    installProcess->setProcessChannelMode(QProcess::MergedChannels);

    connect(installProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = QString::fromUtf8(installProcess->readAllStandardOutput());
        qDebug() << "Output:" << output;

        if (output.contains("Unpacking") || output.contains("Распаковывается") ||
            output.contains("Preparing") || output.contains("Подготовка")) {
            ui->progressBar->setValue(30);
        }
        else if (output.contains("Setting up") || output.contains("Настраивается") ||
                 output.contains("Installing") || output.contains("Установка")) {
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

void MainWindow::on_pushButton_clicked() {
    QString pkgFile = QFileDialog::getOpenFileName(this,
                                                   "Выберите пакет",
                                                   "",
                                                   currentPackageTypeFilter);
    if (pkgFile.isEmpty()) return;

    ui->progressBar->setValue(0);

    QStringList args;
    if (currentPackageManager == "dpkg") {
        args = {"dpkg", "-i", "--force-all", pkgFile};
    }
    else if (currentPackageManager == "rpm") {
        args = {"rpm", "-i", pkgFile};
    }
    else if (currentPackageManager == "pacman") {
        args = {"pacman", "-U", pkgFile};
    }

    installProcess->start("pkexec", args);
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
