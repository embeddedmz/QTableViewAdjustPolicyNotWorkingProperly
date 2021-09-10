#ifndef SHARED_H
#define SHARED_H

#include <cstddef>
#include <ctime>

#include <QString>
#include <QVector>

const int g_VALVES_COUNT = 2;

/* Global String Literals */

/* Data Structures */
struct MeasureItem
{
    MeasureItem() = default;
    MeasureItem(QString name, QString unit) : name(name), unit(unit) {}

    QString name;
    QString unit;
    double value = 0.;
};

struct DiagnosisDataItem
{
    double current; // A
    double voltage; // V
    int index;
    int count;
};

struct PH66Informations
{
    QString version;
    size_t address;
    bool comStatus;
};


/* Functions */

#endif // SHARED_H
