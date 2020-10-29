#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "世界之树" NOR);
        set("long", @LONG
这里是古村的正中心，一个很宽阔的广场，上面铺着青石地面。中
央一棵大树(tree)盘根错节，已经看不出它究竟有着多大的树龄了，它
就是传说中的世界之树——传说就是它带来了整个世界的绿色，是自然
之祖。树下站着一个老者，正耐心地辅导着新手。

==== 如果你需要帮助请输入指令 ask lao about here ====

LONG);
        set("item_desc", ([
                 "tree" : GRN "\n这是一棵巨大古老的大树，枝叶非常"
                         "的茂密。\n" NOR,
        ]));

        set("objects", ([
                __DIR__"npc/laocunzhang" : 1,
        ]));

        set("valid_startroom", 1);
        set("exits", ([
                "east"  :  __DIR__"road2",
                "west"  :  __DIR__"road",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");
        
        set("no_fight", 1);
        set("no_pk", 1);
	setup();

        "/clone/board/newbie_b"->foo();
        replace_program(ROOM); 
}
