// wuji5-1.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIG "飘逸步法" NOR, ({ "wuji" }));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long", HIG "这是一本残破的旧书，上面画着舞动的小人。\n" NOR);
                set("value", 100);
                set("material", "paper");
                set("skill", ([
                        "name": "piaoyi-bu",        // name of the skill
                        "exp_required": 10000,  // minimum combat experience required
                        "jing_cost":    100,     // jing cost every time study this
                        "difficulty":   50,     // the base int to learn this skill
                        "max_skill":    100,    // the maximum level you can learn
                        "min_skill":    0,     // the minimum level you can learn
                ]));
        }
}

