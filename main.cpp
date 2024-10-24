#include "Lab10.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon("D:\\Facultate\\Anul1\\Sem2\\Oop\\Lab\\Lab9\\Lab9\\pleading"));
	a.setApplicationDisplayName(QString::fromStdString("Trench Coats Manager"));

	Service service;
	GUI gui{ service };
	gui.show();

	return a.exec();
}
