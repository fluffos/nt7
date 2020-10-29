inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
开封府内西面的主要交通要道，街道两边店铺林立，行人车马如
梭。商贩的吆喝，市民与小贩的讨价还价喧闹无比。此地向北不远就
到了延庆观的大门。
LONG );
        set("objects", ([
                  __DIR__"npc/lisi" : 1,
        ]));
        set("outdoors", "kaifeng");
        set("exits", ([
                  "north" : __DIR__"wroad2",
                  "south" : __DIR__"wroad",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5070);
	set("coor/y", 2230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}