#include "componentsdb.h"
#include "settings.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QtAlgorithms>
#include <QtCore/QFile>
#include <QDebug>
ComponentsDB::ComponentsDB(QObject *parent) : QObject(parent) {
	componentsList = new ComponentsList();
	assembliesList = new QList<Assembly>();
}

bool ComponentsDB::loadFromFile(QString filename) {
	QFile loadFile(filename);
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open base file.");
		return false;
	}
	QByteArray saveData = loadFile.readAll();
	QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
	QJsonObject obj = loadDoc.object();
	assembliesList->clear();
	foreach(QJsonValue value, obj["assemblies"].toArray()) {
		assembliesList->append(Assembly::fromJsonObject(value.toObject()));
	}
	componentsList->loadfromJson(obj["components"].toObject());
	loadFile.close();
	return true;
}

bool ComponentsDB::saveToFile(QString filename) {
	QFile saveFile(filename);
	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("Couldn't save base file.");
		return false;
	}
	QJsonArray arr;
	foreach(Assembly item, *assembliesList) { arr.append(item.getJsonObject()); }
	QJsonObject obj;
	obj["assemblies"] = arr;
	obj["components"] = componentsList->saveToJson();
	QJsonDocument saveDoc(obj);
	saveFile.write(saveDoc.toJson());
	saveFile.close();
	return true;
}

int ComponentsDB::getPerfomanceIndex(QString perfomanceLevel) {
	return Settings::Instance()->getPowerLevelsList().indexOf(perfomanceLevel);
}

int ComponentsDB::findItemIndex(Parts part, QString model) {
	switch (part) {
	case CPU: {
		QList<Cpu> *list = componentsList->getCpus();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case MOTHERBOARD: {
		QList<Motherboard> *list = componentsList->getMotherboards();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case RAM: {
		QList<Ram> *list = componentsList->getRams();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case GPU: {
		QList<Gpu> *list = componentsList->getGpus();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case PSU: {
		QList<Psu> *list = componentsList->getPsus();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case DATASTORAGE: {
		QList<DataStorage> *list = componentsList->getDataStorages();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case PERIPHERAL: {
		QList<Peripheral> *list = componentsList->getPeripherals();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case CASE: {
		QList<Case> *list = componentsList->getCases();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case COOLER: {
		QList<Cooler> *list = componentsList->getCoolers();
		for (int i = 0; i < list->length(); i++) {
			if (list->at(i).baseInfo.model == model)
				return i;
		}
		return -1;
	}
	case PARTS_TYPE_COUNT: {
		return -1;
	}
	}
	return -1;
}

int ComponentsDB::findComponentIndex(QString model) {
	QList<Component> *list = componentsList->getComponents();
	for (int i = 0; i < list->length(); i++) {
		if (list->at(i).model == model)
			return i;
	}
	return -1;
}

QList<Case> ComponentsDB::getSortedCaseList(SortType sortType) {
	QList<Case> result = *(componentsList->getCases());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(),
			[](Case a, Case b) { return a.baseInfo.price < b.baseInfo.price; });
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Case a, Case b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Case a, Case b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Cooler> ComponentsDB::getSortedCoolerList(SortType sortType) {
	QList<Cooler> result = *(componentsList->getCoolers());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(), [](Cooler a, Cooler b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Cooler a, Cooler b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Cooler a, Cooler b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Cpu> ComponentsDB::getSortedCpuList(SortType sortType) {
	QList<Cpu> result = *(componentsList->getCpus());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(),
			[](Cpu a, Cpu b) { return a.baseInfo.price < b.baseInfo.price; });
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Cpu a, Cpu b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Cpu a, Cpu b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<DataStorage> ComponentsDB::getSortedDataStorageList(SortType sortType) {
	QList<DataStorage> result = *(componentsList->getDataStorages());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(), [](DataStorage a, DataStorage b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](DataStorage a, DataStorage b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](DataStorage a, DataStorage b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Gpu> ComponentsDB::getSortedGpuList(SortType sortType) {
	QList<Gpu> result = *(componentsList->getGpus());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(),
			[](Gpu a, Gpu b) { return a.baseInfo.price < b.baseInfo.price; });
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Gpu a, Gpu b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Gpu a, Gpu b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Motherboard> ComponentsDB::getSortedMotherboardList(SortType sortType) {
	QList<Motherboard> result = *(componentsList->getMotherboards());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(), [](Motherboard a, Motherboard b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Motherboard a, Motherboard b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Motherboard a, Motherboard b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Peripheral> ComponentsDB::getSortedPeripheralList(SortType sortType) {
	QList<Peripheral> result = *(componentsList->getPeripherals());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(), [](Peripheral a, Peripheral b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Peripheral a, Peripheral b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Peripheral a, Peripheral b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Psu> ComponentsDB::getSortedPsuList(SortType sortType) {
	QList<Psu> result = *(componentsList->getPsus());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(),
			[](Psu a, Psu b) { return a.baseInfo.price < b.baseInfo.price; });
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Psu a, Psu b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Psu a, Psu b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

QList<Ram> ComponentsDB::getSortedRamList(SortType sortType) {
	QList<Ram> result = *(componentsList->getRams());
	switch (sortType) {
	case PRICE: {
		qSort(result.begin(), result.end(),
			[](Ram a, Ram b) { return a.baseInfo.price < b.baseInfo.price; });
		break;
	}
	case POWER: {
		qSort(result.begin(), result.end(), [](Ram a, Ram b) {
			return getPerfomanceIndex(a.baseInfo.perfomanceLevel) <
				getPerfomanceIndex(b.baseInfo.perfomanceLevel);
		});
		break;
	}
	case MANUFACTURER: {
		qSort(result.begin(), result.end(), [](Ram a, Ram b) {
			return a.baseInfo.manufacturer < b.baseInfo.manufacturer;
		});
		break;
	}
	}
	return result;
}

int* ComponentsDB::getPartsListByPower(Parts part, QString perfomanceLevel) {
	switch (part) {
	case CPU: {
		QList<Cpu>* lst = new QList<Cpu>();
		foreach(Cpu item, (*componentsList->getCpus())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Cpu a, Cpu b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case MOTHERBOARD: {
		QList<Motherboard>* lst = new QList<Motherboard>();
		foreach(Motherboard item, (*componentsList->getMotherboards())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Motherboard a, Motherboard b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case RAM: {
		QList<Ram>* lst = new QList<Ram>();
		foreach(Ram item, (*componentsList->getRams())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Ram a, Ram b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case GPU: {
		QList<Gpu>* lst = new QList<Gpu>();
		foreach(Gpu item, (*componentsList->getGpus())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Gpu a, Gpu b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case PSU: {
		QList<Psu>* lst = new QList<Psu>();
		foreach(Psu item, (*componentsList->getPsus())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Psu a, Psu b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case DATASTORAGE: {
		QList<DataStorage>* lst = new QList<DataStorage>();
		foreach(DataStorage item, (*componentsList->getDataStorages())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](DataStorage a, DataStorage b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case PERIPHERAL: {
		QList<Peripheral>* lst = new QList<Peripheral>();
		foreach(Peripheral item, (*componentsList->getPeripherals())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Peripheral a, Peripheral b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case CASE: {
		QList<Case>* lst = new QList<Case>();
		foreach(Case item, (*componentsList->getCases())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Case a, Case b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case COOLER: {
		QList<Cooler>* lst = new QList<Cooler>();
		foreach(Cooler item, (*componentsList->getCoolers())) {
			if (item.baseInfo.perfomanceLevel == perfomanceLevel)
				lst->append(item);
		}
		qSort(lst->begin(), lst->end(), [](Cooler a, Cooler b) {
			return a.baseInfo.price < b.baseInfo.price;
		});
		return (int*)lst;
	}
	case PARTS_TYPE_COUNT: {
		return (int*)(new QList<int>());
	}
	}
}

QList<Assembly> ComponentsDB::generateAssemblies(int price) {
  //QStringList perfomanceLevels = Settings::Instance()->getPowerLevelsList();
  //for(int i = perfomanceLevels.count())
}

QList<Assembly> ComponentsDB::generateAssemblies(QString perfomanceLevel) {
	QList<Assembly> list;
	QList<Motherboard> motherboards;
	QStringList sockets;

	foreach(Motherboard mb, (*(QList<Motherboard>*)(getPartsListByPower(Parts::MOTHERBOARD, perfomanceLevel)))) {
		if (!sockets.contains(mb.socket))
			motherboards.append(mb);
	}

	foreach(Motherboard mb, motherboards) {
		Assembly assmbl = Assembly::getNewAssembly();
		assmbl.motherboard = mb;
		QList<Cpu>* cpuList = (QList<Cpu>*)(getPartsListByPower(Parts::CPU, perfomanceLevel));
		foreach(Cpu cpu, (*cpuList))
		{
			assmbl.cpu = cpu;
			if (assmbl.checkCpuCompatibility())
				break;
		}
		if (!assmbl.checkCpuCompatibility()) break;
		QList<Ram>* ramList = (QList<Ram>*)(getPartsListByPower(Parts::RAM, perfomanceLevel));
		foreach(Ram ram, (*ramList))
		{
			assmbl.rams[0] = ram;
			if (assmbl.checkRamCompatibility())
				break;
		}
		if (!assmbl.checkRamCompatibility()) break;
		QList<Psu>* psuList = (QList<Psu>*)(getPartsListByPower(Parts::PSU, perfomanceLevel));
		foreach(Psu psu, (*psuList))
		{
			assmbl.psu = psu;
			if (assmbl.checkPsuCompatibility())
				break;
		}
		if (!assmbl.checkPsuCompatibility()) break;
		QList<Gpu>* gpuList = (QList<Gpu>*)(getPartsListByPower(Parts::GPU, perfomanceLevel));
		foreach(Gpu gpu, (*gpuList))
		{
			assmbl.gpus[0] = gpu;
			if (assmbl.checkGpuCompatibility())
				break;
		}
		if (!assmbl.checkGpuCompatibility()) break;
		QList<DataStorage>* dataStorageList = (QList<DataStorage>*)(getPartsListByPower(Parts::DATASTORAGE, perfomanceLevel));
		foreach(DataStorage dataStorage, (*dataStorageList))
		{
			assmbl.dataStorages[0] = dataStorage;
			if (assmbl.checkDataStorageCompatibility())
				break;
		}
		if (!assmbl.checkDataStorageCompatibility()) break;
		QList<Case>* caseList = (QList<Case>*)(getPartsListByPower(Parts::CASE, perfomanceLevel));
		foreach(Case body, (*caseList))
		{
			assmbl.body = body;
			if (assmbl.checkCaseCompatibility())
				break;
		}
		if (!assmbl.checkCaseCompatibility()) break;
		QList<Cooler>* coolerList = (QList<Cooler>*)(getPartsListByPower(Parts::COOLER, perfomanceLevel));
		foreach(Cooler cooler, (*coolerList))
		{
			assmbl.cooler = cooler;
			if (assmbl.checkCoolerCompatibility())
				break;
		}
		if (!assmbl.checkCoolerCompatibility()) break;
        assmbl.recountPrice();
        assmbl.descriprion = "Assembly, perfomance: " + perfomanceLevel + "; price: " + QString::number(assmbl.price);
        list.append(assmbl);
    }
    return list;
}
