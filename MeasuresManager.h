#ifndef MEASURESMANAGER_H
#define MEASURESMANAGER_H

#include <QObject>

#include "Shared.h"

class MeasuresModel;

class MeasuresManager final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MeasuresManager)
public:
    explicit MeasuresManager(QObject* parent = nullptr);
    ~MeasuresManager() override;

    MeasuresModel* getPh66MeasuresModel() const;

protected:
    struct Internals;
    Internals* m_Internals;

};

#endif // MEASURESMANAGER_H
