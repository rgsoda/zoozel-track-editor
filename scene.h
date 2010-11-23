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
    void setTrack(QString &trackFileName);
public slots:
    void saveActualFile();
private:
    void mousePressEvent( QMouseEvent * event );
    void addPoly(QPolygon &poly);
    QString path;
    QString fileName;
    QGraphicsScene field;
    QGraphicsView view;
    qreal lastx;
    qreal lasty;
    QPoint firstPoint;
    QPolygon * poly;
    QList<QPolygon*> polys;

};

#endif // SCENE_H
