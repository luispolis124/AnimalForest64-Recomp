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
        boot_TEXT_START = .;
        build/asm/1000.s.o(.text);
        . = ALIGN(., 16);
        boot_TEXT_END = .;
        boot_TEXT_SIZE = ABSOLUTE(boot_TEXT_END - boot_TEXT_START);
        boot_DATA_START = .;
        build/asm/1000.s.o(.data);
        . = ALIGN(., 16);
        boot_DATA_END = .;
        boot_DATA_SIZE = ABSOLUTE(boot_DATA_END - boot_DATA_START);
        boot_RODATA_START = .;
        build/asm/1000.s.o(.rodata);
        . = ALIGN(., 16);
        boot_RODATA_END = .;
        boot_RODATA_SIZE = ABSOLUTE(boot_RODATA_END - boot_RODATA_START);
    }
    boot_bss_VRAM = ADDR(.boot_bss);
    .boot_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        boot_BSS_START = .;
        build/asm/1000.s.o(.bss);
        . = ALIGN(., 16);
        boot_BSS_END = .;
        boot_BSS_SIZE = ABSOLUTE(boot_BSS_END - boot_BSS_START);
    }
    __romPos += SIZEOF(.boot);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    boot_ROM_END = __romPos;
    boot_VRAM_END = .;

    boot_data_ROM_START = __romPos;
    boot_data_VRAM = ADDR(.boot_data);
    .boot_data 0x80000460 : AT(boot_data_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        boot_data_DATA_START = .;
        build/asm/data/boot_data.data.s.o(.data);
        boot_data_DATA_END = .;
        boot_data_DATA_SIZE = ABSOLUTE(boot_data_DATA_END - boot_data_DATA_START);
    }
    __romPos += SIZEOF(.boot_data);
    boot_data_ROM_END = __romPos;
    boot_data_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
