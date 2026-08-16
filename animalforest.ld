SECTIONS
{
    HIDDEN(__romPos = 0);
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header : AT(header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        build/asm/header.s.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    boot_ROM_START = __romPos;
    boot_VRAM = ADDR(.boot);
    .boot 0x80000400 : AT(boot_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        boot_DATA_START = .;
        build/assets/boot.bin.o(.data);
        boot_DATA_END = .;
        boot_DATA_SIZE = ABSOLUTE(boot_DATA_END - boot_DATA_START);
    }
    __romPos += SIZEOF(.boot);
    boot_ROM_END = __romPos;
    boot_VRAM_END = .;

    code_ROM_START = __romPos;
    code_VRAM = ADDR(.code);
    .code 0x80000400 : AT(code_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        code_TEXT_START = .;
        build/asm/boot_code.s.o(.text);
        build/asm/11F0.s.o(.text);
        build/asm/14A0.s.o(.text);
        build/asm/1640.s.o(.text);
        build/asm/17F0.s.o(.text);
        . = ALIGN(., 16);
        code_TEXT_END = .;
        code_TEXT_SIZE = ABSOLUTE(code_TEXT_END - code_TEXT_START);
        code_DATA_START = .;
        build/asm/boot_code.s.o(.data);
        build/asm/11F0.s.o(.data);
        build/asm/14A0.s.o(.data);
        build/asm/1640.s.o(.data);
        build/asm/17F0.s.o(.data);
        build/assets/2000.bin.o(.data);
        . = ALIGN(., 16);
        code_DATA_END = .;
        code_DATA_SIZE = ABSOLUTE(code_DATA_END - code_DATA_START);
        code_RODATA_START = .;
        build/asm/boot_code.s.o(.rodata);
        build/asm/11F0.s.o(.rodata);
        build/asm/14A0.s.o(.rodata);
        build/asm/1640.s.o(.rodata);
        build/asm/17F0.s.o(.rodata);
        . = ALIGN(., 16);
        code_RODATA_END = .;
        code_RODATA_SIZE = ABSOLUTE(code_RODATA_END - code_RODATA_START);
    }
    code_bss_VRAM = ADDR(.code_bss);
    .code_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        code_BSS_START = .;
        build/asm/boot_code.s.o(.bss);
        build/asm/11F0.s.o(.bss);
        build/asm/14A0.s.o(.bss);
        build/asm/1640.s.o(.bss);
        build/asm/17F0.s.o(.bss);
        . = ALIGN(., 16);
        code_BSS_END = .;
        code_BSS_SIZE = ABSOLUTE(code_BSS_END - code_BSS_START);
    }
    __romPos += SIZEOF(.code);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    code_ROM_END = __romPos;
    code_VRAM_END = .;

    data_ROM_START = __romPos;
    data_VRAM = ADDR(.data);
    .data : AT(data_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        data_DATA_START = .;
        build/assets/data.bin.o(.data);
        data_DATA_END = .;
        data_DATA_SIZE = ABSOLUTE(data_DATA_END - data_DATA_START);
    }
    __romPos += SIZEOF(.data);
    data_ROM_END = __romPos;
    data_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
