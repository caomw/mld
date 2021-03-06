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

#ifndef MLD_TSCACHE_H
#define MLD_TSCACHE_H

#include <list>
#include <unordered_map>

//#include <boost/thread/shared_mutex.hpp>
#include <sparksee/gdb/Graph_data.h>

#include "mld/common.h"
#include "mld/model/TimeSeries.h"

namespace mld {

class MLGDao;

using EntryPair = std::pair<sparksee::gdb::oid_t, TimeSeries<double>>;
using CacheList = std::list<EntryPair>;
using CacheMap = std::unordered_map<sparksee::gdb::oid_t, CacheList::iterator>;

//using Lock = boost::shared_mutex;
//using WriteLock = boost::unique_lock<Lock>;
//using ReadLock = boost::shared_lock<Lock>;

class MLD_API TSCache
{
public:
    TSCache( const std::shared_ptr<MLGDao>& dao );
    TSCache( const TSCache& ) = delete;
    TSCache& operator =( TSCache ) = delete;

    void reset( sparksee::gdb::oid_t startLayer, TSDirection dir, size_t radius );
    void clear();

    /**
     * @brief Move to next layer, all the entries are modified accordingly
     */
    void scrollUp();
    EntryPair get( sparksee::gdb::oid_t nid );

private:
    void insert( sparksee::gdb::oid_t nid, const TimeSeries<double>& ts );

private:
    std::shared_ptr<MLGDao> m_dao;
    TSDirection m_dir;
    size_t m_radius;
    sparksee::gdb::oid_t m_activeLayer;
    sparksee::gdb::oid_t m_upperBoundLayer;

    uint64_t m_entries;
    uint64_t m_maxEntries;
    CacheList m_cacheList;
    CacheMap m_cacheMap;
    //Lock m_lock;
};

} // end namespace mld

#endif // MLD_TSCACHE_H
