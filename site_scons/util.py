from SCons.Script import Split, File
import subprocess, re
from config import components, toolchain

# move to util
tool = lambda t: File(('#/%(base)s/%(tuple)s/bin/%(tuple)s-' % toolchain) + t).abspath

def Component(name, modules):
	return ['src/%(component)s/%(module)s.c' % {'component':name, 'module':module} for module in Split(modules)]

def CheckSectionHeaders(env, target, source):
	header_dump = subprocess.check_output([env.Dictionary()['OBJDUMP'], '-h', str(target[0])])
	headers = {
			name: (int(size,16), int(vma,16), int(lma,16))
			for (name, size, vma, lma)
			in re.findall(r'\d+\s+(\.\w+)\s+([\da-fA-F]+)\s+([\da-fA-F]+)\s+([\da-fA-F]+)', header_dump)
			}
	component_sizes = {
			name: sum([headers[section][0] for section in components[name]['sections']])
			for name in components
			}
	if component_sizes['mbr'] >= 512:
		raise OverflowError("MBR too large")
	for component in component_sizes:
		print "  sizeof(%s) = %d" % (component, component_sizes[component])


