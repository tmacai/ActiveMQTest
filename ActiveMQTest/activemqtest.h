#ifndef ACTIVEMQTEST_H
#define ACTIVEMQTEST_H

#include <QtGui/QMainWindow>
#include "ui_activemqtest.h"

#include "ActiveMQProducer.h"
#include "ActiveMQConsumer.h"

class ActiveMQTest : public QMainWindow
{
	Q_OBJECT

public:
	ActiveMQTest(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ActiveMQTest();

	private slots:
		void slotSend();

		void slotRecv(const QString qstrRecv);

		void slotClear();

		void slotRead();

private:
	Ui::ActiveMQTestClass ui;

	CActiveMQProducer *m_pActiveMQProducer;
	CActiveMQConsumer *m_pActiveMQConsumer;
};

#endif // ACTIVEMQTEST_H
