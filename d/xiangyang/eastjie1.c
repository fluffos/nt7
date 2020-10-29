// Room: /d/xiangyang/eastjie1.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "东大街");
        set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。东边是一个大十
字街口。西面是襄阳的中央广场，北边是襄阳守城大将王坚的府邸大
门，只见那儿守备森严，闲杂人等一般是不能接近的。南面飘来一缕
缕的药香，噢，原来是一家药铺。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"eastjie2",
                "west"  : __DIR__"guangchang",
                "south" : __DIR__"yaopu",
                "north" : __DIR__"jiangjungate",
        ]));
        set("coor/x", -7810);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}