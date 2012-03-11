/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  The FreeAccount plugins are free, open source FreeMedForms' plugins.   *
 *  (C) 2010-2011 by Pierre-Marie Desombre, MD <pm.desombre@medsyn.fr>     *
 *  and Eric Maeker, MD <eric.maeker@gmail.com>                            *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *  Main Developers : Pierre-Marie DESOMBRE <pm.desombre@medsyn.fr>,      *
 *                     Eric MAEKER, <eric.maeker@gmail.com>                *
 *  Contributors :                                                         *
 *      NAME <MAIL@ADDRESS.COM>                                            *
 ***************************************************************************/
#include "accountmode.h"
#include "accountview.h"
#include "receipts/receiptviewer.h"

#include <coreplugin/icore.h>
#include <coreplugin/isettings.h>
#include <coreplugin/itheme.h>
#include <coreplugin/iuser.h>
#include <coreplugin/constants_menus.h>
#include <coreplugin/constants_icons.h>
#include <coreplugin/modemanager/modemanager.h>

#include <utils/log.h>
#include <utils/global.h>
#include <translationutils/constants.h>
#include <translationutils/trans_account.h>

#include <QFile>
#include <QPushButton>

using namespace Account::Internal;
using namespace Trans::ConstantTranslations;

static inline Core::ITheme *theme()  { return Core::ICore::instance()->theme(); }
static inline Core::ISettings *settings() { return Core::ICore::instance()->settings(); }
static inline Core::ModeManager *modeManager() {return Core::ICore::instance()->modeManager();}

AccountMode::AccountMode(QObject *parent) :
    Core::BaseMode(parent)
{
//    setName(tr("Accountancy"));
    setIcon(theme()->icon(Core::Constants::ICONACCOUNTMODE, Core::ITheme::BigIcon));
    setPriority(Core::Constants::P_MODE_ACCOUNT);
    setUniqueModeName(Core::Constants::MODE_ACCOUNT);
    setPatientBarVisibility(true);

//    const QList<int> &context;
//    setContext();
    m_Stack = new QStackedWidget;
    setWidget(m_Stack);

    connect(Core::ICore::instance(), SIGNAL(coreOpened()), this, SLOT(postCoreInitialization()));
    connect(modeManager(), SIGNAL(currentModeChanged(Core::IMode*)), this, SLOT(modeActivated(Core::IMode*)));

    /** \todo connect actions from the account menu */
    /** \todo connect patient changed and refresh views ? */
}

QString AccountMode::name() const
{
    return tr("Accountancy");
}

void AccountMode::setCentralWidget(QWidget *widget)
{
    QWidget *w = m_Stack->currentWidget();
    m_Stack->removeWidget(w);
    delete w;
    w = 0;
    m_Stack->addWidget(widget);
    m_Stack->setCurrentWidget(widget);
}

void AccountMode::postCoreInitialization()
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << Q_FUNC_INFO;
    if (m_Stack)
        m_Stack->addWidget(new ReceiptViewer);
}

void AccountMode::modeActivated(Core::IMode *mode)
{
    if (mode!=this) {
        return;
    }
    if (settings()->firstTimeRunning(Core::Constants::MODE_ACCOUNT)) {
        const QString &firstExplanationText = tr("Please read this explanation before using FreeAccount.\n"
                                              "FreeAccount is composed of:\n"
                                              "  - Receipts to get your earnings,\n"
                                              "  - Movements in your accountancy,\n"
                                              "  - Asset for your assets,\n"
                                              "  - Ledger to analyse your accountancy and produce and print your ledger.");
        const QString &detail = tr("The shortcuts for those programs are:\n"
                                   "  - for your rapid receipt, CTRL+R,\n"
                                   "  - for the receipts widget, Maj+R,\n"
                                   "  - for the movements widget, CTRL+M,\n"
                                   "  - for assets widget, ALT+Z,\n"
                                   "  - for ledger and analysis widget, ALT+L.\n"
                                   "Before the first use, open Configuration > Preferences > Accountancy > Defaults,\n"
                                   "and create defaults.\n"
                                   "Then parametrize your user, sites, bank and so on.");
        int b = Utils::withButtonsMessageBox(tkTr(Trans::Constants::ACCOUNTANCY),
                                             firstExplanationText,
                                             detail,
                                             QStringList() << tr("Ok") << trUtf8("Do not show this message again"),
                                             tkTr(Trans::Constants::ACCOUNTANCY), false);

        if (b==1) { // Don't show again
            LOG("Removing Account first run dialog");
            settings()->noMoreFirstTimeRunning(Core::Constants::MODE_ACCOUNT);
        }
    }
}
