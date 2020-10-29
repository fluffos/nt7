#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(NOR + YEL "活骨灵药" NOR, ({ "huogu lingyao", "huogu", "lingyao", "yao" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", YEL "这是一粒灿金色的药丸，在武林中被喻为是疗伤圣药。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 10000);
                set("base_weight", 55);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;
        mapping my;
        int time = 600;

        na = query("name");
        un = query("base_unit");

        // vip的效果
        switch( me->query_viplevel() )
        {
        case 1:
                time = time - time / 10;
                break;
        case 2:
                time = time - time * 2 / 10;
                break;
        case 3:
                time = time - time * 3 / 10;
                break;
        case 4:
                time = time - time * 4 / 10;
                break;
        case 5:
                time = time - time * 5 / 10;
                break;
        case 6:
                time = time - time * 6 / 10;
                break;  
        case 7:
                time = time - time * 7 / 10;
                break;                  
        }
        if( time < 10 ) time = 10;


        if( time() - query_temp("last_eat/dan_full1", me) < time )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan_full1", time(), me);

        message_vision(HIY "$N" HIY "吞下一" + un + na + HIY "，再也感觉"
                       "不到任何疲惫。\n" NOR, me);

        my["jing"]   = my["max_jing"];
        my["qi"]     = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["eff_qi"]   = my["max_qi"];

        me->start_busy(5);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
