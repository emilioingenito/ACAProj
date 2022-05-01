with open('/home/emilio/ACAProj/PythonScript/source_atom.txt','r') as source, open('/home/emilio/ACAProj/PythonScript/atom_data.h','w') as dest, open('/home/emilio/MD/miniMD/ref/atom.txt') as data:

    #first line
    natoms = data.readline().rstrip('\n')
    dest.write(source.readline().split("#")[0]+natoms+";\n")
    #second line -- save nlocal
    sr = source.readline().split("#")[0]
    dt = data.readline().rstrip('\n')
    nlocal = int(dt)
    dest.write(sr+dt+";\n")
    #third line -- save nghost
    sr = source.readline().split("#")[0]
    dt = data.readline().rstrip('\n')
    nghost = int(dt)
    dest.write(sr+dt+";\n")
    #fourth line
    nmax = data.readline().rstrip('\n')
    dest.write(source.readline().split("#")[0]+nmax+";\n")

    #save arrays
    x = "u_int64_t* x = new u_int64_t[(nlocal + nghost)*PAD];\n"
    v = "u_int64_t* v = new u_int64_t[(nlocal + nghost)*PAD];\n"
    f = "u_int64_t* f = new u_int64_t[(nlocal + nghost)*PAD];\n"
    t = "int* type = new int[nlocal + nghost];\n"
    aa = "MMD_float* x_f = new MMD_float[(nlocal + nghost)*PAD];\n"
    ab = "MMD_float* v_f = new MMD_float[(nlocal + nghost)*PAD];\n"
    ac = "MMD_float* f_f = new MMD_float[(nlocal + nghost)*PAD];\n"
    dest.write(x)
    dest.write(v)
    dest.write(f)
    dest.write(t)
    dest.write(aa)
    dest.write(ab)
    dest.write(ac)
    
    #save each element of array
    
    loop_range = (nlocal + nghost)*3
    type_range = nlocal + nghost
    for i in range(loop_range):
        dest.write("x["+str(i)+"] = "+data.readline().rstrip('\n')+"u;\n")
    for i in range(loop_range):
            dest.write("v["+str(i)+"] = "+data.readline().rstrip('\n')+"u;\n")
    for i in range(loop_range):
        dest.write("f["+str(i)+"] = "+data.readline().rstrip('\n')+"u;\n")
    for i in range(type_range):
        dest.write("type["+str(i)+"] = "+data.readline().rstrip('\n')+";\n")
    #last five lines
    for i in range(5):
    	dest.write(source.readline().split("#")[0]+data.readline().rstrip('\n')+";\n")

source.close()
dest.close()
data.close()


