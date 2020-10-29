inherit ROOM;

void create()
{
        set("short", "南岭山口");
        set("long", @LONG
这里是南岭的一个山口。南面是岭南的大镇佛山，北面是湖南的
地界。岭南广东富庶繁盛，颇有豪侠之士。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northdown" : __DIR__"hsroad5",
                "southdown" : "/d/foshan/nanling",
        ]));
	set("coor/x", -6930);
	set("coor/y", -5710);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}