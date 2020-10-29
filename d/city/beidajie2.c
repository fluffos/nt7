// Room: /city/beidajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
这是一条宽阔的青石街道，向南北两头延伸。北边是北城门通向
城外。南边显得很繁忙。东边是一座两层的楼阁，挂着『太白遗风』
的招帘，门额上悬挂一方横匾，『醉仙楼』三字擦得闪闪发亮，乃是
苏学士的手笔。阵阵酒肉香酒香让你垂涎欲滴。西边是一座古朴的庙
宇，香火缭绕，那就是天下学武之人所共同敬仰的武庙了。
LONG );
        set("outdoors", "city");
        set("objects", ([
            "/d/city/npc/meipo" : 1,
        ]));
        set("exits", ([
                "east"  : "/d/city/zuixianlou",
                "south" : "/d/city/beidajie1",
                "west"  : "/d/city/wumiao",
                "north" : "/d/city/beimen",
        ]));
	set("coor/x", 0);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}