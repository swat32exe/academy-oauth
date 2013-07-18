environment = Environment(CPPPATH='include')

environment.VariantDir('build', 'src', duplicate = 0)

helloWorld = environment.Program('build/helloWorld.cpp', LIBS = ['helloStringMaker'], LIBPATH = 'build')
helloStringMaker = environment.StaticLibrary('build/helloStringMaker','build/helloStringMaker.cpp')

environment.Install('bin', helloWorld)
environment.Install('bin', helloStringMaker)
