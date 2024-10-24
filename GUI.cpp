#include "GUI.h"
#include "CartModelView.h"
#include <warning.h>
#include <qmessagebox.h>
#include <qshortcut.h>
#include <QTableView>
#include <QDialog>
#include <qheaderview.h>
#include <QVBoxLayout>

GUI::GUI(Service service, QWidget *parent)
	: QWidget(parent), service(service)
{
	ui.setupUi(this);
	this->populateList();
	this->connectSignalsAndSlots();
}

GUI::~GUI()
{
	delete this->modelCart;
}


void GUI::populateList()
{
	this->ui.trenchList->clear();
	QColor pink(255, 123, 184);
	QBrush brush(pink);

	for (auto i : this->service.returnRepository().all_objects())
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(i.getSize() + " - " + i.getColour() + ", Cost: " + std::to_string(static_cast<int>(i.getPrice())) + ", Qt: " + std::to_string(i.getQuantity())) };
		QFont font{ "Comic Sans MS", 12, 10 };
		item->setFont(font);
		item->setBackground(brush);
		this->ui.trenchList->addItem(item);
	}
}


void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->ui.trenchList, &QListWidget::itemClicked, this, &GUI::itemClickedHandler);

	QObject::connect(this->ui.trenchList, &QListWidget::itemDoubleClicked, this, &GUI::itemDoubleClickedHandler);

	QObject::connect(this->ui.shoppingList, &QListWidget::itemDoubleClicked, this, &GUI::itemDoubleClickedHandler2);

	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);

	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);

	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);
	
	QObject::connect(this->ui.filterEdit, &QLineEdit::textChanged, this, &GUI::filterLineEditHandler);

	QObject::connect(this->ui.buyButton, &QPushButton::clicked, this, &GUI::addToCart);

	QObject::connect(this->ui.csvButton, &QPushButton::clicked, this, &GUI::openCSV);

	QObject::connect(this->ui.htmlButton, &QPushButton::clicked, this, &GUI::openHTML);

	QObject::connect(this->ui.graphButton, &QPushButton::clicked, this, &GUI::graphButtonHandler);

	QObject::connect(this->ui.undoButton, &QPushButton::clicked, this, &GUI::undoHandler);

	QObject::connect(this->ui.redoButton, &QPushButton::clicked, this, &GUI::redoHandler);

	QObject::connect(this->ui.tableButton, &QPushButton::clicked, this, &GUI::modelHandler);

	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &GUI::undoHandler);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &GUI::redoHandler);
}


int GUI::getSelectedIndex()
{
	QModelIndexList index = this->ui.trenchList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
		return -1;

	int idx = index.at(0).row();
	return idx;
}


int GUI::getSelectedIndex2()
{
	QModelIndexList index = this->ui.shoppingList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
		return -1;

	int idx = index.at(0).row();
	return idx;
}


void GUI::itemClickedHandler()
{
	int row = this->getSelectedIndex();
	if (row == -1)
	{
		this->ui.sizeEdit->clear();
		this->ui.colourEdit->clear();
		this->ui.priceEdit->clear();
		this->ui.quantityEdit->clear();
		this->ui.linkEdit->clear();
		return;
	}

	TrenchCoat t = this->service.returnRepository().all_objects()[row];
	this->ui.sizeEdit->setText(QString::fromStdString(t.getSize()));
	this->ui.colourEdit->setText(QString::fromStdString(t.getColour()));
	this->ui.priceEdit->setText(QString::fromStdString(std::to_string(static_cast<int>(t.getPrice()))));
	this->ui.quantityEdit->setText(QString::fromStdString(std::to_string(t.getQuantity())));
	this->ui.linkEdit->setText(QString::fromStdString(t.getPhoto()));

}


void GUI::itemDoubleClickedHandler()
{
	int row = this->getSelectedIndex();
	if (row != -1) {
		TrenchCoat t = this->service.returnRepository().all_objects()[row];

		this->openLink(t.getPhoto());
	}
}


void GUI::itemDoubleClickedHandler2()
{
	int row = this->getSelectedIndex2();
	if (row != -1) {
		TrenchCoat t = this->csvCart.returnCart()[row];

		this->openLink(t.getPhoto());
	}
}


void GUI::populateCart()
{
	this->ui.shoppingList->clear();
	QColor pink(255, 123, 184);
	QBrush brush(pink);

	for (auto i : this->csvCart.returnCart())
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(i.getSize() + " - " + i.getColour() + ", Cost: " + std::to_string(static_cast<int>(i.getPrice())) + ", Qt: " + std::to_string(i.getQuantity())) };
		QFont font{ "Comic Sans MS", 12, 10 };
		item->setFont(font);
		item->setBackground(brush);
		this->ui.shoppingList->addItem(item);
	}
}


void GUI::deleteButtonHandler()
{
	int row = this->getSelectedIndex();
	if (row == -1) {
		QMessageBox::warning(nullptr, "Error", "Select a trench coat to delete first!");
		return;
	}

	this->service.remove_from_repository(this->service.returnRepository()[row].getPrice(), this->service.returnRepository()[row].getColour());
	this->populateList();
}


void GUI::addButtonHandler()
{
	std::string size = this->ui.sizeEdit->text().toStdString();
	std::string colour = this->ui.colourEdit->text().toStdString();
	std::string price = this->ui.priceEdit->text().toStdString();
	std::string quantity = this->ui.quantityEdit->text().toStdString();
	std::string link = this->ui.linkEdit->text().toStdString();

	try {
		this->validator.validateStringData(price, quantity);
	}
	catch (std::exception& e) {
		QMessageBox::warning(nullptr, "Error", "Invalid trench coat!");
		return;
	}

	float price2 = stof(price);
	int quantity2 = stoi(quantity);
	TrenchCoat t = TrenchCoat(size, colour, price2, quantity2, link);

	try {
		this->validator.validateTrench(t);
	}
	catch (std::exception& e) {
		QMessageBox::warning(nullptr, "Error", "Invalid trench coat!");
		return;
	}

	this->service.add_to_repository(t);
	this->populateList();
}


void GUI::updateButtonHandler()
{
	int row = this->getSelectedIndex();
	if (row == -1) {
		QMessageBox::warning(nullptr, "Error", "Select a trench coat to update first!");
		return;
	}

	std::string size = this->ui.sizeEdit->text().toStdString();
	std::string colour = this->ui.colourEdit->text().toStdString();
	std::string price = this->ui.priceEdit->text().toStdString();
	std::string quantity = this->ui.quantityEdit->text().toStdString();
	std::string link = this->ui.linkEdit->text().toStdString();

	try {
		this->validator.validateStringData(price, quantity);
	}
	catch (std::exception& e) {
		QMessageBox::warning(nullptr, "Error", "Invalid trench coat!");
		return;
	}

	float price2 = stof(price);
	int quantity2 = stoi(quantity);
	TrenchCoat t = TrenchCoat(size, colour, price2, quantity2, link);

	this->service.update_from_repository(this->service.returnRepository()[row].getPrice(), this->service.returnRepository()[row].getColour(), t);
	this->populateList();
}


void GUI::filterLineEditHandler()
{
	this->ui.trenchList->clear();

	std::string contents = this->ui.filterEdit->text().toStdString();
	QColor pink(255, 123, 184);
	QFont font{ "Comic Sans MS", 12, 10 };
	QBrush brush(pink);

	for (auto coat : this->service.returnRepository().all_objects()) {
		if (contents.length() == 0 || coat.getSize() == contents) {
			QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(coat.getSize() + " - " + coat.getColour() + ", Cost: " + std::to_string(static_cast<int>(coat.getPrice())) + ", Qt: " + std::to_string(coat.getQuantity())) };
			item->setFont(font);
			item->setBackground(brush);
			this->ui.trenchList->addItem(item);
		}

	}
}


void GUI::addToCart()
{
	int row = this->getSelectedIndex();
	if (row == -1) {
		QMessageBox::warning(nullptr, "Error", "Select a trench coat to delete first!");
		return;
	}

	std::string size = this->service.returnRepository()[row].getSize();
	std::string colour = this->service.returnRepository()[row].getColour();
	float price = this->service.returnRepository()[row].getPrice();
	int quantity = this->service.returnRepository()[row].getQuantity();
	std::string link = this->service.returnRepository()[row].getPhoto();
	TrenchCoat t = TrenchCoat(size, colour, price, quantity, link);

	this->csvCart.add_to_cart(t);
	this->htmlCart.add_to_cart(t);
	this->csvCart.saveToFile();
	this->htmlCart.saveToFile();
	this->ui.totalLabel->setText(QString::fromStdString("Total: " + std::to_string(this->csvCart.returnTotal())));
	this->populateCart();
}


void GUI::openLink(std::string link)
{
	std::string url = link;
	std::string op = std::string("start ").append(url);
	system(op.c_str());
}


void GUI::graphButtonHandler()
{

	QMap<QString, int> data;
	data["XS"] = 0;
	data["S"] = 0;
	data["M"] = 0;
	data["L"] = 0;
	data["XL"] = 0;
	data["XXL"] = 0;
	for (auto i : this->service.returnRepository().all_objects())
	{
		if (i.getSize() == "XS")
			data["XS"]++;
		else if (i.getSize() == "S")
			data["S"]++;
		else if (i.getSize() == "M")
			data["M"]++;
		else if (i.getSize() == "L")
			data["L"]++;
		else if (i.getSize() == "XL")
			data["XL"]++;
		else if (i.getSize() == "XXL")
			data["XXL"]++;
	}

	GraphRepresentation* graphWidget = new GraphRepresentation();
	graphWidget->setData(data);

	QDialog* dialog = new QDialog(this);
	QVBoxLayout* layout = new QVBoxLayout(dialog);
	layout->addWidget(graphWidget);
	dialog->setLayout(layout);
	dialog->setFixedSize(600, 400);

	dialog->setWindowTitle("Graph");
	dialog->setAttribute(Qt::WA_DeleteOnClose);

	dialog->exec();
}

void GUI::undoHandler()
{
	try {
		this->service.undo();
		this->populateList();
	}
	catch (std::exception& e) {
		QMessageBox::warning(nullptr, "Error", "Cannot undo anymore!");
		return;
	}

}

void GUI::redoHandler()
{
	try {
		this->service.redo();
		this->populateList();
	}
	catch (std::exception& e) {
		QMessageBox::warning(nullptr, "Error", "Cannot redo anymore!");
		return;
	}

}


void GUI::openCSV()
{
	this->csvCart.displayCart();
}


void GUI::openHTML()
{
	this->htmlCart.displayCart();
}

void GUI::modelHandler()
{
	QDialog* dialog = new QDialog(this);
	dialog->setWindowTitle("Shopping Cart Model View");
	dialog->setFixedSize(600, 400);

	QVBoxLayout* layout = new QVBoxLayout(dialog);

	QTableView* view = new QTableView(dialog);
	view->setModel(modelCart);

	view->setSelectionBehavior(QTableView::SelectRows);
	view->setSelectionMode(QTableView::SingleSelection);
	view->horizontalHeader()->setStretchLastSection(true);
	view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	layout->addWidget(view);

	dialog->setLayout(layout);

	dialog->exec();
}