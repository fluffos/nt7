// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "天宝阁");
        set("long", @LONG
这里专卖市坊中各种字画和书籍刻本，其中还有不少是难得一见的
珍本，但由于因该店孙老板经营不善而倒闭。在此之后扬州外的长乐帮
曾经租下过这个店面，但不知为何又搬走了。辛友清最近刚将此店买下，
店内目前还没有雇用员工，只有老板辛友清一人无精打采地守着，四周
书架子(shelf) 乱七八糟堆着一些卷轴，线订本，给人一种杂乱无章的
感觉。
LONG );
        set("region", "yangzhou");
        set("exits", ([
                "south" : __DIR__"xidajie3",
        ]));

        set("objects", ([
                __DIR__"npc/bookboss" : 1,
        ]));

        set("no_fight", 1);
        set("no_sleep", 1);
        set("day_shop", 1);
        set("item_desc", ([
                "shelf"  : "书架上堆满了书，有些已经翻得破破烂烂。\n",
        ]));

	set("coor/x", -30);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}