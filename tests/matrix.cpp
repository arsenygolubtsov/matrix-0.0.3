#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("add matrix")
{
    std::string input1{
        "3, 3\n"
        "1 2 3\n"
        "4 5 6\n"
        "7 8 9" }; 
    std::string input2{
        "3, 3\n"
        "9 8 7\n"
        "6 5 4\n"
        "3 2 1" };
    std::string input3{
        "3, 3\n"
        "10 10 10\n"
        "10 10 10\n"
        "10 10 10" };
    matrix_t matrix1, matrix2, matrix3;   
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    matrix1.read( istream1 );
    matrix2.read( istream2 );
    matrix3 = matrix1 + matrix2;
    std::ostringstream ostream;
    matrix3.write( ostream );
    REQUIRE( input3 == ostream.str() );
}

TEST_CASE("sub matrix")
{
    std::string input1{
        "3, 3\n"
        "1 2 3\n"
        "4 5 6\n"
        "7 8 9" }; 
    std::string input2{
        "3, 3\n"
        "0 1 2\n"
        "3 4 5\n"
        "6 7 8" };
    std::string input3{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    matrix_t matrix1, matrix2, matrix3;   
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    matrix1.read( istream1 );
    matrix2.read( istream2 );
    matrix3 = matrix1 - matrix2;
    std::ostringstream ostream;
    matrix3.write( ostream );
    REQUIRE( input3 == ostream.str() );
}

TEST_CASE("mul matrix")
{
    std::string input1{
        "3, 3\n"
        "1 2 3\n"
        "1 2 3\n"
        "1 2 3" }; 
    std::string input2{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input3{
        "3, 3\n"
        "11 11 11\n"
        "11 11 11\n"
        "11 11 11" };
    matrix_t matrix1, matrix2, matrix3;   
    std::istringstream istream1{ input1 };
    std::istringstream istream2{ input2 };
    matrix1.read( istream1 );
    matrix2.read( istream2 );
    matrix3 = matrix1 * matrix2;
    std::ostringstream ostream;
    matrix3.write( ostream );
    REQUIRE( input3 == ostream.str() );
}

