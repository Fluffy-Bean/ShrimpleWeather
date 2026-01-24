#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "search_bar.h"

SearchBar::SearchBar(QWidget* parent) : QWidget(parent)
{
    setObjectName("SearchBar");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setFixedHeight(100);

    layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(32, 32, 32, 32);
    layout->setSpacing(16);

    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("Brighton");

    searchButton = new QPushButton(this);
    searchButton->setFlat(true);
    searchButton->setText("Search");

    layout->addWidget(searchBox);
    layout->addWidget(searchButton);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(handleClick()));
}

SearchBar::~SearchBar()
{
}

void SearchBar::handleClick()
{
    QString query = searchBox->text();

    qDebug() << "Search query:" << query;
    emit onSearch(query);
}
