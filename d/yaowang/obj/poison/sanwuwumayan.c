// bicanfeng.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "三蜈五蟆烟" NOR, ({"sanwuwuma yan", "fen"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一袋剧毒的毒药，如果用来炼暗器有见血封喉之效。\n");
                set("unit", "袋");
                set("value", 20000);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 180,
                        "id"    : "yaowang",
                        "name"  : "剧毒",
                        "duration": 15,
                ]));
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N仰头把一小袋" + name() + "都咽了下去。\n", me);
        set_temp("die_reason", "吸了三蜈五蟆烟，莫名其妙的见了阎王", me);
        me->die();
        destruct(this_object());
        return 1;
}
void init() 
{ 
        add_action("do_dian", "dian"); 
} 
// 后面的待写!如果点燃后，在场的所有id根据本身内力的深厚来决定是否中毒。
// 并且此烟点燃的时间有限，在一个点燃的有效时间可以判断有几次中毒的机会。
// 此毒的载体可以放到火折、火把或者香烟一类。也可以考虑别的。
