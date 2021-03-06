#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>
#include <QHash>
#include <QMutex>
#include "types.h"
#include "QueryHit.h"

class CManagedSearch;
class G2Packet;
class CG2Node;

class CSearchManager : public QObject
{
    Q_OBJECT

public:
	QHash<QUuid,CManagedSearch*> m_lSearches;
    QMutex  m_pSection;
    quint32 m_nPruneCounter;
	quint32 m_nCookie;

public:
    CSearchManager(QObject *parent = 0);

    void OnTimer();

    void Add(CManagedSearch* pSearch);
    void Remove(CManagedSearch* pSearch);

    CManagedSearch* Find(QUuid& oGUID);

    // zwraca true jesli pakiet ma byc routowany
    bool OnQueryAcknowledge(G2Packet* pPacket, IPv4_ENDPOINT& addr, QUuid& oGUID);
	void OnQueryHit(G2Packet* pPacket, CG2Node* pNode = 0, IPv4_ENDPOINT* pEndpoint = 0);

signals:

public slots:

};

extern CSearchManager SearchManager;

#endif // SEARCHMANAGER_H
