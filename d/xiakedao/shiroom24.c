// /d/xiakedao/shishi24.c 侠客岛 石室24

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "石室");
        set("long", @LONG
这里火光昏暗，只见那龙岛主与木岛主盘膝坐在锦垫之上，面对
石壁(wall)，凝神苦思。此石室已是山腹最深处，却宽阔高大，足可
容下近百人。洞中火把亦是其他洞的二三倍之多。
LONG );
        set("exits", ([
                "east" : __DIR__"shihole6",
        ]));
        set("item_desc", ([
                "wall" : @WALL
墙的正上方刻着「白首太玄经」几个大字。字的下方刻的是密密麻麻
的蝌蚪文，成千上万。文字排列甚不整齐，或横或竖，或直或斜。左
下的大片甚至混成一团难分次序，委实难以辨认。
WALL
        ]));
        set("objects", ([
                CLASS_D("xiakedao") + "/long" : 1,
                CLASS_D("xiakedao") + "/mu"   : 1,
        ]));
        set("no_fight", 1);
        set("coor/x", -3100);
        set("coor/y", -25600);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_study", "think");
        add_action("do_study", "study");
        add_action("do_canwu", "canwu");
}

int do_canwu(string msg)
{
        object me = this_player();
        string where, witch;

        if (! msg) return notify_fail("什么？\n");

        if (sscanf(msg, "%s from %s", witch, where) != 2)
                return notify_fail("干什么？\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("你在战斗哦？！小心，来了！！！\n");

        if (witch != "白首太玄经")
                return notify_fail("你想参悟什么？\n");

        if (where != "wall")
                return notify_fail("这里没什么给你参悟的啊！\n");

        if (me->query_skill("literate", 1)
         || query("learned_literate", me) )
                return notify_fail("你对着石壁想了半天也没发现什么！\n");

        if ((int)me->query_skill("force", 1) < 340)
                return notify_fail("你的内功修为不够，无法贯通石壁上的绝学！\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你的内力修为不足，无法贯通石壁上的绝学！\n");

        if( query("jing", me)<100 )
                return notify_fail("你的精力无法集中，无法领悟石壁上的绝学！\n");

        if (me->query_skill("taixuan-gong", 1) < 340)
                return notify_fail("你对太玄功所知实在有限，无法领悟石壁上的绝学！\n");

        if( query("can_perform/taixuan-gong/jing", me) )
                return notify_fail("这项绝学你不是已经会了吗？\n");

        me->receive_damage("jing", 95);

        me->start_busy(2 + random(4));

        if (random(50) == 1 || wizardp(me))
        {
                addn("taixuan_perform/jing/count", 1, me);

                if( query("taixuan_perform/jing/count", me) >= 300 )
                {
                        write(HIM "猛然间，你一声长啸，胸中豁然贯通，再无疑虑。\n" NOR);
                        write(HIC "你终于通晓了绝学「白首太玄经」。\n" NOR);

                        set("can_perform/taixuan-gong/jing", 1, me);
                        delete("taixuan_perform/jing/count", me);

                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("taixuan-gong"))
                                me->improve_skill("taixuan-gong", 1500000);
                        if (me->can_improve_skill("martial-cognize"))
                                me->improve_skill("martial-cognize", 1500000);

                        return 1;
                }

                write(HIC "你对「白首太玄经」这招有了新的认识，但是仍有许多不解之处。\n" NOR);
                me->start_busy(2 + random(6));
                return 1;
        }

        else return notify_fail("你试图从石壁上研究有关「" + witch + "」的内容，但却没什么效果！\n");

}

int do_study(string arg)
{
        object me;
        int lvl;

        if (arg != "wall")
                return notify_fail("你想研究什么？\n");

        me = this_player();
        if( query("combat_exp", me)<500000 )
        {
                write("你看了半天，只恨自己实战经验太浅薄，无法领悟上面的高深知识。\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你现在正忙，没空研究上面的诗句。\n");
                return 1;
        }

        me->receive_damage("jing", 15);
        me->start_busy(1);

        lvl = me->query_skill("literate", 1);
        if (lvl >= 200)
                write("你看了半天，觉得这首诗写的很好，不过似乎没什么特别之处。\n");
        else
        if (lvl >= 100)
                write("你觉得这上面的诗大有寓意，不由的尽心苦思。\n");
        else
        if (lvl >= 1)
                write("你心中暗想：这定是前辈高手留下的秘籍，这些词句可要好好分析。\n");
        else
        if (random(2))
        {
                write("你望着上面的笔划，想起所修习的武功来，不禁渐渐有所体会。\n");
                if( query("experience", me)<me->query_experience_limit() )
                        addn("experience", 1, me);
        } else
                write("你潜心琢磨上面的笔划，全然没有想它是什么含义。\n");

        return 1;
}
