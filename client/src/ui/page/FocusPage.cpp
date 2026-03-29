#include "ui/page/FocusPage.h"
#include "ui/widget/TaskCard.h"
#include "ui/widget/GroupCard.h"
#include <iostream>
#include <QApplication>
#include <QFile>

FocusPage::FocusPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QGroupBox* group = new QGroupBox("Pomodoro Timer");
    QVBoxLayout* groupLayout = new QVBoxLayout(group);
    groupLayout->setAlignment(Qt::AlignCenter);

    QComboBox* taskSelect = new QComboBox();
    taskSelect->addItem("Review Cell Division Notes");

    QLabel* timerLabel = new QLabel("25:00");
    QFont timerFont = timerLabel->font();
    timerFont.setPointSize(48);
    timerLabel->setFont(timerFont);
    timerLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(new QPushButton("Start"));
    btnLayout->addWidget(new QPushButton("Pause"));
    btnLayout->addWidget(new QPushButton("Reset"));

    groupLayout->addWidget(taskSelect);
    groupLayout->addWidget(timerLabel);
    groupLayout->addLayout(btnLayout);

    layout->addWidget(group);
}
