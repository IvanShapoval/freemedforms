/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2011 by Eric MAEKER, MD (France) <eric.maeker@free.fr>        *
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
 *   Main Developper : Eric MAEKER, <eric.maeker@free.fr>                  *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADRESS>                                                *
 *       NAME <MAIL@ADRESS>                                                *
 ***************************************************************************/
#ifndef FORMMANAGERMODE_H
#define FORMMANAGERMODE_H

#include <coreplugin/modemanager/basemode.h>

#include <QObject>

/**
 * \file formmanagermode.h
 * \author Eric MAEKER <eric.maeker@free.fr>
 * \version 0.5.0
 * \date 25 Mar 2011
*/


namespace Form {
class FormPlaceHolder;
namespace Internal {

class FormManagerMode : public Core::BaseMode
{
    Q_OBJECT
public:
    FormManagerMode(QObject *parent);
    ~FormManagerMode();

private Q_SLOTS:
    bool loadPatientFile();

private:
    FormPlaceHolder *m_Holder;
};

}  // End namespace Internal
}  // End namespace Form

#endif // FORMMANAGERMODE_H
