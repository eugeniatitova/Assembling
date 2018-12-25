#include "settings.h"
#include <QDebug>
#include <QJsonArray>
#include <QtCore/QDir>
#include <QtCore/QSettings>
Settings *Settings::pInstance = nullptr;

Settings *Settings::Instance() {
  if (!pInstance)
    pInstance = new Settings;

  return pInstance;
}

Settings::Settings() {
  dataBase = new ComponentsDB();
  authHash = new QHash<QString, QString>();
  isInitialized = false;
  loadSettings();
}

void Settings::loadSettings() {
  QSettings settings;
  lastMainWindowPart = static_cast<Parts>(
      settings.value("/Settings/LastMainWindowPart", 0).toInt());
  lastAdmPart =
      static_cast<Parts>(settings.value("/Settings/LastAdmPart", 0).toInt());
  dataBasePath = settings.value("/Settings/DataBasePath", QDir::currentPath().append("/partsDataBase.json")).toString();
  configFilePath = settings.value("/Settings/ConfigFilePath", QDir::currentPath().append("/config.json")).toString();
  if (!readConfig(configFilePath)) {
    if (initConfig(configFilePath)) {
      if (!readConfig(configFilePath)) {
        isInitialized = false;
        return;
      }
    } else {
      isInitialized = false;
      return;
    }
  }
  dataBase->loadFromFile(dataBasePath);
  isInitialized = true;
}

void Settings::saveSettings() {
  QSettings settings;
  settings.setValue("/Settings/LastMainWindowPart", lastMainWindowPart);
  settings.setValue("/Settings/LastAdmPart", lastAdmPart);
  settings.setValue("/Settings/DataBasePath", dataBasePath);
  settings.setValue("/Settings/ConfigFilePath", configFilePath);
  dataBase->saveToFile(dataBasePath);
  saveConfig(configFilePath);
}

bool Settings::initConfig(QString filename) {
  QFile initFile(filename);
  if (!initFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't init config file.");
    return false;
  }
  QJsonObject authHashDefault;
  QJsonArray powerLevels, sockets, formFactors, ramTypes, storeTypes,
      periphSupply, gpuSupply, cpuSupply, mbSupply;
  powerLevels << "Ultra-Low"
              << "Low"
              << "Mid"
              << "High"
              << "High-end";
  sockets << "AM3"
          << "AM4"
          << "LGA1151";
  formFactors << "mATX"
              << "ATX";
  ramTypes << "DDR2"
           << "DDR3"
           << "DDR4";
  storeTypes << "HDD"
             << "SHDD"
             << "SDD";
  periphSupply << "Molex"
               << "SATA";
  gpuSupply << "6-pin"
            << "8-pin";
  cpuSupply << "4-pin";
  mbSupply << "24-pin";
  authHashDefault["admin"] = "admin";
  QJsonObject obj;
  obj["powerLevels"] = powerLevels;
  obj["sockets"] = sockets;
  obj["formFactors"] = formFactors;
  obj["ramTypes"] = ramTypes;
  obj["storeTypes"] = storeTypes;
  obj["periphSupply"] = periphSupply;
  obj["gpuSupply"] = gpuSupply;
  obj["cpuSupply"] = cpuSupply;
  obj["mbSupply"] = mbSupply;
  obj["authHash"] = authHashDefault;
  QJsonDocument saveDoc(obj);
  initFile.write(saveDoc.toJson());
  initFile.close();
  return true;
}

bool Settings::readConfig(QString filename) {
  QFile loadFile(filename);
  if (!loadFile.open(QIODevice::ReadOnly)) {
    qDebug() << filename;
    qWarning("Couldn't open config file.");
    return false;
  }
  QByteArray configData = loadFile.readAll();
  QJsonDocument configDoc = QJsonDocument::fromJson(configData);
  QJsonObject obj = configDoc.object();
  resetConfig();
  foreach (QJsonValue value, obj["powerLevels"].toArray()) {
    powerLevelsList << value.toString();
  }
  foreach (QJsonValue value, obj["sockets"].toArray()) {
    socketsList << value.toString();
  }
  foreach (QJsonValue value, obj["formFactors"].toArray()) {
    formFactorsList << value.toString();
  }
  foreach (QJsonValue value, obj["ramTypes"].toArray()) {
    ramTypesList << value.toString();
  }
  foreach (QJsonValue value, obj["storeTypes"].toArray()) {
    storeTypesList << value.toString();
  }
  foreach (QJsonValue value, obj["periphSupply"].toArray()) {
    periphSupplyPlugTypesList << value.toString();
  }
  foreach (QJsonValue value, obj["gpuSupply"].toArray()) {
    gpuSupplyPlugTypesList << value.toString();
  }
  foreach (QJsonValue value, obj["cpuSupply"].toArray()) {
    cpuSupplyPlugTypesList << value.toString();
  }
  foreach (QJsonValue value, obj["mbSupply"].toArray()) {
    mbSupplyPlugTypesList << value.toString();
  }
  foreach (QString key, obj["authHash"].toObject().keys()) {
    authHash->insert(key, obj["authHash"].toObject()[key].toString());
  }
  return true;
}

bool Settings::saveConfig(QString filename) {
  QFile saveFile(filename);
  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't save config file.");
    return false;
  }
  QJsonObject obj, authHashObj;
  obj["powerLevels"] = QJsonArray::fromStringList(powerLevelsList);
  obj["sockets"] = QJsonArray::fromStringList(socketsList);
  obj["formFactors"] = QJsonArray::fromStringList(formFactorsList);
  obj["ramTypes"] = QJsonArray::fromStringList(ramTypesList);
  obj["storeTypes"] = QJsonArray::fromStringList(storeTypesList);
  obj["periphSupply"] = QJsonArray::fromStringList(periphSupplyPlugTypesList);
  obj["gpuSupply"] = QJsonArray::fromStringList(gpuSupplyPlugTypesList);
  obj["cpuSupply"] = QJsonArray::fromStringList(cpuSupplyPlugTypesList);
  obj["mbSupply"] = QJsonArray::fromStringList(mbSupplyPlugTypesList);
  foreach(QString key, authHash->keys()){
      authHashObj[key] = authHash->value(key);
    }
  obj["authHash"] = authHashObj;
  QJsonDocument saveDoc(obj);
  saveFile.write(saveDoc.toJson());
  saveFile.close();
  return true;
}

void Settings::resetConfig() {
  authHash->clear();
  powerLevelsList.clear();
  socketsList.clear();
  formFactorsList.clear();
  ramTypesList.clear();
  storeTypesList.clear();
  periphSupplyPlugTypesList.clear();
  gpuSupplyPlugTypesList.clear();
  cpuSupplyPlugTypesList.clear();
  mbSupplyPlugTypesList.clear();
}
