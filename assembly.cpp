#include "assembly.h"

#include <QJsonArray>
QJsonObject Assembly::getJsonObject() {
  QJsonObject obj;
  obj["descriprion"] = descriprion;
  obj["perfomanceLevel"] = perfomanceLevel;
  obj["price"] = price;
  obj["body"] = body.getJsonObject();
  obj["cooler"] = cooler.getJsonObject();
  obj["cpu"] = cpu.getJsonObject();
  obj["motherboard"] = motherboard.getJsonObject();
  obj["psu"] = psu.getJsonObject();

  QJsonArray componentsArr;
  foreach (Component item, components) {
    componentsArr.append(item.getJsonObject());
  }
  obj["components"] = componentsArr;

  QJsonArray dataStoragesArr;
  foreach (DataStorage item, dataStorages) {
    dataStoragesArr.append(item.getJsonObject());
  }
  obj["dataStorages"] = dataStoragesArr;

  QJsonArray gpusArr;
  foreach (Gpu item, gpus) { gpusArr.append(item.getJsonObject()); }
  obj["gpus"] = gpusArr;

  QJsonArray peripheralsArr;
  foreach (Peripheral item, peripherals) {
    peripheralsArr.append(item.getJsonObject());
  }
  obj["peripherals"] = peripheralsArr;

  QJsonArray ramsArr;
  foreach (Ram item, rams) { ramsArr.append(item.getJsonObject()); }
  obj["rams"] = ramsArr;

  return obj;
}

bool Assembly::isEmpty() {
  return price == 0 && descriprion.isEmpty() && perfomanceLevel.isEmpty();
}

Assembly Assembly::fromJsonObject(const QJsonObject &jsonObj) {
  Assembly object;
  object.descriprion = jsonObj["descriprion"].toString();
  object.perfomanceLevel = jsonObj["perfomanceLevel"].toString();
  object.price = jsonObj["price"].toInt();
  object.body = Case::fromJsonObject(jsonObj["body"].toObject());
  object.cooler = Cooler::fromJsonObject(jsonObj["cooler"].toObject());
  object.cpu = Cpu::fromJsonObject(jsonObj["cpu"].toObject());
  object.motherboard =
      Motherboard::fromJsonObject(jsonObj["motherboard"].toObject());
  object.psu = Psu::fromJsonObject(jsonObj["psu"].toObject());

  QJsonArray componentsArr = jsonObj["components"].toArray();
  foreach (QJsonValue value, componentsArr) {
    object.components.append(Component::fromJsonObject(value.toObject()));
  }

  QJsonArray dataStoragesArr = jsonObj["dataStorages"].toArray();
  foreach (QJsonValue value, dataStoragesArr) {
    object.dataStorages.append(DataStorage::fromJsonObject(value.toObject()));
  }

  QJsonArray gpusArr = jsonObj["gpus"].toArray();
  foreach (QJsonValue value, gpusArr) {
    object.gpus.append(Gpu::fromJsonObject(value.toObject()));
  }

  QJsonArray peripheralsArr = jsonObj["peripherals"].toArray();
  foreach (QJsonValue value, peripheralsArr) {
    object.peripherals.append(Peripheral::fromJsonObject(value.toObject()));
  }

  QJsonArray ramsArr = jsonObj["rams"].toArray();
  foreach (QJsonValue value, ramsArr) {
    object.rams.append(Ram::fromJsonObject(value.toObject()));
  }

  return object;
}

Assembly Assembly::getNewAssembly() {
  Assembly result;
  result.descriprion = "";
  result.perfomanceLevel = "";
  result.price = 0;
  result.body = Case::getNewCase();
  result.cooler = Cooler::getNewCooler();
  result.cpu = Cpu::getNewCpu();
  result.motherboard = Motherboard::getNewMotherboard();
  result.psu = Psu::getNewPsu();
  return result;
}

bool Assembly::checkCpuCompatibility() {
  if (motherboard.isEmpty() || cpu.isEmpty())
    return true;
  else
    return motherboard.socket == cpu.socket;
}

bool Assembly::checkGpuCompatibility() {
  if (motherboard.isEmpty() || gpus.isEmpty())
    return true;
  else {
    return gpus.length() <= motherboard.numOfPcieX16Slots;
  }
}

bool Assembly::checkRamCompatibility() {
  if (motherboard.isEmpty() || rams.isEmpty())
    return true;
  else {
    int numOfModules = 0;
    foreach (Ram ram, rams) {
      if (ram.ramType != motherboard.ramType)
        return false;
      numOfModules += ram.numOfModules;
    }
    return motherboard.numOfRamSlots >= numOfModules;
  }
}

bool Assembly::checkDataStorageCompatibility() {
  if (motherboard.isEmpty() || dataStorages.isEmpty())
    return true;
  else {
    if (dataStorages.length() >
        motherboard.numOfSata2Slots + motherboard.numOfSata3Slots)
      return false;
    else
      return true;
  }
}

bool Assembly::checkPsuCompatibility() {
  int wattage = 0;
  if (motherboard.isEmpty() || psu.isEmpty())
    return true;
  if (!(motherboard.cpuSupplyPlug == psu.cpuPlugType &&
        motherboard.numOfCpuSupplyPlug <= psu.numOfCpuPlug &&
        motherboard.mbSupplyPlug == psu.mbPlugType))
    return false;
  wattage += 50;

  if (!cpu.isEmpty())
    wattage += cpu.tdp;

  int sixPinPlugs = 0;
  int eightPinPlugs = 0;

  foreach (Gpu gpu, gpus) {
    wattage += gpu.tdp;
    QString plugs = gpu.supplyPlugType;
    QRegExp regExp6("6-pin");
    QRegExp regExp8("8-pin");
    int lastPos = 0;
    while ((lastPos = regExp6.indexIn(plugs, lastPos)) != -1) {
      lastPos += regExp6.matchedLength();
      sixPinPlugs++;
    }
    lastPos = 0;
    while ((lastPos = regExp8.indexIn(plugs, lastPos)) != -1) {
      lastPos += regExp8.matchedLength();
      eightPinPlugs++;
    }
  }
  if ((sixPinPlugs - psu.numOf6PinPciePlug) +
          (eightPinPlugs - psu.numOf8PinPciePlug) >
      psu.numOf6p2PinPciePlug)
    return false;

  int molexPlugs = 0;
  int sataPlugs = 0;

  foreach (DataStorage item, dataStorages) {
    if (item.supplyPlugType.contains("Molex"))
      molexPlugs++;
    if (item.supplyPlugType.contains("SATA"))
      sataPlugs++;
    wattage += item.powerConsumption;
  }

  foreach (Peripheral item, peripherals) {
    if (item.supplyPlugType.contains("Molex"))
      molexPlugs++;
    if (item.supplyPlugType.contains("SATA"))
      sataPlugs++;
    wattage += item.powerConsumption;
  }

  foreach (Ram item, rams) { wattage += 5; }

  return wattage * 1.1 < psu.power && molexPlugs <= psu.numOfMolexPlug &&
         sataPlugs <= psu.numOfSataPlug;
}

bool Assembly::checkCaseCompatibility() {
  if (motherboard.isEmpty() || body.isEmpty())
    return true;
  else {
    return body.formFactors.contains(motherboard.formFactor);
  }
}

bool Assembly::checkCoolerCompatibility() {
  if (motherboard.isEmpty() || cpu.isEmpty() || cooler.isEmpty())
    return true;
  else {
    return cooler.sockets.contains(motherboard.socket) &&
           cooler.sockets.contains(cpu.socket) && cooler.maxTdp >= cpu.tdp;
  }
}

QString Assembly::checkCompatibility() {
  if (!checkCpuCompatibility())
    return "CPU";
  if (!checkRamCompatibility())
    return "RAM";
  if (!checkGpuCompatibility())
    return "GPU";
  if (!checkDataStorageCompatibility())
    return "Data storages";
  if (!checkPsuCompatibility())
    return "PSU";
  if (!checkCaseCompatibility())
    return "Case";
  if (!checkCoolerCompatibility())
    return "Cooler";
  return "OK";
}

QString Assembly::getAssemblyReport() {
  if (isEmpty())
    return "Empty assembly";
  QString report;
  report = "Description: " + descriprion + "\n";
  report += "Perfomance level: " + perfomanceLevel + "\n";
  report += "Total price: " + QString::number(price) + "\n";
  report += "CPU: " + cpu.baseInfo.manufacturer + " " + cpu.baseInfo.model +
            " Price: " + QString::number(cpu.baseInfo.price) + "\n";
  report += "Motherboard: " + motherboard.baseInfo.manufacturer + " " +
            motherboard.baseInfo.model +
            " Price: " + QString::number(motherboard.baseInfo.price) + "\n";

  report += "RAM: ";
  QString spacer = "";
  foreach (Ram ram, rams) {
    report += spacer + ram.baseInfo.manufacturer + " " + ram.baseInfo.model +
              " x" + QString::number(ram.numOfModules) +
              " Price: " + QString::number(ram.baseInfo.price) + "\n";
    spacer = "     ";
  }

  report += "GPU: ";
  spacer = "";
  foreach (Gpu gpu, gpus) {
    report += spacer + gpu.baseInfo.manufacturer + " " + gpu.baseInfo.model +
              " Price: " + QString::number(gpu.baseInfo.price) + "\n";
    spacer = "     ";
  }

  report += "Data storage: ";
  spacer = "";
  foreach (DataStorage ds, dataStorages) {
    report += spacer + ds.baseInfo.manufacturer + " " + ds.baseInfo.model +
              " Price: " + QString::number(ds.baseInfo.price) + "\n";
    spacer = "              ";
  }

  report += "PSU: " + psu.baseInfo.manufacturer + " " + psu.baseInfo.model +
            " Price: " + QString::number(psu.baseInfo.price) + "\n";
  report += "Cooler: " + cooler.baseInfo.manufacturer + " " +
            cooler.baseInfo.model +
            " Price: " + QString::number(cooler.baseInfo.price) + "\n";
  report += "Case: " + body.baseInfo.manufacturer + " " + body.baseInfo.model +
            " Price: " + QString::number(body.baseInfo.price) + "\n";
  return report;
}

void Assembly::recountPrice() {
    price = 0;
    if(!cpu.isEmpty())
        price += cpu.baseInfo.price;
    if(!motherboard.isEmpty())
        price += motherboard.baseInfo.price;
    if(!rams.isEmpty())
        price += rams.first().baseInfo.price * rams.length();
    if(!gpus.isEmpty())
        price += gpus.first().baseInfo.price * gpus.length();
    if(!psu.isEmpty())
        price += psu.baseInfo.price;
    if(!dataStorages.isEmpty())
        price += dataStorages.first().baseInfo.price * dataStorages.length();
    if(!peripherals.isEmpty())
        price += peripherals.first().baseInfo.price * peripherals.length();
    if(!body.isEmpty())
        price += body.baseInfo.price;
    if(!cooler.isEmpty())
        price += cooler.baseInfo.price;
}
