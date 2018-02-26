#include "QtClass.h"
#include <QtMath>

QtClass::QtClass(QWidget *parent)
	: QWidget(parent)
{
	zapnutieKreslenia = 0;
	vyber_farby();
}


QtClass::~QtClass(){
}

void QtClass::newImage(int x, int y){
	obrazok = new QImage(x, y, QImage::Format_RGB32);
	obrazok->fill(Qt::white);

	update();
}

void QtClass::vyber_farby() {
	color = QColorDialog::getColor(Qt::magenta, this);
	qDebug() << color;

}

void QtClass::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *obrazok, area);
}

void QtClass::mousePressEvent(QMouseEvent *event) {
	QPainter painter(obrazok);
	painter.setPen(QPen(color, 3));

	if (event->button() == Qt::LeftButton && zapnutieKreslenia==0) {
		Point.push_back(event->pos());
		painter.drawPoint(event->pos());
		n++;
	}

	update();
}

void QtClass::mouseMoveEvent(QMouseEvent *event) {
	if (event->button() == Qt::RightButton && n >= 3) {
		posun(event->pos());
	}
}

void QtClass::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::RightButton && n >= 3) {
		posun(event->pos());
	}
}

void QtClass::wheelEvent(QWheelEvent *event) {
	if (n >= 3) {
		skalovanie(event->angleDelta());
	}
}

void QtClass::kresli_body() {
	QPainter painter(obrazok);
	painter.setPen(QPen(color, 3));

	for (int i = 0; i < n; i++)
		painter.drawPoint(Point[i].x(), Point[i].y());
	
	update();
}

void QtClass::kresli_spoje(){
	if (n < 3)
		qDebug() << "Malo bodov!";
	else {
		QPainter painter(obrazok);
		painter.setPen(QPen(color, 1));

		for (int i = 1; i <= n; i++) {
			if (i != n) {
				painter.drawLine(Point[i - 1].x(), Point[i - 1].y(), Point[i].x(), Point[i].y());
				}
			else {
				painter.drawLine(Point[i - 1].x(), Point[i - 1].y(), Point[0].x(), Point[0].y());
				}
		}
		zapnutieKreslenia = 1;
	}
	update();
}

void QtClass::kresli_ciaruPreklopenie() {
	QPainter painter(obrazok);
	painter.setPen(QPen(Qt::black, 1));

	painter.drawLine(Point[0].x() - 80, Point[0].y(), Point[0].x() + 80, Point[0].y());

	update();
}

void QtClass::vymaz(){
	n = 0;
	Point.clear();
	zapnutieKreslenia = 0;
}

void QtClass::vymaz_platno() {
	newImage(450,400);
	zapnutieKreslenia = 0;
}

void QtClass::rotaciaPSHR(double alfa) {
	double x1, y1,rozdielx,rozdiely;

	alfa = alfa*(M_PI/180);
	for (int i = 1; i < n; i++) {
		rozdielx = Point[i].x() - Point[0].x();
		rozdiely = Point[i].y() - Point[0].y();
		x1 = rozdielx *qCos(alfa) + rozdiely *qSin(alfa) + Point[0].x();
		y1 = -rozdielx *qSin(alfa) + rozdiely*qCos(alfa) + Point[0].y();
		Point[i].setX(x1);
		Point[i].setY(y1);
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();

}

void QtClass::rotaciaSHR(double alfa) {
	double x1, y1,rozdielx,rozdiely;

	alfa = alfa * (M_PI / 180);
	for (int i = 1; i < n; i++) {
		rozdielx = Point[i].x() - Point[0].x();
		rozdiely = Point[i].y() - Point[0].y();
		x1 = rozdielx*qCos(alfa) - rozdiely*qSin(alfa) + Point[0].x();
		y1 = rozdielx*qSin(alfa) + rozdiely*qCos(alfa) + Point[0].y();
		Point[i].setX(x1);
		Point[i].setY(y1);
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();

}

void QtClass::posun(QPoint &endPoint) {
	double x1, y1, rozdielx, rozdiely;

	for (int i = 1; i < n; i++) {
		rozdielx = Point[i].x() - Point[0].x();
		rozdiely = Point[i].y() - Point[0].y();
		Point[i].setX(rozdielx);
		Point[i].setY(rozdiely);
	}
	Point[0] = endPoint;

	for (int i = 1; i < n; i++) {
		Point[i].setX(Point[0].x() + Point[i].x());
		Point[i].setY(Point[0].y() + Point[i].y());
		beginPoint = endPoint;
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();
}

void QtClass::preklopenie() {
	double y;

	for (int i = 1; i < n; i++) {
		y= Point[0].y() - Point[i].y() + Point[0].y();
		Point[i].setY(y);
	}
	//vymaz_platno();
	kresli_ciaruPreklopenie();
	kresli_body();
	kresli_spoje();
}

void QtClass::skosenie(double x, double y) {
	double newx, newy,rozdielx,rozdiely;

	for (int i = 1; i <n; i++) {
		rozdielx =Point[i].x()-Point[0].x() ;
		rozdiely = Point[i].y() - Point[0].y();
		newx = Point[i].x()+x*rozdiely;
		newy = rozdielx*y+Point[i].y();
		Point[i].setX(newx);
		Point[i].setY(newy);
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();
	
}

void QtClass::skalovanie(double skala,int smer) {
	double newx, newy;

	if (smer == 0) {
		for (int i = 1; i < n; i++) {
			newx = ((Point[i].x() - Point[0].x())*skala + Point[0].x());
			newy = ((Point[i].y() - Point[0].y())*skala + Point[0].y());
			Point[i].setX(newx);
			Point[i].setY(newy);
		}
	}

	else{
		for (int i = 1; i < n; i++) {
			newx = ((Point[i].x() - Point[0].x())/skala + Point[0].x());
			newy = ((Point[i].y() - Point[0].y())/skala + Point[0].y());
			Point[i].setX(newx);
			Point[i].setY(newy);
		}
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();

}

void QtClass::skalovanie(double skala1, double skala2,int smer) {
	double newx, newy;

	if (smer == 0) {
		for (int i = 1; i < n; i++) {
			newx = ((Point[i].x() - Point[0].x())*skala1 + Point[0].x());
			newy = ((Point[i].y() - Point[0].y())*skala2 + Point[0].y());
			Point[i].setX(newx);
			Point[i].setY(newy);
		}
	}

	else {
		for (int i = 1; i < n; i++) {
			newx = ((Point[i].x() - Point[0].x()) / skala1 + Point[0].x());
			newy = ((Point[i].y() - Point[0].y()) / skala2 + Point[0].y());
			Point[i].setX(newx);
			Point[i].setY(newy);
		}
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();

}

void QtClass::skalovanie(QPoint &endPoint) {
	double newx, newy, parameter=1.3;
	
	if (endPoint.y()==120) {
		for (int i = 1; i < n; i++) {
			newx = ((Point[i].x() - Point[0].x())*parameter + Point[0].x());
			newy = ((Point[i].y() - Point[0].y())*parameter + Point[0].y());
			Point[i].setX(newx);
			Point[i].setY(newy);
		}
	}
	else {
		for (int i = 1; i < n; i++) {
			newx = ((Point[i].x() - Point[0].x())/parameter + Point[0].x());
			newy = ((Point[i].y() - Point[0].y())/parameter + Point[0].y());
			Point[i].setX(newx);
			Point[i].setY(newy);
		}
	}
	vymaz_platno();
	kresli_body();
	kresli_spoje();

}

void QtClass::SaveImg(QString menoSuboru)
{
	if (obrazok->save(menoSuboru, "png"))
		qDebug() << "Saved";
	else
		qDebug() << "Unsaved";
}