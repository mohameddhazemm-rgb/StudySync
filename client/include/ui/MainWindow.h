#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include "DataStructures.h"
#include "ui/ClientState.h"

#include "ui/page/DashboardPage.h"
#include "ui/page/TasksPage.h"
#include "ui/page/FocusPage.h"
#include "ui/page/GroupsPage.h"
#include "ui/page/GroupChatPage.h"
#include "ui/page/AiTutorPage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
private:
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;

    QWidget* sidebar;
    QPushButton* btnDashboard;
    QPushButton* btnFocus;
    QPushButton* btnGroups;
    QPushButton* btnAiTutor;
    QPushButton* btnLogout;

    QWidget* topbar;
    QLabel* topbarTitle;

    QStackedWidget* stackedWidget;
    DashboardPage* pageDashboard;
    TasksPage* pageTasks;
    FocusPage* pageFocus;
    GroupsPage* pageGroups;
    GroupChatPage* pageGroupChat;
    AiTutorPage* pageAiTutor;

    void setupUi();
    void setupSidebar();
    void setupTopbar();
    void connectSignals();

private slots:
    void switchPage();
};