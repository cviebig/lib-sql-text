#include "sql/text/parser_def.hpp"
#include "test.hpp"

namespace sql{ namespace text {

    TEST_CASE( "Star schema benchmark: Q1.1", "[ssb]" ) {
        auto e = parse(sql, "SELECT sum(lo_extendedprice*lo_discount) AS revenue FROM lineorder, date WHERE lo_orderdate = d_datekey AND d_year = 1993 AND lo_discount > 1 AND lo_discount < 3 AND lo_quantity < 25");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q1.2", "[ssb]" ) {
        auto e = parse(sql, "SELECT sum(lo_extendedprice*lo_discount) AS revenue FROM lineorder, date WHERE lo_orderdate = d_datekey AND d_yearmonthnum = 199401 AND lo_discount > 4 AND lo_discount < 6 AND lo_quantity > 26 AND lo_quantity < 35");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q1.3", "[ssb]" ) {
        auto e = parse(sql, "SELECT sum(lo_extendedprice*lo_discount) AS revenue FROM lineorder, date WHERE lo_orderdate = d_datekey AND d_weeknuminyear = 6 AND d_year = 1994 AND lo_discount > 5 AND lo_discount < 7 AND lo_quantity > 26 AND lo_quantity < 35");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q2.1", "[ssb]" ) {
        auto e = parse(sql, "SELECT sum(lo_revenue), d_year, p_brand1 FROM lineorder, date, part, supplier WHERE lo_orderdate = d_datekey AND lo_partkey = p_partkey AND lo_suppkey = s_suppkey AND p_category = 'MFGR#12' AND s_region = 'AMERICA' GROUP BY d_year, p_brand1 ORDER BY d_year, p_brand1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q2.2", "[ssb]" ) {
        auto e = parse(sql, "SELECT sum(lo_revenue), d_year, p_brand1 FROM lineorder, date, part, supplier WHERE lo_orderdate = d_datekey AND lo_partkey = p_partkey AND lo_suppkey = s_suppkey AND p_brand1 > 'MFGR#2221' AND p_brand1 < 'MFGR#2228' AND s_region = 'ASIA' GROUP BY d_year, p_brand1 ORDER BY d_year, p_brand1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q2.3", "[ssb]" ) {
        auto e = parse(sql, "SELECT sum(lo_revenue), d_year, p_brand1 FROM lineorder, date, part, supplier WHERE lo_orderdate = d_datekey AND lo_partkey = p_partkey AND lo_suppkey = s_suppkey AND p_brand1 = 'MFGR#2221' AND s_region = 'EUROPE' GROUP BY d_year, p_brand1 ORDER BY d_year, p_brand1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q3.1", "[ssb]" ) {
        auto e = parse(sql, "SELECT c_nation, s_nation, d_year, sum(lo_revenue) AS revenue FROM customer, lineorder, supplier, date WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_orderdate = d_datekey AND c_region = 'ASIA' AND s_region = 'ASIA' AND d_year >= 1992 AND d_year <= 1997 GROUP BY c_nation, s_nation, d_year ORDER BY d_year ASC, revenue DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q3.2", "[ssb]" ) {
        auto e = parse(sql, "SELECT c_city, s_city, d_year, sum(lo_revenue) AS revenue FROM customer, lineorder, supplier, date WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_orderdate = d_datekey AND c_nation = 'UNITED STATES' AND s_nation = 'UNITED STATES' AND d_year >= 1992 AND d_year <= 1997 GROUP BY c_city, s_city, d_year ORDER BY d_year ASC, revenue DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q3.3", "[ssb]" ) {
        auto e = parse(sql, "SELECT c_city, s_city, d_year, sum(lo_revenue) AS revenue FROM customer, lineorder, supplier, date WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_orderdate = d_datekey AND (c_city='UNITED KI1' OR c_city='UNITED KI5') AND (s_city='UNITED KI1' OR s_city='UNITED KI5') AND d_year >= 1992 AND d_year <= 1997 GROUP BY c_city, s_city, d_year ORDER BY d_year ASC, revenue DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q3.4", "[ssb]" ) {
        auto e = parse(sql, "SELECT c_city, s_city, d_year, sum(lo_revenue) AS revenue FROM customer, lineorder, supplier, date WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_orderdate = d_datekey AND (c_city='UNITED KI1' OR c_city='UNITED KI5') AND (s_city='UNITED KI1' OR s_city='UNITED KI5') AND d_yearmonth = 'Dec1997' GROUP BY c_city, s_city, d_year ORDER BY d_year ASC, revenue DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q4.1", "[ssb]" ) {
        auto e = parse(sql, "SELECT d_year, c_nation, sum(lo_revenue - lo_supplycost) AS profit FROM date, customer, supplier, part, lineorder WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_partkey = p_partkey AND lo_orderdate = d_datekey AND c_region = 'AMERICA' AND s_region = 'AMERICA' AND (p_mfgr = 'MFGR#1' OR p_mfgr = 'MFGR#2') GROUP BY d_year, c_nation ORDER BY d_year, c_nation");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q4.2", "[ssb]" ) {
        auto e = parse(sql, "SELECT d_year, s_nation, p_category, sum(lo_revenue - lo_supplycost) AS profit FROM date, customer, supplier, part, lineorder WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_partkey = p_partkey AND lo_orderdate = d_datekey AND c_region = 'AMERICA' AND s_region = 'AMERICA' AND (d_year = 1997 OR d_year = 1998) AND (p_mfgr = 'MFGR#1' AND p_mfgr = 'MFGR#2') GROUP BY d_year, s_nation, p_category ORDER BY d_year, s_nation, p_category");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: Q4.3", "[ssb]" ) {
        auto e = parse(sql, "SELECT d_year, s_city, p_brand1, sum(lo_revenue - lo_supplycost) AS profit FROM date, customer, supplier, part, lineorder WHERE lo_custkey = c_custkey AND lo_suppkey = s_suppkey AND lo_partkey = p_partkey AND lo_orderdate = d_datekey AND c_region = 'AMERICA' AND s_nation = 'UNITED STATES' AND (d_year = 1997 OR d_year = 1998) AND p_category = 'MFGR#14' GROUP BY d_year, s_city, p_brand1 ORDER BY d_year, s_city, p_brand1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }



    TEST_CASE( "Star schema benchmark: table LINEORDER", "[ssb]" ) {
        auto e = parse(sql, "CREATE TABLE LINEORDER (  LO_ORDERKEY INT,  LO_LINENUMBER INT(7),  LO_CUSTKEY INT,  LO_PARTKEY INT,  LO_SUPPKEY INT,  LO_ORDERDATE INT,  LO_ORDERPRIORITY TEXT(15),  LO_SHIPPRIORITY TEXT(1),   LO_QUANTITY INT(1, 50),  LO_EXTENDEDPRICE FLOAT(55,450),  LO_ORDTOTALPRICE FLOAT(388,000),  LO_DISCOUNT INT(0, 10),  LO_REVENUE FLOAT,  LO_SUPPLYCOST FLOAT,  LO_TAX INT(0, 8),  LO_COMMITDATE INT,  LO_SHIPMODE TEXT(10),  CONSTRAINT LINEORDER_PK PRIMARY KEY (LO_ORDERKEY, LO_LINENUMBER),  CONSTRAINT LINEORDER_FK_CUSTKEY FOREIGN KEY (LO_CUSTKEY) REFERENCES CUSTOMER (C_CUSTKEY),  CONSTRAINT LINEORDER_FK_PARTKEY FOREIGN KEY (LO_PARTKEY) REFERENCES PART (P_PARTKEY),  CONSTRAINT LINEORDER_FK_SUPPKEY FOREIGN KEY (LO_SUPPKEY) REFERENCES SUPPLIER (S_SUPPKEY),  CONSTRAINT LINEORDER_FK_ORDERDATE FOREIGN KEY (LO_ORDERDATE) REFERENCES DATE (D_DATEKEY),  CONSTRAINT LINEORDER_FK_COMMITDATE FOREIGN KEY (LO_COMMITDATE) REFERENCES DATE (D_DATEKEY))");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: table PART", "[ssb]" ) {
        auto e = parse(sql, "CREATE TABLE PART (  P_PARTKEY INT,  P_NAME TEXT(0,22),  P_MFGR TEXT(6),  P_CATEGORY TEXT(7),  P_BRAND1 TEXT(9),  P_COLOR TEXT(0,11),  P_TYPE TEXT(0,25),  P_SIZE INT(1,50),  P_CONTAINER TEXT(10),  CONSTRAINT PART_PK PRIMARY KEY (P_PARTKEY))");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: table SUPPLIER", "[ssb]" ) {
        auto e = parse(sql, "CREATE TABLE SUPPLIER (  S_SUPPKEY INT,  S_NAME TEXT(25),  S_ADDRESS TEXT(0,25),  S_CITY TEXT(0,10),  S_NATION TEXT(15),  S_REGION TEXT(12),  S_PHONE TEXT(15),  CONSTRAINT SUPPLIER_PK PRIMARY KEY (S_SUPPKEY))");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: table CUSTOMER", "[ssb]" ) {
        auto e = parse(sql, "CREATE TABLE CUSTOMER (  C_CUSTKEY INT,   C_NAME TEXT(0,25),  C_ADDRESS TEXT(0,25),  C_CITY TEXT(10),  C_NATION TEXT(15))");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Star schema benchmark: table DATE", "[ssb]" ) {
        auto e = parse(sql, "CREATE TABLE DATE (  D_DATEKEY INT,  D_DATE TEXT(18),  D_DAYOFWEEK TEXT(8),  D_MONTH TEXT(9),  D_YEAR INT(1992,1998),  D_YEARMONTHNUM INT(111111,300012),  D_YEARMONTH TEXT(7),  D_DAYNUMINWEEK INT(1,7),  D_DAYNUMINMONTH INT(1,31),  D_DAYNUMINYEAR INT(1,366),  D_MONTHNUMINYEAR INT(1,12),  D_WEEKNUMINYEAR INT(1,53),  D_SELLINGSEASON TEXT(0,12),  D_LASTDAYINWEEKFL BOOLEAN,  D_LASTDAYINMONTHFL BOOLEAN,  D_HOLIDAYFL BOOLEAN,  D_WEEKDAYFL BOOLEAN,  CONSTRAINT DATE_PK PRIMARY KEY (D_DATEKEY))");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
