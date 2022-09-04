if [ -n "$1" ]
then
    if [ "$1" = "Lab0" ]
    then
        cp ./src/main/resource/Lab0_inst.asm ./src/main/resource/inst.asm
        cp ./src/main/resource/Lab0_m_code.hex ./src/main/resource/m_code.hex
    elif [ "$1" = "Lab1" ]
    then
        cp ./src/main/resource/Lab1_inst.asm ./src/main/resource/inst.asm
        cp ./src/main/resource/Lab1_m_code.hex ./src/main/resource/m_code.hex
    elif [ "$1" = "Hw1" ]
    then
        cp ./src/main/resource/Hw1_inst.asm ./src/main/resource/inst.asm
        cp ./src/main/resource/Hw1_m_code.hex ./src/main/resource/m_code.hex
    elif [ "$1" = "group" ]
    then
        cp ../lab4-group/example_code/inst.asm ./src/main/resource/inst.asm
        cp ../lab4-group/example_code/m_code.hex ./src/main/resource/m_code.hex
	cp ../lab4-group/example_code/data.hex ./src/main/resource/data.hex
    else
        echo "[Error] parameter 1 is wrong"
    fi
else
    echo "[Error] usage should be: ./test_data.sh <which Lab>"
fi
