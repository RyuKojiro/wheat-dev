ENTRY(main)

OUTPUT_FORMAT(binary)

MEMORY
{
	ROM (rx) : ORIGIN = 0, LENGTH = 2M
	RAM (wx) : org = 0x80000000, len = 2M
}

SECTIONS
{
	.text {
		_TEXT_START_ = .;
		*(.text)
		_TEXT_END_ = .;
	}

	.data {
		_DATA_START_ = .;
		*(.data)
		_DATA_END_ = .;
	}

	.bss {
		_BSS_START_ = .;
		*(.bss)
		_BSS_END_ = .;
	}
}

