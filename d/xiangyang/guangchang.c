// Room: /d/xiangyang/guangchang.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "中央广场");
        set("long", @LONG
这里是襄阳的中央广场，铺着青石地面。东面通向青龙门，西面
通向白虎门，南面直达朱雀门，远远地你可看到北面是襄阳安抚使衙
门。近年来蒙古大军屡次攻打襄阳，官府为防止蒙古奸细混杂进来，
已经不允许人们在此聚集。只见一队官兵在此往来巡逻，你还是快离
开吧。
LONG );
        set("outdoors", "xiangyang");
        set("item_desc", ([
                "dong" : "\n",
        ]));

        set("exits", ([
                "east"  : __DIR__"eastjie1",
                "west"  : __DIR__"westjie1",
                "south" : __DIR__"southjie1",
                "north" : __DIR__"anfupailou",
        ]));
        set("objects", ([
                __DIR__"npc/pian" : 1,
                __DIR__"npc/bing" : 1,
                "/clone/npc/walker"  : 1, 
        ]));
        set("coor/x", -7820);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}