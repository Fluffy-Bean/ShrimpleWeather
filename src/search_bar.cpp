#include "search_bar.h"

SearchBar::SearchBar(QWidget* parent) : QWidget(parent)
{
    setObjectName("SearchBar");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);

    layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);

    searchBox = new QLineEdit(this);
    searchBox->setObjectName("SearchBox");
    searchBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    searchBox->setPlaceholderText("Brighton");

    searchButton = new QPushButton(this);
    searchButton->setObjectName("SearchButton");
    searchButton->setFlat(true);
    searchButton->setText("Search");

    layout->addWidget(searchBox);
    layout->addWidget(searchButton);

    connect(searchButton, &QPushButton::clicked, this, &SearchBar::handleClick);
}

SearchBar::~SearchBar()
{
}

void SearchBar::handleClick()
{
    QString query = searchBox->text();
    emit onSearch(query);
}
