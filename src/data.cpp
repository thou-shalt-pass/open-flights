#include "data.h"

void Data::read_airport() {
    std::ifstream ifs{"data/airport.csv"};
    if (!ifs.is_open()) std::cout<<"file not able to open" << std::endl;

    // read each line
    std::string line;
    while (std::getline(ifs, line)) {
        std::vector<std::string> info;
        bool quotation = false;
        std::string str="";

        for (size_t a=0; a<line.size(); a++) {
            char curr = line[a];
            // outside of a quote
            if (!quotation) {
                // start a quote
                if (curr == '"') {
                    quotation = true;
                    str+='"';
                } else if (curr == ',') {
                    info.push_back(str);
                    str="";
                } else str+=curr;
            }
            // within a quote
            else {
                // end a quote
                if (curr == '"' ) { 
                    quotation = false;
                    str+='"';
                } else {
                    str+=curr;
                }
            }
        }
        Node tmp;
        tmp.city_ = info[0];
        tmp.airport_name_ = info[1];
        tmp.iata_code_ = info[2];
        tmp.longitude_ = std::stod(info[3]);
        tmp.latitude_ = std::stod(info[4]);
        airports.push_back(tmp);
    }
}
std::vector<Node> Data::get_airports(){
    return airports;
}
void Data::display(Node airprot) {
    std::cout<<airprot.city_<<std::endl;
    std::cout<<airprot.airport_name_<<std::endl;
    std::cout<<airprot.iata_code_<<std::endl;
    std::cout<<airprot.longitude_<<std::endl;
    std::cout<<airprot.latitude_<<std::endl;
}
void Data::read_airline() {
    return;
}
