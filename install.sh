#!/bin/bash

QM="/usr/local/share/Qt-4.5.0/bin/qmake"

cd src
$QM -makefile
$QM
make
cd ..
