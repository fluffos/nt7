// poison.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(50);
        set_name(HIG "唐门奇毒" NOR, ({"tangmen qidu", "du yao", "poison"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "粒");
                set("long", "这是一粒由唐门特殊秘方配置而成的毒药，只要一丁点就可以置人于死地！\n");
                set("value", 50);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 1100,
                        "id"    : "tang du",
                        "name"  : "唐门奇毒",
                        "duration": 40,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，把唐门奇毒全部倒入了嘴中。\n",
                       me);
        set_temp("die_reason", "吃了唐门奇毒暴毙身亡了", me);
        me->die();
        destruct(this_object());
        return 1;
}