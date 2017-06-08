ENTRY(main)

OUTPUT_FORMAT(srec)

MEMORY
{
	flash (rx) : ORIGIN = 0x00000000, LENGTH = 64M
	ram (wx) : ORIGIN = 0x88000000, LENGTH = 32M
}

SECTIONS
{
	_GLOBAL_OFFSET_TABLE_ = .;
	.text : {
		_TEXT_START_ = .;
		*(.text.startup);
		*(.text);
		_TEXT_END_ = .;
	} >flash

	.data : {
		_DATA_START_ = .;
		*(.data);
		_DATA_END_ = .;
	} >flash

	.bss : {
		_BSS_START_ = .;
		*(.bss);
		_BSS_END_ = .;
	} >ram
}
