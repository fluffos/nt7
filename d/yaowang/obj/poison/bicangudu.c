// gudu.c

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + WHT "碧蚕蛊毒" NOR, ({ "bican gudu", "bican", "gudu" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIB "这是一粒集百毒之精华炼制而成的毒药，毒性猛烈之极。经过孔雀胆、鹤顶红练制后无色无味，唯见效较缓!\n" NOR);
                set("base_unit", "粒");
                set("base_value", 200000);
                set("base_weight", 10);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 350,
                        "id"    : "yaowang",
                        "name"  : "碧蚕蛊毒",
                        "duration" : 22,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        message_vision("$N一仰脖，把碧蚕蛊毒全部倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了碧蚕蛊毒暴毙身亡了", me);
        me->die();

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
