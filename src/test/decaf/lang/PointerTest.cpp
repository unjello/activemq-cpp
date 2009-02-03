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

#include "PointerTest.h"

#include <decaf/lang/Pointer.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>

#include <map>
#include <string>

using namespace std;
using namespace decaf;
using namespace decaf::lang;

////////////////////////////////////////////////////////////////////////////////
class TestClassBase {
public:

    virtual ~TestClassBase(){}

    virtual std::string returnHello() = 0;

};

////////////////////////////////////////////////////////////////////////////////
class TestClassA : public TestClassBase {
public:

    virtual ~TestClassA() {
        //std::cout << std::endl << "TestClassA - Destructor" << std::endl;
    }

    std::string returnHello() {
        return "Hello";
    }

};

////////////////////////////////////////////////////////////////////////////////
class TestClassB : public TestClassBase {
public:

    virtual ~TestClassB() {
        //std::cout << std::endl << "TestClassB - Destructor" << std::endl;
    }

    std::string returnHello() {
        return "GoodBye";
    }

};

////////////////////////////////////////////////////////////////////////////////
class SomeOtherClass {
public:

};

////////////////////////////////////////////////////////////////////////////////
struct X {
    Pointer<X> next;
};

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testBasics() {

    TestClassA* thePointer = new TestClassA();

    // Test Null Initialize
    Pointer<TestClassA> nullPointer;
    CPPUNIT_ASSERT( nullPointer.get() == NULL );

    // Test Value Constructor
    Pointer<TestClassA> pointer( thePointer );
    CPPUNIT_ASSERT( pointer.get() == thePointer );

    // Test Copy Constructor
    Pointer<TestClassA> ctorCopy( pointer );
    CPPUNIT_ASSERT( ctorCopy.get() == thePointer );

    // Test Assignment
    Pointer<TestClassA> copy = pointer;
    CPPUNIT_ASSERT( copy.get() == thePointer );

    CPPUNIT_ASSERT( ( *pointer ).returnHello() == "Hello" );
    CPPUNIT_ASSERT( pointer->returnHello() == "Hello" );

    copy.reset( NULL );
    CPPUNIT_ASSERT( copy.get() == NULL );

    Pointer<X> p( new X );
    p->next = Pointer<X>( new X );
    p = p->next;
    CPPUNIT_ASSERT( !p->next );
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
void ConstReferenceMethod( const Pointer<T>& pointer ) {

    Pointer<T> copy = pointer;
    CPPUNIT_ASSERT( copy.get() != NULL );
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
void ReferenceMethod( Pointer<T>& pointer ) {

    pointer.reset( NULL );
    CPPUNIT_ASSERT( pointer.get() == NULL );
}

////////////////////////////////////////////////////////////////////////////////
Pointer<TestClassA> ReturnByValue() {

    Pointer<TestClassA> pointer( new TestClassA );
    CPPUNIT_ASSERT( pointer.get() != NULL );
    return pointer;
}

////////////////////////////////////////////////////////////////////////////////
const Pointer<TestClassA>& ReturnByConstReference() {

    static Pointer<TestClassA> pointer( new TestClassA );
    CPPUNIT_ASSERT( pointer.get() != NULL );
    return pointer;
}

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testAssignment() {

    TestClassA* thePointerA = new TestClassA();
    TestClassB* thePointerB = new TestClassB();

    Pointer<TestClassBase> pointer;
    CPPUNIT_ASSERT( pointer.get() == NULL );

    pointer.reset( thePointerA );
    CPPUNIT_ASSERT( pointer.get() == thePointerA );

    pointer.reset( thePointerB );
    CPPUNIT_ASSERT( pointer.get() == thePointerB );

    // Doing this however won't compile.
    //    SomeOtherClass other;
    //    pointer.reset( &other );

    Pointer<TestClassA> pointer1( new TestClassA() );
    Pointer<TestClassA> pointer2 = pointer1;
    Pointer<TestClassA> pointer3 = pointer2;

    CPPUNIT_ASSERT( pointer1.get() == pointer2.get() );
    CPPUNIT_ASSERT( pointer2.get() == pointer3.get() );

    pointer3.reset( NULL );
    CPPUNIT_ASSERT( pointer1.get() != NULL );
    CPPUNIT_ASSERT( pointer2.get() != NULL );
    CPPUNIT_ASSERT( pointer3.get() == NULL );

    ConstReferenceMethod( pointer1 );
    ReferenceMethod( pointer2 );
    CPPUNIT_ASSERT( pointer2.get() == NULL );

    ReturnByValue();

    {
        Pointer<TestClassA> copy = ReturnByValue();
    }

    {
        Pointer<TestClassA> copy = ReturnByConstReference();
    }

    ReturnByConstReference();
}

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testComparisons() {

    Pointer<TestClassBase> pointer1( new TestClassA );
    Pointer<TestClassBase> pointer2( new TestClassB );

    TestClassA* raw1 = new TestClassA;

    CPPUNIT_ASSERT( ( pointer1 == pointer2 ) == false );
    CPPUNIT_ASSERT( ( pointer1 != pointer2 ) == true );

    CPPUNIT_ASSERT( ( pointer1 == raw1 ) == false );
    CPPUNIT_ASSERT( ( pointer1 != raw1 ) == true );
    CPPUNIT_ASSERT( ( raw1 == pointer2 ) == false );
    CPPUNIT_ASSERT( ( raw1 != pointer2 ) == true );

    delete raw1;

    Pointer<TestClassBase> pointer3( new TestClassA );
    Pointer<TestClassA> pointer4( new TestClassA );

    CPPUNIT_ASSERT( ( pointer3 == pointer4 ) == false );
    CPPUNIT_ASSERT( ( pointer3 != pointer4 ) == true );

    CPPUNIT_ASSERT( pointer1 != NULL );
    CPPUNIT_ASSERT( !pointer1 == false );
    CPPUNIT_ASSERT( !!pointer1 == true );

    // This won't compile which is correct.
    //Pointer<TestClassB> pointer5( new TestClassB );
    //Pointer<TestClassA> pointer6( new TestClassA );
    //CPPUNIT_ASSERT( pointer5 != pointer6 );
}

////////////////////////////////////////////////////////////////////////////////
class PointerTestRunnable : public decaf::lang::Runnable {
private:

    Pointer<TestClassA> mine;

public:

    PointerTestRunnable( const Pointer<TestClassA>& value ) : mine( value ) {}

    void run() {

        for( int i = 0; i < 999; ++i ) {
            Pointer<TestClassBase> copy = this->mine;
            CPPUNIT_ASSERT( copy->returnHello() == "Hello" );
            copy.reset( new TestClassB() );
            CPPUNIT_ASSERT( copy->returnHello() == "GoodBye" );
        }
    }
};

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testThreaded1() {
    Pointer<TestClassA> pointer( new TestClassA() );

    PointerTestRunnable runnable( pointer );
    Thread testThread( &runnable );

    testThread.start();

    for( int i = 0; i < 999; ++i ) {
        Pointer<TestClassBase> copy = pointer;
        CPPUNIT_ASSERT( copy->returnHello() == "Hello" );
        Thread::yield();
        copy.reset( new TestClassB() );
        CPPUNIT_ASSERT( copy->returnHello() == "GoodBye" );
    }

    testThread.join();
}

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testThreaded2() {
}

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testOperators() {

    Pointer<TestClassBase> pointer1( new TestClassA );
    Pointer<TestClassBase> pointer2( new TestClassB );
    Pointer<TestClassBase> pointer3;

    CPPUNIT_ASSERT( pointer1->returnHello() == "Hello" );
    CPPUNIT_ASSERT( pointer2->returnHello() == "GoodBye" );

    CPPUNIT_ASSERT( ( *pointer1 ).returnHello() == "Hello" );
    CPPUNIT_ASSERT( ( *pointer2 ).returnHello() == "GoodBye" );

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "operator* on a NULL Should Throw a NullPointerException",
        ( *pointer3 ).returnHello(),
        decaf::lang::exceptions::NullPointerException );
    CPPUNIT_ASSERT_THROW_MESSAGE(
        "operator-> on a NULL Should Throw a NullPointerException",
        pointer3->returnHello(),
        decaf::lang::exceptions::NullPointerException );

    pointer2.reset( NULL );

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "operator* on a NULL Should Throw a NullPointerException",
        ( *pointer2 ).returnHello(),
        decaf::lang::exceptions::NullPointerException );
    CPPUNIT_ASSERT_THROW_MESSAGE(
        "operator-> on a NULL Should Throw a NullPointerException",
        pointer2->returnHello(),
        decaf::lang::exceptions::NullPointerException );
}

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testSTLContainers() {

    Pointer<TestClassBase> pointer1( new TestClassA );
    Pointer<TestClassBase> pointer2( new TestClassB );
    Pointer<TestClassBase> pointer3( pointer2 );

    CPPUNIT_ASSERT( pointer1.get() != NULL );
    CPPUNIT_ASSERT( pointer2.get() != NULL );

    std::map< Pointer<TestClassBase>, std::string > testMap;

    testMap.insert( std::make_pair( pointer1, "Bob" ) );
    testMap.insert( std::make_pair( pointer2, "Steve" ) );
    testMap.insert( std::make_pair( pointer3, "Steve" ) );

    // Two and Three should be equivalent (not equal) but in this case
    // equivalent is what matters.  So pointer2 should be bumped out of the map.
    CPPUNIT_ASSERT( testMap.size() == 2 );

    testMap.insert( std::make_pair( Pointer<TestClassBase>( new TestClassA ), "Fred" ) );

    CPPUNIT_ASSERT( testMap.find( pointer1 ) != testMap.end() );
    CPPUNIT_ASSERT( testMap.find( pointer2 ) != testMap.end() );
}

////////////////////////////////////////////////////////////////////////////////
class SelfCounting {
private:

    int refCount;

public:

    SelfCounting() : refCount( 0 ) {}
    SelfCounting( const SelfCounting& other ) : refCount( other.refCount ) {}

    void addReference() { this->refCount++; }
    bool releaseReference() { return !( --this->refCount ); }

    std::string returnHello() { return "Hello"; }
};

////////////////////////////////////////////////////////////////////////////////
void PointerTest::testInvasive() {

    Pointer< SelfCounting, InvasiveCounter<SelfCounting> > thePointer( new SelfCounting );

    // Test Null Initialize
    Pointer< SelfCounting, InvasiveCounter<SelfCounting> > nullPointer;
    CPPUNIT_ASSERT( nullPointer.get() == NULL );

    // Test Value Constructor
    Pointer< SelfCounting, InvasiveCounter<SelfCounting> > pointer( thePointer );
    CPPUNIT_ASSERT( pointer.get() == thePointer );

    // Test Copy Constructor
    Pointer< SelfCounting, InvasiveCounter<SelfCounting> > ctorCopy( pointer );
    CPPUNIT_ASSERT( ctorCopy.get() == thePointer );

    // Test Assignment
    Pointer< SelfCounting, InvasiveCounter<SelfCounting> > copy = pointer;
    CPPUNIT_ASSERT( copy.get() == thePointer );

    CPPUNIT_ASSERT( ( *pointer ).returnHello() == "Hello" );
    CPPUNIT_ASSERT( pointer->returnHello() == "Hello" );

    copy.reset( NULL );
    CPPUNIT_ASSERT( copy.get() == NULL );
}
