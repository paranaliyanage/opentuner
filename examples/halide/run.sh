#!/bin/bash
SOURCE_FILE=apps/heat_2d_np.cpp
echo "Source is : $SOURCE_FILE"
for input in 32 64 128 #256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576
    do
		sleep 5
        echo "Input: $input";
        python halidetuner.py --stop-after=10000 $SOURCE_FILE --halide-dir=../../../halide --label=heat --input-size="$input,$input" --limit=100
#       python halidetuner.py --stop-after=10000 apps/halide_heat2d.cpp --halide-dir=../../../halide --label=heat --input-size="$input1 ,$input2 ,$input2" --memory-limit=105601155200 --limit=100
    done
