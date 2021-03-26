/*
 *
 *  D-Bus++ - C++ bindings for D-Bus
 *
 *  Copyright (C) 2005-2007  Paolo Durante <shackan@gmail.com>
 *
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#ifndef __DBUSXX_TYPES_H
#define __DBUSXX_TYPES_H

#include <map>
#include <string>

#include "error.h"
#include "message.h"

namespace DBus
{

class Variant
{
public:
    Variant() : _msg(CallMessage()) {}

    MessageIter reader() const
    {
        return _msg.reader();
    }

    MessageIter writer()
    {
        return _msg.writer();
    }

    template <typename T>
    inline operator T() const
    {
        T cast;
        DBus::MessageIter ri = _msg.reader();
        ri >> cast;

        return cast;
    }

private:
    Message _msg;
};

inline DBus::MessageIter &operator << (DBus::MessageIter &iter, const std::string &val)
{
    iter.append_string(val.c_str());

    return iter;
}

inline DBus::MessageIter &operator >> (DBus::MessageIter &iter, std::string &val)
{
    val = iter.get_string();

    return ++iter;
}

inline DBus::MessageIter &operator >> (DBus::MessageIter &iter, DBus::Variant &val)
{
    if (iter.type() != DBUS_TYPE_VARIANT) {
        throw Error("org.freedesktop.DBus.Error.InvalidArgs", "variant type expected");
    }

    MessageIter vit = iter.recurse();
    MessageIter mit = val.writer();

    vit.copy_data(mit);

    return ++iter;
}

template<typename K, typename V>
inline DBus::MessageIter &operator >> (DBus::MessageIter &iter, std::map<K, V>& val)
{
    if (!iter.is_dict()) {
        throw DBus::Error("org.freedesktop.DBus.Error.InvalidArgs", "dictionary value expected");
    }

    DBus::MessageIter mit = iter.recurse();

    while (!mit.at_end()) {
        K key;
        V value;

        DBus::MessageIter eit = mit.recurse();

        eit >> key >> value;

        val[key] = value;

        ++mit;
    }

    return ++iter;
}

}

#endif //__DBUSXX_TYPES_H
