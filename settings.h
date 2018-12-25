#ifndef SETTINGS_H
#define SETTINGS_H

#include "componentsdb.h"
#include "partsenum.h"
#include <QString>

class Settings {

public:
  static Settings *Instance();

  inline bool getIsInitialized() { return isInitialized; }
  inline void setIsInitialized(const bool &isInitialized = true) {
    this->isInitialized = isInitialized;
  }

  inline Parts getLastMainWindowPart() { return lastMainWindowPart; }
  inline void setLastMainWindowPart(const Parts &lastMainWindowPart) {
    this->lastMainWindowPart = lastMainWindowPart;
  }

  inline Parts getLastAdmPart() { return lastAdmPart; }
  inline void setLastAdmPart(const Parts &lastAdmPart) {
    this->lastAdmPart = lastAdmPart;
  }

  inline QString getDataBasePath() { return dataBasePath; }
  inline void setDataBasePath(const QString &dataBasePath) {
    this->dataBasePath = dataBasePath;
  }

  inline QString getConfigFilePath() { return configFilePath; }
  inline void setConfigFilePath(const QString &configFilePath) {
    this->dataBasePath = configFilePath;
  }

  inline QStringList getPowerLevelsList() { return powerLevelsList; }
  inline void setPowerLevelsList(const QStringList &powerLevelsList) {
    this->powerLevelsList = powerLevelsList;
  }

  inline QStringList getSocketsList() { return socketsList; }
  inline void setSocketsList(const QStringList &socketsList) {
    this->socketsList = socketsList;
  }

  inline QStringList getFormFactorsList() { return formFactorsList; }
  inline void setFormFactorsList(const QStringList &formFactorsList) {
    this->formFactorsList = formFactorsList;
  }

  inline QStringList getRamTypesList() { return ramTypesList; }
  inline void setRamTypesList(const QStringList &ramTypesList) {
    this->ramTypesList = ramTypesList;
  }

  inline QStringList getStoreTypesList() { return storeTypesList; }
  inline void setStoreTypesList(const QStringList &storeTypesList) {
    this->storeTypesList = storeTypesList;
  }

  inline QStringList getPeriphSupplyPlugTypesList() {
    return periphSupplyPlugTypesList;
  }
  inline void
  setPeriphSupplyPlugTypesList(const QStringList &periphSupplyPlugTypesList) {
    this->periphSupplyPlugTypesList = periphSupplyPlugTypesList;
  }

  inline QStringList getGpuSupplyPlugTypesList() {
    return gpuSupplyPlugTypesList;
  }
  inline void
  setGpuSupplyPlugTypesList(const QStringList &gpuSupplyPlugTypesList) {
    this->gpuSupplyPlugTypesList = gpuSupplyPlugTypesList;
  }

  inline QStringList getCpuSupplyPlugTypesList() {
    return cpuSupplyPlugTypesList;
  }
  inline void
  setCpuSupplyPlugTypesList(const QStringList &mbSupplyPlugTypesList) {
    this->cpuSupplyPlugTypesList = mbSupplyPlugTypesList;
  }

  inline QStringList getMbSupplyPlugTypesList() {
    return mbSupplyPlugTypesList;
  }
  inline void
  setMbSupplyPlugTypesList(const QStringList &mbSupplyPlugTypesList) {
    this->mbSupplyPlugTypesList = mbSupplyPlugTypesList;
  }

  inline QHash<QString, QString> *getAuthHash() { return authHash; }

  inline ComponentsDB *getComponentsDB() { return dataBase; }

  void loadSettings();
  void saveSettings();

private:
  Settings();
  Settings(Settings const &) {}
  static Settings *pInstance;

  bool initConfig(QString filename);
  bool readConfig(QString filename);
  bool saveConfig(QString filename);
  void resetConfig();

  bool isInitialized;
  Parts lastMainWindowPart, lastAdmPart;
  QString dataBasePath, configFilePath;
  QStringList powerLevelsList, socketsList, formFactorsList, ramTypesList,
      storeTypesList, periphSupplyPlugTypesList, gpuSupplyPlugTypesList,
      cpuSupplyPlugTypesList, mbSupplyPlugTypesList;
  QHash<QString, QString> *authHash;
  ComponentsDB *dataBase;
};

#endif // SETTINGS_H
