#!/bin/bash
cd `dirname $0`
find . -name '*.o'|xargs rm -f
find . -name '*.d'|xargs rm -f

