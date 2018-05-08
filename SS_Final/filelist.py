import os,glob
def get_filelist():
    os.chdir("../SS_Final")
    filelist = []
    for file in glob.glob("*"):
        # print(file)
        filelist = filelist + [file]
    # print(filelist)
    return filelist


if __name__ == '__main__':
	get_filelist()
