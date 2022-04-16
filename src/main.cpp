#include "data.h"
#include <iostream>

int main() {
    Data data;
    data.read_airport();
    std::vector<Node> airports = data.get_airports();
    data.display(airports[1]);
    return 0;
}
