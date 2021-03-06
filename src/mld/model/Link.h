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

#ifndef MLD_LINK_H
#define MLD_LINK_H

#include "mld/model/GraphObject.h"

namespace mld {

/**
 * @brief The Link abstract class, models an edge in the graph
 */
class MLD_API Link : public GraphObject
{
public:
    inline sparksee::gdb::oid_t source() const { return m_src; }
    inline sparksee::gdb::oid_t target() const { return m_tgt; }

    virtual void print( std::ostream& out ) const override;
protected:
    explicit Link();
    explicit Link( sparksee::gdb::oid_t eid, sparksee::gdb::oid_t src, sparksee::gdb::oid_t tgt );
    explicit Link( sparksee::gdb::oid_t eid, sparksee::gdb::oid_t src,
          sparksee::gdb::oid_t tgt, const AttrMap& data );
    // "Hide" setId method
    using GraphObject::setId;

    inline void setSource( sparksee::gdb::oid_t src ) { m_src = src; }
    inline void setTarget( sparksee::gdb::oid_t tgt ) { m_tgt = tgt; }

protected:
    sparksee::gdb::oid_t m_src;
    sparksee::gdb::oid_t m_tgt;
};


/**
 * @brief The HLink concrete class, represent a H_LINK relationship
 * It links a Node to another in the same Layer
 */
class MLD_API HLink : public Link
{
    friend class AbstractDao;
    friend class LinkDao;
    friend class MLGDao;
public:
    virtual ~HLink() override;

    inline double weight() const { return m_data[Attrs::V[HLinkAttr::WEIGHT]].GetDouble(); }
    void setWeight( double v );

protected:
    explicit HLink();
    explicit HLink( sparksee::gdb::oid_t eid, sparksee::gdb::oid_t src,
           sparksee::gdb::oid_t tgt, const AttrMap& data );

    // "Hide" setId method
    using GraphObject::setId;
};


/**
 * @brief The VLink concrete class, represent a V_LINK relationship
 * It links a SuperNode to another in a consecutive Layer (above or under the current layer)
 * There are 2 different implementation because HLINKs are different
 * even if they look similar in the implementation
 */
class MLD_API VLink : public Link
{
    friend class AbstractDao;
    friend class LinkDao;
    friend class MLGDao;
public:
    virtual ~VLink() override;

    inline double weight() const { return m_data[Attrs::V[VLinkAttr::WEIGHT]].GetDouble(); }
    void setWeight( double v );

protected:
    explicit VLink();
    explicit VLink( sparksee::gdb::oid_t eid, sparksee::gdb::oid_t src,
           sparksee::gdb::oid_t tgt, const AttrMap& data );

    // "Hide" setId method
    using GraphObject::setId;
};

/**
 * @brief The Owns link class
 */
class MLD_API OLink : public Link
{
    friend class AbstractDao;
    friend class LinkDao;
    friend class MLGDao;
public:
    virtual ~OLink() override;

    inline double weight() const { return m_data[Attrs::V[OLinkAttr::WEIGHT]].GetDouble(); }
    void setWeight( double v );

protected:
    explicit OLink();
    explicit OLink( sparksee::gdb::oid_t eid, sparksee::gdb::oid_t src,
           sparksee::gdb::oid_t tgt, const AttrMap& data );

    // "Hide" setId method
    using GraphObject::setId;
};

/**
 * @brief The Child_Of link class
 */
class MLD_API CLink : public Link
{
    friend class AbstractDao;
    friend class LayerDao;
    friend class MLGDao;
public:
    virtual ~CLink() override;

    inline double weight() const { return m_data[Attrs::V[CLinkAttr::WEIGHT]].GetDouble(); }
    void setWeight( double v );

protected:
    explicit CLink();
    explicit CLink( sparksee::gdb::oid_t eid, sparksee::gdb::oid_t src,
           sparksee::gdb::oid_t tgt, const AttrMap& data );

    // "Hide" setId method
    using GraphObject::setId;
};


} // end namespace mld

std::ostream& operator<<( std::ostream& out, const mld::HLink& hlink );
std::ostream& operator<<( std::ostream& out, const mld::VLink& vlink );
std::ostream& operator<<( std::ostream& out, const mld::OLink& olink );
std::ostream& operator<<( std::ostream& out, const mld::CLink& clink );

#endif // LINK_H
