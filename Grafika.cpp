#include "Grafika.h"

Grafika::Grafika(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidget(&this->widgetNaKreslenie);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);

	widgetNaKreslenie.newImage(650, 400); 
	ui.groupBox_otocenie->setEnabled(false);
	ui.groupBox_preklopenie->setEnabled(false);
	ui.groupBox_skosenie->setEnabled(false);
	ui.groupBox_skalovanie->setEnabled(false);
	
}

void Grafika::on_kresli_clicked() {
	
	if (widgetNaKreslenie.getN()>=3) {
		widgetNaKreslenie.kresli_spoje();
		ui.kresli->setEnabled(false);

		ui.groupBox_otocenie->setEnabled(true);
		ui.groupBox_preklopenie->setEnabled(true);
		ui.groupBox_skosenie->setEnabled(true);
		ui.parameter_skalovania2->setEnabled(true);
		ui.groupBox_skalovanie->setEnabled(true);
	}
	else {
		QMessageBox msgBox;
		msgBox.setText(QStringLiteral("Málo bodov!!"));
		msgBox.exec();
	}
}

void Grafika::on_vymaz_clicked() {
	widgetNaKreslenie.newImage(450, 400);
	widgetNaKreslenie.vymaz();


	ui.kresli->setEnabled(true);
	ui.groupBox_otocenie->setEnabled(false);
	ui.groupBox_preklopenie->setEnabled(false);
	ui.groupBox_skosenie->setEnabled(false);
	ui.groupBox_skalovanie->setEnabled(false);
}

void Grafika::on_smerHR_clicked(){
	double stupne=ui.stupne->value();
	
	widgetNaKreslenie.rotaciaSHR(stupne);
}

void Grafika::on_protismerHR_clicked() {
	double stupne = ui.stupne->value();
		
	widgetNaKreslenie.rotaciaPSHR(stupne);
}


void Grafika::on_preklopenie_clicked() {
	widgetNaKreslenie.preklopenie();
}

void Grafika::on_skos_clicked() {
	double x, y;
	x=ui.smer_x->value();
	y=ui.smer_y->value();
	
	widgetNaKreslenie.skosenie(x,y);
}

void Grafika::on_plus_clicked() {
	int typ = ui.typ->currentIndex();
	double skala = ui.parameterSkalovania->value();

	if (typ == 0)
		widgetNaKreslenie.skalovanie(skala,0);
	else {
		double skala2 = ui.parameter_skalovania2->value();
		widgetNaKreslenie.skalovanie(skala, skala2,0);
	}
}

void Grafika::on_minus_clicked() {
	int typ = ui.typ->currentIndex();
	double skala = ui.parameterSkalovania->value();

	if (typ == 0)
		widgetNaKreslenie.skalovanie(skala,1);
	else { 
		double skala2 = ui.parameter_skalovania2->value();
		widgetNaKreslenie.skalovanie(skala, skala2,1); }
}


void Grafika::on_actionSave_triggered()
{
	widgetNaKreslenie.SaveImg("GrafikaKreslenieCiary.png");
}

