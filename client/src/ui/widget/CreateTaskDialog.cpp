#include "ui/widget/CreateTaskDialog.h"

CreateTaskDialog::CreateTaskDialog(QWidget* parent)
    : QDialog(parent) {

    setWindowTitle("Create Task");
    resize(300, 250);

    QFormLayout* layout = new QFormLayout(this);

    titleInput = new QLineEdit(this);
    tagInput = new QLineEdit(this);
    assignedToInput = new QLineEdit(this);
    groupIdInput = new QLineEdit(this);
    completedCheck = new QCheckBox("Completed", this);

    btnCreate = new QPushButton("Create", this);
    btnCancel = new QPushButton("Cancel", this);

    layout->addRow("Title:", titleInput);
    layout->addRow("Tag:", tagInput);
    layout->addRow("Assigned To ID:", assignedToInput);
    layout->addRow("Group ID:", groupIdInput);
    layout->addRow(completedCheck);
    layout->addRow(btnCreate, btnCancel);

    connect(btnCreate, &QPushButton::clicked, this, &CreateTaskDialog::handleCreate);
    connect(btnCancel, &QPushButton::clicked, this, &CreateTaskDialog::reject);
}

void CreateTaskDialog::handleCreate() {
    int id = rand();

    Task task(
        id,
        titleInput->text().toStdString(),
        tagInput->text().toStdString(),
        completedCheck->isChecked(),
        1,
        assignedToInput->text().toInt(),
        groupIdInput->text().toInt()
    );

    emit taskCreated(task);
    accept(); 
}