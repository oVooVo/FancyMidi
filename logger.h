#ifndef LOGGER_H
#define LOGGER_H

#include "QObject"

class Logger : public QObject
{
    Q_OBJECT
private:
    Logger();
    static Logger* _singleton;
    void emitNewLogMessage(QString message);
public:
    static void log(QString message);
    static Logger* singleton() { return _singleton; }

signals:
    void newLogMessage(QString);
};

#endif // LOGGER_H
