import os
import shutil
import tempfile
import subprocess

def search_executable(cmd_list):
  for cmd in cmd_list:
    ret = shutil.which(cmd)
    if ret is not None:
        return ret
  raise FileNotFoundError('Executable not found: {}'.format(cmd_list))

cmd_clang = search_executable(['clang++', 'clang++-17', 'clang++-16'])
cmd_opt = search_executable(['opt', 'opt-17', 'opt-16'])
ctx_dir = tempfile.mkdtemp()


def compile_program(source: str) -> str:
  proc = subprocess.run(['./bin/miniclang', source],
                          capture_output=True,
                          timeout=10)
  assert proc.returncode == 0, proc.stderr
  ir = proc.stdout.decode('utf-8')
  return ir

def validate_compiled(filename, expected):
  proc = subprocess.run([cmd_clang, filename, '-o', 'tmp.out'])
  assert proc.returncode == 0, proc.stderr
  proc = subprocess.run(['./tmp.out'])
  assert proc.returncode == expected

def expect_wellformed(source, expected):
  ir = compile_program(source)
  with tempfile.TemporaryDirectory() as tmp_dirpath:
    tmp_ll_path = os.path.join(tmp_dirpath, 'tmp.ll')
    tmp_out_path = os.path.join(tmp_dirpath, 'tmp.out')
    with open(tmp_ll_path, 'w') as f:
      f.write(ir)
    proc = subprocess.run([cmd_clang, tmp_ll_path, '-o', tmp_out_path])
    assert proc.returncode == 0, proc.stderr
    proc = subprocess.run([tmp_out_path])
    assert proc.returncode == expected

def test_wellformed_programs():
  expect_wellformed('0', 0)
  expect_wellformed('42', 42)
  expect_wellformed('42+5', 47)
  expect_wellformed(' 5 + 3 - 1', 7)
  expect_wellformed('5+20-4', 21)
  expect_wellformed(' 12 + 34 - 5', 41)
