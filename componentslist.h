#ifndef COMPONENTSLIST_H
#define COMPONENTSLIST_H

#include "assembly.h"

#include <QList>
#include <QObject>

class ComponentsList : public QObject {
  Q_OBJECT
public:
  explicit ComponentsList(QObject *parent = 0);
  ~ComponentsList();

  void loadfromJson(const QJsonObject &obj);
  QJsonObject saveToJson();

  QList<Case> *getCases() { return caseList; }
  QList<Component> *getComponents() { return componentList; }
  QList<Cooler> *getCoolers() { return coolerList; }
  QList<Cpu> *getCpus() { return cpuList; }
  QList<DataStorage> *getDataStorages() { return dataStorageList; }
  QList<Gpu> *getGpus() { return gpuList; }
  QList<Motherboard> *getMotherboards() { return motherboardList; }
  QList<Peripheral> *getPeripherals() { return peripheralList; }
  QList<Psu> *getPsus() { return psuList; }
  QList<Ram> *getRams() { return ramList; }
signals:

public slots:

private:
  void clearLists();
  void loadCases(const QJsonArray &);
  void loadComponents(const QJsonArray &);
  void loadCoolers(const QJsonArray &);
  void loadCpus(const QJsonArray &);
  void loadDataStorages(const QJsonArray &);
  void loadGpus(const QJsonArray &);
  void loadMotherboards(const QJsonArray &);
  void loadPeripherals(const QJsonArray &);
  void loadPsus(const QJsonArray &);
  void loadRams(const QJsonArray &);

  QJsonArray saveCases();
  QJsonArray saveComponents();
  QJsonArray saveCoolers();
  QJsonArray saveCpus();
  QJsonArray saveDataStorages();
  QJsonArray saveGpus();
  QJsonArray saveMotherboards();
  QJsonArray savePeripherals();
  QJsonArray savePsus();
  QJsonArray saveRams();

  QList<Case> *caseList;
  QList<Component> *componentList;
  QList<Cooler> *coolerList;
  QList<Cpu> *cpuList;
  QList<DataStorage> *dataStorageList;
  QList<Gpu> *gpuList;
  QList<Motherboard> *motherboardList;
  QList<Peripheral> *peripheralList;
  QList<Psu> *psuList;
  QList<Ram> *ramList;
};

#endif // COMPONENTSLIST_H
