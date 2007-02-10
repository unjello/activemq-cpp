/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_JOURNALQUEUEACK_H_
#define _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_JOURNALQUEUEACK_H_

// Turn off warning message for ignored exception specification
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include <activemq/connector/openwire/commands/BaseDataStructure.h>
#include <activemq/connector/openwire/commands/ActiveMQDestination.h>
#include <activemq/connector/openwire/commands/MessageAck.h>
#include <vector>
#include <string>

namespace activemq{
namespace connector{
namespace openwire{
namespace commands{

    /*
     *
     *  Command and marshaling code for OpenWire format for ${className}
     *
     *
     *  NOTE!: This file is autogenerated - do not modify!
     *         if you need to make a change, please see the Java Classes
     *         in the activemq-openwire-generator module
     *
     */
    class JournalQueueAck : public BaseDataStructure
    {
    protected:

        ActiveMQDestination* destination;
        MessageAck* messageAck;

    public:

        const static unsigned char ID_JOURNALQUEUEACK = 52;

    public:

        JournalQueueAck();
        virtual ~JournalQueueAck();

        /**
         * Get the unique identifier that this object and its own
         * Marshaller share.
         * @returns new DataStructure type copy.
         */
        virtual unsigned char getDataStructureType() const;

        /**
         * Clone this object and return a new instance that the
         * caller now owns, this will be an exact copy of this one
         * @returns new copy of this object.
         */
        virtual DataStructure* cloneDataStructure() const;

        /**
         * Copy the contents of the passed object into this object's
         * members, overwriting any existing data.
         * @param src - Source Object
         */
        virtual void copyDataStructure( const DataStructure* src );

        virtual const ActiveMQDestination* getDestination() const;
        virtual ActiveMQDestination* getDestination();
        virtual void setDestination( ActiveMQDestination* destination );

        virtual const MessageAck* getMessageAck() const;
        virtual MessageAck* getMessageAck();
        virtual void setMessageAck( MessageAck* messageAck );

    };

}}}}

#endif /*_ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_JOURNALQUEUEACK_H_*/

