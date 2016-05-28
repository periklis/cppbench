#!/usr/bin/env bash

apt-add-repository -y ppa:ubuntu-toolchain-r/test
apt-get update -qq
apt-get install -yqq automake build-essential cmake gcc-5 g++-5 git doxygen nginx-full zsh
apt-get install -yqq libboost1.55-all-dev
chsh -s $(which zsh)
