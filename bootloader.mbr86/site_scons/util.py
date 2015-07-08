from SCons.Script import Split, File
import subprocess, re
from config import components, toolchain
import collections

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

# Idea shamelessly stolen and extended from
# http://stackoverflow.com/questions/6027558/flatten-nested-python-dictionaries-compressing-keys#answer-6027615
def flatten(d, parent_key='', sep='_'):
    items = []
    for k, v in d.items():
        new_key = str(parent_key) + sep + str(k) if parent_key else k
        if isinstance(v, collections.MutableMapping):
            items.extend(flatten(v, new_key, sep=sep).items())
        elif isinstance(v, collections.MutableSequence):
            items.append((new_key, ', '.join(v)))
        elif isinstance(v, bool):
            items.append((new_key, 1 if v else 0))
        else:
            items.append((new_key, v))
    return dict(items)

