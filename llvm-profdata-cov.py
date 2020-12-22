import subprocess
import shlex

subprocess.call(shlex.split("""llvm-profdata merge
  Debug/libCloudundancyTests/coverage.profraw -sparse -o coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov report
  Debug/libCloudundancyTests/libCloudundancyTests -instr-profile=coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov show
  Debug/libCloudundancyTests/libCloudundancyTests -instr-profile=coverage.profdata -project-title=Cloudundancy -format=html -output-dir=covhtml -show-instantiation-summary -show-line-counts-or-regions -Xdemangler c++filt"""))

