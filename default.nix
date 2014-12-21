with import <nixpkgs> {};

with stdenv;
with pkgs;

buildPythonPackage {
    name = "VkParser";
    buildInputs = with pkgs.pythonPackages; [ requests time ];
    src = ./.;
}
