#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
int main(int argc, char **argv)
{
    boost::gregorian::date d(boost::gregorian::day_clock::local_day());
    std::cout<< d.year() << " " << d.month() << " " << d.day() << std::endl;
    return 0;
}
