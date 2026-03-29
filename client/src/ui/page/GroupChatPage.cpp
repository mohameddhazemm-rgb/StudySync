#include "ui/page/GroupChatPage.h"
#include "ui/ClientState.h"
#include <iostream>
#include <QPushButton>

GroupChatPage::GroupChatPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Back button
    QPushButton* btnBack = new QPushButton("Back to Groups");
    connect(btnBack, &QPushButton::clicked, this, &GroupChatPage::backToGroupsRequested);
    mainLayout->addWidget(btnBack, 0, Qt::AlignLeft);

    group = new QGroupBox("Chat");
    QVBoxLayout* groupLayout = new QVBoxLayout(group);

    chatHistory = new QTextEdit();
    chatHistory->setReadOnly(true);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    chatInput = new QLineEdit();
    QPushButton* btnSend = new QPushButton("Send");
    inputLayout->addWidget(chatInput);
    inputLayout->addWidget(btnSend);

    groupLayout->addWidget(chatHistory);
    groupLayout->addLayout(inputLayout);
    connect(btnSend, &QPushButton::clicked, this, [this]() {
        QString text = chatInput->text();
        if (text.isEmpty()) return;
        ClientState::mockSendMessage(currentGroupId, text.toStdString());
        chatInput->clear();
        loadChat(currentGroupId);
    });

    mainLayout->addWidget(group);
}

void GroupChatPage::loadChat(int groupId) {
    currentGroupId = groupId;
    chatHistory->clear();

    const StudyGroup* studyGroup = ClientState::getGroupById(groupId);
    if (!studyGroup) {
        group->setTitle("Unknown Group - Chat");
        return;
    }
    group->setTitle(QString::fromStdString(studyGroup->getName()) + " - Chat");
    const User* currentUser = ClientState::getUser();
    int myId = currentUser ? currentUser->getId() : -1;

    for (const Message& msg : studyGroup->getMessages()) {
        QString senderName = (msg.getUserId() == myId) ? "Me" : "User " + QString::number(msg.getUserId());
        QString chatLine = senderName + ": " + QString::fromStdString(msg.getText());
        chatHistory->append(chatLine);
    }
}