import os.path
from SConfig import *

cppPath = ['#include', '#src']
if Environment()['CC'] == 'cl':
    environment = Environment(tools = ['mingw'])
else:
    environment = Environment()
environment.Replace(ENV = {'PATH' : os.environ['PATH']}, CPPPATH = cppPath)

defaultSslLibPath = ''
defaultSslIncludePath = ''
if environment['PLATFORM'] == 'win32':
    defaultSslLibPath = os.path.join('C:\\', 'OpenSSL-Win32', 'lib', 'MinGW')
    defaultSslIncludePath = os.path.join('C:\\', 'OpenSSL-Win32', 'include')
else:
    defaultSslLibPath = '/usr/lib'
    defaultSslIncludePath = '/usr/lib/include'

AddOption('--with-rsa', action = 'store_true', dest = 'buildWithRsa', default = False,
help = 'Build the library with RSA-SHA1 signature and OpenSSL')

AddOption('--with-curl', action = 'store_true', dest = 'buildWithCurl', default = False,
help = 'Build the library with default cURL-based function for making requests')

AddOption('--openssl-libpath', action = 'store', dest = 'opensslLibPath', default = defaultSslLibPath,
nargs = 1, type = 'string', help = 'Path to directory with OpenSSL crypto library \
(libeay32.dll on Windows or libcrypto.so on Linux)')

AddOption('--openssl-includepath', action = 'store', dest = 'opensslIncludePath', 
default = defaultSslIncludePath, nargs = 1, type = 'string', 
help = 'Path to OpenSSL include directory')

AddOption('--curl-libpath', action = 'store', dest = 'curlLibPath', default = '.',
nargs = 1, type = 'string', help = 'Path to directory with curl library')

AddOption('--curl-includepath', action = 'store', dest = 'curlIncludePath', 
default = '.', nargs = 1, type = 'string', help = 'Path to curl include directory')

buildWithRsa = GetOption('buildWithRsa')
buildWithCurl = GetOption('buildWithCurl')
opensslLibPath = GetOption('opensslLibPath')
opensslIncludePath = GetOption('opensslIncludePath')
curlLibPath = GetOption('curlLibPath')
curlIncludePath = GetOption('curlIncludePath')
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

if os.path.isdir(curlIncludePath):
    environment.Append(CPPPATH = curlIncludePath)
else:
    print 'Warning: cURL include path you set does not exist.'

if not os.path.isdir(curlLibPath):
    print 'Warning: cURL library path you set does not exist.'

variantDirPath = os.path.join(BUILD_DIR, configuration)
if configuration == TEST_CONFIG:
    SConscript('src/SConscript', variant_dir = os.path.join(BUILD_DIR, DEBUG_CONFIG), duplicate = 0,
    exports = {'configuration' : DEBUG_CONFIG, 'environment' : environment, 'buildWithRsa' : True, 
    'buildWithCurl' : True, 'opensslLibPath' : opensslLibPath})
    SConscript('test/SConscript', variant_dir = variantDirPath, duplicate = 0,
    exports = {'environment' : environment, 'opensslLibPath' : opensslLibPath, 'curlLibPath' : curlLibPath})
else:
    SConscript('src/SConscript', variant_dir = variantDirPath, duplicate = 0,
    exports = {'configuration' : configuration, 'environment' : environment,
    'buildWithRsa': buildWithRsa, 'buildWithCurl' : buildWithCurl, 'opensslLibPath' : opensslLibPath})
