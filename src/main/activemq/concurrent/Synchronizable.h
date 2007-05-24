/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ACTIVEMQ_CONCURRENT_SYNCHRONIZABLE_H
#define ACTIVEMQ_CONCURRENT_SYNCHRONIZABLE_H

#include <activemq/exceptions/ActiveMQException.h>
#include <activemq/util/Config.h>

namespace activemq{
namespace concurrent{
    
    /**
     * The interface for all synchronizable objects (that is, objects
     * that can be locked and unlocked).
     */
    class AMQCPP_API Synchronizable
    {
    public:

        virtual ~Synchronizable(){}
    
        /**
         * Locks the object.
         * @throws ActiveMQException
         */
        virtual void lock() throw(exceptions::ActiveMQException) = 0;

        /**
         * Unlocks the object.
         * @throws ActiveMQException
         */
        virtual void unlock() throw(exceptions::ActiveMQException) = 0;
    
        /**
         * Waits on a signal from this object, which is generated
         * by a call to Notify.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void wait() throw(exceptions::ActiveMQException) = 0;
    
        /**
         * Waits on a signal from this object, which is generated
         * by a call to Notify.  Must have this object locked before
         * calling.  This wait will timeout after the specified time
         * interval.
         * @param millisecs the time in millisecsonds to wait, or 
         * WAIT_INIFINITE
         * @throws ActiveMQException
         */
        virtual void wait(unsigned long millisecs) 
            throw(exceptions::ActiveMQException) = 0;

        /**
         * Signals a waiter on this object that it can now wake
         * up and continue.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void notify() throw( exceptions::ActiveMQException ) = 0;
    
        /**
         * Signals the waiters on this object that it can now wake
         * up and continue.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void notifyAll() throw( exceptions::ActiveMQException ) = 0;

    }; 

}}

#endif /*ACTIVEMQ_CONCURRENT_SYNCHRONIZABLE_H*/
