/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2011 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
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
 *   Main Developpers :                                                    *
 *       Eric MAEKER, MD <eric.maeker@gmail.com>                           *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADRESS>                                                *
 ***************************************************************************/
#include "server.h"
#include "server_p.h"

#include <translationutils/constanttranslations.h>

#include <QFileInfo>

using namespace DataPack;
using namespace Internal;

Server::Server(const QUrl &url, QObject *parent) : QObject(parent),
	m_d(new ServerPrivate(url))
{
//    m_d->networkAccessManager = qobject_cast<ServerManagerPrivate*>(parent)->networkAccessManager;
}

Server::~Server()
{
    // TODO stop all jobs linked to the server if there are running ones
}

void Server::setUrl(const QUrl &url)
{
    m_d->m_IsLocal = false;
    m_d->url.clear();
//    if (url.startsWith("file://", Qt::CaseInsensitive)) {
//        QString t = url;
//        QFileInfo file(t.replace("file:/", ""));
//        if (file.exists() && file.isDir()) {
//            m_d->url = url;
//            m_d->m_IsLocal = true;
//            m_d->connected = true;
//        } else {
//            LOG_ERROR(tkTr(Trans::Constants::PATH_1_DOESNOT_EXISTS).arg(url));
//            m_d->connected = false;
//            return;
//        }
//    }
    m_d->url = url;
}

const QUrl &Server::url() const
{
    return m_d->url;
}

bool Server::isConnected() const
{
    return m_d->connected;
}

/** Return true if server's url starts with \e file:// and path exists. */
bool Server::isLocalPath() const
{
    return m_d->m_IsLocal;
}

void Server::connectAndUpdate()
{
    if (!m_d->m_IsLocal)
        m_d->connectAndUpdate();
}
