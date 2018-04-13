#include "activemqtest.h"


ActiveMQTest::ActiveMQTest(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.pbSend, SIGNAL(clicked()), this, SLOT(slotSend()));
	connect(ui.pbClear, SIGNAL(clicked()), this, SLOT(slotClear()));
	connect(ui.pbRead, SIGNAL(clicked()), this, SLOT(slotRead()));

	activemq::library::ActiveMQCPP::initializeLibrary();

	m_pActiveMQConsumer = new CActiveMQConsumer();
	connect(m_pActiveMQConsumer, SIGNAL(sigNewMessage(const QString)), this, SLOT(slotRecv(const QString)));
	m_pActiveMQConsumer->start("failover://(tcp://127.0.0.1:61616)", "admin", "admin", "Cy.Spxzrw");
	//m_pActiveMQConsumer->start("failover://(tcp://192.168.212.14:61616)", "ropeok", "ropeok2017@", "Cy.Spxzrw.jg");

	//m_pActiveMQProducer = new CActiveMQProducer();
	//m_pActiveMQProducer->start("failover://(tcp://127.0.0.1:61616)", "admin", "admin", "Cy.Spxzrw.jg");
	//m_pActiveMQProducer->start("failover://(tcp://192.168.212.14:61616)", "ropeok", "ropeok2017@", "Cy.Spxzrw");
}

ActiveMQTest::~ActiveMQTest()
{
	activemq::library::ActiveMQCPP::shutdownLibrary();  
}

void ActiveMQTest::slotSend()
{
	QString qstrTxt = ui.lEdtSend->text().trimmed();
	

	m_pActiveMQProducer->sendAMQMessage(qstrTxt.toAscii().data());

	//m_pActiveMQConsumer->readAMQMessage();
}

void ActiveMQTest::slotRecv(const QString qstrRecv)
{
	QString qstrMsg = ui.textEditRecv->toPlainText();
	qstrMsg.append("\n\n");
	qstrMsg.append(qstrRecv);

	ui.textEditRecv->setText(qstrMsg);
}

void ActiveMQTest::slotClear()
{
	ui.textEditRecv->clear();
}

void ActiveMQTest::slotRead()
{
	if (m_pActiveMQConsumer)
	{
		m_pActiveMQConsumer->readAMQMessage();
	}
}
