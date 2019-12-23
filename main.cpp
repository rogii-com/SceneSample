#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>

#include "Scene.hpp"
#include "LogTrackSceneCameraManipulator.hpp"
#include "LineStrip.hpp"

class Helper : public QObject
{
    Q_OBJECT

public:
    enum Direction
    {
        Horizontal = 0x1,
        Vertical = 0x2
    };

    Q_DECLARE_FLAGS(Directions, Direction)

public:
    Helper(rogii::qt_quick::Scene * scene)
        : QObject(scene)
        , mScene(scene)
        , mFlags(Directions().setFlag(Horizontal).setFlag(Vertical))
    {
    }

    Directions & getFlags()
    {
        return mFlags;
    }

public Q_SLOTS:
    void onShift(double dx, double dy)
    {
        rogii::qt_quick::LogTrackSceneCameraManipulator m(mScene->getSceneCamera());

        const double trueDx = (mFlags.testFlag(Horizontal) ? dx : 0);
        const double trueDy = (mFlags.testFlag(Vertical) ? dy : 0);
        m.shift(trueDx, trueDy);
    }

    void onZoom(double step, QPointF pivot)
    {
        rogii::qt_quick::LogTrackSceneCameraManipulator m(mScene->getSceneCamera());

        const double trueX = (mFlags.testFlag(Horizontal) ? pivot.x() : 0);
        const double trueY = (mFlags.testFlag(Vertical) ? pivot.y() : 0);
        m.zoom(step, QPoint(trueX, trueY));
    }

private:
    rogii::qt_quick::Scene * mScene;
    Directions mFlags;
};

int main(int argc, char * argv[])
{
	QApplication::setAttribute(Qt::AA_UseOpenGLES);
	QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	QApplication app(argc, argv);

    qmlRegisterType<rogii::qt_quick::Scene>("ROGII.QtQuick", 1, 0, "Scene");
    qmlRegisterType<LineStrip>("ROGII.QtQuick", 1, 0, "LineStrip");

    QQuickView view;
    view.engine()->addImportPath(QCoreApplication::applicationDirPath() + QStringLiteral("/qml"));
    view.resize(800, 400);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///SceneSample/main.qml"));
    view.show();

    {
        auto * scene1 = view.rootObject()->findChild<rogii::qt_quick::Scene *>(QLatin1String("scene1"));
        auto * shiftArea = scene1->findChild<QQuickItem *>(QLatin1String("sceneMouseArea"));

        auto * h = new Helper(scene1);
        QObject::connect(shiftArea, SIGNAL(shift(double, double)),
                         h, SLOT(onShift(double, double)));
        QObject::connect(shiftArea, SIGNAL(zoom(double, QPointF)),
                         h, SLOT(onZoom(double, QPointF)));

        h->getFlags().setFlag(Helper::Horizontal, false);
    }
    {
        auto * scene = view.rootObject()->findChild<rogii::qt_quick::Scene *>(QLatin1String("scene2"));
        auto * shiftArea = scene->findChild<QQuickItem *>(QLatin1String("sceneMouseArea"));

        auto * h = new Helper(scene);
        QObject::connect(shiftArea, SIGNAL(shift(double, double)),
                         h, SLOT(onShift(double, double)));
        QObject::connect(shiftArea, SIGNAL(zoom(double, QPointF)),
                         h, SLOT(onZoom(double, QPointF)));

        h->getFlags().setFlag(Helper::Vertical, false);
    }
    {
        auto * scene = view.rootObject()->findChild<rogii::qt_quick::Scene *>(QLatin1String("scene3"));
        auto * shiftArea = scene->findChild<QQuickItem *>(QLatin1String("sceneMouseArea"));

        auto * h = new Helper(scene);
        QObject::connect(shiftArea, SIGNAL(shift(double, double)),
                         h, SLOT(onShift(double, double)));
        QObject::connect(shiftArea, SIGNAL(zoom(double, QPointF)),
                         h, SLOT(onZoom(double, QPointF)));
    }

    return app.exec();
}

#include "main.moc"
