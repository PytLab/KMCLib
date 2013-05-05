/*
  Copyright (c)  2012-2013  Mikael Leetmaa

  This file is part of the KMCLib project distributed under the terms of the
  GNU General Public License version 3, see <http://www.gnu.org/licenses/>.
*/


// Include the test definition.
#include "test_coordinate.h"

// Include the files to test.
#include "coordinate.h"

#include <cmath>


// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testConstructionAndQuery()
{
    // Default construct.
    Coordinate c0;
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c0.x(), 0.0, 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c0.y(), 0.0, 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c0.z(), 0.0, 1.0e-14);

    // Construct with arguments.
    Coordinate c(0.1,0.2,0.3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c.x(), 0.1, 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c.y(), 0.2, 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c.z(), 0.3, 1.0e-14);
}


// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testLessOperator()
{
    // Two equal.
    {
        Coordinate c1(0.1,0.2,0.3);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT( !(c1 < c2) );
        CPPUNIT_ASSERT( !(c2 < c1) );
    }

    // c1 smaller in x.
    {
        Coordinate c1(0.099999,0.2,0.3);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT(  (c1 < c2) );
        CPPUNIT_ASSERT( !(c2 < c1) );
    }

    // c1 smaller in y.
    {
        Coordinate c1(0.1,0.19999999999,0.3);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT(  (c1 < c2) );
        CPPUNIT_ASSERT( !(c2 < c1) );
    }

    // c1 smaller in z.
    {
        Coordinate c1(0.1,0.2,0.299999999);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT(  (c1 < c2) );
        CPPUNIT_ASSERT( !(c2 < c1) );
    }
}


// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testAddIntoOperator()
{
    Coordinate c1(0.1, -1.2, 3.3);
    const Coordinate ref_c1 = c1;
    const Coordinate c2(-0.123, 0.2, 99.3);

    // Add c2 into c1.
    c1 += c2;

    // Check against elementarty operation.
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.x(), ref_c1.x() + c2.x(), 1.0e-12 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.y(), ref_c1.y() + c2.y(), 1.0e-12 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.z(), ref_c1.z() + c2.z(), 1.0e-12 );

    // Check against hardcoded ref.
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.x(), -0.023, 1.0e-12 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.y(), -1.000, 1.0e-12 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.z(),  102.6, 1.0e-12 );

}


// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testEqualsOperator()
{
    // Two equal.
    {
        Coordinate c1(0.1,0.2,0.3);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT(  (c1 == c2) );
        CPPUNIT_ASSERT( !(c1 != c2) );
    }

    // c1 smaller in x.
    {
        Coordinate c1(0.099999,0.2,0.3);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT( !(c1 == c2) );
        CPPUNIT_ASSERT(  (c1 != c2) );
    }

    // c1 smaller in y.
    {
        Coordinate c1(0.1,0.19999999999,0.3);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT( !(c1 == c2) );
        CPPUNIT_ASSERT(  (c1 != c2) );
    }

    // c1 smaller in z.
    {
        Coordinate c1(0.1,0.2,0.299999999);
        Coordinate c2(0.1,0.2,0.3);
        CPPUNIT_ASSERT( !(c1 == c2) );
        CPPUNIT_ASSERT(  (c1 != c2) );
     }
}


// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testDistance()
{
    {
        Coordinate c1(0.0,0.0,0.0);
        Coordinate c2(1.0,1.0,1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c2.distance(c1), std::sqrt(3), 1.0e-14 );
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.distance(c2), std::sqrt(3), 1.0e-14 );
    }

    {
        Coordinate c1(-1.0,-1.0,-1.0);
        Coordinate c2(1.0,1.0,1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c2.distance(c1), 2.0 * std::sqrt(3), 1.0e-14 );
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.distance(c2), 2.0 * std::sqrt(3), 1.0e-14 );
    }

    {
        Coordinate c1(0.0,0.0,0.0);
        Coordinate c2(1.0,2.0,3.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c2.distance(c1), std::sqrt(1.0+4.0+9.0), 1.0e-14 );
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.distance(c2), std::sqrt(1.0+4.0+9.0), 1.0e-14 );
    }

    {
        Coordinate c1(-1.0,1.0,5.0);
        Coordinate c2(-1.0,2.0,3.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c2.distance(c1), std::sqrt(5.0), 1.0e-14 );
        CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.distance(c2), std::sqrt(5.0), 1.0e-14 );
    }
}


// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testMinusOperator()
{
    const Coordinate c1(std::sqrt(2.0),-std::sqrt(8),1.0/3.0);
    const Coordinate c2(0.1,3.2,5.3);
    Coordinate c3 = c1 - c2;
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c3.x(), c1.x() - c2.x(), 1.0e-14 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c3.y(), c1.y() - c2.y(), 1.0e-14 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c3.z(), c1.z() - c2.z(), 1.0e-14 );


}

// -------------------------------------------------------------------------- //
//
void Test_Coordinate::testAccessOperator()
{
    Coordinate c1(std::sqrt(2.0),-std::sqrt(8),1.0/3.0);

    // Test the values.
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.x(), c1[0], 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.y(), c1[1], 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( c1.z(), c1[2], 1.0e-14);

    // Test the references.

    // X
    const double & x_ref_1 = c1[0];
    CPPUNIT_ASSERT_EQUAL( &x_ref_1, &c1.x() );
    // Check that the reference is not constant.
    c1[0] = 12.0;
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.0, c1.x(), 1.0e-14);
    // But these are not changed.
    CPPUNIT_ASSERT_DOUBLES_EQUAL( -std::sqrt(8.0), c1.y(), 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0/3.0, c1.z(), 1.0e-14);

    // Y
    const double & y_ref_1 = c1[1];
    CPPUNIT_ASSERT_EQUAL( &y_ref_1, &c1.y() );
    // Check that the reference is not constant.
    c1[1] = 13.0;
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 13.0, c1.y(), 1.0e-14);
    // But these are not changed.
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.0, c1.x(), 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0/3.0, c1.z(), 1.0e-14);

    // Z
    const double & z_ref_1 = c1[2];
    CPPUNIT_ASSERT_EQUAL( &z_ref_1, &c1.z() );
    // Check that the reference is not constant.
    c1[2] = 14.0;
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0, c1.z(), 1.0e-14);
    // But these are not changed.
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.0, c1.x(), 1.0e-14);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 13.0, c1.y(), 1.0e-14);

    // DONE
}
