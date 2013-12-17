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

#include "mld/operator/MultiAdditiveMerger.h"
#include "mld/model/SuperNode.h"
#include "mld/operator/AbstractSelector.h"

using namespace mld;
using namespace dex::gdb;

MultiAdditiveMerger::MultiAdditiveMerger( Graph* g )
    : AbstractMultiMerger(g)
{
}

MultiAdditiveMerger::~MultiAdditiveMerger()
{
}

SuperNode MultiAdditiveMerger::merge( const SuperNode& source,
                                      const ObjectsPtr& neighbors
                                    )
{
    // TODO
    return SuperNode();
}
