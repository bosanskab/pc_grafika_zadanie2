#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QtWidgets>
#include <QPainter>
#include <QColorDialog>

class QtClass : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
	QImage *obrazok;
	QColor color;
	QVector<QPoint> Point;
	QPoint beginPoint;
	int n = 0;
	bool zapnutieKreslenia=0;
public:
	QtClass(QWidget *parent = Q_NULLPTR); 
	~QtClass();
	void newImage(int x, int y);
	int getN() { return n; }
	void vyber_farby();
	void kresli_body();
	void kresli_spoje();
	void kresli_ciaruPreklopenie();
	void vymaz();
	void vymaz_platno();
	void rotaciaSHR(double stupne);
	void rotaciaPSHR(double stupne);
	void posun(QPoint &endPoint);
	void preklopenie();
	void skosenie(double x, double y);
	void skalovanie(double skala,int smer);
	void skalovanie(double skala1,double skala2,int smer);
	void skalovanie(QPoint &endPoint);
	void SaveImg(QString menoSuboru);
};
