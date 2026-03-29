#include "ui/page/TasksPage.h"
#include "ui/widget/TaskCard.h"
#include "ui/ClientState.h"
#include <QVBoxLayout>
#include <QPushButton>

TasksPage::TasksPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Back Button (similar to GroupChatPage)
    QPushButton* btnBack = new QPushButton("Back to Groups");
    connect(btnBack, &QPushButton::clicked, this, &TasksPage::backToGroupsRequested);
    mainLayout->addWidget(btnBack, 0, Qt::AlignLeft);

    // Group Box to contain the dynamic tasks
    group = new QGroupBox("Tasks");
    tasksLayout = new QVBoxLayout(group);

    mainLayout->addWidget(group);
}

void TasksPage::loadTasks(int groupId) {
    // 1. Clear existing tasks from the layout
    QLayoutItem* item;
    while ((item = tasksLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // 2. Fetch data from ClientState
    const StudyGroup* studyGroup = ClientState::getGroupById(groupId);
    if (!studyGroup) return;

    QString groupName = QString::fromStdString(studyGroup->getName());
    group->setTitle(groupName + " - Tasks");

    // 3. Render only the tasks for this group
    const std::vector<Task>& allTasks = ClientState::getTasks();
    for (const Task& t : allTasks) {
        if (t.getGroupId() == groupId) {
            tasksLayout->addWidget(new TaskCard(t, groupName));
        }
    }

    tasksLayout->addStretch();
}