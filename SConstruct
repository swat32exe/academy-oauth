def compileDebug():
	if environment['CC'] == 'cl':
		environment.Append( CCFLAGS = [ '/Zi', '/Od'])
	else:
		environment.Append( CCFLAGS = [ '-g', '-O0'] )
	commonBuild()

def compileRelease():
	if environment['CC'] == 'cl':
		environment.Append( CCFLAGS = ['/Ox'] )
	else:
		environment.Append( CCFLAGS = ['-O2'] )
	commonBuild()

def compileTest():
	if environment['CC'] == 'cl':
		environment.Append( CCFLAGS = [] )
	else:
		environment.Append( CCFLAGS = [] )
	commonBuild()
	

def commonBuild():
	helloWorld = environment.Program('build/helloWorld.cpp', LIBS = ['helloStringMaker'], LIBPATH = 'build')
	helloStringMaker = environment.StaticLibrary('build/helloStringMaker','build/helloStringMaker.cpp')
	environment.Install('bin', helloWorld)
	environment.Install('bin', helloStringMaker)

configuration = ARGUMENTS.get('config', 'release');

if configuration=='debug' and Environment()['CC'] == 'cl':
	environment = Environment(CPPPATH='include', tools = ['mingw']);
else:
	environment = Environment(CPPPATH='include')

if environment['CC'] == 'cl':
	environment.Append( CCFLAGS = ['/Wall', '/WX', '/W3', '/EHsc'] )
elif environment['CC'] == 'gcc':
	environment.Append( CCFLAGS = ['-Wall', '-Wextra', '-Werror', '-pedantic', '-std=c++0x'])
else:
	print 'Unsupported Compiler: ' + environment['CC']

environment.VariantDir('build', 'src', duplicate = 0)

if configuration=='debug':
	compileDebug()
elif configuration=='release':
	compileRelease()
elif configuration=='test':
	compileTest()
else:
	print 'unknown configuration'


