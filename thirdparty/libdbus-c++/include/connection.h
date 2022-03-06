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
#ifndef CONNECTION_H
#define CONNECTION_H

#include "message.h"
#include "types.h"

namespace DBus
{

class Connection
{
public:
    explicit Connection()
    {
        Error error;

        this->conn = dbus_bus_get_private(DBUS_BUS_SESSION, (DBusError*)error);

        if (error.hasError()) {
            std::string errorMessage(error.message());
            dbus_error_free((DBusError*)error);

            throw Error("DBus Error:", errorMessage);
        }

        dbus_connection_set_exit_on_disconnect(this->conn, dbus_bool_t(false));
    }

    ~Connection()
    {
        dbus_connection_close(this->conn);
    }

    [[nodiscard]] Message sendBlocking(const Message &message) const
    {
        Error error;
        DBusMessage *reply = dbus_connection_send_with_reply_and_block(
            this->conn,
            &message.getMessage(),
            -1,
            (DBusError*)error
        );

        if (error.hasError()) {
            std::string errorMessage(error.message());
            dbus_error_free((DBusError*)error);

            throw Error("DBus Error:", errorMessage);
        }

        return Message(reply);
    }

private:
    DBusConnection *conn {};
};

}

#endif //CONNECTION_H
