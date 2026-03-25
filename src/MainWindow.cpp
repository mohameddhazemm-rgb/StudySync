#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout;
    centralWidget->setLayout(layout);

    label = new QLabel("Study planner", centralWidget);
    button = new QPushButton("Click to exit", centralWidget);

    layout->addWidget(label);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &MainWindow::close);
}