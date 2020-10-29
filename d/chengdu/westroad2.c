// Room: westroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "西大街");
        set("long", @LONG
一条青石铺成的大道通向南北。路上行人络绎不绝，只见南面不
远处的古树下有一个简陋的摊子，摊子一角的招牌在风中摇晃着，上
面写着『诸葛再世』，居然也围了一堆人。往西就是西门了，东边是
蜀都大道。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "south" : __DIR__"westroad1",
            "east"  : __DIR__"shuduroad2",
            "west"  : __DIR__"westgate",
            "north" : __DIR__"westroad3",
        ]));
        set("objects", ([
            "/d/taishan/npc/tangzi": 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}