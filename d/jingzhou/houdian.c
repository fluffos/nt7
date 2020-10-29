inherit ROOM;

void create()
{
        set("short", "后殿");
        set("long", @LONG
这里是关帝庙的后殿，殿中堆放着香、烛等杂物。墙上的幔布看
起来满新的。
LONG );
        set("exits", ([
                "north" : __DIR__"houmen",
                "south" : __DIR__"guanmiao",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}