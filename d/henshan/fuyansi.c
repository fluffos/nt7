#include <ansi.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", "福严寺");
        set("long", @LONG
福严寺为禅宗七祖怀让的道场，怀让曾在此宏扬顿悟法门。山门
的上匾额「[1；31m天下法院[2；37；0m」正是当年写照，两边门联「[1；37m六朝古刹  七祖道
场[2；37；0m」字迹剥落颜色极古。只见山门的墙边上有古人留字(zi)，年代古
远，犹历历可辩。福严寺内的石柱上有一对联(lian)，字迹圆润回转，
不露机锋。
LONG );
        set("exits", ([ 
                "southdown"  : __DIR__"shanlu9",
                "westup"     : __DIR__"sansheng",         
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 2,
        ]));        

        set("item_desc", ([
            "zi":
HIW"\n
          诸峰翠少中峰翠  五寺名高此寺名
          石路险盘岚霭滑  僧窗高倚济寥明
          凌空殿阁由天设  遍地松杉是自生
          更有上方难上处  紫苔红藓远峥嵘
\n\n"NOR,
            "lian" : (: look_duilian :),

        ]));

        set("no_clean_up", 0);

	set("coor/x", -6940);
	set("coor/y", -5570);
	set("coor/z", 0);
	setup();
}


string look_duilian()
{
        return
        HIR "\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "　福　" NOR + HIR "※※            ※※" NOR + HIW "  般  " NOR + HIR "※※\n"
        "             ※※　 　 ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  严  " NOR + HIR "※※            ※※" NOR + HIW "  若  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  为  " NOR + HIR "※※            ※※" NOR + HIW "  为  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  南  " NOR + HIR "※※            ※※" NOR + HIW "  老  " NOR + HIR "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  山  " NOR + HIR "※※            ※※" NOR + HIW "  祖  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  第  " NOR + HIR "※※            ※※" NOR + HIW "  不  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  一  " NOR + HIR "※※            ※※" NOR + HIW "  二  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  古  " NOR + HIR "※※            ※※" NOR + HIW "  法  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  刹  " NOR + HIR "※※            ※※" NOR + HIW "  门  " NOR + HIR "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n\n" NOR;
}
