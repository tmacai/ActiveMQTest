#include "ActiveMQConsumer.h"

CActiveMQConsumer::CActiveMQConsumer(QObject *parent)
	:QObject(parent),
	latch(1),
	doneLatch(0),
	connection(NULL),
	session(NULL),
	destination(NULL),
	consumer(NULL),
	producer(NULL),
	waitMillis(3000),
	useTopic(false),
	sessionTransacted(false),
	brokerURI("")
{

}


CActiveMQConsumer::~CActiveMQConsumer(void)
{
	cleanup();
}

void CActiveMQConsumer::close()
{
	this->cleanup();
}
void CActiveMQConsumer::waitUntilReady() 
{
	latch.await();
}
int CActiveMQConsumer::start(char* szBrokerUrl,char* szUsername,char* szPassword,char* szQueueName)
{
	try 
	{
		// Create a ConnectionFactory
		auto_ptr<ConnectionFactory> connectionFactory(
			ConnectionFactory::createCMSConnectionFactory(szBrokerUrl));
		// Create a Connection
		connection = connectionFactory->createConnection(szUsername,szPassword);

		connection->start();
		connection->setExceptionListener(this);
		// Create a Session
		if (this->sessionTransacted == true) 
		{
			session = connection->createSession(Session::SESSION_TRANSACTED);
		} 
		else 
		{
			session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
		}
		// Create the destination (Topic or Queue)
		if (useTopic)
		{
			destination = session->createTopic(szQueueName);
		} 
		else 
		{
			destination = session->createQueue(szQueueName);
		}
		//producer = session->createProducer();
		//producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
		// Create a MessageConsumer from the Session to the Topic or Queue
		consumer = session->createConsumer(destination);
		consumer->setMessageListener(this);
	}
	catch (CMSException& e) 
	{
		printf("Consumer onException() CMS Exception occurred.  Shutting down client. \n" );
		// Indicate we are ready for messages.
		latch.countDown();
		e.printStackTrace();
		return 0;
	}
	return 1;
}
void CActiveMQConsumer::run()
{
	//try 
	//{
	//	// Create a ConnectionFactory
	//	auto_ptr<ConnectionFactory> connectionFactory(
	//		ConnectionFactory::createCMSConnectionFactory(brokerURI));
	//	// Create a Connection
	//	connection = connectionFactory->createConnection("lpt","lpt123");

	//	connection->start();
	//	connection->setExceptionListener(this);
	//	// Create a Session
	//	if (this->sessionTransacted == true) 
	//	{
	//		session = connection->createSession(Session::SESSION_TRANSACTED);
	//	} 
	//	else 
	//	{
	//		session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
	//	}
	//	// Create the destination (Topic or Queue)
	//	if (useTopic)
	//	{
	//		destination = session->createTopic(QUEUE_NAME);
	//	} 
	//	else 
	//	{
	//		destination = session->createQueue(QUEUE_NAME);
	//	}
	//	//producer = session->createProducer();
	//	//producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	//	// Create a MessageConsumer from the Session to the Topic or Queue
	//	consumer = session->createConsumer(destination);
	//	consumer->setMessageListener(this);
	//	std::cout.flush();
	//	std::cerr.flush();
	//	// Indicate we are ready for messages.
	//	latch.countDown();
	//	// Wait while asynchronous messages come in.
	//	doneLatch.await();
	//}
	//catch (CMSException& e) 
	//{
	//	printf("Consumer onException() CMS Exception occurred.  Shutting down client. \n" );
	//	// Indicate we are ready for messages.
	//	latch.countDown();
	//	e.printStackTrace();
	//}
}
// Called from the consumer since this class is a registered MessageListener.
void CActiveMQConsumer::onMessage(const Message* message)
{
	static int count = 0;
	try 
	{
		count++;
		// Create the Thread Id String
		string strReply="";
		const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);
		if(NULL==textMessage)
		{
			printf("NULL==textMessage", message->getCMSType().c_str());
			return;
		}
		//std::auto_ptr<TextMessage> responsemessage(session->createTextMessage(strReply));
		//responsemessage->setCMSCorrelationID(textMessage->getCMSCorrelationID());
		string text = "";
		if (textMessage != NULL)
		{
			text = textMessage->getText();
			//static char szTemp[64] = {0};
			//memset(szTemp,0,sizeof(szTemp));
			//strcpy(szTemp,text.c_str());
			QString strtemp = QString::fromStdString(text);
			emit sigNewMessage(strtemp);
		} 
		else 
		{
			text = "NOT A TEXTMESSAGE!";
		}
		int nProPerty=textMessage->getIntProperty("Integer");
		printf("consumer Message #%d Received: %s,nProPerty[%d]\n", count, text.c_str(),nProPerty);
		//const cms::Destination* destSend=textMessage->getCMSReplyTo();
	} 
	catch (CMSException& e) 
	{
		printf("Consumer onMessage() CMS Exception occurred.  Shutting down client. \n" );
		e.printStackTrace();
	}
	// Commit all messages.
	if (this->sessionTransacted) 
	{
		session->commit();
	}

	static int ntime = 0;
	if (1 == count)
	{
		ntime = GetTickCount();
		printf("consumer Message GetTickCount = %d\n", ntime);
	}
	else if (3000 == count)
	{
		//ntime = GetTickCount();
		count = 0;
		printf("consumer Message GetTickCount = %d\n", (GetTickCount() - ntime));
	}
	// No matter what, tag the count down latch until done.
	//doneLatch.countDown();
}
// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void CActiveMQConsumer::onException(const CMSException& ex AMQCPP_UNUSED)
{
	printf("Consumer onException() CMS Exception occurred.  Shutting down client. \n" );
	//printf("CMS Exception occurred.  Shutting down client.\n");
	ex.printStackTrace();
	exit(1);
}
void CActiveMQConsumer::cleanup()
{
	if (connection != NULL) 
	{
		try 
		{
			connection->close();
		} 
		catch (cms::CMSException& ex) 
		{
			ex.printStackTrace();
		}
	}
	// Destroy resources.
	try 
	{
		if (NULL != destination)
		{
			delete destination;
			destination = NULL;
		}
		if (NULL != consumer)
		{
			delete consumer;
			consumer = NULL;
		}
		if (NULL != session)
		{
			delete session;
			session = NULL;
		}
		if (NULL != connection)
		{
			delete connection;
			connection = NULL;
		}
	}
	catch (CMSException& e) 
	{
		e.printStackTrace();
	}
}

int CActiveMQConsumer::readAMQMessage()
{	
	string strReply="";
	const Message* message = consumer->receiveNoWait();
	const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);
	if(NULL==textMessage)
	{
		return 0;
	}
	string text = "";
	if (textMessage != NULL)
	{
		text = textMessage->getText();
		//static char szTemp[64] = {0};
		//memset(szTemp,0,sizeof(szTemp));
		//strcpy(szTemp,text.c_str());
		QString strtemp = QString::fromStdString(text);
		emit sigNewMessage(strtemp);
	} 
	else 
	{
		text = "NOT A TEXTMESSAGE!";
	}
	std::cout.flush();
	std::cerr.flush();
	return 1;
}