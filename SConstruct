# vim: set ft=python :


colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

compile_source_message = '%sCompiling %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])
compile_shared_source_message = '%sCompiling shared %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])
link_program_message = '%sLinking %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

if ARGUMENTS.get('VERBOSE') != "1":
    env = Environment(
        CXXCOMSTR = compile_source_message,
        CCCOMSTR = compile_source_message,
        SHCCCOMSTR = compile_shared_source_message,
        SHCXXCOMSTR = compile_shared_source_message,
        LINKCOMSTR = link_program_message
    )
else:
    env = Environment()

SConscript(dirs=['bootloader.mbr86'], exports='env')
