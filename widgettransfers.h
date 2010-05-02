#ifndef WIDGETTRANSFERS_H
#define WIDGETTRANSFERS_H

#include <QWidget>
#include "widgetdownloads.h"
#include "widgetuploads.h"

namespace Ui {
    class WidgetTransfers;
}

class WidgetTransfers : public QWidget {
    Q_OBJECT
public:
    WidgetTransfers(QWidget *parent = 0);
    ~WidgetTransfers();
	WidgetDownloads *panelDownloads;
	WidgetUploads *panelUploads;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::WidgetTransfers *ui;
};

#endif // WIDGETTRANSFERS_H