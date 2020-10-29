// This program is a part of NT MudLIB

inherit __DIR__"shamo";

int valid_leave(object me, string dir)
{
        string dest;

        if (dir == "east")
        {
                if( addn_temp("out_shamo",1,me) >= 3 )
                {
                        me->move(__DIR__"silk5");
                        write("你累得半死，终於走出了沙漠。\n");
                        return -1;
                }
        }

        return ::valid_leave(me, dir);
}
