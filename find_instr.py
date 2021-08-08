from immlib import *
import struct
def main(args):
    immunity = Debugger()
    immunity.log('')
    immunity.log('start script')
    modules = ['vuln18.exe', 'func.dll', 'KERNEL32.DLL', 'msvcrt.dll', 'KERNELBASE.dll', 'ntdll.dll']
    for module in modules:
        mod = immunity.getModule(module)
        if not mod:
            immunity.log('no module ' + module)
            continue
        MZbase = mod.getBaseAddress()
        PEoffset = struct.unpack('<L',immunity.readMemory(MZbase + 0x3c,4))[0]
        PEbase = MZbase + PEoffset
        flags = struct.unpack('<H',immunity.readMemory(PEbase + 0x5e,2))[0]
        if((flags&0x0040) == 0):
            immunity.log('module ' + module + ' no ASLR')
        else:
            immunity.log('module ' + module + ' ASLR')
    return 'end' 