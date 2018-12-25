#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "partsenum.h"
#include "settings.h"
#include <QDialog>

namespace Ui {
class Administrator;
}

class Administrator : public QDialog {
  Q_OBJECT

public:
  explicit Administrator(QWidget *parent = 0);
  ~Administrator();

  static QString genetateBaseInfoTooltip(Component baseInfo);
  static QString generateCpuTooltip(Cpu item);
  static QString generateMotherboardTooltip(Motherboard item);
  static QString generateRamTooltip(Ram item);
  static QString generateGpuTooltip(Gpu item);
  static QString generatePsuTooltip(Psu item);
  static QString generateDataStorageTooltip(DataStorage item);
  static QString generatePeripheralTooltip(Peripheral item);
  static QString generateCaseTooltip(Case item);
  static QString generateCoolerTooltip(Cooler item);
private:
  void fillComboBox(QList<QString> items);
  void fillPartsCatalog(Parts parts);
  void fillPartsFields(Parts part);
  void initGUI();
  void fillPartsBaseInfo(Component baseInfo);
  void itemHandlerBaseInfo();
  void fillPartsCatalogBaseInfo(Component baseInfo, QString toolTip);

  Component getComponentFromFields();
  Ui::Administrator *ui;
private slots:
  void itemHandler(int currIndex);
  void catalogTableSelectChanged();
  void addPart();
  void deletePart();
  void changePart();
};

#endif // ADMINISTRATOR_H
