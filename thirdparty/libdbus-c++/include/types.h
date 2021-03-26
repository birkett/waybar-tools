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
#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <string>

#include "error.h"
#include "message.h"

namespace DBus
{

class Variant
{
public:
    Variant() : message(CallMessage()) {}

    MessageIter reader() const
    {
        return message.reader();
    }

    MessageIter writer()
    {
        return message.writer();
    }

    template <typename T>
    inline explicit operator T() const
    {
        T cast;
        MessageIter ri = message.reader();
        ri >> cast;

        return cast;
    }

private:
    Message message;
};

inline MessageIter &operator << (MessageIter &iter, const std::string &val)
{
    iter.appendString(val.c_str());

    return iter;
}

inline MessageIter &operator >> (MessageIter &iter, std::string &val)
{
    val = iter.getString();

    return ++iter;
}

inline MessageIter &operator >> (MessageIter &iter, Variant &val)
{
    if (iter.type() != DBUS_TYPE_VARIANT) {
        throw Error("org.freedesktop.DBus.Error.InvalidArgs", "variant type expected");
    }

    MessageIter vit = iter.recurse();
    MessageIter mit = val.writer();

    vit.copyData(mit);

    return ++iter;
}

template<typename K, typename V>
inline MessageIter &operator >> (MessageIter &iter, std::map<K, V>& val)
{
    if (!iter.isDict()) {
        throw Error("org.freedesktop.DBus.Error.InvalidArgs", "dictionary value expected");
    }

    MessageIter mit = iter.recurse();

    while (!mit.atEnd()) {
        K key;
        V value;

        MessageIter eit = mit.recurse();

        eit >> key >> value;

        val[key] = value;

        ++mit;
    }

    return ++iter;
}

}

#endif //TYPES_H
