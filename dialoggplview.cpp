#include "dialoggplview.h"
#include "ui_dialoggplview.h"
#include "QSkinDialog/qskinsettings.h"
#include <QDesktopServices>

DialogGPLView::DialogGPLView(QWidget *parent) :
	QDialog(parent),
	m_ui(new Ui::DialogGPLView)
{
	m_ui->setupUi(this);
	connect(&skinSettings, SIGNAL(skinChanged()), this, SLOT(skinChangeEvent()));
	skinChangeEvent();
}

DialogGPLView::~DialogGPLView()
{
	delete m_ui;
}

void DialogGPLView::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void DialogGPLView::on_pushButtonOK_clicked()
{
	emit closed();
	close();
}

void DialogGPLView::on_textBrowserGPL_anchorClicked(QUrl link)
{
	QDesktopServices::openUrl(link);
}

void DialogGPLView::skinChangeEvent()
{
	m_ui->frameCommonHeader->setStyleSheet(skinSettings.dialogHeader);
}
