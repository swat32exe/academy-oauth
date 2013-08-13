academy-oauth
=============
##Preparation steps
To build the library you need to install python 2.x.x, scons, gcc 4.8.0+ and cURL.

Run LoadcURLpp.py which is located in project root directory. It will download 
cURLpp files.

You can use
```
--curl-libpath=<path>
```
and
```
--curl-includepath=<path>
```
options to specify cURL libraries and headers locations, if required

If configuration you want to build requires openssl and it is not located in default directory, you can use 
```
--openssl-libpath=<path>
```
and
```
--openssl-includepath=<path>
```
options to specify libraries and headers locations.

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

##Running tests
Install openssl.

Now you can build and run tests with
```
scons config=Test
```
