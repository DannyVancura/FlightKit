//
//  XplaneBuffer.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#include "XplaneBuffer.hpp"

Data::Xplane::XplaneBuffer::XplaneBuffer(unsigned char *data, long length) {
    if (length >= 5) {
        prefix = (char *) malloc(5);
        memcpy(prefix, data, 5);
    }
    for (int i = 5; i < length; i += (sizeof(int) + 8 * sizeof(float))) {
        int index = 0;
        float values[8];

        memcpy(&index, data + i, sizeof(int));
        memcpy(values, data + i + sizeof(int), 8 * sizeof(float));
        std::vector<float> vector(8);
        for (int j = 0; j < 8; j++) {
            vector[j] = values[j];
        }
        dataMap.insert(std::pair<int, std::vector<float>>(index, vector));
    }
    airplane = new Airplane();
}

void Data::Xplane::XplaneBuffer::debug() {
    printf("Prefix: %s", prefix);
}
