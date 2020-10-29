inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
这是个阴暗的密室，墙上的油灯发出昏暗的黄光。
LONG );
        set("exits", ([
                "south" : __DIR__"midao13",
                "north" : __DIR__"midao14",
                "east" : __DIR__"midao14",
                "up" : __DIR__"huayuan",
        ]));
        setup();
        replace_program(ROOM);
}