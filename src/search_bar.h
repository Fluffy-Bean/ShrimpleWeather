#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class SearchBar : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout* layout = nullptr;
    QLineEdit*   searchBox = nullptr;
    QPushButton* searchButton = nullptr;

public:
    SearchBar(QWidget* parent = nullptr);
    ~SearchBar();

signals:
    void onSearch(QStringView query);

private slots:
    void handleClick();
};
