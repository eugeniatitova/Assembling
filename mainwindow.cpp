#include "mainwindow.h"
#include "administrator.h"
#include "authorization.h"
#include "configurations.h"
#include "generator.h"
#include "settings.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  Settings *settings = Settings::Instance();
  settings->loadSettings();
  admDialog = new Administrator(this);
  authDialog = new Authorization(this);
  configDialog = new Configurations(this);
  generatorDialog = new Generator(this);
  currentAssembly = Assembly::getNewAssembly();
  initGUI();
}

MainWindow::~MainWindow() {
  Settings::Instance()->saveSettings();
  delete ui;
}

void MainWindow::initGUI() {
  connect(authDialog, SIGNAL(authPass()), this, SLOT(authPassed()));
  connect(configDialog, SIGNAL(assemblySelected(Assembly)), this, SLOT(openAssembly(Assembly)));
  connect(ui->authorizationAction, SIGNAL(triggered(bool)), this,
          SLOT(authorizationMenuClicked()));
  connect(ui->editAction, SIGNAL(triggered(bool)), this,
          SLOT(administratorMenuClicked()));
  connect(ui->savedConfigurationsAction, SIGNAL(triggered(bool)), this,
          SLOT(assembliesMenuClicked()));
  connect(ui->generateConfigurationAction, SIGNAL(triggered(bool)), this,
          SLOT(generatorMenuClicked()));
  connect(ui->partsCmbBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(partsTableChanged()));
  connect(ui->sortCmbBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(partsTableChanged()));
  connect(ui->clearButton, SIGNAL(pressed()), this, SLOT(clearButtonPressed()));
  connect(ui->saveButton, SIGNAL(pressed()), this, SLOT(saveButtonPressed()));
  connect(ui->reportButton, SIGNAL(pressed()), this,
          SLOT(getReportButtonPressed()));
  connect(ui->catalogTable, SIGNAL(doubleClicked(const QModelIndex &)), this,
          SLOT(catalogTableDoubleClickHandler()));
  connect(ui->assembleTable, SIGNAL(doubleClicked(const QModelIndex &)), this,
          SLOT(assembleTableDoubleClickHandler()));

  ui->catalogTable->setSortingEnabled(true);
  ui->catalogTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);
  ui->assembleTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);
  ui->assembleTable->verticalHeader()->setVisible(true);
  ui->assembleTable->verticalHeader()->setSectionResizeMode(
      QHeaderView::ResizeMode::Stretch);

  refreshGUI(false);
}

void MainWindow::refreshGUI(bool checkParts) {
  chooseParts(static_cast<Parts>(ui->partsCmbBox->currentIndex()));
  if (checkParts)
    fillAssemblyTable();
}

void MainWindow::authPassed() { administratorAccept = true; }

void MainWindow::authorizationMenuClicked() {
  if (!administratorAccept)
    authDialog->show();
}

void MainWindow::administratorMenuClicked() {
  if (administratorAccept) {
    admDialog->show();
  } else {
    QMessageBox::warning(this, "Error", "You are not authorized.");
  }
}

void MainWindow::assembliesMenuClicked() {
  //Settings::Instance()->getComponentsDB()->generateAssemblies("Low");
  if(configDialog->exec() == QDialog::DialogCode::Accepted)
  refreshGUI(true);
}

void MainWindow::generatorMenuClicked() {
  if(generatorDialog->exec() == QDialog::DialogCode::Accepted)
  refreshGUI(true);
}

void MainWindow::catalogTableDoubleClickHandler() {
  if (ui->catalogTable->currentRow() == -1)
    return;
  Parts part = static_cast<Parts>(ui->partsCmbBox->currentIndex());
  QString model =
      qobject_cast<QLabel *>(
          (ui->catalogTable->cellWidget(ui->catalogTable->currentRow(), 1)))
          ->text();
  int partIndex =
      Settings::Instance()->getComponentsDB()->findItemIndex(part, model);
  if (partIndex != -1) {
    switch (part) {
    case CPU:
      currentAssembly.cpu = Settings::Instance()
                                ->getComponentsDB()
                                ->getComponentsList()
                                ->getCpus()
                                ->at(partIndex);
      break;
    case MOTHERBOARD:
      currentAssembly.motherboard = Settings::Instance()
                                        ->getComponentsDB()
                                        ->getComponentsList()
                                        ->getMotherboards()
                                        ->at(partIndex);
      break;
    case RAM:
      currentAssembly.rams.clear();
      currentAssembly.rams.append(Settings::Instance()
                                      ->getComponentsDB()
                                      ->getComponentsList()
                                      ->getRams()
                                      ->at(partIndex));
      break;
    case GPU:
      currentAssembly.gpus.clear();
      currentAssembly.gpus.append(Settings::Instance()
                                      ->getComponentsDB()
                                      ->getComponentsList()
                                      ->getGpus()
                                      ->at(partIndex));
      break;
    case PSU:
      currentAssembly.psu = Settings::Instance()
                                ->getComponentsDB()
                                ->getComponentsList()
                                ->getPsus()
                                ->at(partIndex);
      break;
    case DATASTORAGE:
      currentAssembly.dataStorages.clear();
      currentAssembly.dataStorages.append(Settings::Instance()
                                              ->getComponentsDB()
                                              ->getComponentsList()
                                              ->getDataStorages()
                                              ->at(partIndex));
      break;
    case PERIPHERAL:
      currentAssembly.peripherals.clear();
      currentAssembly.peripherals.append(Settings::Instance()
                                             ->getComponentsDB()
                                             ->getComponentsList()
                                             ->getPeripherals()
                                             ->at(partIndex));
      break;
    case CASE:
      currentAssembly.body = Settings::Instance()
                                 ->getComponentsDB()
                                 ->getComponentsList()
                                 ->getCases()
                                 ->at(partIndex);
      break;
    case COOLER:
      currentAssembly.cooler = Settings::Instance()
                                   ->getComponentsDB()
                                   ->getComponentsList()
                                   ->getCoolers()
                                   ->at(partIndex);
      break;
    case PARTS_TYPE_COUNT:
      return;
    }
    refreshGUI(true);
  }
}

void MainWindow::assembleTableDoubleClickHandler() {
  if (ui->assembleTable->currentRow() == -1)
    return;
  Parts part = static_cast<Parts>(ui->assembleTable->currentRow());
  switch (part) {
  case CPU:
    currentAssembly.cpu = Cpu::getNewCpu();
    break;

  case MOTHERBOARD:
    currentAssembly.motherboard = Motherboard::getNewMotherboard();
    break;

  case RAM:
    currentAssembly.rams.clear();
    break;

  case GPU:
    currentAssembly.gpus.clear();
    break;

  case PSU:
    currentAssembly.psu = Psu::getNewPsu();
    break;

  case DATASTORAGE:
    currentAssembly.dataStorages.clear();
    break;

  case PERIPHERAL:
    currentAssembly.peripherals.clear();
    break;

  case CASE:
    currentAssembly.body = Case::getNewCase();
    break;

  case COOLER:
    currentAssembly.cooler = Cooler::getNewCooler();
    break;

  case PARTS_TYPE_COUNT:
    return;
  }
  refreshGUI(true);
}

void MainWindow::clearButtonPressed() {
  currentAssembly = Assembly::getNewAssembly();
  refreshGUI(true);
}

void MainWindow::getReportButtonPressed() {
  currentAssembly.descriprion = QString("Parts cart");
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save assembly report", QDir::currentPath(), "txt (*.txt)");
  QFile file(fileName);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream stream(&file);
    stream << currentAssembly.getAssemblyReport() << endl;
    file.close();
  }
}

void MainWindow::saveButtonPressed() {
  if (!currentAssembly.isEmpty()) {
    QString compatability = currentAssembly.checkCompatibility();
    if (compatability == "OK") {
      currentAssembly.descriprion = QInputDialog::getText(
          this, "Assembly description", "Enter description", QLineEdit::Normal);
      Settings::Instance()->getComponentsDB()->getAssembliesList()->append(
          currentAssembly);
    } else {
      QMessageBox::warning(this, "Error", "Incompatible " + compatability);
    }
  } else
    QMessageBox::warning(this, "Error", "Assembly is empty.");
}

void MainWindow::partsTableChanged() { refreshGUI(false); }

void MainWindow::openAssembly(Assembly a)
{
  currentAssembly = a;
  refreshGUI(true);
}

void MainWindow::fillPartBaseInfo(Component baseInfo, QString toolTip) {
  int count = ui->catalogTable->rowCount();
  ui->catalogTable->setRowCount(count + 1);
  ui->catalogTable->setCellWidget(
      count, 0, new QLabel(baseInfo.manufacturer, ui->catalogTable));
  ui->catalogTable->cellWidget(count, 0)->setToolTip(toolTip);
  ui->catalogTable->setCellWidget(count, 1,
                                  new QLabel(baseInfo.model, ui->catalogTable));
  ui->catalogTable->cellWidget(count, 1)->setToolTip(toolTip);
  ui->catalogTable->setCellWidget(
      count, 2, new QLabel(baseInfo.description, ui->catalogTable));
  ui->catalogTable->cellWidget(count, 2)->setToolTip(toolTip);
  ui->catalogTable->setCellWidget(
      count, 3, new QLabel(QString::number(baseInfo.price), ui->catalogTable));
  ui->catalogTable->cellWidget(count, 3)->setToolTip(toolTip);
}

void MainWindow::chooseParts(Parts parts) {
  ui->catalogTable->setRowCount(0);
  switch (parts) {
  case CPU: {
    foreach (Cpu item,
             Settings::Instance()->getComponentsDB()->getSortedCpuList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo, Cpu::generateCpuTooltip(item));
    }
    break;
  }
  case MOTHERBOARD: {
    foreach (Motherboard item,
             Settings::Instance()->getComponentsDB()->getSortedMotherboardList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo,
                       Motherboard::generateMotherboardTooltip(item));
    }
    break;
  }
  case RAM: {
    foreach (Ram item,
             Settings::Instance()->getComponentsDB()->getSortedRamList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo, Ram::generateRamTooltip(item));
    }
    break;
  }
  case GPU: {
    foreach (Gpu item,
             Settings::Instance()->getComponentsDB()->getSortedGpuList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo, Gpu::generateGpuTooltip(item));
    }
    break;
  }
  case PSU: {
    foreach (Psu item,
             Settings::Instance()->getComponentsDB()->getSortedPsuList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo, Psu::generatePsuTooltip(item));
    }
    break;
  }
  case DATASTORAGE: {
    foreach (DataStorage item,
             Settings::Instance()->getComponentsDB()->getSortedDataStorageList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo,
                       DataStorage::generateDataStorageTooltip(item));
    }
    break;
  }
  case PERIPHERAL: {
    foreach (Peripheral item,
             Settings::Instance()->getComponentsDB()->getSortedPeripheralList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo,
                       Peripheral::generatePeripheralTooltip(item));
    }
    break;
  }
  case CASE: {
    foreach (Case item,
             Settings::Instance()->getComponentsDB()->getSortedCaseList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo, Case::generateCaseTooltip(item));
    }
    break;
  }
  case COOLER: {
    foreach (Cooler item,
             Settings::Instance()->getComponentsDB()->getSortedCoolerList(
                 static_cast<SortType>(ui->sortCmbBox->currentIndex()))) {
      fillPartBaseInfo(item.baseInfo, Cooler::generateCoolerTooltip(item));
    }
    break;
  }
  case PARTS_TYPE_COUNT:
    break;
  }
}

void MainWindow::fillAssemblyTableRow(Component baseInfo, int row, int count,
                                      bool useSpinBox) {
  QLabel *lbl = new QLabel(ui->assembleTable);
  lbl->setText(baseInfo.manufacturer);
  ui->assembleTable->setCellWidget(row, 0, lbl);
  lbl = new QLabel(ui->assembleTable);
  lbl->setText(baseInfo.model);
  ui->assembleTable->setCellWidget(row, 1, lbl);
  if (useSpinBox) {
    QSpinBox *spinBox = new QSpinBox();
    spinBox->setRange(1, 10);
    spinBox->setValue(count % 11);
    ui->assembleTable->setCellWidget(row, 2, spinBox);
  } else {
    lbl = new QLabel(ui->assembleTable);
    lbl->setText(QString::number(count));
    ui->assembleTable->setCellWidget(row, 2, lbl);
  }
  lbl = new QLabel(ui->assembleTable);
  lbl->setText(QString::number(baseInfo.price * count));
  ui->assembleTable->setCellWidget(row, 3, lbl);
}

void MainWindow::fillAssemblyTable() {
  ui->assembleTable->clearContents();
  if (!currentAssembly.cpu.isEmpty())
    fillAssemblyTableRow(currentAssembly.cpu.baseInfo, 0, 1, false);
  if (!currentAssembly.motherboard.isEmpty())
    fillAssemblyTableRow(currentAssembly.motherboard.baseInfo, 1, 1, false);
  if (!currentAssembly.rams.isEmpty()) {
    fillAssemblyTableRow(currentAssembly.rams.at(0).baseInfo, 2,
                         currentAssembly.rams.length(), true);
    connect(qobject_cast<QSpinBox *>(ui->assembleTable->cellWidget(2, 2)),
            SIGNAL(valueChanged(int)), this,
            SLOT(assemblyNumOfRamChanged(int)));
  }
  if (!currentAssembly.gpus.isEmpty()) {
    fillAssemblyTableRow(currentAssembly.gpus.at(0).baseInfo, 3,
                         currentAssembly.gpus.length(), true);
    connect(qobject_cast<QSpinBox *>(ui->assembleTable->cellWidget(3, 2)),
            SIGNAL(valueChanged(int)), this,
            SLOT(assemblyNumOfGpuChanged(int)));
  }
  if (!currentAssembly.psu.isEmpty())
    fillAssemblyTableRow(currentAssembly.psu.baseInfo, 4, 1, false);
  if (!currentAssembly.dataStorages.isEmpty()) {
    fillAssemblyTableRow(currentAssembly.dataStorages.at(0).baseInfo, 5,
                         currentAssembly.dataStorages.length(), true);
    connect(qobject_cast<QSpinBox *>(ui->assembleTable->cellWidget(5, 2)),
            SIGNAL(valueChanged(int)), this,
            SLOT(assemblyNumOfDataStoragesChanged(int)));
  }
  if (!currentAssembly.peripherals.isEmpty())
    fillAssemblyTableRow(currentAssembly.peripherals.at(0).baseInfo, 6,
                         currentAssembly.peripherals.length(), false);
  if (!currentAssembly.body.isEmpty())
    fillAssemblyTableRow(currentAssembly.body.baseInfo, 7, 1, false);
  if (!currentAssembly.cooler.isEmpty())
    fillAssemblyTableRow(currentAssembly.cooler.baseInfo, 8, 1, false);

  currentAssembly.recountPrice();
  ui->assembleTable->setCellWidget(9, 3,
                                   new QLabel(QString::number(currentAssembly.price)));
  processAssemblyCheck();
}

void MainWindow::assembleTableRowPainting(int row, QString stylesheet) {
  for (int i = 0; i < 4; i++)
    ui->assembleTable->cellWidget(row, i)->setStyleSheet(stylesheet);
  return;
}

void MainWindow::processAssemblyCheck() {
  QString result = currentAssembly.checkCompatibility();

  if (result != "OK")
      QMessageBox::warning(this, "Warning", result + " is incompatible.");

  if (!currentAssembly.cpu.isEmpty()) {
    if (result == "CPU") {
      assembleTableRowPainting(0, "background-color: red");
      return;
    }
    assembleTableRowPainting(0, "background-color: green");
  }

  if (!currentAssembly.motherboard.isEmpty()) {
    assembleTableRowPainting(1, "background-color: green");
  }

  if (!currentAssembly.rams.isEmpty()) {
    if (result == "RAM") {
      assembleTableRowPainting(2, "background-color: red");
      return;
    }
    assembleTableRowPainting(2, "background-color: green");
  }

  if (!currentAssembly.gpus.isEmpty()) {
    if (result == "GPU") {
      assembleTableRowPainting(3, "background-color: red");
      return;
    }
    assembleTableRowPainting(3, "background-color: green");
  }
  if (!currentAssembly.psu.isEmpty()) {
    if (result == "PSU") {
      assembleTableRowPainting(4, "background-color: red");
      return;
    }
    assembleTableRowPainting(4, "background-color: green");
  }
  if (!currentAssembly.dataStorages.isEmpty()) {
    if (result == "Data storages") {
      assembleTableRowPainting(5, "background-color: red");
      return;
    }
    assembleTableRowPainting(5, "background-color: green");
  }
  if (!currentAssembly.peripherals.isEmpty()) {
    assembleTableRowPainting(6, "background-color: green");
  }
  if (!currentAssembly.body.isEmpty()) {
    if (result == "Case") {
      assembleTableRowPainting(7, "background-color: red");
      return;
    }
    assembleTableRowPainting(7, "background-color: green");
  }
  if (!currentAssembly.cooler.isEmpty()) {
    if (result == "Cooler") {
      assembleTableRowPainting(8, "background-color: red");
      return;
    }
    assembleTableRowPainting(8, "background-color: green");
  }
}

void MainWindow::assemblyNumOfRamChanged(int value) {
  QList<Ram> newList;
  for (int i = 0; i < value; i++) {
    newList.append(currentAssembly.rams.at(0));
  }
  currentAssembly.rams = newList;
  refreshGUI(true);
}

void MainWindow::assemblyNumOfGpuChanged(int value) {
  QList<Gpu> newList;
  for (int i = 0; i < value; i++) {
    newList.append(currentAssembly.gpus.at(0));
  }
  currentAssembly.gpus = newList;
  refreshGUI(true);
}

void MainWindow::assemblyNumOfDataStoragesChanged(int value) {
  QList<DataStorage> newList;
  for (int i = 0; i < value; i++) {
    newList.append(currentAssembly.dataStorages.at(0));
  }
  currentAssembly.dataStorages = newList;
  refreshGUI(true);
}
