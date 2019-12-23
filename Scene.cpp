#include "Scene.hpp"

#include "LogTrackSceneCameraManipulator.hpp"

#include "IChildMouseEventListener.hpp"

#include "utils.hpp"

#include <QQuickWindow>
#include <QtQuick/QSGSimpleRectNode>

namespace rogii
{
namespace qt_quick
{

namespace
{

using List = QList<QQuickItem *>;

// include the @a item itself
auto collectParents(QQuickItem * item)
{
    Q_ASSERT(item != nullptr);

    List parentList;
    // i believe this is enough in most cases
    parentList.reserve(16);

    QQuickItem * parent = item;
    do
    {
        parentList.append(parent);
        parent = parent->parentItem();
    }
    while (parent != nullptr);

    return parentList;
}

/** This class is monitoring all parent items of the specified item (@a parent in
 *      constructor) for x/y/width/height-changes. And also it monitors if some of
 *      an item in the parent chain has changed its parent.
 *
 * The class is required since NDC of the monitored item may change but its x/y/width/height
 * stay the same - these are specified in parent coordinates and wasn't changed if the
 * direct parent shifted/moved or some higher parent.
 *
 * Examine NDCWatcher guts for details.
 */
class NDCWatcher : public QObject
{
    Q_OBJECT

public:
    explicit NDCWatcher(QQuickItem * parent = nullptr)
        : QObject(parent)
        , parentItems(collectParents(parent))
    {
        connectTo(parentItems);
    }

    void connectTo(const List & parentList)
    {
        for (auto * item : parentList)
        {
            connect(item, &QQuickItem::parentChanged,
                    this, &NDCWatcher::onParentChanged);

            connect(item, &QQuickItem::xChanged,
                    this, &NDCWatcher::sceneItemPositionProbablyChanged);
            connect(item, &QQuickItem::yChanged,
                    this, &NDCWatcher::sceneItemPositionProbablyChanged);

            connect(item, &QQuickItem::widthChanged,
                    this, &NDCWatcher::sceneItemSizeProbablyChanged);
            connect(item, &QQuickItem::heightChanged,
                    this, &NDCWatcher::sceneItemSizeProbablyChanged);
        }
    }

Q_SIGNALS:
    void sceneItemPositionProbablyChanged();
    void sceneItemSizeProbablyChanged();

public Q_SLOTS:
    void onParentChanged(QQuickItem *)
    {
        auto * sender = QObject::sender();

        // find who signals
        List::iterator iterator = parentItems.begin();
        const auto endIterator = parentItems.end();
        for (; iterator != endIterator; ++iterator)
        {
            if (sender == *iterator)
                break;
        }

        Q_ASSERT(iterator != endIterator);

        QQuickItem * signallingItem = qobject_cast<QQuickItem *>(sender);

        // disconnects this from old parents
        // since they may still continue to live
        ++iterator;
        {
            for (auto iterator2 = iterator; iterator2 != endIterator; ++iterator2)
            {
                auto * oldParent = *iterator2;
                oldParent->disconnect(this);
            }
        }

        // remove these items from watched list
        parentItems.erase(iterator, endIterator);

        // construct new list of parents if any
        Q_ASSERT(signallingItem == parentItems.back());
        if (signallingItem->parentItem() == nullptr)
            return;

        auto newParents = collectParents(signallingItem->parentItem());
        connectTo(newParents);
        parentItems.append(newParents);
    }

private:
    List parentItems;
};

} // namespace anonymous

Scene::Scene(QQuickItem * parent)
    : QQuickItem(parent)
    , mCamera(*this)
    , mManipulator(mCamera)
    , mChildMouseEventListener(nullptr)
{
    connect(&mCamera, &SceneCamera::cameraChanged, this, &Scene::onCameraChanged);

    setAcceptedMouseButtons(Qt::AllButtons);
    setKeepMouseGrab(true);

    setFlag(ItemHasContents);
    setClip(true);

    // we don't need to connect this, sinc it get done by NDCWatcher
    connect(this, &QQuickItem::windowChanged, this, &Scene::onWindowChanged);

    auto * ndcWatcher = new NDCWatcher(this);
    connect(ndcWatcher, &NDCWatcher::sceneItemPositionProbablyChanged,
            this, &Scene::onSceneItemPositionChanged);
    connect(ndcWatcher, &NDCWatcher::sceneItemSizeProbablyChanged,
            this, &Scene::onSceneItemSizeChanged);
}

QTransform Scene::getCombinedMatrix() const
{
    return mCombinedMatrix;
}

const SceneCamera & Scene::getSceneCamera() const
{
    return mCamera;
}

SceneCamera &Scene::getSceneCamera()
{
    return mCamera;
}

void Scene::addItem(std::unique_ptr<SceneItem> item)
{
    item->setScene(this);

    mSceneItems.push_back(std::move(item));

    update();
}

void Scene::removeItem(SceneItem * item)
{
    auto index = std::find_if(mSceneItems.begin(),
                           mSceneItems.end(),
                           [item](const auto & itemPtr)
    {
        return itemPtr.get() == item;
    });

    if (index != mSceneItems.end())
        mSceneItems.erase(index);
}

void Scene::setChildMouseEventListener(IChildMouseEventListener * listener)
{
    mChildMouseEventListener = listener;
}

void Scene::geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry)
{
    correctCameraAfterViewportResize(newGeometry.size().toSize(), oldGeometry.size().toSize());
    updateFakeNdcMatrix();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

bool Scene::childMouseEventFilter(QQuickItem * item, QEvent * event)
{
    auto result(false);
    if (mChildMouseEventListener != nullptr)
        result = mChildMouseEventListener->childMouseEvent(item, event);

    if (!result)
        return QQuickItem::childMouseEventFilter(item, event);

    return true;
}

void Scene::onCameraChanged()
{
    updateCombinedMatrix();
}

void Scene::onSceneItemPositionChanged()
{
    updateFakeNdcMatrix();
}

void Scene::onSceneItemSizeChanged()
{
    updateFakeNdcMatrix();
}

void Scene::onWindowChanged()
{
    updateFakeNdcMatrix();
    updateWindow();
}

void Scene::onWindowSizeChanged()
{
    updateFakeNdcMatrix();
}

void Scene::correctCameraAfterViewportResize(const QSize & newSize, const QSize & oldSize)
{
    // TODO: take into account limits!

    const QPointF topLeftScenePoint(::rogii::qt_quick::mapToScene(oldSize,
                                                          mCamera.getInvertedViewProjectionMatrix(),
                                                          QPoint(0, 0)));
    const QPointF newBottomRightScenePoint(::rogii::qt_quick::mapToScene(oldSize,
                                                                 mCamera.getInvertedViewProjectionMatrix(),
                                                                 QPoint(newSize.width(), newSize.height())));

    LogTrackSceneCameraManipulator manipulator(mCamera);

    manipulator.showSceneArea(QRectF(topLeftScenePoint, newBottomRightScenePoint));
}

void Scene::updateFakeNdcMatrix()
{
    mFakeNdcMatrix.reset();

    if (window() == nullptr)
        return;

    if (window()->width() == 0 || window()->height() == 0)
        return;

    // If you ever need to support scene rotation and scaling,
    // it's important to remember that these operations are performed
    // relative to the QQuickItem::transformOrigin point
    {
        auto parentList(collectParents(this));
        for (auto * item : parentList)
        {
            Q_ASSERT(item->rotation() == 0);
            Q_ASSERT(item->scale() == 1);
        }
    }

//    QMatrix4x4 scaleMatrix;
//    scaleMatrix.scale(mSceneItem.width() / window->width(),
//                      mSceneItem.height() / window->height());

    const QRectF mappedRect(
                mapRectToScene(
                    QRectF(QPointF(0.5, 0.5),
                           QPointF(width() - 0.5, height() - 0.5))));

//    const QVector3D translateVector(2 * mappedRect.center().x() / window()->width() - 1,
//                                    - (2 * mappedRect.center().y() / window()->height() - 1),
//                                    0.0);

//    QMatrix4x4 translateMatrix;
//    translateMatrix.translate(translateVector);

//    mFakeNdcMatrix = translateMatrix * scaleMatrix;

//    mFakeNdcMatrix.translate(translateVector);
    mFakeNdcMatrix.translate(2 * mappedRect.center().x() / window()->width() - 1,
                             - (2 * mappedRect.center().y() / window()->height() - 1));
    mFakeNdcMatrix.scale(width() / window()->width(),
                         height() / window()->height());

    updateCombinedMatrix();
}

void Scene::updateCombinedMatrix()
{
    mCombinedMatrix = mCamera.getViewProjectionMatrix() * mFakeNdcMatrix;

    update();

    Q_EMIT(combinedMatrixChanged());
}

void Scene::updateWindow()
{
    disconnect(mWindowWidthChangedConnection);
    disconnect(mWindowHeightChangedConnection);

    if (window() == nullptr)
        return;

    mWindowWidthChangedConnection = connect(window(), &QQuickWindow::widthChanged,
                                            this, &Scene::onWindowSizeChanged);
    mWindowHeightChangedConnection = connect(window(), &QQuickWindow::heightChanged,
                                             this, &Scene::onWindowSizeChanged);

    updateFakeNdcMatrix();
}

} //~namespace qt_quick
} //~namespace rogii

#include "Scene.moc"
