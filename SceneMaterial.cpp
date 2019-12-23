#include "SceneMaterial.hpp"

#include "Scene.hpp"

namespace rogii
{
namespace qt_quick
{

const QMatrix4x4 & SceneShader::SceneRenderState::getCombinedMatrix() const
{
    return mCombinedMatrix;
}

SceneShader::SceneRenderState::SceneRenderState(const SceneMaterial & material,
                                                const RenderState & renderState)
    : mMaterial(material)
    , mCombinedMatrix(mMaterial.getCombinedMatrix())
{
    // preserve coefficients for z: they are modified by Qt
    mCombinedMatrix(2, 2) = renderState.combinedMatrix()(2, 2);
    mCombinedMatrix(2, 3) = renderState.combinedMatrix()(2, 3);
}

SceneShader::SceneShader()
{
}

void SceneShader::updateState(const QSGMaterialShader::RenderState & state,
                              QSGMaterial * newMaterial,
                              QSGMaterial * oldMaterial)
{
    Q_ASSERT(program()->isLinked());

    SceneMaterial * newSceneMaterial(static_cast<SceneMaterial *>(newMaterial));
    SceneMaterial * oldSceneMaterial(static_cast<SceneMaterial *>(oldMaterial));
    SceneRenderState rs(*newSceneMaterial, state);

    updateState(rs, newSceneMaterial, oldSceneMaterial);
}

SceneMaterial::SceneMaterial(const Scene & scene)
    : mScene(scene)
    , mModelMatrix()
    , mCombinedMatrix()
{
    setFlag(QSGMaterial::RequiresFullMatrix);

    connect(&mScene, &Scene::combinedMatrixChanged, this, &SceneMaterial::onSceneCombinedMatrixChanged);
}

void SceneMaterial::setModelMatrix(const QTransform &m)
{
    mModelMatrix = m;
    updateOwnCombinedMatrix();
}

const Scene & SceneMaterial::getScene() const
{
    return mScene;
}

const QTransform & SceneMaterial::getCombinedMatrix() const
{
    return mCombinedMatrix;
}

void SceneMaterial::updateOwnCombinedMatrix()
{
    Q_ASSERT(flags().testFlag(QSGMaterial::RequiresFullMatrix));

    mCombinedMatrix = mModelMatrix * mScene.getCombinedMatrix();
}

void SceneMaterial::onSceneCombinedMatrixChanged()
{
    updateOwnCombinedMatrix();
}

} //~namespace qt_quick
} //~namespace rogii
