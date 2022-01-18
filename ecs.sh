#!/bin/bash
cd build/ && cmake -DCMAKE_BUILD_TYPE=Debug ..  && cmake --build . -j8 && cd ../ && ./build/bin/Rtype_client localhost 5000
