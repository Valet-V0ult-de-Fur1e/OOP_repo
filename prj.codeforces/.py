from os import listdir
from os.path import isfile, join

with open('prj.codeforces/CMakeLists.txt', mode='w') as cmake_file:
    for file_in_workfolder in [file_name for file_name in listdir('prj.codeforces') if isfile(join('prj.codeforces', file_name))]:
        if file_in_workfolder.endswith('.cpp'):
            new_line = f"add_executable({file_in_workfolder.split('.')[0]} {file_in_workfolder})\n"
            cmake_file.write(new_line)