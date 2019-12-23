#include "FlatColorSceneMaterial.hpp"

namespace rogii
{

namespace qt_quick
{

namespace
{

class Shader : public SceneShader
{
public:
    Shader()
        : mMatrixUniformId(-1)
        , mColorUniformId(-1)
    {
        setShaderSourceFile(QOpenGLShader::Vertex, QLatin1String(":/SceneSample/FlatColor.vert"));
        setShaderSourceFile(QOpenGLShader::Fragment, QLatin1String(":/SceneSample/FlatColor.frag"));
    }

    const char * const * attributeNames() const override
    {
        static char const *const names[] = { "vertex", nullptr };
        return names;
    }

    void initialize() override
    {
        // don't bind program - see comments to SceneShader
        QSGMaterialShader::initialize();
        mMatrixUniformId = program()->uniformLocation("matrix");
        mColorUniformId = program()->uniformLocation("color");
    }

    void updateState(const SceneRenderState & renderState, SceneMaterial * newMaterial, SceneMaterial * oldMaterial) override
    {
        const FlatColorSceneMaterial * m(static_cast<FlatColorSceneMaterial *>(newMaterial));

        program()->setUniformValue(mMatrixUniformId, renderState.getCombinedMatrix());
        program()->setUniformValue(mColorUniformId, m->getColor());
    }

private:
      int mMatrixUniformId;
      int mColorUniformId;
};

} //~anonymous namespace

FlatColorSceneMaterial::FlatColorSceneMaterial(const Scene & sceneItem)
    : SceneMaterial(sceneItem)
    , mColor(Qt::black)
{
}

FlatColorSceneMaterial::FlatColorSceneMaterial(const Scene & sceneItem, const QColor & color)
    : SceneMaterial(sceneItem)
    , mColor(color)
{
}

QSGMaterialType * FlatColorSceneMaterial::type() const
{
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader * FlatColorSceneMaterial::createShader() const
{
    return new Shader();
}

const QColor & FlatColorSceneMaterial::getColor() const
{
    return mColor;
}

void FlatColorSceneMaterial::setColor(const QColor & color)
{
    mColor = color;
}

} //~namespace qt_quick

} //~namespace rogii
