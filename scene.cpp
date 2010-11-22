#include <QtGui>
#include <QMouseEvent>

#include "scene.h"
#include "mainwindow.h"
#include <stdlib.h>
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
    view.setBackgroundBrush(QPixmap("images/track.jpg"));
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
            addPoly(poly);
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

void scene::addPoly(QPolygon *poly) {
    polys.append(poly);
    poly = new QPolygon();
    lastx = 0;
    lasty = 0;
}


void scene::saveActualFile() {
    foreach(QPolygon *p, polys) {
        qDebug("POLY SIZE = %d",p->size());
        for(int i=0;i<p->size();i++) {
            qDebug("%d-%d",p->point(i).x(),p->point(i).y());
        }


    }
}
