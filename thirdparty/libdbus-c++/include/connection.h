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
#ifndef __DBUSXX_CONNECTION_H
#define __DBUSXX_CONNECTION_H

#include "message.h"
#include "types.h"

namespace DBus
{

class Connection
{
public:
    Connection() = default;

    explicit Connection(DBusBusType type)
    {
        InternalError e;

        conn = dbus_bus_get_private(type, e);

        if (e) {
            throw Error(e);
        }

        dbus_connection_set_exit_on_disconnect(conn, false);
    }

    virtual ~Connection() = default;

    Message send_blocking(Message &msg)
    {
        DBusMessage *reply;
        InternalError e;

        reply = dbus_connection_send_with_reply_and_block(conn, msg.msg, -1, e);

        if (e) {
            throw Error(e);
        }

        Message pvt;
        pvt.msg = reply;

        return pvt;
    }

private:
    DBusConnection *conn {};
};

}

#endif//__DBUSXX_CONNECTION_H
