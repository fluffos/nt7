inherit ROOM;

void create()
{
        set("short", "面馆");
        set("long", @LONG
这里是虎坊路尽头的一家小面馆，几个皇宫里的摔跤手拥在里面。
面馆的掌柜和伙计威于他们的势头，连大气也不敢出一声。
LONG );
        set("exits", ([
                "north" : "/d/beijing/fu_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/zhanggui":1,
                "/d/beijing/npc/mianhuoji":1,
                "/d/beijing/npc/jiao1":3,
                "/d/beijing/npc/jiao2":1,
              "/clone/npc/walker"  : 1, 
        ]));
	set("coor/x", -2820);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}