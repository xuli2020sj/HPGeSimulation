import os
import subprocess

# subprocess.run(args=['ifconfig', ])

mac_path = r'/home/x/code/HPGeSimulation/autoScript/2022-05-14/'


def get_file(dir):
    file_list = []
    for item in os.listdir(dir):
        file_list.append(os.path.join(dir, item))
    return file_list


def test():

    cmd = './sim'
    p = subprocess.Popen(cmd, shell=True, cwd=r'/home/x/code/HPGeSimulation/build')
    p.wait()


if __name__ == '__main__':
    test()
    # for file in get_file(mac_path):
    #     cmd = './sim ' + file
    #     p = subprocess.Popen(cmd, shell=True, cwd=r'/home/x/code/HPGeSimulation/build')
    #     p.wait()
    #     print(cmd, p.returncode)
