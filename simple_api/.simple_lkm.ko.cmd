cmd_/home/PLib/simple_api/simple_lkm.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/PLib/simple_api/simple_lkm.ko /home/PLib/simple_api/simple_lkm.o /home/PLib/simple_api/simple_lkm.mod.o;  true
