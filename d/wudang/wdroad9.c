inherit ROOM;

void create()
{
        set("short", "黄土路");
        set("long", @LONG
你走在一条尘土飞扬的黄土路上，两旁尽是阴森森的树林。这里
是湖北境界，据说经常有土匪出没，不可久留。向东南去可至湖南。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "northwest" : __DIR__"sanbuguan",
                "south"     : __DIR__"wdroad10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -320);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
