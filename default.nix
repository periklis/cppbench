let
  nixpkgs = import <nixpkgs> {};
  allpkgs = nixpkgs // pkgs;

  pkgs = with nixpkgs; {
    cppbench = callPackage ({
      stdenv, lib, autoconf, automake, gnumake, cmake, llvmPackages_39, boost
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
        llvmPackages_39.clang
        llvmPackages_39.libcxx
        llvmPackages_39.libcxxabi
     ];
  }) {};
};
in pkgs
