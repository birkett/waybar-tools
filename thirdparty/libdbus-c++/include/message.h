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
#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdlib>
#include <dbus/dbus.h>
#include <string>

#include "error.h"

namespace DBus
{

class Message;

class MessageIter
{
public:
    int type() const
    {
        return dbus_message_iter_get_arg_type((DBusMessageIter *)&_iter);
    }

    bool at_end() const
    {
        return type() == DBUS_TYPE_INVALID;
    }

    MessageIter &operator ++()
    {
        dbus_message_iter_next((DBusMessageIter *)&_iter);

        return (*this);
    }

    bool append_string(const char *chars)
    {
        return append_basic(DBUS_TYPE_STRING, &chars);
    }

    std::string get_string()
    {
        char *chars;
        get_basic(DBUS_TYPE_STRING, &chars);

        return chars;
    }

    MessageIter recurse() const
    {
        MessageIter iter(msg());
        dbus_message_iter_recurse((DBusMessageIter *)&_iter, (DBusMessageIter *) & (iter._iter));

        return iter;
    }

    char *signature() const
    {
        return dbus_message_iter_get_signature((DBusMessageIter *)&_iter);
    }

    bool is_array() const
    {
        return dbus_message_iter_get_arg_type((DBusMessageIter *)&_iter) == DBUS_TYPE_ARRAY;
    }

    bool is_dict() const
    {
        return is_array() && dbus_message_iter_get_element_type((DBusMessageIter *)_iter) == DBUS_TYPE_DICT_ENTRY;
    }

    void close_container(MessageIter &container) const
    {
        dbus_message_iter_close_container((DBusMessageIter *)&_iter, (DBusMessageIter *) & (container._iter));
    }

    void copy_data(MessageIter &to)
    {
        for (MessageIter &from = *this; !from.at_end(); ++from) {
            if (is_basic_type(from.type())) {
                unsigned char value[8];
                from.get_basic(from.type(), &value);
                to.append_basic(from.type(), &value);
            } else {
                MessageIter from_container = from.recurse();
                char *sig = from_container.signature();

                MessageIter to_container(to.msg());
                dbus_bool_t ret = dbus_message_iter_open_container(
                        (DBusMessageIter *) & (to._iter),
                        from.type(),
                        (from.type() == DBUS_TYPE_VARIANT || from.type() == DBUS_TYPE_ARRAY) ? sig : nullptr,
                        (DBusMessageIter *) & (to_container._iter)
                );

                if (!ret) {
                    throw Error("org.freedesktop.DBus.Error.NoMemory", "Unable to append container");
                }

                from_container.copy_data(to_container);
                to.close_container(to_container);
                free(sig);
            }
        }
    }

    Message &msg() const
    {
        return *_msg;
    }

private:
    explicit MessageIter(Message &msg) : _msg(&msg) {}

    bool append_basic(int type_id, void *value) const
    {
        return dbus_message_iter_append_basic((DBusMessageIter *)&_iter, type_id, value);
    }

    void get_basic(int type_id, void *ptr) const
    {
        if (type() != type_id) {
            throw Error("org.freedesktop.DBus.Error.InvalidArgs", "type mismatch");
        }

        dbus_message_iter_get_basic((DBusMessageIter *)_iter, ptr);
    }

    static bool is_basic_type(int typecode)
    {
        switch (typecode)
        {
            case 'y':
            case 'b':
            case 'n':
            case 'q':
            case 'i':
            case 'u':
            case 'x':
            case 't':
            case 'd':
            case 's':
            case 'o':
            case 'g':
                return true;
            default:
                return false;
        }
    }

    unsigned char _iter[sizeof(void *) * 3 + sizeof(int) * 11] {};
    Message *_msg {};

    friend class Message;
};

class Message
{
public:
    explicit Message(DBusMessage* message) : message(message) {}

    MessageIter writer()
    {
        MessageIter iter(*this);
        dbus_message_iter_init_append(message, (DBusMessageIter *) & (iter._iter));

        return iter;
    }

    MessageIter reader() const
    {
        MessageIter iter(const_cast<Message &>(*this));
        dbus_message_iter_init(message, (DBusMessageIter *) & (iter._iter));

        return iter;
    }

    DBusMessage &msg() const
    {
        return *message;
    }

protected:
    DBusMessage* message{};
};

class CallMessage : public Message
{
public:
    CallMessage() : Message(dbus_message_new(DBUS_MESSAGE_TYPE_METHOD_CALL)) {}

    CallMessage(const std::string& member, const std::string& interface, const std::string& path, const std::string& destination)
        : Message(dbus_message_new(DBUS_MESSAGE_TYPE_METHOD_CALL))
    {
        dbus_message_set_member(message, member.c_str());
        dbus_message_set_interface(message, interface.c_str());
        dbus_message_set_path(message, path.c_str());
        dbus_message_set_destination(message, destination.c_str());
    }
};

}

#endif //MESSAGE_H
