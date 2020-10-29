inherit ROOM;

void create()
{
        set("short", "卉园");
        set("long", @LONG
这里是一处幽静的环境所在，偶尔听到外面竹林中传来几声清脆
的鸟叫，园子里种着各式各样的珍奇花草。有绿菊，兰花，杜鹃、牡
丹……
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "out" : "/d/jingzhou/zizhulin1"
        ]));
        set("objects",([
                "/d/jingzhou/obj/lvju" : 3,
                "/d/jingzhou/npc/obj/juhua" : 1,
        ]));

        set("coor/x", -7091);
	set("coor/y", -2101);
	set("coor/z", -11);
	setup();
        replace_program(ROOM);
}