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
#ifndef __DBUSXX_OBJECT_H
#define __DBUSXX_OBJECT_H

#include <dbus/dbus.h>
#include <string>

#include "connection.h"
#include "message.h"

namespace DBus
{

class Object
{
public:
    Object(const char* path, const char *service)
        : _path(path), _service(service ? service : "")
    {
        _conn = new Connection(DBUS_BUS_SESSION);
    };

    virtual ~Object() = default;

    Message invoke_method(CallMessage &call)
    {
        call.path(path().c_str());

        call.destination(service().c_str());

        return conn()->send_blocking(call);
    };

    inline const std::string &path() const { return _path; };
    inline const std::string &service() const { return _service; };
    inline Connection* conn() { return _conn; };

private:
    Connection*	_conn;
    std::string	_path;
    std::string	_service;
};

}

#endif //__DBUSXX_OBJECT_H
