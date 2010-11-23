#include <QtGui>
#include <QMouseEvent>

#include "scene.h"
#include "mainwindow.h"
#include <stdlib.h>
#include <qjson/parser.h>
#include <qjson/serializer.h>

scene::scene() : QWidget() , field(0,0,870,600), view(&field, this), poly(0), polys()
{
    view.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setOptimizationFlags(QGraphicsView::DontClipPainter
                              | QGraphicsView::DontSavePainterState
                              );
    view.setRenderHint(QPainter::Antialiasing);
    view.viewport()->setFocusProxy( this );

    lastx = 0;
    lasty = 0;
    poly = new QPolygon();
}


void scene::mousePressEvent(QMouseEvent *event) {
    qDebug("mouse pressed %d:%d" , event->pos().x(),event->pos().y() );
    int ax = event->pos().x();
    int ay = event->pos().y();
    qDebug("POLY_SIZE = %d" , poly->size());
    qDebug("POLYS_SIZE = %d" , polys.size());
    bool first_point_in_poly = false;
    if (lastx == 0) {
        first_point_in_poly = true;
        firstPoint = QPoint(ax,ay);
        poly->append(QPoint(ax,ay));
        field.addEllipse(ax-5,ay-5,10,10);
        lastx = ax;
        lasty = ay;
    }
    if ((abs(ax-firstPoint.x())<=5) && abs(ay-firstPoint.y())<=5) {
        if(!first_point_in_poly) {
            field.addLine(lastx,lasty,firstPoint.x(),firstPoint.y());
            poly->append(QPoint(firstPoint.x(),firstPoint.y()));
            addPoly(*poly);
            return;
        }

    }
    if (lastx != 0) {
        if(!first_point_in_poly) {
          first_point_in_poly = false;
          field.addLine(lastx,lasty,ax,ay);
          field.addEllipse(ax-5,ay-5,10,10);
          poly->append(QPoint(ax,ay));
        }
    }

    lastx = ax;
    lasty = ay;

}

void scene::addPoly(QPolygon &p) {
    polys.append(&p);
    poly = new QPolygon();

    lastx = 0;
    lasty = 0;
}


void scene::saveActualFile() {
    //QJson::Parser parser;
    QJson::Serializer serializer;

    QVariantList polygons;
    int polysIter = 0;
    foreach(QPolygon *p, polys) {       
        QList<QVariant> polygonElements;
        for(int i=0;i<p->size();i++) {
            QVariantMap point;

            qDebug("%d-%d",p->point(i).x(),p->point(i).y());
            point.insert("x",p->point(i).x());
            point.insert("y",p->point(i).y());

            polygonElements.insert(i,point);
        }

        polygons.insert(polysIter,polygonElements);
        polysIter++;
    }

    QByteArray json = serializer.serialize(polygons);
    qDebug() << json;

    QFile file(QString("%1/%2.dat").arg(path,fileName));
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << json;
}

void scene::setTrack(QString &trackFileName) {
    QPixmap pixmap(trackFileName);
    view.setBackgroundBrush(pixmap);
    view.resize(pixmap.size());
    field.setSceneRect(pixmap.rect());
    dynamic_cast<MainWindow*>(this->parent())->resize(pixmap.size());
    QFileInfo pathInfo( trackFileName );
    this->path = pathInfo.absolutePath();
    this->fileName = pathInfo.baseName();

}
