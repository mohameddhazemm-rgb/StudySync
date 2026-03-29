#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include "DataStructures.h"

class TasksPage : public QWidget {
    Q_OBJECT
public:
    TasksPage(QWidget* parent = nullptr);

    // Call this to load a specific group's tasks dynamically
    void loadTasks(int groupId);

    signals:
        void backToGroupsRequested(); // Signal to return to GroupsPage

private:
    QVBoxLayout* tasksLayout;
    QGroupBox* group;
};