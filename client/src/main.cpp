#include <QApplication>
#include "ui/MainWindow.h"
#include "ClientNetworkManager.h"
#include <iostream>
#include "ui/ClientState.h"


int main(int argc, char* argv[]) {
    ClientNetworkManager api("127.0.0.1", "8080");
    ClientState::initDummyData();
    QApplication app(argc, argv);
    MainWindow::loadStylesheet(app);
    MainWindow w;
    w.show();

    api.setOnConnectCallback([&api, &w]() {
        std::cout << "Connected to server" << std::endl;
        std::cout << "testing tcp" << std::endl;
        api.ping([](bool success) {
            std::cout << "testing ping: " << (success ? "Success" : "Failed") << std::endl;
        });

        api.getTime([](std::string timeStr) {
            std::cout << timeStr << std::endl;
        });

        api.printString("Hello world", [](bool success) {
            std::cout << "Print string result: " << (success ? "Success" : "Failed") << std::endl;
        });
    });
    return app.exec();
}
