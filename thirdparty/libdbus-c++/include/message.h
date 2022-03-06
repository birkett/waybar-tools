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
    [[nodiscard]] int type() const
    {
        return dbus_message_iter_get_arg_type((DBusMessageIter *)&iterator);
    }

    [[nodiscard]] bool atEnd() const
    {
        return type() == DBUS_TYPE_INVALID;
    }

    MessageIter &operator ++()
    {
        dbus_message_iter_next((DBusMessageIter *)&iterator);

        return (*this);
    }

    dbus_bool_t appendString(const char *chars)
    {
        return appendBasic(DBUS_TYPE_STRING, &chars);
    }

    std::string getString()
    {
        char *chars;
        getBasic(DBUS_TYPE_STRING, &chars);

        return chars;
    }

    [[nodiscard]] MessageIter recurse() const
    {
        MessageIter iter(getMessage());
        dbus_message_iter_recurse((DBusMessageIter *)&iterator, (DBusMessageIter *) & (iter.iterator));

        return iter;
    }

    [[nodiscard]] char *signature() const
    {
        return dbus_message_iter_get_signature((DBusMessageIter *)&iterator);
    }

    [[nodiscard]] bool isArray() const
    {
        return dbus_message_iter_get_arg_type((DBusMessageIter *)&iterator) == DBUS_TYPE_ARRAY;
    }

    [[nodiscard]] bool isDict() const
    {
        return isArray() && dbus_message_iter_get_element_type((DBusMessageIter *)iterator) == DBUS_TYPE_DICT_ENTRY;
    }

    void closeContainer(MessageIter &container) const
    {
        dbus_message_iter_close_container((DBusMessageIter *)&iterator, (DBusMessageIter *) & (container.iterator));
    }

    void copyData(MessageIter &to)
    {
        for (MessageIter &from = *this; !from.atEnd(); ++from) {
            if (isBasicType(from.type())) {
                unsigned char value[8];
                from.getBasic(from.type(), &value);
                to.appendBasic(from.type(), &value);

                continue;
            }

            MessageIter fromContainer = from.recurse();
            char *sig = fromContainer.signature();

            MessageIter toContainer(to.getMessage());
            dbus_bool_t ret = dbus_message_iter_open_container(
                (DBusMessageIter *) &to.iterator,
                from.type(),
                (from.type() == DBUS_TYPE_VARIANT || from.type() == DBUS_TYPE_ARRAY) ? sig : nullptr,
                (DBusMessageIter *) &toContainer.iterator
            );

            if (!ret) {
                throw Error("org.freedesktop.DBus.Error.NoMemory", "Unable to append container");
            }

            fromContainer.copyData(toContainer);
            to.closeContainer(toContainer);
            free(sig);
        }
    }

    [[nodiscard]] Message &getMessage() const
    {
        return *message;
    }

private:
    explicit MessageIter(Message &message) : message(&message) {}

    dbus_bool_t appendBasic(int type_id, void *value) const
    {
        return dbus_message_iter_append_basic((DBusMessageIter *)&iterator, type_id, value);
    }

    void getBasic(int type_id, void *ptr) const
    {
        if (type() != type_id) {
            throw Error("org.freedesktop.DBus.Error.InvalidArgs", "type mismatch");
        }

        dbus_message_iter_get_basic((DBusMessageIter *)iterator, ptr);
    }

    static bool isBasicType(int typeCode)
    {
        switch (typeCode)
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

    unsigned char iterator[sizeof(void *) * 3 + sizeof(int) * 11] {};
    Message *message {};

    friend class Message;
};

class Message
{
public:
    explicit Message(DBusMessage* message) : message(message) {}

    ~Message()
    {
        dbus_message_unref(message);
    }

    MessageIter writer()
    {
        MessageIter iter(*this);
        dbus_message_iter_init_append(message, (DBusMessageIter *) & (iter.iterator));

        return iter;
    }

    [[nodiscard]] MessageIter reader() const
    {
        MessageIter iter(const_cast<Message &>(*this));
        dbus_message_iter_init(message, (DBusMessageIter *) & (iter.iterator));

        return iter;
    }

    [[nodiscard]] DBusMessage &getMessage() const
    {
        return *message;
    }

protected:
    DBusMessage* message{};
};

class CallMessage : public Message
{
public:
    CallMessage(const std::string& member, const std::string& interface, const std::string& path, const std::string& destination)
        : Message(dbus_message_new(DBUS_MESSAGE_TYPE_METHOD_CALL))
    {
        dbus_message_set_member(message, member.c_str());
        dbus_message_set_interface(message, interface.c_str());
        dbus_message_set_path(message, path.c_str());
        dbus_message_set_destination(message, destination.c_str());
    }
};

class EmptyMessage : public Message
{
public:
    EmptyMessage() : Message(dbus_message_new(DBUS_MESSAGE_TYPE_METHOD_CALL))
    {
        dbus_message_ref(this->message);
        dbus_message_ref(this->message);
    }
};

}

#endif //MESSAGE_H
