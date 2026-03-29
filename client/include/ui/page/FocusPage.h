#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QFrame>
#include "DataStructures.h"


class FocusPage : public QWidget {
    Q_OBJECT
public:
    FocusPage(QWidget* parent = nullptr);
};
