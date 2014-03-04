/****************************************************************************
**
** Copyright (C) 2014 EPFL-LTS2
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

#include <sparksee/gdb/Graph.h>
#include <sparksee/gdb/Objects.h>
#include <sparksee/gdb/ObjectsIterator.h>

#include "mld/operator/selector/NeighborSelector.h"
#include "mld/GraphTypes.h"
#include "mld/dao/MLGDao.h"

using namespace mld;
using namespace sparksee::gdb;

NeighborSelector::NeighborSelector( Graph* g )
    : AbstractSelector(g)
    , m_hasMemory(false)
    , m_layerId(Objects::InvalidOID)
    , m_current(Objects::InvalidOID)
    , m_flagged( m_dao->newObjectsPtr() )
    , m_curNeighbors( m_dao->newObjectsPtr() )
{
}

NeighborSelector::~NeighborSelector()
{
}

void NeighborSelector::resetSelection()
{
    m_scores.clear();
    m_current = Objects::InvalidOID;
    m_layerId = Objects::InvalidOID;
    m_curNeighbors = m_dao->newObjectsPtr();
    m_nodesToRemove.clear();
    m_flagged = m_dao->newObjectsPtr();
}

bool NeighborSelector::rankNodes( const Layer& layer )
{    
    resetSelection();
    m_layerId = layer.id();
    ObjectsPtr nodes(m_dao->getAllNodeIds(layer));
    // Iterate through each node and calculate score
    ObjectsIt it(nodes->Iterator());
    while( it->HasNext() ) {
        oid_t nid = it->Next();
#ifdef MLD_SAFE
        if( nid == Objects::InvalidOID ) {
            LOG(logERROR) << "NeighborSelector::rankNodes invalid node";
            return false;
        }
#endif
        // Add values in the mutable priority queue, no nodes are flagged
        m_scores.push(nid, calcScore(nid));
    }
    // Set m_current to a real value
//    m_current = m_scores.front_value();
    return true;
}

bool NeighborSelector::hasNext()
{
    return !m_scores.empty();
}

SuperNode NeighborSelector::next()
{
    if( m_scores.empty() ) {
        LOG(logWARNING) << "NeighborSelector::next empty scores";
        resetSelection();
        return SuperNode();
    }

    // Clear previous node neighborhood
    removeCandidates();
    ObjectsPtr nodeSet(getNeighbors(m_current));
    if( nodeSet ) {
        if( !m_hasMemory )
            nodeSet->Add(m_current);
        updateScore(nodeSet);
    }

    if( m_hasMemory )
        m_flagged->Add(m_current);

    m_current = m_scores.front_value();
    // Set the best neighbors for the merger, use m_current
    // to set m_curNeighors in child class
    setCurrentBestNeighbors();
    // Copy m_curNeighbors ids to m_nodes2Remove
    setNodesToRemove();

    return m_dao->getNode(m_current);
}

bool NeighborSelector::updateScore( const ObjectsPtr& input )
{
    if( !input ) {
        return false;
    }
//    LOG(logDEBUG) << "NeighborSelector::updateScore start input size " << input->Count();
    ObjectsIt it(input->Iterator());
    while( it->HasNext() ) {
        auto id = it->Next();
        m_scores.update(id, calcScore(id));
    }
//    LOG(logDEBUG) << "NeighborSelector::updateScore end";
    return true;
}

void NeighborSelector::removeCandidates()
{
    // Remove candidates nodes from selection queue
    for( auto id: m_nodesToRemove) {
        m_scores.erase(id);
    }
}

void NeighborSelector::setNodesToRemove()
{
    m_nodesToRemove.clear();

    if( !m_curNeighbors ) {
        if( m_hasMemory ) {
            m_nodesToRemove.push_back(m_current);
        }
        return;
    }

    m_nodesToRemove.reserve(m_curNeighbors->Count() + 1);
    ObjectsIt it(m_curNeighbors->Iterator());
    while( it->HasNext() ) {
        m_nodesToRemove.push_back(it->Next());
    }

    if( m_hasMemory )
        m_nodesToRemove.push_back(m_current);
}

ObjectsPtr NeighborSelector::getNeighbors( oid_t snid )
{
#ifdef MLD_SAFE
    if( snid == Objects::InvalidOID ) {
        return ObjectsPtr();
    }
#endif

    ObjectsPtr neighbors(m_dao->graph()->Neighbors(snid, m_dao->hlinkType(), Any));
    if( m_hasMemory ) {
        // Return only neighbors not flagged
        neighbors->Difference(m_flagged.get());
    }
    return neighbors;
}

ObjectsPtr NeighborSelector::getCurrentBestNeighbors()
{
    if( m_curNeighbors )
        return ObjectsPtr(m_curNeighbors->Copy());
    return ObjectsPtr();
}
