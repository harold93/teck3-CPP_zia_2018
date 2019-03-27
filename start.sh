sudo apt-get install php-cgi
mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
mv ./bin/zia ..



