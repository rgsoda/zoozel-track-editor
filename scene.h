#ifndef SCENE_H
#define SCENE_H
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

class scene : public QWidget
{
public:
    scene();
    QGraphicsScene * getScene();
public slots:
    void saveActualFile();
private:
    void mousePressEvent( QMouseEvent * event );
    void addPoly(QPolygon *poly);
    QGraphicsScene field;
    QGraphicsView view;
    qreal lastx;
    qreal lasty;
    QPoint firstPoint;
    QPolygon *poly;
    QList<QPolygon*> polys;

};

#endif // SCENE_H
