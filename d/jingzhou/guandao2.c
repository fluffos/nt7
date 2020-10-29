inherit ROOM;

void create()
{
        set("short", "官道" );
        set("long", @LONG
你走在一条大官道上，两旁不时有人从你身边走过，可以分辩出
有几个是江湖中人。西面隐约可以看见荆州，东边是通往武昌城。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                  "east" : __DIR__"guandao1",
                  "west" : __DIR__"guandao3",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7050);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}