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
#ifndef __DBUSXX_ERROR_H
#define __DBUSXX_ERROR_H

#include <dbus/dbus.h>
#include <exception>

namespace DBus
{

class InternalError
{
public:
    DBusError error {};

    InternalError()
    {
        dbus_error_init(&error);
    }

    InternalError(InternalError &ie)
    {
        dbus_error_init(&error);
        dbus_move_error(&ie.error, &error);
    }

    ~InternalError()
    {
        dbus_error_free(&error);
    }

    operator DBusError *()
    {
        return &error;
    }
};

class Error : public std::exception
{
public:
    explicit Error(InternalError &i) : _int(new InternalError(i)) {}

    Error(const std::string &name, const std::string &message) : _int(new InternalError)
    {
        dbus_set_error_const(&(_int->error), name.c_str(), message.c_str());
    }

    const char *what() const noexcept override
    {
        return _int->error.message;
    }

    const char *message() const
    {
        return _int->error.message;
    }

private:
    InternalError* _int;
};

class ErrorNoMemory : public Error
{
public:
    explicit ErrorNoMemory(const std::string &message) : Error("org.freedesktop.DBus.Error.NoMemory", message) {}
};

class ErrorInvalidArgs : public Error
{
public:
    explicit ErrorInvalidArgs(const std::string &message) : Error("org.freedesktop.DBus.Error.InvalidArgs", message) {}
};

}

#endif //__DBUSXX_ERROR_H
