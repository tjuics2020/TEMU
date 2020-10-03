OUTPUT_ARCH(mips)
ENTRY(main)
SECTIONS
{
        . = 0x00000000;
        .text : 
        {
            *(.text)
            _etext = .;
        }

        . = 0x00010000;
        .data : 
        {
            *(.data)              
        }

	.bss :
        {
            *(.bss)
        }

} 
