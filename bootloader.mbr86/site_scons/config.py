#vim : set ft=python :
import debug
from SCons.Script import Dir
import yaml

debugger = debug.Bochs

with open("config.yml", "r") as stream:
    configuration = yaml.load(stream)

components = {
	'mbr':	{
		'modules': configuration['stage1']['modules'],
		'sections': ['.text_mbr', '.data_mbr', '.partition_table', '.sig']
		},
	'stage2': {
		'modules': configuration['stage2']['modules'],
		'sections': ['.text_stage2', '.data_stage2']
		}
	}

toolchain = {
	'tuple': 'i386-baremetal-elf',
	'base': 'toolchain/target'
	}
