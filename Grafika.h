#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Grafika.h"
#include <QDebug>
#include "QtClass.h"

class Grafika : public QMainWindow
{
	Q_OBJECT

public:
	Grafika(QWidget *parent = Q_NULLPTR);
public slots:
	void on_actionSave_triggered();
	void on_kresli_clicked();
	void on_vymaz_clicked();
	void on_smerHR_clicked();
	void on_protismerHR_clicked();
	void on_preklopenie_clicked();
	void on_skos_clicked();
	void on_plus_clicked();
	void on_minus_clicked();
private:
	Ui::GrafikaClass ui;
	QtClass widgetNaKreslenie; 
};
