#include <QDebug>
#include <QApplication>
#include <QThread>
#include <QThreadPool>
#include "queueinputport.h"
#include "queuednode.h"

QueueInputPort::QueueInputPort(Node* node, QString name, QString infoText):
    InputPort(node, name, infoText)
{
}

/* Pusht ein Frame in den InputPort des Zielnodes. Dieser speichert das Frame ab (threadsave) und benachrichtigt den Zielnode. */
void QueueInputPort::pushPacket(QSharedPointer<Packet> packet)
{
	// qDebug() << "A inputport of the node (" << _node->getPosition()->getX() << "," << _node->getPosition()->getY() << ") received frame" << frame->getData();
	_readWriteLock.lockForWrite();
    Q_ASSERT_X(!_hashMap.contains(packet->getId()), "caller", "Pushed the packet width the same id twice.");
	_hashMap.insert(packet->getId(), packet);
	_readWriteLock.unlock();
	((QueuedNode*)getNode())->frameArise(this, packet->getId());
}

bool QueueInputPort::hasPacket(int id)
{
	_readWriteLock.lockForRead();

	bool re = _hashMap.contains(id);
	_readWriteLock.unlock();
	return re;
}
QSharedPointer<Packet> QueueInputPort::dequeuePacket(int id)
{
	_readWriteLock.lockForWrite();    // Löscht ja auch noch!

	QSharedPointer<Packet> re = _hashMap.take(id);
	_readWriteLock.unlock();
	return re;
}

void QueueInputPort::clear() {
	Q_ASSERT_X(QThreadPool::globalInstance()->activeThreadCount() == 0, "clear", "Other worker threads running.");
	Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(), "clear", "called from a thread other than the main thread");
    _hashMap.clear();
}










//~ Formatted by Jindent --- http://www.jindent.com
