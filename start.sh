sudo apt-get install php-cgi
sudo apt-get install openssl
mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
mv ./bin/zia ..



