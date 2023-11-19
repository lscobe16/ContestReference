#define time(f...) [&](){\
    auto startT = chrono::high_resolution_clock::now(); \
    f; \
    auto stopT = chrono::high_resolution_clock::now(); \
    return chrono::duration_cast<chrono::milliseconds>(stopT - startT).count();}()
