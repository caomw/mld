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

#include <sparksee/gdb/Objects.h>

#include "mld/model/Link.h"

using namespace sparksee::gdb;
using namespace mld;

// ****** LINK ****** //

Link::Link()
    : GraphObject()
    , m_src(Objects::InvalidOID)
    , m_tgt(Objects::InvalidOID)
{
}

Link::Link( oid_t eid, oid_t src, oid_t tgt )
    : GraphObject(eid)
    , m_src(src)
    , m_tgt(tgt)
{
}

Link::Link( oid_t eid, oid_t src, oid_t tgt, const AttrMap& data )
    : GraphObject(eid, data)
    , m_src(src)
    , m_tgt(tgt)
{
}

void Link::print( std::ostream& out ) const
{
    out << "src: " << m_src << " ";
    out << "tgt: " << m_tgt << " ";
    GraphObject::print(out);
}

// ****** HLINK ****** //

HLink::HLink()
    : Link()
{
}

HLink::HLink( oid_t eid, oid_t src, oid_t tgt, const AttrMap& data )
    : Link(eid, src, tgt, data)
{
}

HLink::~HLink()
{
}

void HLink::setWeight( double v )
{
    m_data[Attrs::V[HLinkAttr::WEIGHT]].SetDoubleVoid(v);
}

std::ostream& operator<<( std::ostream& out, const mld::HLink& hlink )
{
    out << "hlink ";
    hlink.print(out);
    return out;
}


// ****** VLINK ****** //

VLink::VLink()
    : Link()
{
}

VLink::VLink( oid_t eid, oid_t src, oid_t tgt, const AttrMap& data )
    : Link(eid, src, tgt, data)
{
}

VLink::~VLink()
{
}

void VLink::setWeight( double v )
{
    m_data[Attrs::V[VLinkAttr::WEIGHT]].SetDoubleVoid(v);
}

std::ostream& operator<<( std::ostream& out, const mld::VLink& vlink )
{
    out << "vlink ";
    vlink.print(out);
    return out;
}

// ****** OLINK ****** //

OLink::OLink()
    : Link()
{
}

OLink::OLink( oid_t eid, oid_t src, oid_t tgt, const AttrMap& data )
    : Link(eid, src, tgt, data)
{
}

OLink::~OLink()
{
}

void OLink::setWeight( double v )
{
    m_data[Attrs::V[OLinkAttr::WEIGHT]].SetDoubleVoid(v);
}

std::ostream& operator<<( std::ostream& out, const mld::OLink& olink )
{
    out << "olink ";
    olink.print(out);
    return out;
}

// ****** CLINK ****** //

CLink::CLink()
    : Link()
{
}

CLink::CLink( oid_t eid, oid_t src, oid_t tgt, const AttrMap& data )
    : Link(eid, src, tgt, data)
{
}

CLink::~CLink()
{
}

void CLink::setWeight( double v )
{
    m_data[Attrs::V[CLinkAttr::WEIGHT]].SetDoubleVoid(v);
}

std::ostream& operator<<( std::ostream& out, const mld::CLink& clink )
{
    out << "clink ";
    clink.print(out);
    return out;
}








