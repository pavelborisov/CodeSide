#include "Weapon.hpp"
#include <math.h>

Weapon::Weapon() { }
Weapon::Weapon(WeaponType typ, WeaponParams params, int magazine, bool wasShooting, double spread, std::shared_ptr<double> fireTimer, std::shared_ptr<double> lastAngle, std::shared_ptr<int> lastFireTick) : type(typ), params(params), magazine(magazine), wasShooting(wasShooting), spread(spread), fireTimer(*fireTimer), lastAngle(*lastAngle), lastFireTick(*lastFireTick) { }
Weapon Weapon::readFrom(InputStream& stream) {
    Weapon result;
    switch (stream.readInt()) {
    case 0:
        result.type = WeaponType::PISTOL;
        break;
    case 1:
        result.type = WeaponType::ASSAULT_RIFLE;
        break;
    case 2:
        result.type = WeaponType::ROCKET_LAUNCHER;
        break;
    default:
        throw std::runtime_error("Unexpected discriminant value");
    }
    result.params = WeaponParams::readFrom(stream);
    result.magazine = stream.readInt();
    result.wasShooting = stream.readBool();
    result.spread = stream.readDouble();
    if (stream.readBool()) {
        result.fireTimer = stream.readDouble();
    } else {
        result.fireTimer = 0;
    }
    if (stream.readBool()) {
        result.lastAngle = stream.readDouble();
    } else {
        result.lastAngle = NAN;
    }
    if (stream.readBool()) {
        result.lastFireTick = stream.readInt();
    } else {
        result.lastFireTick = -1;
    }
    return result;
}
void Weapon::writeTo(OutputStream& stream) const {
    stream.write((int)(type));
    params.writeTo(stream);
    stream.write(magazine);
    stream.write(wasShooting);
    stream.write(spread);
    if (fireTimer) {
        stream.write(false);
    } else {
        stream.write(true);
        stream.write((fireTimer));
    }
    if (lastAngle) {
        stream.write(false);
    } else {
        stream.write(true);
        stream.write((lastAngle));
    }
    if (lastFireTick) {
        stream.write(false);
    } else {
        stream.write(true);
        stream.write((lastFireTick));
    }
}
std::string Weapon::toString() const {
    return std::string("Weapon") + "(" +
        "TODO" + 
        params.toString() +
        std::to_string(magazine) +
        (wasShooting ? "true" : "false") + 
        std::to_string(spread) +
        "TODO" + 
        "TODO" + 
        "TODO" + 
        ")";
}
