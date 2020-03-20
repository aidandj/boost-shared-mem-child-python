import sys
import python_shared_mem

if python_shared_mem.shared_mem().get_number() == 10:
    sys.exit(0)
else:
    sys.exit(-1)
