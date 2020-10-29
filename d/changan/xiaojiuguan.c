//Room: xiaojiuguan.c

inherit ROOM;

void create ()
{
        set ("short", "小酒馆");
        set("long", @LONG
这是一家小酒馆，屋子并不是很宽敞，酒水也是长安城里最最廉
价的，可是却仍然有许多人来光顾，也不知道他们是来喝酒的，还是
来欣赏那位坐在柜台后面的老板娘。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/liande-nankou",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/ruhua" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10680);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}