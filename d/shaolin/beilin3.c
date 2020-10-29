#include <ansi.h> 
inherit ROOM;

int do_study(string arg);

void create()
{
        set("short", NOR + WHT "地下室" NOR);
        set("long", @LONG
这里是佛塔底下的地下密室。密室虽小，却也五脏俱全，石桌石
椅，石几石床，连室内放的几件器皿，也都是石制的。看来似乎很久
以前有人在这里住过。正中的石桌 (table)上平放着一块薄弧的石板，
上面好象刻着些什么。
LONG );
        set("exits", ([
                "up" : __DIR__"beilin2",
        ]));
        set("objects",([
                "/clone/book/book-stone" : 1,
        ]));
        set("item_desc", ([
                "table" : WHT "这是一整块巨石雕成的石桌"
                          "，上面刻了些奇怪的图形。\n" NOR,
        ]));
        setup();
}

void init()
{
        add_action("do_study", "study");
        add_action("do_study", "du");
}

int do_study(string arg)
{
        object me;
        string msg;

        me = this_player();

        if (arg != "table")
                return notify_fail("你要读什么？\n");

        if ((int)me->query_skill("literate", 1) < 1)
                return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

        me->receive_damage("jing", 10 + random(10));

        if( query("jing", me)<0 )
        {
                me->unconcious();
                return 1;
        }

        msg = HIY "你专心的研读石桌上的古怪图形。\n" NOR;

        switch (random(5)) 
        {
            case 0:
                if ((int)me->query_skill("finger", 1) < 100)
                {
                        me->improve_skill("finger", 2 + random(me->query_int()));
                        msg += "你对着石桌琢磨了一回儿，似乎对指法有点心得。\n";
                        set_temp("stone_learned", 1, me);
                }
                break;

            case 1:
                if ((int)me->query_skill("claw", 1) < 100)
                {
                        me->improve_skill("claw", 2 + random(me->query_int()));
                        msg += "你对着石桌琢磨了一回儿，似乎对爪法有点心得。\n";
                        set_temp("stone_learned", 1, me);
                }
                break;

            case 2:
                if ((int)me->query_skill("strike", 1) < 100)
                {
                        me->improve_skill("strike", 2 + me->query_int());
                        msg += "你对着石桌琢磨了一回儿，似乎对掌法有点心得。\n";
                        set_temp("stone_learned", 1, me);
                }
                break;

            case 3:
                if ((int)me->query_skill("cuff", 1) < 100)
                {
                        me->improve_skill("cuff", 2 + random(me->query_int()));
                        msg += "你对着石桌琢磨了一回儿，似乎对拳法有点心得。\n";
                        set_temp("stone_learned", 1, me);
                }
                break;

            case 4:
                if ( (int)me->query_skill("hand", 1) < 100)
                {
                        me->improve_skill("hand", 2 + random(me->query_int()));
                        msg += "你对着石桌琢磨了一回儿，似乎对手法有点心得。\n";
                        set_temp("stone_learned", 1, me);
                }
        }

        if( !query_temp("stone_learned", me) )
                msg += HIY "你对着石桌琢磨了一回儿，发现上面所说的已经太"
                       "过浅显了。\n" NOR;

        write(msg);
        return 1;
}