#!/usr/bin/env zsh
mv vkparser.temp vkparser.data 2>/dev/null
for i in {1..1000}
do
    ./vkparser
    rm -rf vkparser.data
    mv vkparser.temp vkparser.data 2>/dev/null
done
