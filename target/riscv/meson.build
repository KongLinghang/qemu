# FIXME extra_args should accept files()
dir = meson.current_source_dir()

gen = [
  decodetree.process('insn16.decode', extra_args: ['--static-decode=decode_insn16', '--insnwidth=16']),
  decodetree.process('insn32.decode', extra_args: '--static-decode=decode_insn32'),
  decodetree.process('vector-071.decode', extra_args: '--static-decode=decode_vector_7'),
]

riscv_ss = ss.source_set()
riscv_ss.add(gen)
riscv_ss.add(files(
  'cpu.c',
  'cpu_helper.c',
  'csr.c',
  'fpu_helper.c',
  'gdbstub.c',
  'op_helper.c',
  'vector_helper.c',
  'bitmanip_helper.c',
  'vector_helper_7.c',
  'packed_helper.c',
  'translate.c',
))

riscv_softmmu_ss = ss.source_set()
riscv_softmmu_ss.add(files(
  'arch_dump.c',
  'pmp.c',
  'monitor.c',
  'machine.c'
))

target_arch += {'riscv': riscv_ss}
target_softmmu_arch += {'riscv': riscv_softmmu_ss}
