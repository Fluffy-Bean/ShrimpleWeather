#pragma once

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QList>
#include <QPointer>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>

class SavedLocations : public QScrollArea
{
    Q_OBJECT

private:
    QList<QPointer<QPushButton>> locationButtons = {};

public:
    SavedLocations(QWidget* parent = nullptr);
    ~SavedLocations();

private:
    QPointer<QPushButton> makeLocationButton(QWidget* parent, const QString& name);

signals:
    void onLocationSelect(QStringView query);
};
