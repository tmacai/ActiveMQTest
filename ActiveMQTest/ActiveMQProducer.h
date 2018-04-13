#ifndef ACTIVEMQPRODUCER_H
#define ACTIVEMQPRODUCER_H
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <decaf/util/Random.h>

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;
#define  QUEUE_NAME	"test"
#define NAME_BYTE_LEN		16

class CActiveMQProducer:public Runnable
{
public:
	CActiveMQProducer(void);
	CActiveMQProducer(const CActiveMQProducer&);
	CActiveMQProducer& operator=(const CActiveMQProducer&);
	CActiveMQProducer(const std::string& brokerURI, int numMessages = 0, bool useTopic = false, bool sessionTransacted = false);

	~CActiveMQProducer(void);
private:
	Connection* connection;
	Session* session;
	Destination* destination;
	MessageProducer* producer;
	int numMessages;
	bool useTopic;
	bool sessionTransacted;
	std::string brokerURI;
	bool bReciveMessage;
	long waitMillis;

	void close();
	void waitUntilReady();

	virtual void run();
	// Called from the Producer since this class is a registered MessageListener.
	virtual void onMessage(const Message* message);
	// If something bad happens you see it here as this class is also been
	// registered as an ExceptionListener with the connection.
	virtual void onException(const CMSException& ex AMQCPP_UNUSED);
private:
	void cleanup();

public:
	int sendAMQMessage(char* szMsg,int nPriority = 0);

	int start(char* szBrokerUrl,char* szUsername,char* szPassword,char* szQueueName);
};

#endif // ACTIVEMQPRODUCER_H

