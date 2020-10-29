inherit ROOM;

void create()
{
        set("short", "南岭山口");
        set("long", @LONG
这里是南岭的一个山口。南面就是佛山了，北面是横亘湖南广东
的五岭。这里地气非常炎热，百物速生快长，口音也渐渐远异中原了。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "northup" : "/d/henshan/hsroad9",
                "southwest" : "/d/yaowang/lcd01",
                "south"   : __DIR__"northgate",
        ]));
	set("coor/x", -6570);
	set("coor/y", -9730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}