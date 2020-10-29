inherit ROOM;

void create()
{
        set("short", "大雄宝殿");
        set("long", @LONG
经过九级石头台阶，正面就是佛祖神像，两边普贤和文殊。高大
的佛像几乎挨到了屋顶，令人凌然生威。正对着门的地方摆着几张供
桌，上面是时鲜的瓜果。供桌两边的大蜡烛比人还高。两边是十八罗
汉。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/rulaixiang" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"zhongyuan",
                  "north" : __DIR__"houyuan",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}