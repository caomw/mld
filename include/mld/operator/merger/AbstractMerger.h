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

#ifndef MLD_ABSTRACTMERGER_H
#define MLD_ABSTRACTMERGER_H

#include "mld/common.h"

namespace sparksee {
namespace gdb {
    class Graph;
}}

namespace mld {
// Forward declaration
class MLGDao;
class HLink;
class Node;

/**
 * @brief Base class inherited by all edge mergers
 * Used by all coarseners
 */
class MLD_API AbstractMerger
{
public:
    AbstractMerger( sparksee::gdb::Graph* g );
    virtual ~AbstractMerger() = 0;

    // Disable copy and assignement ctor
    AbstractMerger( const AbstractMerger& ) = delete;
    AbstractMerger& operator=( const AbstractMerger& ) = delete;

    virtual std::string name() const = 0;
protected:
    std::unique_ptr<MLGDao> m_dao;
};

} // end namespace mld

#endif // MLD_ABSTRACTMERGER_H
