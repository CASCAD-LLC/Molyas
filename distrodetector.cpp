#include "distrodetector.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

DistroDetector::PackageType DistroDetector::detectDistro() {
    // Проверяем /etc/os-release
    QFile osRelease("/etc/os-release");
    if (osRelease.open(QIODevice::ReadOnly)) {
        QTextStream in(&osRelease);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("ID=")) {
                QString id = line.mid(3).toLower().remove('"');
                if (id == "debian" || id == "ubuntu" || id == "linuxmint") return DEB;
                if (id == "fedora" || id == "centos" || id == "rhel") return RPM;
                if (id == "arch" || id == "manjaro" || id == "endeavouros") return ARCH;
            }
        }
    }

    if (QFile::exists("/etc/debian_version")) return DEB;
    if (QFile::exists("/etc/redhat-release")) return RPM;
    if (QFile::exists("/etc/arch-release")) return ARCH;

    qWarning() << "Не удалось определить дистрибутив, используется DEB по умолчанию";
    return DEB;
}

QString DistroDetector::packageManagerCommand(PackageType type) {
    switch(type) {
    case DEB: return "dpkg";
    case RPM: return "rpm";
    case ARCH: return "pacman";
    default: return "dpkg";
    }
}

QString DistroDetector::packageExtension(PackageType type) {
    switch(type) {
    case DEB: return "*.deb";
    case RPM: return "*.rpm";
    case ARCH: return "*.pkg.tar.*";
    default: return "*";
    }
}

QString DistroDetector::packageTypeName(PackageType type) {
    switch(type) {
    case DEB: return "Debian Package (*.deb)";
    case RPM: return "RPM Package (*.rpm)";
    case ARCH: return "Arch Linux Package (*.pkg.tar.*)";
    default: return "All Files (*)";
    }
}
