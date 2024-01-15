#!/usr/bin/env nix-shell
#!nix-shell -p lsof gcc sqlite clang-tools cmake ninja git mesa glfw libGLU xorg.libX11 xorg.libXi xorg.libXcursor xorg.libXrandr xorg.libXinerama nix-index pulseaudio sqlitebrowser
#pulseaudioFull libpulseaudio
#!snix-shell -i bash

#nix-store --query --requisites /run/current-system | cut -d- -f2- | sort | uniq

#https://nixos.org/manual/nix/stable/command-ref/nix-shell
#https://search.nixos.org/packages

