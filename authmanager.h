#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H
#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QSettings>
class AuthManager : public QObject
{
    Q_OBJECT

public:
    explicit AuthManager(QObject *parent = nullptr);
    Q_INVOKABLE void saveTasks(const QStringList &tasks);
    Q_INVOKABLE QStringList loadTasks();
    Q_INVOKABLE bool registerUser(const QString &username, const QString &password);
    Q_INVOKABLE bool login(const QString &username, const QString &password);
    Q_INVOKABLE QString getCurrentUser();
private:
    QSettings settings;
    QString usersFile = "users.txt";
    QString currentUser;
};

#endif // AUTHMANAGER_H
