#!/usr/bin/env bash

add-apt-repository ppa:ubuntu-toolchain-r/test
apt-get update
apt-get install -y cmake
apt-get install -y gcc-5
