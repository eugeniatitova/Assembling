#include "componentslist.h"

#include <QJsonArray>

ComponentsList::ComponentsList(QObject *parent) : QObject(parent) {

  caseList = new QList<Case>();
  componentList = new QList<Component>();
  coolerList = new QList<Cooler>();
  cpuList = new QList<Cpu>();
  dataStorageList = new QList<DataStorage>();
  gpuList = new QList<Gpu>();
  motherboardList = new QList<Motherboard>();
  peripheralList = new QList<Peripheral>();
  psuList = new QList<Psu>();
  ramList = new QList<Ram>();
}

ComponentsList::~ComponentsList() {
  clearLists();

  delete caseList;
  delete componentList;
  delete coolerList;
  delete cpuList;
  delete dataStorageList;
  delete gpuList;
  delete motherboardList;
  delete peripheralList;
  delete psuList;
  delete ramList;
}

void ComponentsList::loadfromJson(const QJsonObject &obj) {
  clearLists();
  loadCases(obj["case"].toArray());
  loadComponents(obj["component"].toArray());
  loadCoolers(obj["cooler"].toArray());
  loadCpus(obj["cpu"].toArray());
  loadDataStorages(obj["dataStorage"].toArray());
  loadGpus(obj["gpu"].toArray());
  loadMotherboards(obj["motherboard"].toArray());
  loadPeripherals(obj["peripheral"].toArray());
  loadPsus(obj["psu"].toArray());
  loadRams(obj["ram"].toArray());
}

QJsonObject ComponentsList::saveToJson() {
  QJsonObject obj;
  obj["case"] = saveCases();
  obj["component"] = saveComponents();
  obj["cooler"] = saveCoolers();
  obj["cpu"] = saveCpus();
  obj["dataStorage"] = saveDataStorages();
  obj["gpu"] = saveGpus();
  obj["motherboard"] = saveMotherboards();
  obj["peripheral"] = savePeripherals();
  obj["psu"] = savePsus();
  obj["ram"] = saveRams();
  return obj;
}

void ComponentsList::clearLists() {
  caseList->clear();
  coolerList->clear();
  cpuList->clear();
  dataStorageList->clear();
  gpuList->clear();
  motherboardList->clear();
  peripheralList->clear();
  psuList->clear();
  ramList->clear();
}

void ComponentsList::loadCases(const QJsonArray &arr) {
  caseList->clear();
  foreach (QJsonValue value, arr) {
    caseList->append(Case::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadComponents(const QJsonArray &arr) {
  componentList->clear();
  foreach (QJsonValue value, arr) {
    componentList->append(Component::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadCoolers(const QJsonArray &arr) {
  coolerList->clear();
  foreach (QJsonValue value, arr) {
    coolerList->append(Cooler::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadCpus(const QJsonArray &arr) {
  cpuList->clear();
  foreach (QJsonValue value, arr) {
    cpuList->append(Cpu::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadDataStorages(const QJsonArray &arr) {
  dataStorageList->clear();
  foreach (QJsonValue value, arr) {
    dataStorageList->append(DataStorage::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadGpus(const QJsonArray &arr) {
  gpuList->clear();
  foreach (QJsonValue value, arr) {
    gpuList->append(Gpu::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadMotherboards(const QJsonArray &arr) {
  motherboardList->clear();
  foreach (QJsonValue value, arr) {
    motherboardList->append(Motherboard::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadPeripherals(const QJsonArray &arr) {
  peripheralList->clear();
  foreach (QJsonValue value, arr) {
    peripheralList->append(Peripheral::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadPsus(const QJsonArray &arr) {
  psuList->clear();
  foreach (QJsonValue value, arr) {
    psuList->append(Psu::fromJsonObject(value.toObject()));
  }
}

void ComponentsList::loadRams(const QJsonArray &arr) {
  ramList->clear();
  foreach (QJsonValue value, arr) {
    ramList->append(Ram::fromJsonObject(value.toObject()));
  }
}

QJsonArray ComponentsList::saveCases() {
  QJsonArray arr;
  foreach (Case item, *caseList) { arr.append(item.getJsonObject()); }
  return arr;
}

QJsonArray ComponentsList::saveComponents() {
  QJsonArray arr;
  foreach (Component item, *componentList) { arr.append(item.getJsonObject()); }
  return arr;
}

QJsonArray ComponentsList::saveCoolers() {
  QJsonArray arr;
  foreach (Cooler item, *coolerList) { arr.append(item.getJsonObject()); }
  return arr;
}

QJsonArray ComponentsList::saveCpus() {
  QJsonArray arr;
  foreach (Cpu item, *cpuList) { arr.append(item.getJsonObject()); }
  return arr;
}

QJsonArray ComponentsList::saveDataStorages() {
  QJsonArray arr;
  foreach (DataStorage item, *dataStorageList) {
    arr.append(item.getJsonObject());
  }
  return arr;
}

QJsonArray ComponentsList::saveGpus() {
  QJsonArray arr;
  foreach (Gpu item, *gpuList) { arr.append(item.getJsonObject()); }
  return arr;
}

QJsonArray ComponentsList::saveMotherboards() {
  QJsonArray arr;
  foreach (Motherboard item, *motherboardList) {
    arr.append(item.getJsonObject());
  }
  return arr;
}

QJsonArray ComponentsList::savePeripherals() {
  QJsonArray arr;
  foreach (Peripheral item, *peripheralList) {
    arr.append(item.getJsonObject());
  }
  return arr;
}

QJsonArray ComponentsList::savePsus() {
  QJsonArray arr;
  foreach (Psu item, *psuList) { arr.append(item.getJsonObject()); }
  return arr;
}

QJsonArray ComponentsList::saveRams() {
  QJsonArray arr;
  foreach (Ram item, *ramList) { arr.append(item.getJsonObject()); }
  return arr;
}
