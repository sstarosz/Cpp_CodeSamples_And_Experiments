#include <iostream>

#include <QApplication>
#include <QtWidgets>
#include <QHBoxLayout>

#include <QJsonObject>
#include <QJsonDocument>

#include <string>

void read(){
    QFile loadFile("save.json");

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject loadObject = loadDoc.object();

    if(loadObject.contains("name") && loadObject["name"].isString()){
        qDebug() << loadObject["name"].toString();
    }

}

void writeData(QJsonObject &json){
    QJsonObject days;   //should by a date string

    QString date;
    date = QDate::currentDate().toString("ddd dd MMMM, yyyy");

    QJsonArray CommonTask;
    CommonTask.append(QJsonObject{{"name","test"},
                                        {"status",true}});
    CommonTask.append(QJsonObject{{"name","test2"},
                                        {"status",false}});

    QJsonArray RepetTask;
    RepetTask.append(QJsonObject{{"name","test"},
                                       {"status",true},
                                       {"reapet",true}});

    RepetTask.append(QJsonObject{{"name","test2"},
                                       {"status",false},
                                       {"reapet",true}});

    QJsonObject day1;
    day1["CommonTask"] = CommonTask;
    day1["RepetTask"] = RepetTask;

    QJsonObject day2;
    QString date2 = QDate::currentDate().addDays(1).toString("ddd dd MMMM, yyyy");
    day2["CommonTask"] = CommonTask;
    day2["RepetTask"] = RepetTask;

    json[date] = day1;
    json[date2] = day2;
}

void write()  {

    QFile saveFile("save.json");

    if(!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject gameObject;
    writeData(gameObject);

//    gameObject["name"] = "test";
//    gameObject["level"] = "level";
//    gameObject["classType"] = "type";
//
//
//    QJsonArray testArray;
//    for(int i = 0; i < 10; ++i){
//        QJsonObject object;
//        std::string s = "array" + std::to_string(i);
//        object[s.c_str()] = i;
//        testArray.append(object);
//    }
//    gameObject["array"] = testArray;

    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
}




int main(int argc, char **argv) {

    write();
    read();
    QApplication a( argc, argv );

    QWidget mainApp;
    QHBoxLayout *mainAppLayout = new QHBoxLayout(&mainApp);

    QFile loadFile("save.json");

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open save file.");
    }

    mainAppLayout->addWidget(new QLabel(QString::fromStdString(loadFile.readAll().toStdString())));
    //mainAppLayout->addWidget(new QPushButton("test"));

    mainApp.setMinimumSize(800,800);
    mainApp.show();
    return a.exec();
}
