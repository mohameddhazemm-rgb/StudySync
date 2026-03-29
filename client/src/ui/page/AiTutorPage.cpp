#include "ui/page/AiTutorPage.h"
#include "ui/widget/TaskCard.h"
#include "ui/widget/GroupCard.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QGroupBox>
#include <QPushButton>

AiTutorPage::AiTutorPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QGroupBox* group = new QGroupBox("AI Study Tutor");
    QVBoxLayout* groupLayout = new QVBoxLayout(group);

    QTextEdit* chatHistory = new QTextEdit();
    chatHistory->setReadOnly(true);
    chatHistory->append("AI: Hello! I'm your AI Study Tutor. What subject are we tackling today?");

    QHBoxLayout* inputLayout = new QHBoxLayout();
    QLineEdit* chatInput = new QLineEdit();
    QPushButton* btnSend = new QPushButton("Send");
    inputLayout->addWidget(chatInput);
    inputLayout->addWidget(btnSend);

    groupLayout->addWidget(chatHistory);
    groupLayout->addLayout(inputLayout);

    layout->addWidget(group);
}
