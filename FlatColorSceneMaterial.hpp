#pragma once

#include <QColor>

#include "SceneMaterial.hpp"

namespace rogii
{

namespace qt_quick
{

class FlatColorSceneMaterial final : public SceneMaterial
{
public:
    FlatColorSceneMaterial(const Scene & sceneItem);
    FlatColorSceneMaterial(const Scene & sceneItem, const QColor & color);

    // SceneMaterial implementation
    //@{
    QSGMaterialType * type() const override;
    QSGMaterialShader * createShader() const override;
    //@}

    const QColor & getColor() const;
    void setColor(const QColor & color);

public:
    FlatColorSceneMaterial(const FlatColorSceneMaterial &) = delete;
    FlatColorSceneMaterial(FlatColorSceneMaterial &&) = delete;

    FlatColorSceneMaterial & operator=(const FlatColorSceneMaterial &) = delete;
    FlatColorSceneMaterial & operator=(FlatColorSceneMaterial &&) = delete;

private:
    QColor mColor;
};

} //~namespace qt_quick

} //~namespace rogii
