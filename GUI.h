#pragma once
#include "CSVShoppingCart.h"
#include "HTMLShoppingCart.h"
#include <QWidget>
#include "ui_GUI.h"
#include <Service.h>
#include <Validator.h>
#include "GraphRepresentation.h"
#include "CartModelView.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(Service service, QWidget *parent = nullptr);
	~GUI();

private:
	Service service;
	HTMLShoppingCart htmlCart;
	CSVShoppingCart csvCart;
	Validator validator;
	CartModelView* modelCart = new CartModelView{csvCart};

	Ui::GUIClass ui;
	void populateList();
	void populateCart();
	int getSelectedIndex();
	int getSelectedIndex2();
	void connectSignalsAndSlots();
	void itemClickedHandler();
	void itemDoubleClickedHandler();
	void itemDoubleClickedHandler2();
	void deleteButtonHandler();
	void addButtonHandler();
	void updateButtonHandler();
	void filterLineEditHandler();
	void addToCart();
	void openLink(std::string link);
	void openCSV();
	void openHTML();
	void graphButtonHandler();
	void undoHandler();
	void redoHandler();
	void modelHandler();
};
