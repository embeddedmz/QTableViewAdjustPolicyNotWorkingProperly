#include "MeasuresManager.h"
#include "MeasuresModel.h"
#include "PH66Status.h"
#include "ui_PH66Status.h"

#include <QGroupBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QTableView>

#if 0
namespace
{
    void verticalResizeTableViewToContents(QTableView* tableView)
    {
        tableView->resizeRowsToContents();

        // does it work ?
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        int rowTotalHeight = 0;

        // Rows height
        int count = tableView->verticalHeader()->count();
        for (int i = 0; i < count; ++i) {
            // 2018-03 edit: only account for row if it is visible
            if (!tableView->verticalHeader()->isSectionHidden(i)) {
                rowTotalHeight += tableView->verticalHeader()->sectionSize(i);
            }
        }

        // Check for scrollbar visibility
        if (!tableView->horizontalScrollBar()->isHidden())
        {
            rowTotalHeight += tableView->horizontalScrollBar()->height();
        }

        // Check for header visibility
        if (!tableView->horizontalHeader()->isHidden())
        {
            rowTotalHeight += tableView->horizontalHeader()->height();
        }
        tableView->setMaximumHeight(rowTotalHeight);
    }
}
#endif

struct PH66Status::Internals
{
    Ui::PH66Status Ui;
};

PH66Status::PH66Status(QWidget *parent) :
    QWidget(parent),
    m_Internals(new PH66Status::Internals)
{
    m_Internals->Ui.setupUi(this);
    
    // Address
    // Version
    // ComStatus

    MeasuresManager* mm = new MeasuresManager(this);

    // Board Measures
    m_Internals->Ui.Measures->setModel(mm->getPh66MeasuresModel());
    m_Internals->Ui.Measures->horizontalHeader()->setSectionsMovable(true);
    m_Internals->Ui.Measures->horizontalHeader()->setHighlightSections(false);
    m_Internals->Ui.Measures->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    m_Internals->Ui.Measures->horizontalHeader()->setStretchLastSection(true);

    // Hide vertical header (index of entries)
    m_Internals->Ui.Measures->verticalHeader()->hide();
    m_Internals->Ui.Measures->setSelectionBehavior(QAbstractItemView::SelectRows);
    // no need to use the helper function verticalResizeTableViewToContents
    m_Internals->Ui.Measures->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
    //verticalResizeTableViewToContents(m_Internals->Ui.Measures);
}

PH66Status::~PH66Status()
{
    delete m_Internals;
}
