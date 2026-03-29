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

    // 1. Fetch data dynamically
    const std::vector<StudyGroup>& allGroups = ClientState::getStudyGroups();
    const User* user = ClientState::getUser();

    int row = 0;
    int col = 0;

    for (const StudyGroup& group : allGroups) {
        // 2. Check if the group is pinned by the user
        bool isPinned = false;
        if (user) {
            const auto& pinnedIds = user->getPinnedGroupIds();
            isPinned = std::find(pinnedIds.begin(), pinnedIds.end(), group.getId()) != pinnedIds.end();
        }

        // 3. Create card and wire up signals
        GroupCard* card = new GroupCard(group, isPinned);

        connect(card, &GroupCard::openChatRequested, this, &GroupsPage::openGroupChatRequested);
        connect(card, &GroupCard::openTasksRequested, this, &GroupsPage::openGroupTasksRequested);

        // 4. Arrange in a responsive grid
        gridLayout->addWidget(card, row, col);
        col++;
        if (col > 1) { // 2 cards per row
            col = 0;
            row++;
        }
    }

    // Push everything to the top
    gridLayout->setRowStretch(row + 1, 1);

    layout->addLayout(headerLayout);
    layout->addLayout(gridLayout);
}