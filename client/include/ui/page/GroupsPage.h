#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QWidget> // Fixed missing QWidget include
#include "DataStructures.h"

class GroupsPage : public QWidget {
    Q_OBJECT
public:
    GroupsPage(QWidget* parent = nullptr);
    signals:
        void openGroupChatRequested(int groupId);
    void openGroupTasksRequested(int groupId); // New signal
};