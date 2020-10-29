#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "锦城驿");
        set("long", @LONG
锦城驿是全西南最大的客店，生意非常兴隆。外地游客多选择这
里落脚，你可以在这里打听到各地的风土人情。店小二里里外外忙得
团团转，沉重的川味官话你是实在听不顺耳。这是成都督府官办的客
栈，接待着各地入川的官差浪人。墙上挂着一个牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("item_desc", ([
                "paizi" : WHT "\n\n        ※※※※※※※※※※※※※※※※※\n"
                              "        ※                              ※\n"
                              "        ※    " NOR + HIW "楼上雅房，每夜十两白银。" NOR + WHT "  ※\n"
                              "        ※                              ※\n"
                              "        ※※※※※※※※※※※※※※※※※\n\n\n" NOR,
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "northwest" : __DIR__"southroad1",
                "up"        : __DIR__"kedian2",
                "east"      : __DIR__"majiu",
        ]));
        set("coor/x", -15200);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian3_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail(CYN "店小二一下挡在楼梯前，白眼一翻：怎麽着，想白住啊？\n" NOR);

        /*
        if( query_temp("rent_paid", me) && dir == "east" )
                return notify_fail(CYN "店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！\n" NOR);
        */

        return ::valid_leave(me, dir);
}