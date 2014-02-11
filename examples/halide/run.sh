#!/bin/bash
for input1 in 32 64 #128 256 512 1024 2048 4096 8192 16384 32768 65536
#for input1 in 131072 262144 524288 1048576
    do
        for a in `seq 2`
            do
				sleep 5
                input2=`expr $input1 \\* $a`;
                echo "Input: \"$input1 ,$input2\"";
#				python halidetuner.py --stop-after=5 apps/heat_1d_np.cpp --halide-dir=../../../halide --label=heat --input-size=128,128 --limit=100
                python halidetuner.py --stop-after=5 apps/heat_2d_np.cpp --halide-dir=../../../halide --label=heat --input-size="$input1,$input1,$input2" --limit=100
#               python halidetuner.py --stop-after=10000 apps/halide_heat2d.cpp --halide-dir=../../../halide --label=heat --input-size="$input1 ,$input2 ,$input2" --memory-limit=105601155200 --limit=100
            done;
    done

