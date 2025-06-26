#ifndef DISTRO_DETECTOR_H
#define DISTRO_DETECTOR_H

#include <QString>

class DistroDetector {
public:
    enum PackageType {
        DEB,
        RPM,
        ARCH,
        UNKNOWN
    };

    static PackageType detectDistro();
    static QString packageManagerCommand(PackageType type);
    static QString packageExtension(PackageType type);
    static QString packageTypeName(PackageType type);
};

#endif
