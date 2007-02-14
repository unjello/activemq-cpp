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

#ifndef _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_ACTIVEMQTEMPQUEUE_H_
#define _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_ACTIVEMQTEMPQUEUE_H_

// Turn off warning message for ignored exception specification
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include <activemq/connector/openwire/commands/ActiveMQTempDestination.h>
#include <cms/TemporaryQueue.h>
#include <vector>
#include <string>

namespace activemq{
namespace connector{
namespace openwire{
namespace commands{

    class ActiveMQTempQueue : public ActiveMQTempDestination,
                              public cms::TemporaryQueue
    {
    protected:


    public:

        const static unsigned char ID_ACTIVEMQTEMPQUEUE = 102;

    public:

        ActiveMQTempQueue();
        virtual ~ActiveMQTempQueue();

        virtual unsigned char getDataStructureType() const;

        /**
         * Clone this object and return a new instance that the
         * caller now owns, this will be an exact copy of this one
         * @returns new copy of this object.
         */
        virtual DataStructure* cloneDataStructure() const {
            ActiveMQTempQueue* message = new ActiveMQTempQueue();
            message->copyDataStructure( this );
            return message;
        }

        /**
         * Copy the contents of the passed object into this objects
         * members, overwriting any existing data.
         * @return src - Source Object
         */
        virtual void copyDataStructure( const DataStructure* src ) {
            ActiveMQTempDestination::copyDataStructure( src );
        }

        /**
         * Converts the Destination Name into a String
         * @return string name
         */
        virtual std::string toString(void) const {
            std::ostringstream stream;

            stream << "Begin Class = ActiveMQTempQueue" << std::endl;
            stream << ActiveMQTempDestination::toString();
            stream << "Begin Class = ActiveMQTempQueue" << std::endl;

            return stream.str();
        }

        /**
         * Compares the DataStructure passed in to this one, and returns if
         * they are equivalent.  Equivalent here means that they are of the
         * same type, and that each element of the objects are the same.
         * @returns true if DataStructure's are Equal.
         */
        virtual bool equals( const DataStructure* value ) const {
            return ActiveMQDestination::equals( value );
        }

    public:   // CMS Destination

        /**
         * Retrieve the Destination Type for this Destination
         * @return The Destination Type
         */
        virtual cms::Destination::DestinationType getDestinationType(void) const {
            return cms::Destination::TEMPORARY_QUEUE;
        }

        /**
         * Converts the Destination to a String value representing the
         * Provider specific name fot this destination, which is not
         * necessarily equal to the User Supplied name of the Destination
         * @return Provider specific Name
         */
        virtual std::string toProviderString(void) const {
            return this->getPhysicalName();
        }

        /**
         * Creates a new instance of this destination type that is a
         * copy of this one, and returns it.
         * @returns cloned copy of this object
         */
        virtual cms::Destination* clone(void) const {
            return dynamic_cast<cms::Destination*>(
                this->cloneDataStructure() );
        }

        /**
         * Copies the contents of the given Destinastion object to this one.
         * @param source The source Destination object.
         */
        virtual void copy( const cms::Destination& source ) {
            this->copyDataStructure(
                dynamic_cast<const DataStructure*>( &source ) );
        }

        /**
         * Retrieve any properties that might be part of the destination
         * that was specified.  This is a deviation from the JMS spec
         * but necessary due to C++ restrictions.
         * @return const reference to a properties object.
         */
        virtual const activemq::util::Properties& getProperties(void) const {
            return this->getOptions();
        }

    public:

        /**
         * Gets the name of this queue.
         * @return The queue name.
         */
        virtual std::string getQueueName(void) const
            throw( cms::CMSException ) {
                return this->getPhysicalName();
        }

    };

}}}}

#endif /*_ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_ACTIVEMQTEMPQUEUE_H_*/

