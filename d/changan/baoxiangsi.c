//Room: baoxiangsi.c

inherit ROOM;

void create ()
{
        set ("short", "宝象寺");
        set("long", @LONG
宝象寺规模宏大，房舍近千，别院处处。放眼所见，这里尽是高
阁石壁，佛彩龙像，绕不一会，已然分不清来时的道路。但见那一尊
尊的石刻似乎都裂著嘴在向你嘿嘿而笑。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "north" : "/d/changan/qinglong1",
                "south" : "/d/changan/baodian",
        ]));
        set("objects", 
        ([ //sizeof() == 2
                "/d/changan/npc/monk" : 2,
        ]));

        set("coor/x", -10730);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}