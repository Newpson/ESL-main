SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x1c000, LENGTH = 0x64000
	RAM (rwx) :	ORIGIN = 0x20001198, LENGTH = 0x1ee68
}

SECTIONS
{
}

SECTIONS
{
	. = ALIGN(4);
	.mem_section_dummy_ram :
	{
	}
	.log_dynamic_data :
	{
		PROVIDE(__start_log_dynamic_data = .);
		KEEP(*(SORT(.log_dynamic_data*)))
		PROVIDE(__stop_log_dynamic_data = .);
	} > RAM
	.log_filter_data :
	{
		PROVIDE(__start_log_filter_data = .);
		KEEP(*(SORT(.log_filter_data*)))
		PROVIDE(__stop_log_filter_data = .);
	} > RAM

} INSERT AFTER .data;

SECTIONS
{
	.mem_section_dummy_rom :
	{
	}
	.log_const_data :
	{
		PROVIDE(__start_log_const_data = .);
		KEEP(*(SORT(.log_const_data*)))
		PROVIDE(__stop_log_const_data = .);
	} > FLASH
	.log_backends :
	{
		PROVIDE(__start_log_backends = .);
		KEEP(*(SORT(.log_backends*)))
		PROVIDE(__stop_log_backends = .);
	} > FLASH
	.nrf_balloc :
	{
		PROVIDE(__start_nrf_balloc = .);
		KEEP(*(.nrf_balloc))
		PROVIDE(__stop_nrf_balloc = .);
	} > FLASH
	.sdh_soc_observers :
	{
		PROVIDE(__start_sdh_soc_observers = .);
		KEEP(*(SORT(.sdh_stack_observers*)))
		PROVIDE(__stop_sdh_soc_observers = .);
	} > FLASH
	.sdh_stack_observers :
	{
		PROVIDE(__start_sdh_stack_observers = .);
		KEEP(*(SORT(.sdh_stack_observers*)))
		PROVIDE(__stop_sdh_stack_observers = .);
	} > FLASH

} INSERT AFTER .text

INCLUDE "nrf_common.ld"
