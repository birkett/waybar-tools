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
#include <dbus/dbus.h>

#include "types.h"

namespace DBus {

class MessageIter;

MessageIter &operator >> (MessageIter &iter, Variant &val)
{
    if (iter.type() != DBUS_TYPE_VARIANT) {
        throw ErrorInvalidArgs("variant type expected");
    }

    MessageIter vit = iter.recurse();
    MessageIter mit = val.writer();

    vit.copy_data(mit);

    return ++iter;
}

}
