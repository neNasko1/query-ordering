import os
from subprocess import PIPE, Popen
import math
import json

def get_out(command):
    process = Popen(
        args=command,
        stdout=PIPE,
        stderr=PIPE,
        shell=True
    )
    return str(process.communicate()[1])

def compile():
    os.system('rm main')
    os.system('rm gen')
    os.system('rm pathlength.txt')
    os.system('touch pathlength.txt')
    os.system('./comp.sh')
    print("Compiled")

def generate(input_ind):
    if UPDATES:
        os.system('./gen ' + str(input_ind) + ' 1 > inputs/testing' + str(input_ind))
    else:
        os.system('./gen ' + str(input_ind) + ' 0 > inputs/testing' + str(input_ind))        

def run(ind, input_ind):
    print("Running: ", 'perf stat -d -x\'___\' ./main ' + str(ind) + ' < inputs/testing' + str(input_ind) + ' > outputs/testing' + str(input_ind) + str(ind))
    return get_out('perf stat -d -x\'___\' ./main ' + str(ind) + ' < inputs/testing' + str(input_ind) + ' > outputs/testing' + str(input_ind) + str(ind))

def get_measure(output):
    out = [line.split('___') for line in output.split('\\n')]    
    ret = []
    for x in out:
        try:
            if x[0][0] == 'b':
                ret.append(float(x[0][2:].replace(',', '.')))
            else:
                ret.append(float(x[0].replace(',', '.')))
        except:
            ret.append(0)
    return ret

def save_settings(LOG_N, LOG_Q):
    text = """
    #include <math.h>
    //#pragma GCC optimize("Ofast")
    //#pragma GCC target("sse4")
    #pragma once
    const int MAX_LOG_N = """ + str(LOG_N) + """;
    const int MAX_LOG_Q = """ + str(LOG_Q) + """;
    const int MAX_N = 1 << MAX_LOG_N;
    const int MAX_Q = 1 << MAX_LOG_Q;
    """
    if UPDATES:
        text += 'const int SQRT = pow(MAX_N, 0.69);'
    else:
        text += 'const int SQRT = pow(MAX_N, 0.5);'
    f = open("defines.h", "w")
    f.write(text)
    f.close()    

LENGTH = 10
ALGOS = 10
LENGTH_PARAMS = 15
UPDATES = True

ret = {}

for LOG_N in range(15, 20):
    ret[LOG_N] = {}
    LOG_Q = LOG_N

    save_settings(LOG_N, LOG_Q)
    compile()

    sums = [[0 for y in range(LENGTH_PARAMS)] for x in range(ALGOS)]

    for input_ind in range(LENGTH):
        generate(input_ind)
        for ind in [1, 3, 4]:
            meas = get_measure(run(ind, input_ind))
            for x in range(len(meas)):
                sums[ind][x] += meas[x]
                print(meas[x], end=' ')
            print('')

    sums = [[x // LENGTH for x in s] for s in sums]
    ret[LOG_N][LOG_Q] = [x for x in sums if sum(x) != 0]
    print("Ready: ", LOG_N, LOG_Q)

with open('data.json', 'w') as outfile:
    json.dump(ret, outfile)
