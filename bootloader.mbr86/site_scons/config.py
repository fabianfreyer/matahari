#vim : set ft=python :
import debug
from SCons.Script import Dir
import yaml

debugger = debug.Bochs

with open("modules.yml", "r") as stream:
    modules = yaml.load(stream)

components = {
	'mbr':	{
		'modules': modules['mbr'],
		'sections': ['.text_mbr', '.data_mbr', '.partition_table', '.sig']
		},
	'stage2': {
		'modules': modules['stage2'],
		'sections': ['.text_stage2', '.data_stage2']
		}
	}

toolchain = {
	'tuple': 'i386-baremetal-elf',
	'base': 'toolchain/target'
	}