"""
This script prints the cpu and memory ram usage, just rename the variable
process_name with the process you want
"""

import psutil

def bytes2human(n):
    # http://code.activestate.com/recipes/578019
    # >>> bytes2human(10000)
    # '9.8K'
    # >>> bytes2human(100001221)
    # '95.4M'
    symbols = ('K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y')
    prefix = {}
    for i, s in enumerate(symbols):
        prefix[s] = 1 << (i + 1) * 10
    for s in reversed(symbols):
        if n >= prefix[s]:
            value = float(n) / prefix[s]
            return '%.1f%s' % (value, s)
    return "%sB" % n

if __name__ == "__main__":

    process_name = 'rtabmap'

    #create a list containing the processes of interest
    process_list = [p for p in psutil.process_iter(attrs=['pid', 'name', 'cpu_percent', 'memory_full_info']) if process_name in p.info['name']]

    #call cpu_percent a first time (returns 0.0)
    #psutil.cpu_percent()

    #loop and print string 'CPU MEM'
    while True:
        
        sum_cpu = 0.0
        sum_mem = 0.0

        #iterate over the filtered processes and print the desired info
        for p in process_list:
            try:

                cpu_pct = p.cpu_percent(interval=0.1)/psutil.cpu_count(logical=True)
                used_mem = p.memory_full_info().uss
            except psutil.NoSuchProcess as err:
                pass

            sum_cpu += cpu_pct
            sum_mem += used_mem

            #uncomment this for debug
            #print('PID: {} / Name: {} / CPU: {} / Mem.: {}'.format(p.info['pid'], p.info['name'], cpu_pct, bytes2human(used_mem)))

        print('{:.2f} {}'.format(sum_cpu, bytes2human(sum_mem)))