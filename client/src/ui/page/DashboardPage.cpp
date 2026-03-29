#include "ui/page/DashboardPage.h"
#include "ui/widget/TaskCard.h"
#include "ui/widget/GroupCard.h"
#include "ui/ClientState.h" // Ensure ClientState is included
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QGroupBox>
#include <QPushButton>

DashboardPage::DashboardPage(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);

    QWidget* leftCol = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftCol);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    QGroupBox* welcomeGroup = new QGroupBox("Welcome");
    QVBoxLayout* wLayout = new QVBoxLayout(welcomeGroup);

    const User* user = ClientState::getUser();
    QString username = user ? QString::fromStdString(user->getUsername()) : "Student";
    QLabel* wSub = new QLabel("Welcome back, " + username + "!\nYou have tasks pending.");

    QPushButton* wBtn = new QPushButton("Start Focus Session");
    connect(wBtn, &QPushButton::clicked, this, &DashboardPage::startFocusRequested);
    wLayout->addWidget(wSub);
    wLayout->addWidget(wBtn);

    QGroupBox* tasksGroup = new QGroupBox("Tasks Due Today");
    QVBoxLayout* tLayout = new QVBoxLayout(tasksGroup);

    const std::vector<Task>& allTasks = ClientState::getTasks();
    for (const Task& task : allTasks) {
        QString groupName = "Personal";
        const StudyGroup* group = ClientState::getGroupById(task.getGroupId());
        if (group) {
            groupName = QString::fromStdString(group->getName());
        }
        tLayout->addWidget(new TaskCard(task, groupName));
    }
    tLayout->addStretch();

    leftLayout->addWidget(welcomeGroup);
    leftLayout->addWidget(tasksGroup);

    QGroupBox* rightCol = new QGroupBox("Pinned Groups");
    pinnedGroupsLayout = new QVBoxLayout(rightCol);
    refreshPinnedGroups();

    layout->addWidget(leftCol);
    layout->addWidget(rightCol);

    layout->setStretch(0, 2);
    layout->setStretch(1, 1);
}

void DashboardPage::refreshPinnedGroups() {
    QLayoutItem* item;
    while ((item = pinnedGroupsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
    const std::vector<StudyGroup>& allGroups = ClientState::getStudyGroups();
    for (const StudyGroup& group : allGroups) {
        if (!ClientState::isGroupPinned(group.getId()))
            continue;
        GroupCard* pinnedCard = new GroupCard(group, true);
        connect(pinnedCard, &GroupCard::openChatRequested, this, &DashboardPage::openGroupChatRequested);
        connect(pinnedCard, &GroupCard::openTasksRequested, this, &DashboardPage::openGroupTasksRequested);
        connect(pinnedCard, &GroupCard::pinStateChanged, this, &DashboardPage::refreshPinnedGroups);
        pinnedGroupsLayout->addWidget(pinnedCard);
    }
    pinnedGroupsLayout->addStretch();
}