#include "GraphRepresentation.h"
#include <QPainter>

GraphRepresentation::GraphRepresentation(QWidget *parent)
	: QWidget(parent)
{
	
}


void GraphRepresentation::setData(const QMap<QString, int>& data)
{
    m_data = data;
    update();
}


void GraphRepresentation::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_data.isEmpty()) {
        painter.drawText(rect(), Qt::AlignCenter, "No data available");
        return;
    }

    int maxValue = *std::max_element(m_data.constBegin(), m_data.constEnd());

    int margin = 40; 
    int graphWidth = width() - 2 * margin;
    int graphHeight = height() - 2 * margin;
    int barWidth = graphWidth / m_data.size();

    QStringList sizeOrder = { "XS", "S", "M", "L", "XL", "XXL" };

    QMap<QString, QColor> sizeColors;
    sizeColors["XS"] = Qt::red;
    sizeColors["S"] = Qt::green;
    sizeColors["M"] = Qt::blue;
    sizeColors["L"] = Qt::yellow;
    sizeColors["XL"] = Qt::cyan;
    sizeColors["XXL"] = Qt::magenta;

    int i = 0;
    for (const QString& size : sizeOrder) {
        int count = m_data.value(size, 0); 

        int barHeight = graphHeight * count / maxValue;
        int barX = margin + i * barWidth;
        int barY = height() - margin - barHeight;

        QRect barRect(barX, barY, barWidth, barHeight);
        painter.fillRect(barRect, sizeColors[size]);

        QFontMetrics fm(font());
        QRect textRect = fm.boundingRect(size);
        int textX = barX + (barWidth - textRect.width()) / 2;
        painter.drawText(textX, height() - margin / 4, size);

        QString countLabel = QString::number(count);
        textRect = fm.boundingRect(countLabel);
        textX = barX + (barWidth - textRect.width()) / 2;
        painter.drawText(textX, barY - margin / 4, countLabel);

        ++i;
    }
}


GraphRepresentation::~GraphRepresentation()
{}
