// This program is a part of NITAN MudLIB 
// redl 2013/10
mapping dt = ([]);

int do_save(string key, mixed val)
{
        string rvl;
        string s;
        dt = ([]);

        if (file_size(__DIR__"data.o")>0) {
                s = read_file(__DIR__"data.o");
                dt = restore_variable(s);
        }

        dt[key] = val;
        rvl = save_variable(dt);
        //write(rvl + "\n");
        return write_file(__DIR__"data.o", rvl, 1);
}

mixed do_load(string key)
{
        string s;
        dt = ([]);

        if (file_size(__DIR__"data.o")>0) {
                s = read_file(__DIR__"data.o");
                dt = restore_variable(s);
        }
        return dt[key];
}

void do_clear()
{
        string rvl;
        
        dt = ([]);
        //rm(__DIR__"data.o");
        rvl = save_variable(dt);
        write_file(__DIR__"data.o", rvl, 1);
}

int do_save2(string key, mixed val)
{
        string rvl;
        string s;
        dt = ([]);

        if (file_size(__DIR__"data2.o")>0) {
                s = read_file(__DIR__"data2.o");
                dt = restore_variable(s);
        }

        dt[key] = val;
        rvl = save_variable(dt);
        //write(rvl + "\n");
        return write_file(__DIR__"data2.o", rvl, 1);
}

mixed do_load2(string key)
{
        string s;
        dt = ([]);

        if (file_size(__DIR__"data2.o")>0) {
                s = read_file(__DIR__"data2.o");
                dt = restore_variable(s);
        }
        return dt[key];
}


