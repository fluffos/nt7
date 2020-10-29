inherit ROOM;

void create()
{
        set("short", "三清殿");
        set("long", @LONG
三清殿供奉的是三清神像，不过开封府内的居民大多到大相国寺
去烧香还愿了，这里的香火并不旺。神像也蓬头垢面无人理会。西行
去有座高高的阁楼，就是玉皇阁。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/sanqingxiang" : 1,
                  __DIR__"npc/xianghuo" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yanqing",
                  "west" : __DIR__"yuhuang",
        ]));

	set("coor/x", -5090);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}