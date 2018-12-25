#ifndef COMPONENTSDB_H
#define COMPONENTSDB_H

#include <QJsonDocument>
#include <QObject>

#include "componentslist.h"
#include "partsenum.h"
class ComponentsDB : public QObject {
  Q_OBJECT
public:
  static int getPerfomanceIndex(QString perfomanceLevel);

  explicit ComponentsDB(QObject *parent = 0);
  bool loadFromFile(QString filename);
  bool saveToFile(QString filename);
  bool isLoaded();

  int findItemIndex(Parts part, QString model);
  int findComponentIndex(QString model);

  QList<Case> getSortedCaseList(SortType sortType);
  QList<Cooler> getSortedCoolerList(SortType sortType);
  QList<Cpu> getSortedCpuList(SortType sortType);
  QList<DataStorage> getSortedDataStorageList(SortType sortType);
  QList<Gpu> getSortedGpuList(SortType sortType);
  QList<Motherboard> getSortedMotherboardList(SortType sortType);
  QList<Peripheral> getSortedPeripheralList(SortType sortType);
  QList<Psu> getSortedPsuList(SortType sortType);
  QList<Ram> getSortedRamList(SortType sortType);

  ComponentsList *getComponentsList() { return componentsList; }
  QList<Assembly> *getAssembliesList() { return assembliesList; }
  QList<Assembly> generateAssemblies(int price);
  QList<Assembly> generateAssemblies(QString perfomanceLevel);
  int* getPartsListByPower(Parts part, QString perfomanceLevel);
signals:

public slots:

private:
  bool loadedState = false;
  ComponentsList *componentsList;
  QList<Assembly> *assembliesList;
};

#endif // COMPONENTSDB_H
