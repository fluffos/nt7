int a()
{
        string s1,s2;
        int i1;
        s1 = base_name(environment(find_player("redl")));
        write("1>>>>>" + s1 + "\n");
        i1 = sscanf(s1, "/d/dongtian/%*sliandanfang");
        s2 = (string)i1;
        write("2>>>>>" + s2 + "\n");
}


