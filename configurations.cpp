#include "configurations.h"
#include "settings.h"
#include "ui_configurations.h"
#include <QMessageBox>

Configurations::Configurations(QWidget *parent)
    : QDialog(parent), ui(new Ui::Configurations) {
  ui->setupUi(this);
  ui->openButton->setEnabled(false);
  ui->deleteButton->setEnabled(false);
  connect(ui->configurationsList, SIGNAL(currentRowChanged(int)), this,
          SLOT(selectItemHandler()));
  connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(deleteItemHandler()));
  connect(ui->openButton, SIGNAL(pressed()), this, SLOT(openAssembly()));
  fillList();
}

Configurations::~Configurations() { delete ui; }

void Configurations::selectItemHandler() {
  ui->openButton->setEnabled(true);
  ui->deleteButton->setEnabled(false);
}

void Configurations::deleteItemHandler() {
  int result = QMessageBox::warning(
      this, "Warning", "Are you sure you want to delete this assembly?",
      QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No,
      QMessageBox::StandardButton::No);
  if (result == QMessageBox::StandardButton::Yes) {
    Settings::Instance()->getComponentsDB()->getAssembliesList()->removeAt(
        ui->configurationsList->currentRow());
    fillList();
  }
}
void Configurations::fillList() {
  ui->configurationsList->clear();
  ui->openButton->setEnabled(false);
  ui->deleteButton->setEnabled(false);
  foreach (Assembly item,
           *(Settings::Instance()->getComponentsDB()->getAssembliesList())) {
    ui->configurationsList->addItem(item.descriprion +
                                    " Price: " + QString::number(item.price));
  }
}

void Configurations::openAssembly() {
  if (ui->configurationsList->currentRow() == -1)
    return;
  Assembly assembly =
      Settings::Instance()->getComponentsDB()->getAssembliesList()->at(
          ui->configurationsList->currentRow());
  emit assemblySelected(assembly);
  emit accepted();
  close();
}
