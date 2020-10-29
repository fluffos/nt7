// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，人来人往地非常繁忙，不时地有人骑着马
匆匆而过。北边通向高丽城。南面是海边了，在这里你可以听见海浪的
声音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadao6",
                "west":__DIR__"xiaolu1",
                "southwest":__DIR__"suishilu1",
                "southeast":__DIR__"shatan1",
        ]));
       setup();
        replace_program(ROOM);
}        
