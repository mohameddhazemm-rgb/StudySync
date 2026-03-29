#include "ui/page/GroupsPage.h"
#include "ui/widget/GroupCard.h"
#include "ui/ClientState.h" // Fetch groups from state
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <algorithm>

GroupsPage::GroupsPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->addStretch();
    headerLayout->addWidget(new QPushButton("Create Group"));

    QGridLayout* gridLayout = new QGridLayout();

    const std::vector<StudyGroup>& allGroups = ClientState::getStudyGroups();
    const User* user = ClientState::getUser();

    int row = 0;
    int col = 0;

    for (const StudyGroup& group : allGroups) {
        bool isPinned = false;
        if (user) {
            const auto& pinnedIds = user->getPinnedGroupIds();
            isPinned = std::find(pinnedIds.begin(), pinnedIds.end(), group.getId()) != pinnedIds.end();
        }

        GroupCard* card = new GroupCard(group, isPinned);

        connect(card, &GroupCard::openChatRequested, this, &GroupsPage::openGroupChatRequested);
        connect(card, &GroupCard::openTasksRequested, this, &GroupsPage::openGroupTasksRequested);

        gridLayout->addWidget(card, row, col);
        col++;
        if (col > 1) {
            col = 0;
            row++;
        }
    }

    gridLayout->setRowStretch(row + 1, 1);

    layout->addLayout(headerLayout);
    layout->addLayout(gridLayout);
}