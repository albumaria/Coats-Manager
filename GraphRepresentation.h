#pragma once

#include <QWidget>
#include "ui_GraphRepresentation.h"

class GraphRepresentation : public QWidget
{
	Q_OBJECT

public:
	GraphRepresentation(QWidget *parent = nullptr);
	void setData(const QMap<QString, int > & data);
	~GraphRepresentation();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QMap<QString, int> m_data;
};
