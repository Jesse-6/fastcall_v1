; Properly detects ELF64 or ELF64 executable/dynamic, and includes the correct header
if defined ELF.SECTION_NAME
    include 'fastcall_v2.inc'
else
    include 'fastcall_v1.inc'
end if
