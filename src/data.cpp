#include "data.h"
using namespace std;
void Info::read_airport() {
    std::ifstream ifs{"tluo9-yanzhen4-yirongc3/data/airport.csv"};
    // std::string city;
    // std::string airport_name;
    // std::string iata_code;
    if (!ifs.is_open()) std::cout<<"file not able to open" << std::endl;
    std::vector<std::string> info;
    std::string value;
    while (ifs.good()) {
        ifs >> value;
        if (ifs.fail()) {
            ifs.clear();
            ifs.ignore(1, '\n');
        } 
        else info.push_back(value);
    }
    std::cout<<info[0]<<std::endl;
    // while (std::getline(ifs, line)) {
    //     std::stringstream str(line);
    //     for (int a=0; a<5; a++) {
    //         Node tmp;
    //         double longitude;
    //         double latitude;
    //         getline(str,tmp.city_,',');
    //         getline(str,tmp.airport_name_,',');
    //         getline(str,tmp.iata_code_,',');
    //         getline(str,longitude,',');
    //         getline(str,latitude,'\n');
    //         tmp.longitude_=std::stod(longitude);
    //         tmp.latitude_=std::stod(latitude);
    //     }
    //     airports.push_back(tmp);
    // }
}
void Info::read_airline() {
    return;
}
