import urllib2
import zipfile
from StringIO import StringIO
import os.path

def extractWithoutPath(archive, archivePath, extractPath):
    newFile = open(extractPath,'w')
    newFile.write(archive.read(archivePath))
    newFile.close();

files = [
    ['gmock-1.6.0/fused-src/gmock-gtest-all.cc', 'test/gmock-gtest-all.cc'],
    ['gmock-1.6.0/fused-src/gmock/gmock.h', 'test/gmock/gmock.h'],
    ['gmock-1.6.0/fused-src/gtest/gtest.h', 'test/gtest/gtest.h']
]

filesMissing = False

for (archivePath, extractPath) in files:
    if not os.path.isfile(extractPath):
        filesMissing = True

if filesMissing:
    print "GTest not found, downloading..."

    if not os.path.exists('test/gtest'):
        os.makedirs('test/gtest')
    if not os.path.exists('test/gmock'):
        os.makedirs('test/gmock')

    response = urllib2.urlopen('https://googlemock.googlecode.com/files/gmock-1.6.0.zip')
    gtestRawZip = response.read()
    gtestZip = zipfile.ZipFile(StringIO(gtestRawZip))
    for (archivePath, extractPath) in files:
        extractWithoutPath(gtestZip, archivePath, extractPath)