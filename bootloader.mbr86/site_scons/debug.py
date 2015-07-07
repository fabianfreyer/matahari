import subprocess

qemu="qemu-system-i386"

def QEMU(env, target, sources):
	pass

def Bochs(env, target, source):
	bochs = subprocess.Popen(['bochs', '-q'], stdout=subprocess.PIPE)
	bochs.communicate()
