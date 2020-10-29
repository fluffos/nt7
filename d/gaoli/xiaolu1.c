// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "小路");
        set("long", @LONG
你走在一条小路之上。东边是一条青石大路，南边就是海边了，从
这里可以听到波涛汹涌的声音，不时有几只海鸥从你的头上飞过。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"dadao9",
                "southwest":__DIR__"xiaolu2",
        ]));
       setup();
        replace_program(ROOM);
}        
