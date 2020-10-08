#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <unordered_map>
int main(int argc, char **argv)
{
    boost::gregorian::date d(boost::gregorian::day_clock::local_day());
    std::cout<< d.year() << " " << d.month() << " " << d.day() << std::endl;
	using String = std::basic_string<char, std::char_traits<char>>;
    boost::hash<std::pair<String, String>> string_hash;
    std::unordered_map<std::pair<String, String>, String, boost::hash<std::pair<String, String>>> mapTest;
    std::cout << string_hash({"test", "test"}) << "\n";
    return 0;
}
