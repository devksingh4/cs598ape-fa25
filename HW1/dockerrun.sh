#!/bin/bash
docker run -it --security-opt seccomp=unconfined -v $PWD:/host wsmoses/598ape /bin/bash
