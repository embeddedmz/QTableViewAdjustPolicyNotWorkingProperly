#ifndef PH66STATUS_H
#define PH66STATUS_H

#include <QWidget>

class PH66Status : public QWidget
{
    Q_OBJECT

public:
    explicit PH66Status(QWidget* parent = nullptr);
    ~PH66Status() override;

private:
    Q_DISABLE_COPY(PH66Status)

    struct Internals;
    Internals* m_Internals;
};

#endif // PH66STATUS_H
