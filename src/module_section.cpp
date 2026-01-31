#include "module_section.h"

ModuleSection::ModuleSection(QWidget* parent) : QWidget(parent)
{
    setObjectName("ModuleSection");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setMaximumWidth(1000);

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);

    setLayout(layout);
}

ModuleSection::~ModuleSection()
{
}

void ModuleSection::addWidget(QPointer<QWidget> widget)
{
    layout->addWidget(widget);
}
