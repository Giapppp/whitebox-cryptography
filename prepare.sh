g++ -std=c++17 generateSBox.cpp shake128.cpp constant.cpp -o generateSBox
g++ -std=c++17 WBspn.cpp spn.cpp constant.cpp shake128.cpp -o WBspn
./generateSBox 
