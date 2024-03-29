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
#ifndef ERROR_H
#define ERROR_H

#include <dbus/dbus.h>
#include <exception>
#include <string>

namespace DBus
{

class Error : public std::exception
{
public:
    Error()
    {
        dbus_error_init(&error);
    };

    Error(const std::string &name, const std::string &message)
    {
        dbus_error_init(&error);
        dbus_set_error_const(&(error), name.c_str(), message.c_str());
    }

    dbus_bool_t hasError()
    {
        return dbus_error_is_set(&error);
    }

    explicit operator DBusError *()
    {
        return &error;
    }

    [[nodiscard]] const char *what() const noexcept override
    {
        return error.message;
    }

    [[nodiscard]] const char *message() const
    {
        return error.message;
    }

private:
    DBusError error {};
};

}

#endif //ERROR_H
