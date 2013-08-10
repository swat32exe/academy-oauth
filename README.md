academy-oauth
=============
##Installation
To build the library you need to install python 2.x.x, scons, and gcc 4.8.0+.
Then, run 'scons' command in project directory to build release version of the
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
If openssl is not located in default directory, you can use 
```
--openssl-libpath=<path>
```
and
```
--openssl-includepath=<path>
```
options to specify libraries and headers locations.

##Running tests
Install libcurl. After this it should be possible to simply include header into 
any project and use it. Install openssl.

Run LoadcURLpp.py which is located in project root directory. It will download 
cURLpp files.

Now you can build and run tests with
```
scons config=Test
```
If openssl is not located in default directory, you can use 
```
--openssl-libpath=<path>
```
and
```
--openssl-includepath=<path>
```
options to specify libraries and headers locations.
