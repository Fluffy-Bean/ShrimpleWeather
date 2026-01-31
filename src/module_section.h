#pragma once

#include <QLayout>
#include <QPointer>
#include <QString>
#include <QWidget>

class ModuleSection : public QWidget
{
    Q_OBJECT

private:
    QPointer<QHBoxLayout> layout = nullptr;

public:
    ModuleSection(QWidget* parent = nullptr);
    ~ModuleSection();

    void addWidget(QPointer<QWidget> widget);
};
