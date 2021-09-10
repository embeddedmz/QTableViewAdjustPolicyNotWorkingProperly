#include "MeasuresManager.h"
#include "Shared.h"
#include "Constants.h"
#include "MeasuresModel.h"

struct MeasuresManager::Internals
{
    // the hash map stuff can be removed if enums were used (using enums as identifiers instead of measure names)
    QHash<QString, MeasureItem> ph66Measures;
    QHash<QString, int> ph66MeasureNameToIndex;
    QHash<int, QString> ph66MeasureIndexToName;

    MeasuresModel* ph66MeasuresModel;
};

MeasuresManager::MeasuresManager(QObject* parent) :
    QObject(parent),
    m_Internals(new MeasuresManager::Internals)
{
    // PH66 Measures
    m_Internals->ph66Measures.insert(g_24V_ALIM, MeasureItem(g_24V_ALIM, g_VOLTAGE_UNIT));
    m_Internals->ph66Measures.insert(g_120V_ALIM, MeasureItem(g_120V_ALIM, g_VOLTAGE_UNIT));
    m_Internals->ph66Measures.insert(g_TEMPERATURE, MeasureItem(g_TEMPERATURE, g_TEMPERATURE_UNIT));

    m_Internals->ph66MeasureNameToIndex.insert(g_24V_ALIM, 0);
    m_Internals->ph66MeasureNameToIndex.insert(g_120V_ALIM, 1);
    m_Internals->ph66MeasureNameToIndex.insert(g_TEMPERATURE, 2);

    m_Internals->ph66MeasureIndexToName.insert(0, g_24V_ALIM);
    m_Internals->ph66MeasureIndexToName.insert(1, g_120V_ALIM);
    m_Internals->ph66MeasureIndexToName.insert(2, g_TEMPERATURE);

    // Models initialization (for the QTableViews)
    m_Internals->ph66MeasuresModel = new MeasuresModel(m_Internals->ph66Measures,
        m_Internals->ph66MeasureNameToIndex, m_Internals->ph66MeasureIndexToName, this);
}

MeasuresManager::~MeasuresManager()
{
    delete m_Internals;
}

MeasuresModel* MeasuresManager::getPh66MeasuresModel() const
{
    return m_Internals->ph66MeasuresModel;
}
