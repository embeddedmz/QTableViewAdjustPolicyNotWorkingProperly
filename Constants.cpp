#include "Constants.h"

// can't use tr() with QLiteralStrings
QString g_120_V_TOO_HIGH = QString(QObject::tr("120 V Too High"));
QString g_120_V_TOO_LOW = QString(QObject::tr("120 V Too Low"));
QString g_24_V_TOO_HIGH = QString(QObject::tr("24 V Too High"));
QString g_24_V_TOO_LOW = QString(QObject::tr("24 V Too Low"));
QString g_TEMP_TOO_HIGH = QString(QObject::tr("Temperature Too High"));
QString g_COM_ERROR = QString(QObject::tr("Communication Error"));

QString g_24V_ALIM = QString(QObject::tr("24V Supply"));
QString g_120V_ALIM = QString(QObject::tr("120V Supply"));
QString g_TEMPERATURE = QString(QObject::tr("Temperature"));

QString g_VOLTAGE_UNIT = QString(QObject::tr("V"));
// pas bien encodé sous Windows/ANSI (format utilisé par Visual Studio)
QString g_TEMPERATURE_UNIT = QLatin1String("°C");
QString g_CURRENT_UNIT = QString(QObject::tr("A"));
QString g_RESISTANCE_UNIT = QString(QObject::tr("Ohm"));
QString g_INDUCTANCE_UNIT = QString(QObject::tr("mH"));

QString g_OPEN_LOOP = QString(QObject::tr("Open Loop"));
QString g_SHORT_CIRCUIT = QString(QObject::tr("Short Circuit"));
QString g_R_TOO_HIGH = QString(QObject::tr("R Too High"));
QString g_R_TOO_LOW = QString(QObject::tr("R Too Low"));
QString g_L_VALUE = QString(QObject::tr("Valve L Error"));

QString g_VOLTAGE = QString(QObject::tr("Voltage"));
QString g_CURRENT = QString(QObject::tr("Current"));
QString g_RESISTANCE = QString(QObject::tr("R"));
QString g_INDUCTANCE = QString(QObject::tr("L"));

QString g_DIAG_VOLTAGE = QString(QObject::tr("Diagnosis Voltage"));
QString g_DIAG_CURRENT = QString(QObject::tr("Diagnosis Current"));
QString g_DIAG_RESISTANCE = QString(QObject::tr("Diagnosis Resistance"));
QString g_DIAG_INDUCTANCE = QString(QObject::tr("Diagnosis Inductance"));
