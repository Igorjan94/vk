with import <nixpkgs> {};

buildPythonPackage {
    name = "VkParser";
    buildInputs = with pkgs.pythonPackages; [ json, requests, collections, binascii, time ];
    src = fetchurl {
        url = "https://github.com/Igorjan94/vk/blob/master/vkparser.py";
        sha256 = "ffc967e4811bb384bbbdf7bfd736228c281d320a14cea7f578039da51063db4d";
    };
}
