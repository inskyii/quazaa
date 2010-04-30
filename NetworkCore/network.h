#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QMutex>
#include <QList>
#include "types.h"
#include "RateController.h"
#include "RouteTable.h"

class QTimer;
class CG2Node;
class QTcpSocket;
class CThread;
class G2Packet;

class QueryHashTable;   // przeniesc to w chuj!
class CManagedSearch;

// do przeniesienia w lepsze miejsce ;)
const quint16 LeafToHub = 10;
const quint16 HubToLeaf = 20;
const quint16 HubToHub = 3;
const quint32 ConnectFactor = 3;

class CNetwork : public QObject
{
    Q_OBJECT

public:    
    QMutex  m_pSection;

    QueryHashTable* m_pHashTable;   // przeniesc!

public:
    bool             m_bActive;
    QTimer*          m_pSecondTimer;
    G2NodeType       m_nNodeState;
    QList<CG2Node*>  m_lNodes;
    CRateController* m_pRateController;
    quint16          m_nHubsConnected;
    quint16          m_nLeavesConnected;
    bool             m_bNeedUpdateLNI;
    quint32          m_nLNIWait;
    quint32          m_nKHLWait;
    IPv4_ENDPOINT    m_oAddress;

    CRouteTable      m_oRoutingTable;
    quint32          m_tCleanRoutesNext;

public:
    CNetwork(QObject* parent = 0);
    ~CNetwork();

    void Connect();
    void Disconnect();
    void DisconnectAllNodes();

    void RemoveNode(CG2Node* pNode);
    bool NeedMore(G2NodeType nType);
    void OnAccept(QTcpSocket* pConn);

    void AcquireLocalAddress(QString& sHeader);
    bool IsListening();
    bool IsFirewalled();

    bool RoutePacket(QUuid& pTargetGUID, G2Packet* pPacket);
    bool RoutePacket(G2Packet* pPacket, CG2Node* pNbr = 0);

    inline bool isHub()
    {
        return (m_nNodeState == G2_HUB);
    }
    inline IPv4_ENDPOINT GetLocalAddress()
    {
        return m_oAddress;
    }

    inline quint32 UploadSpeed()
    {
        if( m_pRateController )
        {
            return m_pRateController->UploadSpeed();
        }
        return 0;
    }
    inline quint32 DownloadSpeed()
    {
        if( m_pRateController )
        {
            return m_pRateController->DownloadSpeed();
        }
        return 0;
    }

    QList<CG2Node*>* List(){ return &m_lNodes; }

    bool IsConnectedTo(IPv4_ENDPOINT addr);

public slots:
    void OnSecondTimer();

    void OnNodeStateChange();

    void SetupThread();
    void CleanupThread();

signals:
    void NodeAdded(CG2Node*);
    void NodeRemoved(CG2Node*);
    void NodeUpdated(CG2Node*);

    void changeThreadSignal(QThread* target);

protected:
    void Maintain();
    void DispatchKHL();
    void DropYoungest(G2NodeType nType, bool bCore = false);

    friend class CG2Node;
};

extern CNetwork Network;
extern CThread NetworkThread;
#endif // NETWORK_H