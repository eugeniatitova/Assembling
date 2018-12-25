#include "administrator.h"
#include "partsenum.h"
#include "settings.h"
#include "ui_administrator.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QSpinBox>

Administrator::Administrator(QWidget *parent)
    : QDialog(parent), ui(new Ui::Administrator) {
  ui->setupUi(this);
  connect(ui->partsCmbBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(itemHandler(int)));
  connect(ui->addButton, SIGNAL(pressed()), this, SLOT(addPart()));
  connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(deletePart()));
  connect(ui->changeButton, SIGNAL(pressed()), this, SLOT(changePart()));
  connect(
      ui->catalogTable->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      this, SLOT(catalogTableSelectChanged()));
  initGUI();
}

Administrator::~Administrator() { delete ui; }

void Administrator::initGUI() {
  ui->catalogTable->setSortingEnabled(true);
  ui->catalogTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);
  ui->catalogTable->horizontalHeader()->setVisible(true);
  itemHandler(Settings::Instance()->getLastAdmPart());
}

void Administrator::catalogTableSelectChanged() {
  fillPartsFields(static_cast<Parts>(ui->partsCmbBox->currentIndex()));
}

void Administrator::itemHandlerBaseInfo() {
  ui->fieldsTable->setCellWidget(0, 0, new QLabel(" Price", ui->fieldsTable));
  ui->fieldsTable->setCellWidget(1, 0,
                                 new QLabel(" Description", ui->fieldsTable));
  ui->fieldsTable->setCellWidget(2, 0,
                                 new QLabel(" Manufacturer", ui->fieldsTable));
  ui->fieldsTable->setCellWidget(3, 0, new QLabel(" Model", ui->fieldsTable));
  ui->fieldsTable->setCellWidget(
      4, 0, new QLabel(" Perfomance level", ui->fieldsTable));

  QLineEdit *lineEdit = new QLineEdit(ui->fieldsTable);
  lineEdit->setValidator(new QIntValidator(0, 9999999));
  ui->fieldsTable->setCellWidget(0, 1, lineEdit);
  ui->fieldsTable->setCellWidget(1, 1, new QLineEdit(ui->fieldsTable));
  ui->fieldsTable->setCellWidget(2, 1, new QLineEdit(ui->fieldsTable));
  ui->fieldsTable->setCellWidget(3, 1, new QLineEdit(ui->fieldsTable));

  QComboBox *comboBox = new QComboBox(ui->fieldsTable);
  comboBox->addItems(Settings::Instance()->getPowerLevelsList());
  ui->fieldsTable->setCellWidget(4, 1, comboBox);
}

void Administrator::itemHandler(int currIndex) {
  Settings::Instance()->setLastAdmPart(static_cast<Parts>(currIndex));
  fillPartsCatalog(Settings::Instance()->getLastAdmPart());

  switch (Settings::Instance()->getLastAdmPart()) {
  case CPU: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(10);
    itemHandlerBaseInfo();
    ui->fieldsTable->setCellWidget(5, 0,
                                   new QLabel(" Socket", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(6, 0,
                                   new QLabel(" CPU family", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        7, 0, new QLabel(" Frequency (MHz)", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        8, 0, new QLabel(" Num of cores", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(9, 0, new QLabel(" TDP", ui->fieldsTable));

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getSocketsList());
    ui->fieldsTable->setCellWidget(5, 1, comboBox);

    ui->fieldsTable->setCellWidget(6, 1, new QLineEdit(ui->fieldsTable));

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 10000);
    ui->fieldsTable->setCellWidget(7, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 32);
    ui->fieldsTable->setCellWidget(8, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 1000);
    ui->fieldsTable->setCellWidget(9, 1, spinBox);
    break;
  }
  case MOTHERBOARD: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(21);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(5, 0,
                                   new QLabel(" Form factor", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(6, 0,
                                   new QLabel(" Socket", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(7, 0,
                                   new QLabel(" RAM type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        8, 0, new QLabel(" CPU supply plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        9, 0, new QLabel(" MB supply plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        10, 0, new QLabel(" Num of CPU supply plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        11, 0, new QLabel(" Num of RAM slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        12, 0, new QLabel(" Num of SATA2 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        13, 0, new QLabel(" Num of SATA3 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        14, 0, new QLabel(" Num of USB2 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        15, 0, new QLabel(" Num of USB3 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        16, 0, new QLabel(" Num of PCI-E X16 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        17, 0, new QLabel(" Num of PCI-E X8 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        18, 0, new QLabel(" Num of PCI-E X4 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        19, 0, new QLabel(" Num of PCI-E X1 slots", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        20, 0, new QLabel(" Num of PCI slots", ui->fieldsTable));

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getFormFactorsList());
    ui->fieldsTable->setCellWidget(5, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getSocketsList());
    ui->fieldsTable->setCellWidget(6, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getRamTypesList());
    ui->fieldsTable->setCellWidget(7, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getCpuSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(8, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getMbSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(9, 1, comboBox);

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 4);
    ui->fieldsTable->setCellWidget(10, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 16);
    ui->fieldsTable->setCellWidget(11, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(12, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(13, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(14, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(15, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(16, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(17, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(18, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(19, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 32);
    ui->fieldsTable->setCellWidget(20, 1, spinBox);

    break;
  }
  case RAM: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(8);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(5, 0,
                                   new QLabel(" RAM type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(6, 0,
                                   new QLabel(" Memory size", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        7, 0, new QLabel("Num of modules", ui->fieldsTable));

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getRamTypesList());
    ui->fieldsTable->setCellWidget(5, 1, comboBox);

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 65536);
    ui->fieldsTable->setCellWidget(6, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 16);
    ui->fieldsTable->setCellWidget(7, 1, spinBox);

    break;
  }
  case GPU: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(11);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(5, 0, new QLabel(" TDP", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(6, 0,
                                   new QLabel(" Supply plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        7, 0, new QLabel(" Core clock (MHz)", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        8, 0, new QLabel(" Memory bus width", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(9, 0,
                                   new QLabel(" Memory size", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        10, 0, new QLabel(" Memory clock (MHz)", ui->fieldsTable));

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 1000);
    ui->fieldsTable->setCellWidget(5, 1, spinBox);

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getGpuSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(6, 1, comboBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 100000);
    ui->fieldsTable->setCellWidget(7, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 100000);
    ui->fieldsTable->setCellWidget(8, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 65536);
    ui->fieldsTable->setCellWidget(9, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 100000);
    ui->fieldsTable->setCellWidget(10, 1, spinBox);
    break;
  }
  case PSU: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(15);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(5, 0,
                                   new QLabel(" Form factor", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        6, 0, new QLabel(" MB plug type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        7, 0, new QLabel(" CPU plug type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(8, 0,
                                   new QLabel(" Power (W)", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        9, 0, new QLabel(" Num of CPU plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        10, 0, new QLabel(" Num of 6pin PCI-E plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        11, 0, new QLabel(" Num of 6+2pin PCI-E plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        12, 0, new QLabel(" Num of 8pin PCI-E plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        13, 0, new QLabel(" Num of SATA plug", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        14, 0, new QLabel(" Num of Molex plug", ui->fieldsTable));

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getFormFactorsList());
    ui->fieldsTable->setCellWidget(5, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getMbSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(6, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getCpuSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(7, 1, comboBox);

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 10000);
    ui->fieldsTable->setCellWidget(8, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 10);
    ui->fieldsTable->setCellWidget(9, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 10);
    ui->fieldsTable->setCellWidget(10, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 10);
    ui->fieldsTable->setCellWidget(11, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 10);
    ui->fieldsTable->setCellWidget(12, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 10);
    ui->fieldsTable->setCellWidget(13, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 10);
    ui->fieldsTable->setCellWidget(14, 1, spinBox);

    break;
  }
  case DATASTORAGE: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(9);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(5, 0,
                                   new QLabel(" Store type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        6, 0, new QLabel(" Supply plug type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        7, 0, new QLabel(" Power consumption", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        8, 0, new QLabel(" Memory size (GB)", ui->fieldsTable));

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getStoreTypesList());
    ui->fieldsTable->setCellWidget(5, 1, comboBox);

    comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getPeriphSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(6, 1, comboBox);

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 10000);
    ui->fieldsTable->setCellWidget(7, 1, spinBox);

    spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(1, 20000);
    ui->fieldsTable->setCellWidget(8, 1, spinBox);

    break;
  }
  case PERIPHERAL: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(7);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(
        5, 0, new QLabel(" Supply plug type", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(
        6, 0, new QLabel(" Power consumption", ui->fieldsTable));

    QComboBox *comboBox = new QComboBox(ui->fieldsTable);
    comboBox->addItems(Settings::Instance()->getPeriphSupplyPlugTypesList());
    ui->fieldsTable->setCellWidget(5, 1, comboBox);

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 1000);
    ui->fieldsTable->setCellWidget(6, 1, spinBox);

    break;
  }
  case CASE: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(6);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(
        5, 0, new QLabel(" Form factors", ui->fieldsTable));

    ui->fieldsTable->setCellWidget(5, 1, new QLineEdit(ui->fieldsTable));
    break;
  }
  case COOLER: {
    ui->fieldsTable->clear();
    ui->fieldsTable->setColumnCount(2);
    ui->fieldsTable->setRowCount(7);
    itemHandlerBaseInfo();

    ui->fieldsTable->setCellWidget(5, 0,
                                   new QLabel(" Sockets", ui->fieldsTable));
    ui->fieldsTable->setCellWidget(6, 0,
                                   new QLabel(" Max TDP", ui->fieldsTable));

    ui->fieldsTable->setCellWidget(5, 1, new QLineEdit(ui->fieldsTable));

    QSpinBox *spinBox = new QSpinBox(ui->fieldsTable);
    spinBox->setRange(0, 1000);
    ui->fieldsTable->setCellWidget(6, 1, spinBox);

    break;
  }
  case PARTS_TYPE_COUNT:
    break;
  }
}

void Administrator::fillPartsCatalogBaseInfo(Component baseInfo, QString toolTip) {
  int count = ui->catalogTable->rowCount();
  ui->catalogTable->setRowCount(count + 1);
  ui->catalogTable->setCellWidget(
      count, 0, new QLabel(baseInfo.manufacturer, ui->catalogTable));
  ui->catalogTable->cellWidget(count, 0)->setToolTip(toolTip);
  ui->catalogTable->setCellWidget(count, 1,
                                  new QLabel(baseInfo.model, ui->catalogTable));
  ui->catalogTable->cellWidget(count, 1)->setToolTip(toolTip);
  ui->catalogTable->setCellWidget(
      count, 2, new QLabel(QString::number(baseInfo.price), ui->catalogTable));
  ui->catalogTable->cellWidget(count, 2)->setToolTip(toolTip);
}

void Administrator::fillPartsCatalog(Parts parts) {
  ui->catalogTable->setRowCount(0);
  switch (parts) {
  case CPU: {
    foreach (Cpu item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getCpus()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Cpu::generateCpuTooltip(item));

    }
    break;
  }
  case MOTHERBOARD: {
    foreach (Motherboard item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getMotherboards()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Motherboard::generateMotherboardTooltip(item));
    }
    break;
  }
  case RAM: {
    foreach (Ram item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getRams()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Ram::generateRamTooltip(item));
    }
    break;
  }
  case GPU: {
    foreach (Gpu item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getGpus()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Gpu::generateGpuTooltip(item));
    }
    break;
  }
  case PSU: {
    foreach (Psu item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getPsus()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Psu::generatePsuTooltip(item));
    }
    break;
  }
  case DATASTORAGE: {
    foreach (DataStorage item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getDataStorages()) {
      fillPartsCatalogBaseInfo(item.baseInfo, DataStorage::generateDataStorageTooltip(item));
    }
    break;
  }
  case PERIPHERAL: {
    foreach (Peripheral item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getPeripherals()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Peripheral::generatePeripheralTooltip(item));
    }
    break;
  }
  case CASE: {
    foreach (Case item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getCases()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Case::generateCaseTooltip(item));
    }
    break;
  }
  case COOLER: {
    foreach (Cooler item,
             *Settings::Instance()
                  ->getComponentsDB()
                  ->getComponentsList()
                  ->getCoolers()) {
      fillPartsCatalogBaseInfo(item.baseInfo, Cooler::generateCoolerTooltip(item));
    }
    break;
  }
  case PARTS_TYPE_COUNT:
    break;
  }
}

void Administrator::fillPartsBaseInfo(Component baseInfo) {
  qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(0, 1))
      ->setText(QString::number(baseInfo.price));
  qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(1, 1))
      ->setText(baseInfo.description);
  qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(2, 1))
      ->setText(baseInfo.manufacturer);
  qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(3, 1))
      ->setText(baseInfo.model);
  qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(4, 1))
      ->setCurrentText(baseInfo.perfomanceLevel);
}

void Administrator::fillPartsFields(Parts part) {
  if (ui->catalogTable->currentRow() == -1)
    return;
  switch (part) {
  case CPU: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Cpu currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getCpus()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));
      fillPartsBaseInfo(currentPart.baseInfo);

      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setCurrentText(currentPart.socket);
      qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(6, 1))
          ->setText(currentPart.cpuFamily);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1))
          ->setValue(currentPart.mhzFrequency);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1))
          ->setValue(currentPart.numOfCores);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(9, 1))
          ->setValue(currentPart.tdp);
    }
    break;
  }
  case MOTHERBOARD: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Motherboard currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getMotherboards()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));
      fillPartsBaseInfo(currentPart.baseInfo);

      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setCurrentText(currentPart.formFactor);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setCurrentText(currentPart.socket);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(7, 1))
          ->setCurrentText(currentPart.ramType);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(8, 1))
          ->setCurrentText(currentPart.cpuSupplyPlug);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(9, 1))
          ->setCurrentText(currentPart.mbSupplyPlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(10, 1))
          ->setValue(currentPart.numOfCpuSupplyPlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(11, 1))
          ->setValue(currentPart.numOfRamSlots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(12, 1))
          ->setValue(currentPart.numOfSata2Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(13, 1))
          ->setValue(currentPart.numOfSata3Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(14, 1))
          ->setValue(currentPart.numOfUSB2Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(15, 1))
          ->setValue(currentPart.numOfUSB3Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(16, 1))
          ->setValue(currentPart.numOfPcieX16Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(17, 1))
          ->setValue(currentPart.numOfPcieX8Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(18, 1))
          ->setValue(currentPart.numOfPcieX4Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(19, 1))
          ->setValue(currentPart.numOfPcieX1Slots);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(20, 1))
          ->setValue(currentPart.numOfPciSlots);
    }
    break;
  }
  case RAM: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Ram currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getRams()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);

      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setCurrentText(currentPart.ramType);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setValue(currentPart.memorySize);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1))
          ->setValue(currentPart.numOfModules);
    }
    break;
  }
  case GPU: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Gpu currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getGpus()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setValue(currentPart.tdp);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setCurrentText(currentPart.supplyPlugType);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1))
          ->setValue(currentPart.coreClock);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1))
          ->setValue(currentPart.memoryBusWidth);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(9, 1))
          ->setValue(currentPart.memorySize);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(10, 1))
          ->setValue(currentPart.memoryClock);
    }
    break;
  }
  case PSU: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Psu currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getPsus()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setCurrentText(currentPart.formFactor);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setCurrentText(currentPart.mbPlugType);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(7, 1))
          ->setCurrentText(currentPart.cpuPlugType);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1))
          ->setValue(currentPart.power);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(9, 1))
          ->setValue(currentPart.numOfCpuPlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(10, 1))
          ->setValue(currentPart.numOf6PinPciePlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(11, 1))
          ->setValue(currentPart.numOf6p2PinPciePlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(12, 1))
          ->setValue(currentPart.numOf8PinPciePlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(13, 1))
          ->setValue(currentPart.numOfSataPlug);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(14, 1))
          ->setValue(currentPart.numOfMolexPlug);
    }
    break;
  }
  case DATASTORAGE: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      DataStorage currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getDataStorages()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setCurrentText(currentPart.storeType);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setCurrentText(currentPart.supplyPlugType);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1))
          ->setValue(currentPart.powerConsumption);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1))
          ->setValue(currentPart.memorySize);
    }
    break;
  }
  case PERIPHERAL: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Peripheral currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getPeripherals()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);
      qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1))
          ->setCurrentText(currentPart.supplyPlugType);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setValue(currentPart.powerConsumption);
    }
    break;
  }
  case CASE: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Case currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getCases()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);
      qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(5, 1))
          ->setText(currentPart.formFactors);
    }
    break;
  }
  case COOLER: {
    QString modelName =
        qobject_cast<QLabel *>(
            ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1))
            ->text();
    int index =
        Settings::Instance()->getComponentsDB()->findItemIndex(part, modelName);
    if (index != -1) {
      Cooler currentPart =
          Settings::Instance()
              ->getComponentsDB()
              ->getComponentsList()
              ->getCoolers()
              ->at(Settings::Instance()->getComponentsDB()->findItemIndex(
                  part, modelName));

      fillPartsBaseInfo(currentPart.baseInfo);
      qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(5, 1))
          ->setText(currentPart.sockets);
      qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(6, 1))
          ->setValue(currentPart.maxTdp);
    }
    break;
  }
  case PARTS_TYPE_COUNT:
    break;
  }
}

Component Administrator::getComponentFromFields() {
  Component baseInfo = Component::getNewComponent();
  baseInfo.price =
      (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(0, 1)))
          ->text()
          .toInt();
  baseInfo.description =
      (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(1, 1)))->text();
  baseInfo.manufacturer =
      (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(2, 1)))->text();
  baseInfo.model =
      (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(3, 1)))->text();
  baseInfo.perfomanceLevel =
      (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(4, 1)))
          ->currentText();
  return baseInfo;
}

void Administrator::addPart() {
  switch (static_cast<Parts>(ui->partsCmbBox->currentIndex())) {
  case CPU: {
    Cpu cpu = Cpu::getNewCpu();
    cpu.baseInfo = getComponentFromFields();
    cpu.socket = (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1)))
                     ->currentText();
    cpu.cpuFamily =
        (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(6, 1)))->text();
    cpu.mhzFrequency =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1)))->value();
    cpu.numOfCores =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1)))->value();
    cpu.tdp =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(9, 1)))->value();
    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::CPU, cpu.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getCpus()
          ->append(cpu);
      fillPartsCatalog(Parts::CPU);
    }
    break;
  }
  case MOTHERBOARD: {
    Motherboard motherboard = Motherboard::getNewMotherboard();
    motherboard.baseInfo = getComponentFromFields();
    motherboard.formFactor =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1)))
            ->currentText();
    motherboard.socket =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1)))
            ->currentText();
    motherboard.ramType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(7, 1)))
            ->currentText();
    motherboard.cpuSupplyPlug =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(8, 1)))
            ->currentText();
    motherboard.mbSupplyPlug =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(9, 1)))
            ->currentText();
    motherboard.numOfCpuSupplyPlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(10, 1)))->value();
    motherboard.numOfRamSlots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(11, 1)))->value();
    motherboard.numOfSata2Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(12, 1)))->value();
    motherboard.numOfSata3Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(13, 1)))->value();
    motherboard.numOfUSB2Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(14, 1)))->value();
    motherboard.numOfUSB3Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(15, 1)))->value();
    motherboard.numOfPcieX16Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(16, 1)))->value();
    motherboard.numOfPcieX8Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(17, 1)))->value();
    motherboard.numOfPcieX4Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(18, 1)))->value();
    motherboard.numOfPcieX1Slots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(19, 1)))->value();
    motherboard.numOfPciSlots =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(20, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::MOTHERBOARD, motherboard.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getMotherboards()
          ->append(motherboard);
      fillPartsCatalog(Parts::MOTHERBOARD);
    }

    break;
  }
  case RAM: {
    Ram ram = Ram::getNewRam();
    ram.baseInfo = getComponentFromFields();
    ram.ramType = (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1)))
                      ->currentText();
    ram.memorySize =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(6, 1)))->value();
    ram.numOfModules =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::RAM, ram.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getRams()
          ->append(ram);
      fillPartsCatalog(Parts::RAM);
    }
    break;
  }
  case GPU: {
    Gpu gpu = Gpu::getNewGpu();
    gpu.baseInfo = getComponentFromFields();
    gpu.tdp =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(5, 1)))->value();
    gpu.supplyPlugType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1)))->currentText();
    gpu.coreClock =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1)))->value();
    gpu.memoryBusWidth =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1)))->value();
    gpu.memorySize =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(9, 1)))->value();
    gpu.memoryClock =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(10, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::GPU, gpu.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getGpus()
          ->append(gpu);
      fillPartsCatalog(Parts::GPU);
    }
    break;
  }
  case PSU: {
    Psu psu = Psu::getNewPsu();
    psu.baseInfo = getComponentFromFields();
    psu.formFactor =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1)))
            ->currentText();
    psu.mbPlugType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1)))
            ->currentText();
    psu.cpuPlugType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(7, 1)))
            ->currentText();
    psu.power =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1)))->value();
    psu.numOfCpuPlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(9, 1)))->value();
    psu.numOf6PinPciePlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(10, 1)))->value();
    psu.numOf6p2PinPciePlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(11, 1)))->value();
    psu.numOf8PinPciePlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(12, 1)))->value();
    psu.numOfSataPlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(13, 1)))->value();
    psu.numOfMolexPlug =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(14, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::PSU, psu.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getPsus()
          ->append(psu);
      fillPartsCatalog(Parts::PSU);
    }
    break;
  }
  case DATASTORAGE: {
    DataStorage dataStorage = DataStorage::getNewDataStorage();
    dataStorage.baseInfo = getComponentFromFields();
    dataStorage.storeType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1)))
            ->currentText();
    dataStorage.supplyPlugType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(6, 1)))
            ->currentText();
    dataStorage.powerConsumption =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(7, 1)))->value();
    dataStorage.memorySize =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(8, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::DATASTORAGE, dataStorage.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getDataStorages()
          ->append(dataStorage);
      fillPartsCatalog(Parts::DATASTORAGE);
    }
    break;
  }
  case PERIPHERAL: {
    Peripheral peripheral = Peripheral::getNewPeripheral();
    peripheral.baseInfo = getComponentFromFields();
    peripheral.supplyPlugType =
        (qobject_cast<QComboBox *>(ui->fieldsTable->cellWidget(5, 1)))
            ->currentText();
    peripheral.powerConsumption =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(6, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::PERIPHERAL, peripheral.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getPeripherals()
          ->append(peripheral);
      fillPartsCatalog(Parts::PERIPHERAL);
    }
    break;
  }
  case CASE: {
    Case Case = Case::getNewCase();
    Case.baseInfo = getComponentFromFields();
    Case.formFactors =
        (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(5, 1)))->text();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::CASE, Case.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getCases()
          ->append(Case);
      fillPartsCatalog(Parts::CASE);
    }
    break;
  }
  case COOLER: {
    Cooler cooler = Cooler::getNewCooler();
    cooler.baseInfo = getComponentFromFields();
    cooler.sockets =
        (qobject_cast<QLineEdit *>(ui->fieldsTable->cellWidget(5, 1)))->text();
    cooler.maxTdp =
        (qobject_cast<QSpinBox *>(ui->fieldsTable->cellWidget(6, 1)))->value();

    if (Settings::Instance()->getComponentsDB()->findItemIndex(
            Parts::COOLER, cooler.baseInfo.model) != -1) {
      QMessageBox msgBox;
      msgBox.setText("Model is already exist.");
      msgBox.exec();
    } else {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getCoolers()
          ->append(cooler);
      fillPartsCatalog(Parts::COOLER);
    }
    break;
  }
  case PARTS_TYPE_COUNT:
    break;
  }
}

void Administrator::deletePart() {
  if (ui->catalogTable->currentRow() == -1)
    return;
  Parts currentPart = static_cast<Parts>(ui->partsCmbBox->currentIndex());
  QString model = qobject_cast<QLabel *>(ui->catalogTable->cellWidget(
                                             ui->catalogTable->currentRow(), 1))
                      ->text();
  int index = Settings::Instance()->getComponentsDB()->findItemIndex(
      currentPart, model);
  if (index != -1) {
    switch (currentPart) {
    case CPU: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getCpus()
          ->removeAt(index);
      break;
    }
    case MOTHERBOARD: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getMotherboards()
          ->removeAt(index);
      break;
    }
    case RAM: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getRams()
          ->removeAt(index);
      break;
    }
    case GPU: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getGpus()
          ->removeAt(index);
      break;
    }
    case PSU: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getPsus()
          ->removeAt(index);
      break;
    }
    case DATASTORAGE: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getDataStorages()
          ->removeAt(index);
      break;
    }
    case PERIPHERAL: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getPeripherals()
          ->removeAt(index);
      break;
    }
    case CASE: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getCases()
          ->removeAt(index);
      break;
    }
    case COOLER: {
      Settings::Instance()
          ->getComponentsDB()
          ->getComponentsList()
          ->getCoolers()
          ->removeAt(index);
      break;
    }
    case PARTS_TYPE_COUNT: {
      break;
    }
    }
  }
  fillPartsCatalog(currentPart);
}

void Administrator::changePart() {
  deletePart();
  addPart();
}
