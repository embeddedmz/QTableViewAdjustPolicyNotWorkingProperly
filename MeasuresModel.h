#pragma once

#include <QAbstractTableModel>
#include <QHash>

#include "Shared.h"

// QAbstractTableModel subclass for viewing a real time measures through a table interface.
// First column is the name of the measure, the second is its value and the thrid columns is its unit

class MeasuresModel : public QAbstractTableModel
{
    Q_OBJECT
    typedef QAbstractTableModel Superclass;

public:
    enum class ColumnType
    {
        Name = 0,
        Value,
        Unit,
        ColumnTypeMax  // Columns count in this model
    };

    MeasuresModel(QHash<QString, MeasureItem>& measures,
        QHash<QString, int>& measureNameToIndex,
        QHash<int, QString>& measureIndexToName,
        QObject* parentObject = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    bool setData(const MeasureItem& trapItem);

private:
    Q_DISABLE_COPY(MeasuresModel)

    QHash<QString, MeasureItem>& m_measures;
    QHash<QString, int>& m_measureNameToIndex;
    QHash<int, QString>& m_measureIndexToName;
};
