#pragma once

#include <memory>

#include <QQuickItem>

#include "SceneCamera.hpp"
#include "SceneItem.hpp"
#include "LogTrackSceneCameraManipulator.hpp"

namespace rogii
{
namespace qt_quick
{

class IChildMouseEventListener;

class Scene : public QQuickItem
{
    Q_OBJECT

public:
    explicit Scene(QQuickItem * parent = nullptr);

    QTransform getCombinedMatrix() const;
    const SceneCamera & getSceneCamera() const;
    SceneCamera & getSceneCamera();

    void addItem(std::unique_ptr<SceneItem> item);
    void removeItem(SceneItem * item);

    void setChildMouseEventListener(IChildMouseEventListener * listener);

public:
    Scene(const Scene &) = delete;
    Scene(Scene &&) = delete;

    Scene & operator=(const Scene &) = delete;
    Scene & operator=(Scene &&) = delete;

Q_SIGNALS:
    void combinedMatrixChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    bool childMouseEventFilter(QQuickItem * item, QEvent * event) override;

private Q_SLOTS:
    void onCameraChanged();

    void onSceneItemPositionChanged();
    void onSceneItemSizeChanged();
    void onWindowChanged();
    void onWindowSizeChanged();

private:
    void correctCameraAfterViewportResize(const QSize & newSize, const QSize & oldSize);

    void updateFakeNdcMatrix();
    void updateCombinedMatrix();

    void updateWindow();

public:
    SceneCamera mCamera;
    LogTrackSceneCameraManipulator mManipulator;

    QTransform mFakeNdcMatrix;
    QTransform mCombinedMatrix;

    QMetaObject::Connection mWindowWidthChangedConnection;
    QMetaObject::Connection mWindowHeightChangedConnection;

    std::vector<std::unique_ptr<SceneItem>> mSceneItems;

    IChildMouseEventListener * mChildMouseEventListener;
};

} //~namespace qt_quick
} //~namespace rogii

