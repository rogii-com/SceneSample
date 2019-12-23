#pragma once

#include "SceneCamera.hpp"

#include <QSGMaterial>
#include <QSGMaterialShader>

namespace rogii
{
namespace qt_quick
{

class SceneMaterial;

/** Documentation says that in void QSGMaterialShader::initialize() the shader program
 * is not bound. Check docs for details.
 *      However the default OpenGL QtQuick-backend binds program before calling this
 * method. See sources for details: 'void QSGDefaultRenderContext::initializeShader'
 * in 5.9.6 qtdeclarative\src\quick\scenegraph\qsgdefaultrendercontext.cpp +275
 *      So we don't have to bind the program too.
 */
class SceneShader : public QSGMaterialShader
{
public:
    class SceneRenderState
    {
    public:
        const QMatrix4x4 & getCombinedMatrix() const;

    private:
        friend class SceneShader;
        friend class SceneMaterial;

    private:
        SceneRenderState(const SceneMaterial & material,
                         const RenderState & renderState);

        const SceneMaterial & mMaterial;
        QMatrix4x4 mCombinedMatrix;
    };

public:
    SceneShader();

    void updateState(const RenderState & state, QSGMaterial * newMaterial, QSGMaterial * oldMaterial) override;

    virtual void updateState(const SceneRenderState & renderState, SceneMaterial * newMaterial, SceneMaterial * oldMaterial) = 0;

public:
    SceneShader(const SceneShader &) = delete;
    SceneShader(SceneShader &&) = delete;

    SceneShader & operator=(const SceneShader &) = delete;
    SceneShader & operator=(SceneShader &&) = delete;
};

class SceneMaterial : public QObject, public QSGMaterial
{
    Q_OBJECT

public:
    SceneMaterial(const Scene & scene);

    void setModelMatrix(const QTransform & m);

    const Scene & getScene() const;

public:
    SceneMaterial(const SceneMaterial &) = delete;
    SceneMaterial(SceneMaterial &&) = delete;

    SceneMaterial & operator=(const SceneMaterial &) = delete;
    SceneMaterial & operator=(SceneMaterial &&) = delete;

private:
    friend class SceneShader::SceneRenderState;

    // Interface for SceneShader::SceneRenderState
    //@{
    const QTransform & getCombinedMatrix() const;
    //@}

private:
    void updateOwnCombinedMatrix();

private Q_SLOTS:
    void onSceneCombinedMatrixChanged();

private:
    const Scene & mScene;

    QTransform mModelMatrix;
    QTransform mCombinedMatrix;
};

} //~namespace qt_quick
} //~namespace rogii
