#!/bin/bash
make clean
make -j
cp open_testcase/example3/*.bin .
./CMP
vimdiff report.rpt open_testcase/example3/report.rpt
