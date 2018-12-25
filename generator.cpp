#include "generator.h"
#include "ui_generator.h"
#include "settings.h"

Generator::Generator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);
    connect(ui->powerRButton, SIGNAL(toggled(bool)),this,SLOT(genTypeChanged()));
    connect(ui->priceRButton, SIGNAL(toggled(bool)),this,SLOT(genTypeChanged()));
    initGUI();
    }

Generator::~Generator()
{
  delete ui;
}

void Generator::initGUI()
{
  ui->priceRButton->toggled(true);
  ui->powerCmbBox->setEditable(false);
  foreach(QString item, Settings::Instance()->getPowerLevelsList()){
      ui->powerCmbBox->addItem(item);
    }
}

void Generator::genTypeChanged() {
  ui->powerCmbBox->setEnabled(ui->powerRButton->isChecked());
  ui->priceLineEdit->setEnabled(ui->priceRButton->isChecked());
}

void Generator::fillAssembliesListView(QList<Assembly> *assembliesList)
{
  ui->assembliesList->clear();
  foreach(Assembly item, *assembliesList){
      ui->assembliesList->addItem("Description: " + item.descriprion + "; Price: " + item.price);
    }
}



//void generator::ItemHandler(QString currItem){}
