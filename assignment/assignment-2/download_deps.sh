#!/bin/bash

# Create deps directory
mkdir -p deps

# Download pugixml
echo "Downloading pugixml..."
git clone https://github.com/zeux/pugixml.git deps/pugixml

# Download spdlog
echo "Downloading spdlog..."
git clone -b v1.14.1 https://github.com/gabime/spdlog.git deps/spdlog

# Download cxxopts
echo "Downloading cxxopts..."
git clone https://github.com/jarro2783/cxxopts.git deps/cxxopts
