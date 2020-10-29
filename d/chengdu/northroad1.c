// Room: northroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
这里就是北大街了，空气中有着一种怪怪的气味，不是太好闻。
路很宽，但人却不多，尤其是在黄昏以后。西南是另一条大街，北大
街从此一直往东，西北有一家兵器铺，进进出出的人都面无表情，死
气沉沉。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"       : __DIR__"northroad2",
            "southwest"  : __DIR__"westroad3",
            "northwest"  : __DIR__"bingqidian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15230);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}