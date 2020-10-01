#include <iostream>

#include <QApplication>
#include <QtWidgets>


int main(int argc, char **argv) {

    QApplication a( argc, argv );

    QPushButton hello( "Hello world!", 0 );
    hello.resize( 100, 30 );
    hello.show();
    std::cout << "Hello, World!" << std::endl;


    return a.exec();

    return 0;
}
