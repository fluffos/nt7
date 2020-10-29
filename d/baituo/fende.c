inherit ROOM;

void create()
{
        set("short", "坟地");
        set("long", @LONG
这里是一片荒凉阴森的荒坟地，时不时传来几声乌鸦的叫声。有
位中年妇女正在这里吊丧，哭泣个不停。
LONG );
        set("outdoors", "baituo");

        set("exits", ([
                "southwest" : __DIR__"xiaolu1",
        ]));

        set("objects" , ([
                __DIR__"npc/guafu" : 1,
        ]));

        set("coor/x", -49960);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}