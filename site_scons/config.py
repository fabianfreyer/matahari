#vim : set ft=python :
import debug
from SCons.Script import Dir

debugger = debug.Bochs

components = {
	'mbr':	{
		'modules': ['entry', 'disk', 'io', 'partition_table'],
		'sections': ['.text_mbr', '.data_mbr', '.partition_table', '.sig']
		},
	'stage2': {
		'modules': ['entry', 'gdt', 'pmode', 'video', 'a20', 'mem', 'debug', 'fat', 'diskio'],
		'sections': ['.text_stage2', '.data_stage2']
		}
	}

toolchain = {
	'tuple': 'i386-baremetal-elf',
	'base': 'toolchain/target'
	}
