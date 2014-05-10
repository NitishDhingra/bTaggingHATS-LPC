#!/bin/sh

mv bTaggingHATS-LPC/* . 
rm -rf bTaggingHATS-LPC
scram b -j10
