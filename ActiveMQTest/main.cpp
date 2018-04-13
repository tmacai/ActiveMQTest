#include "activemqtest.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ActiveMQTest w;
	w.show();
	return a.exec();
}
