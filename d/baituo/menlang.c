inherit ROOM;

void create()
{
        set("short", "门廊");
        set("long", @LONG
这是个门廊，门廊的飞檐上挂着一串串的小铜铃，在清风中发出
清脆动听的铃声。
LONG );
        set("exits", ([
                "north" : __DIR__"huayuan",
                "south" : __DIR__"liangong",
        ]));
        set("objects", ([
                __DIR__"npc/guanjia" : 1,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}