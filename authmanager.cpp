#include "authmanager.h"
#include <QDebug>
#include <QTextStream>
#include <QStandardPaths>

AuthManager::AuthManager(QObject *parent)
    : QObject(parent),
    settings(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/settings.ini", QSettings::IniFormat),
    usersFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/users.txt")
{
    // Убедимся, что файл пользователей существует
    QFile file(usersFile);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        }
    }
}

bool AuthManager::registerUser(const QString &username, const QString &password) {
    qDebug() << "Файл пользователей:" << usersFile;
    qDebug() << "Файл существует:" << QFile::exists(usersFile);

    // Проверяем, существует ли логин
    QFile fileRead(usersFile);
    if (fileRead.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileRead);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(':');
            if (parts.size() == 2 && parts[0] == username) {
                fileRead.close();
                return false;
            }
        }
        fileRead.close();
    }

    // Добавляем нового пользователя
    QFile fileWrite(usersFile);
    if (fileWrite.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&fileWrite);
        out << username << ":" << password << "\n";
        fileWrite.close();
        return true;
    }
    return false;
}

bool AuthManager::login(const QString &username, const QString &password) {
    qDebug() << "Попытка входа:" << username;
    currentUser.clear();

    QFile file(usersFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() == 2 && parts[0] == username && parts[1] == password) {
            currentUser = username;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void AuthManager::saveTasks(const QStringList &tasks) {
    if (currentUser.isEmpty()) return;
    settings.beginGroup("Users/" + currentUser + "/Tasks");
    settings.setValue("count", tasks.size());
    for (int i = 0; i < tasks.size(); ++i) {
        settings.setValue(QString("task%1").arg(i), tasks[i]);
    }
    settings.endGroup();
}

QStringList AuthManager::loadTasks() {
    if (currentUser.isEmpty()) return {};
    QStringList tasks;
    settings.beginGroup("Users/" + currentUser + "/Tasks");
    int count = settings.value("count", 0).toInt();
    for (int i = 0; i < count; ++i) {
        tasks << settings.value(QString("task%1").arg(i)).toString();
    }
    settings.endGroup();
    return tasks;
}

QString AuthManager::getCurrentUser() {
    return currentUser;
}
