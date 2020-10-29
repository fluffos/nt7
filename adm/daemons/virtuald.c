// virtuald.c
// Modified by Find.

void create()
{
        seteuid(getuid());
        if( clonep() ) 
                destruct(this_object());
}

// This function is called by master object to return the "virtual" object
// of <file> when dirver failed to find such a file.

nomask varargs object compile_object(string file, int cloning)
{
        string pname = file;
        object ob;

        if( file[0..1] == "/f" )
        {
                ob = FUBEN_D->compile_object(file);
                if( objectp(ob) ) 
                {
                        ob->setup();
                        return ob;
                }
                return 0;
        }
        else if( file[0..1] == "/p" )
        {
                ob = FUBEN_D->compile_private_object(file);
                if( objectp(ob) ) 
                {
                        ob->setup();
                        return ob;
                }
                return 0;
        }

        while (1)
        {
                int idx = strsrch(pname, "/", -1);

                if(idx == -1)
                        return 0;

                if(idx != 0)
                        pname = pname[0..idx-1];

                if(file_size(pname + ".c") >= 0)
                        if(ob = pname->query_maze_room(file[idx + 1..]))
                        {
                                ob->set_virtual_flag();
                                return ob;
                        }
                if(! idx)
                        return 0;
        }

        return 0;
}

/*
string query_name()
{
        return "虚拟物件系统(VIRTUAL_D)";
}
*/
