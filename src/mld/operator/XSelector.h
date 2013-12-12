/****************************************************************************
**
** Copyright (C) 2013 EPFL-LTS2
** Contact: Kirell Benzi (first.last@epfl.ch)
**
** This file is part of MLD.
**
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.md included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements
** will be met: http://www.gnu.org/licenses/
**
****************************************************************************/

#ifndef MLD_XSELECTOR_H
#define MLD_XSELECTOR_H

#include "mld/common.h"
#include "mld/operator/AbstractSelector.h"

namespace mld {

class MLD_API XSelector : public AbstractMultiSelector
{
public:
    XSelector( dex::gdb::Graph* g );
    virtual ~XSelector() override;

    virtual SuperNode selectBestNode( const Layer& layer ) override;
};

} // end namespace mld

#endif // XSELECTOR_H