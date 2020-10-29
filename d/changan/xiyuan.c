//Room: xiyuan.c

inherit ROOM;

void create ()
{
        set ("short", "戏院");
        set("long", @LONG
这里屋深幽暗，屋子西端搭有一座精巧但已有点退色的戏台。戏
台两边挂有数盏明亮的灯笼。前几排有些矮凳，后面是一些红油茶桌
和宽背扶手椅。
LONG );
        set("exits", ([
                "south" : "/d/changan/liande-beikou",
        ]));
        set("objects", ([
                "/d/changan/npc/xizi" : 1,
        ]));

        set("coor/x", -10680);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}