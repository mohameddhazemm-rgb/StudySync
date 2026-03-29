#include "ui/page/TasksPage.h"
#include "ui/widget/TaskCard.h"
#include "ui/ClientState.h"
#include <QVBoxLayout>
#include <QPushButton>

TasksPage::TasksPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QPushButton* btnBack = new QPushButton("Back to Groups");
    connect(btnBack, &QPushButton::clicked, this, &TasksPage::backToGroupsRequested);
    mainLayout->addWidget(btnBack, 0, Qt::AlignLeft);

    group = new QGroupBox("Tasks");
    tasksLayout = new QVBoxLayout(group);

    mainLayout->addWidget(group);
}

void TasksPage::loadTasks(int groupId) {
    QLayoutItem* item;
    while ((item = tasksLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    const StudyGroup* studyGroup = ClientState::getGroupById(groupId);
    if (!studyGroup) return;

    QString groupName = QString::fromStdString(studyGroup->getName());
    group->setTitle(groupName + " - Tasks");

    const std::vector<Task>& allTasks = ClientState::getTasks();
    for (const Task& t : allTasks) {
        if (t.getGroupId() == groupId) {
            tasksLayout->addWidget(new TaskCard(t, groupName));
        }
    }

    tasksLayout->addStretch();
}