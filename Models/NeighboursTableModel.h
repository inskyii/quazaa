#ifndef NEIGHBOURSTABLEMODELL_H
#define NEIGHBOURSTABLEMODELL_H

#include <QAbstractTableModel>
#include "types.h"
#include <QList>
#include <QTime>

class CG2Node;

typedef struct
{
    CG2Node*    pNode;
    G2NodeType  nType;
    int         nState;
    quint32     tConnected;
    quint32     nPacketsIn;
    quint32     nPacketsOut;
    quint32     nBandwidthIn;
    quint32     nBandwidthOut;
    quint64     nBytesSent;
    quint64     nBytesReceived;
    float       nCompressionIn;
    float       nCompressionOut;
    quint32     nLeafCount;
    quint32     nLeafMax;
    quint32     nRTT;
    QString     sUserAgent;
	QString		sCountry;
} sNeighbour;

class CNeighboursTableModel : public QAbstractTableModel
{
    Q_OBJECT

protected:
    QList<sNeighbour>   m_lNodes;
public:
    explicit CNeighboursTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    QList<sNeighbour>* GetList()
    {
        return &m_lNodes;
    }


protected:
    QString StateToString(int s) const;
    QString TypeToString(G2NodeType t) const;
signals:

public slots:
    void OnNodeAdded(CG2Node* pNode);
    void UpdateNeighbourData(CG2Node* pNode);
    void OnRemoveNode(CG2Node* pNode);
    void UpdateAll();
};

#endif // NEIGHBOURSTABLEMODELL_H
