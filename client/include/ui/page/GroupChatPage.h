#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include "DataStructures.h"

class GroupChatPage : public QWidget {
    Q_OBJECT
public:
    GroupChatPage(QWidget* parent = nullptr);
    void loadChat(int groupId);

    signals:
        void backToGroupsRequested();

private:
    QGroupBox* group;
    QTextEdit* chatHistory;
    QLineEdit* chatInput;
    int currentGroupId;
};