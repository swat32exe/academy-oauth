academy-oauth
=============
##Preparation steps
To build the library you need to install python 2.x.x, scons, gcc 4.8.0+.

##Building library
Run 'scons' command in project directory to build release version of the
library. If you need to build debug version, explicitly specify it with:
```
scons config=Debug
```

By default, the library includes PLAINTEXT and HMAC-SHA1 signatures. To build 
it with RSA-SHA1 you need to install openssl library. Then, you must pass 
--with-rsa flag to the build command, e.g.
```
scons config=Debug --with-rsa
```
If you want to configure build process with specific include and lib paths for openssl, you can use:
```
--openssl-libpath=<path>
```
and
```
--openssl-includepath=<path>
```

By default, the library does not include function to send requests over network.
User will need to provide one. If you want to enable default cURL-based function,
do the following:

1. Run LoadcURLpp.py which is located in project root directory. It will download 
cURLpp files.
2. Use --with-curl flag, e.g.
```
scons config=Debug --with-curl
```

If you want to configure build process with specific include and lib paths for cURL, you can use:
```
--curl-libpath=<path>
```
and
```
--curl-includepath=<path>
```


##Running tests
Install openssl.
Run LoadcURLpp.py which is located in project root directory. It will download 
cURLpp files.

Now you can build and run tests with
```
scons config=Test
```
