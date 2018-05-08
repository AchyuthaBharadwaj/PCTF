import io
import os
from filelist import get_filelist
import re

def runner():  
    cwd = os.path.dirname(os.path.realpath(__file__))
    filelist = get_filelist()
    data = []
    vulnerabilities = "gets scanf sprintf strcat strcpy strcmp printf fprintf vprintf snprintf vsnprintf syslog access chown chgrp chmod mktemp tempnam tmpfile tmpnam rand random exec popen system _GET _POST _REQUEST _COOKIE include_once script conn->query shell_exec exec passthru ` preg_replace".split()
    # print(vulnerabilities)

    print("Choose a file")
    for idx, file in enumerate(filelist):
        print(str(idx) + "    " + file)
    file_no = input("Choose a file from the list above 0-N")
    if filelist[file_no]:
        file = filelist[file_no]
        file_path = os.path.join(cwd,'..','SS_Final',file)
        data = data + extract_data(file)
        # print(data)
        print(" PRINTING POSSIBLE VULNERABILITIES ")
        print("#"*500)
        print(vulnerabilities)
        for line in data:
            for v in vulnerabilities:
                # print(v)
                if v in line:
                    print(line)

        print(" PRINTING All Comments ")
        print("#"*500)
        for idx,line in enumerate(data):
            if ('#' in line or '//' in line or '/*' in line or '\*' in line):
                print(str(idx) + "     " + line)
        # pass
def extract_data(filename):
    data_list = []
    with io.open(filename, 'r') as file:
        for idx,line in enumerate(file):
            data_list = data_list + [str(filename) + " " + str(idx+1) + " " + str(line)]
	file.close()
    return data_list

if __name__ == "__main__":
    runner()
