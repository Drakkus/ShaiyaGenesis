# Shaiya Genesis

## Introduction
Shaiya Genesis is an emulator for the Shaiya MMORPG. It is written mostly in C++. The goal is to provide an open source, community involved emulator for Shaiya, and provide developers with an alternative that allows them to better develop content, and operate using a more stable server.

Shaiya Genesis is completely open source; community involvement is highly encouraged. If you wish to contribute ideas or code, please make a pull request to our [Github repository](https://github.com/TristonPlummer/ShaiyaGenesis/pulls).

## Requirements
The following libraries are required to build Shaiya Genesis:

 - Boost >= 1.55
 - MySQL
 - OpenSSL

## Building

	```
	apt-get install libboost-all-dev libmysql++-dev libssl-dev
	cmake -B./build/ -H. && cd build && make
	```
	
## Copyright
License: MIT
Read file: [LICENSE](LICENSE)
