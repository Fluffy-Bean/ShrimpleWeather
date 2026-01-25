#pragma once

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QPointer>

class SearchBar : public QWidget
{
    Q_OBJECT

private:
    QPointer<QHBoxLayout> layout = nullptr;
    QPointer<QLineEdit>   searchBox = nullptr;
    QPointer<QPushButton> searchButton = nullptr;

public:
    SearchBar(QWidget* parent = nullptr);
    ~SearchBar();

private slots:
    void handleClick();

signals:
    void onSearch(QStringView query);
};
