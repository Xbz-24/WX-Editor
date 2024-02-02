{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.gnumake
    pkgs.wxGTK32
    pkgs.darwin.apple_sdk.frameworks.Cocoa
    pkgs.darwin.apple_sdk.frameworks.System
    pkgs.darwin.apple_sdk.frameworks.IOKit
  ];
   shellHook = ''
   '';
}
