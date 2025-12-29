#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QStandardPaths>

class AuthManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

    Q_INVOKABLE bool registerUser(const QString &username, const QString &password);
    Q_INVOKABLE bool login(const QString &username, const QString &password);
    Q_INVOKABLE void saveTasks(const QStringList &tasks);
    Q_INVOKABLE QStringList loadTasks();
    Q_INVOKABLE QString getCurrentUser();

private:
    QSettings settings;
    QString usersFile;
    QString currentUser;
};

#endif // AUTHMANAGER_H
