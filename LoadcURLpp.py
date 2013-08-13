import urllib2
import tarfile
import glob
import shutil
from StringIO import StringIO
import os.path

EXTRACT_DIR = 'src/cURLpp/';

if not os.path.exists(EXTRACT_DIR):
    os.makedirs(EXTRACT_DIR)

response = urllib2.urlopen('https://curlpp.googlecode.com/files/curlpp-0.7.3.tar.gz')
rawTarGz = response.read()
tar = tarfile.open(mode="r:gz", fileobj = StringIO(rawTarGz))
subdir_and_files = [
    tarinfo for tarinfo in tar.getmembers()
    if tarinfo.name.startswith("curlpp-0.7.3/src/") or tarinfo.name.startswith("curlpp-0.7.3/include/")
    ]
tar.extractall(path=EXTRACT_DIR, members=subdir_and_files)

for dir in glob.glob(EXTRACT_DIR + 'curlpp-0.7.3/*'):
    shutil.move(dir, EXTRACT_DIR)

shutil.rmtree(EXTRACT_DIR + 'curlpp-0.7.3/');
