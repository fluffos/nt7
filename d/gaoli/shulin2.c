// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "树林");
        set("long", @LONG
你走在一片树林之中。这里树木茂盛，参天蔽日，非常凉快。四下
望了望，看不到树林的边界，看来这片树林非常大。一阵清风吹过，树
木发出沙沙的声音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"shulin1",
                "north":__DIR__"shulin3",
        ]));
       setup();
        replace_program(ROOM);
}        
