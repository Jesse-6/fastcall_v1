# NOTE: install 'lld' LLVM linker to use this script! Is a much better linker than 'ld', because it does not censors
# your decision on how a section should be. Also deliver smaller executables than GNU 'ld'. Also runs fast.

lldlibs="-lc $(pkg-config --libs gtk+-3.0)"
if [ -f "$1.subver" ]; then
        echo $(($(<$1.subver)+1)) > $1.subver
else
        echo 1 > $1.subver
fi
fasm2 -n $1.asm
ld.lld -L /usr/lib -s -o $1 $1.o -pie $lldlibs --dynamic-linker=/lib64/ld-linux-x86-64.so.2
echo "+1 LastError: $? `date`" >> $1.built
rm $1.o
strip -R .comment $1
if [ -n "$2" ]; then
        if [ $2 == '-x'  ]; then
                ./$1
        fi
fi
