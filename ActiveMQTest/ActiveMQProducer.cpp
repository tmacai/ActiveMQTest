#include "ActiveMQProducer.h"


CActiveMQProducer::CActiveMQProducer():
connection(NULL),
session(NULL),
destination(NULL),
producer(NULL),
numMessages(0),
useTopic(false),
sessionTransacted(false),
brokerURI("")
{

}


CActiveMQProducer::~CActiveMQProducer(void)
{
	this->cleanup();
}


void CActiveMQProducer::close()
{
	this->cleanup();
}
void CActiveMQProducer::waitUntilReady()
{
	//latch.await();
}
int CActiveMQProducer::start(char* szBrokerUrl,char* szUsername,char* szPassword,char* szQueueName)
{

	try 
	{
		std::string brokerurl = szBrokerUrl;
		std::string username = szUsername;
		std::string password = szPassword;
		// Create a ConnectionFactory
		auto_ptr<ConnectionFactory> connectionFactory( ConnectionFactory::createCMSConnectionFactory( brokerurl ) );

		// Create a Connection
		connection = connectionFactory->createConnection(username,password);
		connection->start();
		// Create a Session
		if (this->sessionTransacted) 
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
		// Create a MessageProducer from the Session to the Topic or Queue
		producer = session->createProducer(destination);
		producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	}	
	catch (CMSException& e) 
	{
		printf("Producer run() CMSException \n" );
		// Indicate we are ready for messages.
		//latch.countDown();
		e.printStackTrace();
		return 0;
	}
	return 1;
}
void CActiveMQProducer::run() 
{
	//try {

	//	// Create a ConnectionFactory
	//	auto_ptr<ConnectionFactory> connectionFactory(
	//		ConnectionFactory::createCMSConnectionFactory(brokerURI));

	//	// Create a Connection
	//	connection = connectionFactory->createConnection();
	//	connection->start();

	//	// Create a Session
	//	if (this->sessionTransacted) {
	//		session = connection->createSession(Session::SESSION_TRANSACTED);
	//	}
	//	else {
	//		session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
	//	}

	//	// Create the destination (Topic or Queue)
	//	if (useTopic) {
	//		destination = session->createTopic("TEST.FOO");
	//	}
	//	else {
	//		destination = session->createQueue("TEST.FOO");
	//	}

	//	// Create a MessageProducer from the Session to the Topic or Queue
	//	producer = session->createProducer(destination);
	//	producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);

	//	// Create the Thread Id String
	//	string threadIdStr = Long::toString(Thread::currentThread()->getId());

	//	// Create a messages
	//	string text = (string) "Hello world! from thread " + threadIdStr;

	//	for (int ix = 0; ix < numMessages; ++ix) {
	//		std::auto_ptr<TextMessage> message(session->createTextMessage(text));
	//		message->setIntProperty("Integer", ix);
	//		printf("Sent message #%d from thread %s\n", ix + 1, threadIdStr.c_str());
	//		producer->send(message.get());
	//	}

	//}
	//catch (CMSException& e) {
	//	e.printStackTrace();
	//}
}
// Called from the Producer since this class is a registered MessageListener.
void CActiveMQProducer::onMessage(const Message* message) 
{
	static int count = 0;
	try 
	{
		count++;
		const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);
		//ActiveMQMessageTransformation
		//std::auto_ptr<TextMessage> responsemessage(session->createTextMessage());
		//responsemessage->setCMSCorrelationID(textMessage->getCMSCorrelationID());
		//responsemessage->getCMSReplyTo()
		string text = "";
		if (textMessage != NULL)
		{
			text = textMessage->getText();
		} 
		else
		{
			text = "NOT A TEXTMESSAGE!";
		}
		printf("Producer Message #%d Received: %s\n", count, text.c_str());
		//producer.send
	} 
	catch (CMSException& e)
	{
		printf("Producer onMessage() CMSException \n" );
		e.printStackTrace();
	}
	// Commit all messages.
	if (this->sessionTransacted)
	{
		session->commit();
	}
	// No matter what, tag the count down latch until done.
	//doneLatch.countDown();
}
// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void CActiveMQProducer::onException(const CMSException& ex AMQCPP_UNUSED)
{
	printf("Producer onException() CMS Exception occurred.  Shutting down client. \n" );
	ex.printStackTrace();
	exit(1);
}
void CActiveMQProducer::cleanup() 
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
		if (NULL != producer)
		{
			delete producer;
			producer = NULL;
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

int CActiveMQProducer::sendAMQMessage(char* szMsg,int nPriority)
{
	try
	{
		producer->setPriority(nPriority);

		// Create a messages
		string text = (string)szMsg;
		TextMessage* message = session->createTextMessage( text );   
		if (NULL != message)
		{
			message->setIntProperty("Integer", 0);
			producer->send(message);

			delete message;
			message = NULL;
		}
	}
	catch (CMSException& e)
	{
		printf("Producer sendAMQMessage() CMSException \n" );
		e.printStackTrace();
		return 0;
	}
	return 1;
}