inherit ROOM;

void create ()
{
        set("short","中心广场");
        set("long", @LONG
这里是武汉最繁华的地带了。这里汇集了五湖四海的商人、游客。
熙熙攘攘，好不热闹。虽然近来动乱不住，但是这里仍然热闹非凡。
LONG);

        set("exits", ([
                "west": __DIR__"hzjie4",
                "east": __DIR__"dongmen",
                "south" : __DIR__"hzjie3",
                "north" : __DIR__"hzjie2",
        ]));
        set("objects",([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}