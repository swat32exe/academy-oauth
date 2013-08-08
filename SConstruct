import os.path
from SConfig import *

cppPath = ['#include', '#src']
if Environment()['CC'] == 'cl':
    environment = Environment(CPPPATH = cppPath, tools = ['mingw']);
else:
    environment = Environment(CPPPATH = cppPath)

defaultSslLibPath = ''
if environment['PLATFORM'] == 'win32':
    defaultSslLibPath = os.path.join('C:\\', 'Program Files', 'OpenSSL')
else:
    defaultSslLibPath = '/usr/lib'

AddOption('--with-rsa', action = 'store_true', dest = 'buildWithRsa', default = False,
help = 'Build the library with RSA-SHA1 signature and OpenSSL')

AddOption('--openssl-libpath', action = 'store', dest = 'opensslLibPath', default = defaultSslLibPath,
nargs = 1, type = 'string', help = 'Path to directory with OpenSSL crypto library \
(libeay32.dll on Windows or libcrypto.so on Linux)')

AddOption('--openssl-includepath', action = 'store', dest = 'opensslIncludePath', 
default = os.path.join(defaultSslLibPath, 'include'), nargs = 1, type = 'string', 
help = 'Path to OpenSSL include directory')

buildWithRsa = GetOption('buildWithRsa')
opensslLibPath = GetOption('opensslLibPath')
opensslIncludePath = GetOption('opensslIncludePath')
configuration = ARGUMENTS.get('config', RELEASE_CONFIG)

if configuration == TEST_CONFIG:
    execfile('LoadGTest.py')

if environment['CC'] == 'gcc':
    environment.Append(CCFLAGS = ['-Wall', '-Wextra', '-Werror', '-pedantic', '-std=c++0x'])
else:
    print 'Unsupported Compiler: ' + environment['CC']

if os.path.isdir(opensslIncludePath):
    environment.Append(CPPPATH = opensslIncludePath)
else:
    print 'Warning: OpenSSL include directory not found. \
    If it is not under your PATH, specify it with --openssl-includepath'

variantDirPath = os.path.join(BUILD_DIR, configuration)
if configuration == TEST_CONFIG:
    SConscript('src/SConscript', variant_dir = os.path.join(BUILD_DIR, DEBUG_CONFIG), duplicate = 0,
    exports = {'configuration' : DEBUG_CONFIG, 'environment' : environment, 'buildWithRsa': True,
    'opensslLibPath' : opensslLibPath})
    SConscript('test/SConscript', variant_dir = variantDirPath, duplicate = 0,
    exports = {'environment' : environment})
else:
    SConscript('src/SConscript', variant_dir = variantDirPath, duplicate = 0,
    exports = {'configuration' : configuration, 'environment' : environment,
    'buildWithRsa': buildWithRsa, 'opensslLibPath' : opensslLibPath})
