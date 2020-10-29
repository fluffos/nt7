#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(100);
        set_name(HIW "七星海棠粉" NOR, ({"qixing-haitang fen", "qixing fen", "fen"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "包");
                set("long", HIW "这是一瓶白色的剧毒粉末，可杀人于无形。\n" NOR);
                set("value", 50000);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                              "id"    : "yaowang", 
                        "name"  : "七星海棠粉",
                        "duration": 15,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，将七星海棠粉倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了七星海棠粉去见黑白无常了", me);
        me->die();
        destruct(this_object());
        return 1;
}