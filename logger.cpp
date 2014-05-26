#include "logger.h"

Logger* Logger::_singleton = new Logger();

Logger::Logger()
{
}

void Logger::emitNewLogMessage(QString message)
{
    emit newLogMessage(message);
}

void Logger::log(QString message)
{
#ifdef VERBOSE
    qDebug() << message;
#endif
    singleton()->emitNewLogMessage(message);

}
