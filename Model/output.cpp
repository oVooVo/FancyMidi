#include <QDebug>
#include "output.h"
#include "queueinputport.h"
#include <QApplication>
#include <QThread>

Output::Output(QPoint position, Project* parent, QString name, QString infoText)
    :QueuedNode(position, parent, name, infoText)
{
    _inputs += new QueueInputPort(this, "", "Input A");
    _count = 0;
	_exactCount = -1;
}

void Output::frameArise(QueueInputPort* port, int id) {
	Q_ASSERT_X(QApplication::instance()->thread() != QThread::currentThread() || id >= _count, "previouse graph", "FramePackets with the same id arive.");
	_mutex.lock();
	if(id == _count) {
		do {
			QSharedPointer<Packet> packet = port->dequeuePacket(_count);
			if(!packet->isEndPacket()) {
				savePacket(packet);
				_count++;
			}
			else
			{
				finalize();
				if(!isComplete()) {
					_exactCount = _count;
					Q_ASSERT(isComplete());
					qDebug() << "End packet receved! The exactcount is:" << _count;
				}
				packet.clear();
				_count++;
			}
		} while(port->hasPacket(_count));
	}
	_mutex.unlock();
}

void Output::clear() {
    _count = 0;
	_exactCount = -1;
    QueuedNode::clear();
}
int Output::count() const {
    return _count;
}
bool Output::isComplete() {
	return _exactCount != -1;
}

void Output::finalize() {

}
int Output::exactCount() const {
	Q_ASSERT(_exactCount != -1);
	return _exactCount;
}