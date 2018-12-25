#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "components/case.h"
#include "components/component.h"
#include "components/cooler.h"
#include "components/cpu.h"
#include "components/datastorage.h"
#include "components/gpu.h"
#include "components/motherboard.h"
#include "components/peripheral.h"
#include "components/psu.h"
#include "components/ram.h"

#include <QList>
struct Assembly
{
  static Assembly fromJsonObject(const QJsonObject&);
  static Assembly getNewAssembly();

  QJsonObject getJsonObject();
  bool isEmpty();

  bool checkCpuCompatibility();
  bool checkGpuCompatibility();
  bool checkRamCompatibility();
  bool checkDataStorageCompatibility();
  bool checkPsuCompatibility();
  bool checkCaseCompatibility();
  bool checkCoolerCompatibility();
  QString checkCompatibility();
  QString getAssemblyReport();
  void recountPrice();

  QString descriprion;
  QString perfomanceLevel;
  int price;
  Case body;
  Cooler cooler;
  Cpu cpu;
  Motherboard motherboard;
  Psu psu;
  QList<Component> components;
  QList<DataStorage> dataStorages;
  QList<Gpu> gpus;
  QList<Peripheral> peripherals;
  QList<Ram> rams;
};

#endif // ASSEMBLY_H
