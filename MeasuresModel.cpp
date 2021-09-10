#include "MeasuresModel.h"

MeasuresModel::MeasuresModel(QHash<QString, MeasureItem>& measures,
	QHash<QString, int>& measuresNameToIndex,
	QHash<int, QString>& measuresIndexToName,
	QObject* _parent /*= nullptr*/) :
	Superclass(_parent),
	m_measures(measures),
	m_measureNameToIndex(measuresNameToIndex),
	m_measureIndexToName(measuresIndexToName)
{

}

int MeasuresModel::rowCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
	Q_UNUSED(parent)
	
    return m_measures.size();
}

int MeasuresModel::columnCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
	Q_UNUSED(parent)

	return static_cast<int>(ColumnType::ColumnTypeMax);
}

QVariant MeasuresModel::data(const QModelIndex& idx, int role /*= Qt::DisplayRole*/) const
{
	// you can gather data from an object here and return it...
	if (!idx.isValid() || idx.model() != this ||
		idx.row() >= rowCount() || idx.column() >= columnCount())
	{
		return QVariant();
	}

	// tool tip role infos are header columns names for now
	if (role == Qt::ToolTipRole)
	{
		return this->headerData(idx.column(), Qt::Horizontal, Qt::DisplayRole);
	}

	const MeasureItem& measure = m_measures[m_measureIndexToName[idx.row()]];
	switch (static_cast<ColumnType>(idx.column()))
	{
		case ColumnType::Name:
			switch (role)
			{
				case Qt::DisplayRole:
				case Qt::EditRole:
					return measure.name;
			}
			break;

		case ColumnType::Unit:
			switch (role)
			{
				case Qt::DisplayRole:
				case Qt::EditRole:
					return measure.unit;
			}
			break;

		case ColumnType::Value:
			switch (role)
			{
				case Qt::DisplayRole:
				case Qt::EditRole:
					return QString::number(measure.value, 'f', 2);
			}
			break;
	}
	return QVariant();
}

QVariant MeasuresModel::headerData(int section, Qt::Orientation orientation,
	int role /*= Qt::DisplayRole*/) const
{
	if (orientation == Qt::Horizontal)
	{
		switch (role)
		{
			case Qt::DisplayRole:
				switch (static_cast<ColumnType>(section))
				{
					case ColumnType::Name:
						return QString(tr("Name"));

					case ColumnType::Value:
						return QString(tr("Value"));

					case ColumnType::Unit:
						return QString(tr("Unit"));
				}
				break;
		}
	}

	return Superclass::headerData(section, orientation, role);
}

Qt::ItemFlags MeasuresModel::flags(const QModelIndex& idx) const
{
	return this->Superclass::flags(idx);
}

bool MeasuresModel::setData(const QModelIndex& idx,
	const QVariant& value,
	int role /*= Qt::EditRole*/)
{
    Q_UNUSED(role)

    if (idx.column() >= columnCount() || idx.row() >= rowCount())
    {
        return false;
    }

	MeasureItem& measure = m_measures[m_measureIndexToName[idx.row()]];
	switch (static_cast<ColumnType>(idx.column()))
	{
		case ColumnType::Value:
		{
			const double newVal = value.toDouble();
			if (newVal != measure.value)
			{
				measure.value = newVal;
				emit this->dataChanged(idx, idx);
				return true;
			}
		}
		break;
	}

	return false;
}

bool MeasuresModel::setData(const MeasureItem& measureItem)
{
	if (m_measureNameToIndex.find(measureItem.name) == m_measureNameToIndex.end())
	{
		return false;
	}
	const int eleIdx = m_measureNameToIndex[measureItem.name];

	bool bRet = false;
	if (measureItem.value != m_measures[measureItem.name].value)
	{
		bRet |= setData(createIndex(eleIdx, static_cast<int>(ColumnType::Value)),
			measureItem.value);
	}

	return bRet;
}
