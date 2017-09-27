let
  nixpkgs = import <nixpkgs> {};

  pkgs = with nixpkgs; {
    cppbench = callPackage ({
      stdenv, lib, autoconf, automake, gnumake, cmake, clangStdenv, libcxxStdenv, boost
    }:
    stdenv.mkDerivation rec {
      name = "cppbench-env";
      version = "1.0.0.0";

      buildInputs = [
        autoconf
        automake
        boost
        cmake
        gdb
        gnumake
        clangStdenv
        libcxxStdenv
      ];

      buildConstants = ["Contant 1" "Constant 2"];

      shellHook = ''
        cd build
        make
        ctest
      '';

    }) { /* Put your overrides here */ };
  };
in pkgs
