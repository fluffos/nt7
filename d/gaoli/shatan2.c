// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "沙滩");
        set("long", @LONG        
你走在沙滩之上，脚下是松软的海沙。南边是一艘大战船，正停泊
在那里。据说这是高丽的海面部队之一，近来局势混乱，高丽的战船也
是严加戒备。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northwest" : __DIR__"shatan1",
                "south":__DIR__"jiaban",
        ]));
       setup();
        replace_program(ROOM);
}        
