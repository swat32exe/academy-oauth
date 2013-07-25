import os.path
from SConfig import *

configuration = ARGUMENTS.get('config', RELEASE_CONFIG);

if configuration == TEST_CONFIG:
    execfile('LoadGTest.py')

if Environment()['CC'] == 'cl':
    environment = Environment(CPPPATH='#include', tools = ['mingw']);
else:
    environment = Environment(CPPPATH='#include')

if environment['CC'] == 'gcc':
    if configuration == TEST_CONFIG:
        environment.Append(CCFLAGS = ['-Wall', '-Wextra', '-Werror', '-pedantic', '-std=gnu++0x'])
    else:
        environment.Append(CCFLAGS = ['-Wall', '-Wextra', '-Werror', '-pedantic', '-std=c++0x'])
else:
    print 'Unsupported Compiler: ' + environment['CC']

variantDirPath = os.path.join(BUILD_DIR, configuration)
if configuration == TEST_CONFIG:
    SConscript('src/SConscript', variant_dir = os.path.join(BUILD_DIR, DEBUG_CONFIG), duplicate = 0,
    exports = {'configuration' : DEBUG_CONFIG, 'environment' : environment})
    SConscript('test/SConscript', variant_dir = variantDirPath, duplicate = 0,
    exports = {'environment' : environment})
else:
    SConscript('src/SConscript', variant_dir = variantDirPath, duplicate = 0,
    exports = {'configuration' : configuration, 'environment' : environment})
