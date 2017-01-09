#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    static Settings *getInstance();
    static QString makeAbsolutePath(const QUrl &url);
    static QString makeAbsolutePath(const QString &path);

protected:
    static Settings *self;
};

#endif // SETTINGS_H
