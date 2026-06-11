ldlibs="-lc $(pkg-config --libs gtk4)"
ldentry=Start
if [ -f "$1.subver" ]; then
        echo $(($(<$1.subver)+1)) > $1.subver
else
        echo 1 > $1.subver
fi
fasm2 -n $1.asm
ld -o $1 $1.o -e $ldentry -pie $ldlibs --gc-sections --dynamic-linker=/lib64/ld-linux-x86-64.so.2
echo "+1 LastError: $? `date`" >> $1.built
rm $1.o
strip --strip-unneeded $1
if [ -n "$2" ]; then
        if [ $2 == '-x'  ]; then
                ./$1
        fi
fi
