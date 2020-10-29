// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "沙滩");
        set("long", @LONG        
你走在沙滩之上，脚下是松软的海沙。南边是一望无际的大海。远
远望去，还有几艘大船停泊在岸边，在海浪的冲击下不住的摇晃。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northwest" : __DIR__"dadao9",
                "southeast":__DIR__"shatan2",
        ]));
       setup();
        replace_program(ROOM);
}        
