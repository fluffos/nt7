//绝情丹(Jueqing-dan)
//黑豹(Blacko)2001/8/
// update by jiuer -9/18/2001

#include <ansi.h>

inherit ITEM;

int cure_ob(string);
void init();

void create()
{
        set_name(BLU"绝情丹"NOR, ({"jueqing dan", "jueqing", "dan"}));
        set_weight(50);
        /*if (clonep())
            set_default_object(__FILE__);
    else*/ 
    {
                set("unit", "枚");
        set("long", "一枚四四方方骰子般的丹药，色作深黑，腥臭刺鼻。\n");
                set("value", 30000);
                set("medicine", 1);
                set("no_sell", 1);
    }
        setup();
}

int cure_ob(object me)
{
/* set("eff_jing",query("max_jing",  me), me); 
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
*/
        
        if (me->query_condition("qh_poison") > 10)
        me->apply_condition("qh_poison", 0);
        message_vision(HIG "$N吃下一枚绝情丹，顷刻间便觉一股凉意直透丹田。\n" NOR, me);

        destruct(this_object());
        return 1;
}