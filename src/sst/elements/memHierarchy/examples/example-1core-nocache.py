import sst

# Configuration describes: Single core, L1, Memory

## Debug & output controls
verbose = 2
### These do nothing unless sst-core was configured with `--enable-debug`
DEBUG_MEM = 0
DEBUG_LEVEL = 10

# Core model - may replace with anything that implements StdMem
## StandardCPU is a test component that generates random memory addresses
cpu = sst.Component("core", "memHierarchy.standardCPU")
cpu.addParams({
    "memFreq" : 2,          # On average, issue requests every 2 cycles
    "memSize" : "1MiB",     # Use memory addresses between 0 & 1MiB
    "verbose" : 0,          # No extra output
    "clock" : "3.5GHz",     # Run at 3.5GHz
    "rngseed" : 111,        # Random seed for access type and address generation
    "maxOutstanding" : 16,  # No more than 16 memory accesses outstanding at a time
    "opCount" : 2500,       # Stop after 2500 accesses
    "reqsPerIssue" : 3,     # Issue up to 3 requests in a cycle
    "write_freq" : 36,      # 36% of accesses should be writes
    "read_freq" : 63,       # 63% of accesses should be reads
    "llsc_freq" : 1,        # 1% of accesses should be LLSC pairs
})
iface = cpu.setSubComponent("memory", "memHierarchy.standardInterface")
#iface.addParams({"debug" : 1, "debug_level" : 10})

# Memory controller
## Addresses 0-512MiB map to this controller
memctrl = sst.Component("memory", "memHierarchy.MemController")
memctrl.addParams({
    "debug" : DEBUG_MEM,
    "debug_level" : DEBUG_LEVEL,
    "clock" : "1GHz",
    "verbose" : verbose,
    "addr_range_end" : 512*1024*1024-1,
})

# Memory access timing model - may replace with any available backend
## SimpleMem has a constant access latency for all accesses
## 512MiB memory with 1000ns access latency
memory = memctrl.setSubComponent("backend", "memHierarchy.simpleMem")
memory.addParams({
    "access_time" : "1000ns",
    "mem_size" : "512MiB"
})

# Define the simulation links
link_cpu_mem = sst.Link("link_cpu_mem")
link_cpu_mem.connect( (iface, "lowlink", "500ps"), (memctrl, "highlink", "500ps") )

# Enable statistics for all three components
sst.setStatisticLoadLevel(7)
sst.setStatisticOutput("sst.statOutputConsole")
sst.enableAllStatisticsForAllComponents()


