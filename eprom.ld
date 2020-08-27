ENTRY(main)

OUTPUT_FORMAT(binary)

MEMORY
{
	rom (rx) : ORIGIN = 0, LENGTH = 2M
	ram (wx) : org = 0x08000000, len = 64M
}

SECTIONS
{
	_GLOBAL_OFFSET_TABLE_ = .;
	.text : {
		_TEXT_START_ = .;
		*(.text.startup);
		*(.text)
		_TEXT_END_ = .;
	} >ram

	.data : {
		_DATA_START_ = .;
		*(.data)
		_DATA_END_ = .;
	} >ram

	.bss : {
		_BSS_START_ = .;
		*(.bss)
		_BSS_END_ = .;
	} >ram
}

