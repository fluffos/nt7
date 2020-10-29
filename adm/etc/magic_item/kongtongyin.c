// 上古十大神器之 崆峒印
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIR "崆峒印" NOR, ({ "kongtong yin", "kongtong", "yin" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "个");
                set("long", HIR "这是上古神器之一的崆峒印，拥有着使人不老的神力。\n"
                                "使用(use)后随机减一岁年龄或加一点容貌，当容貌达到\n"
                                "三十后则减年龄。\n" NOR);
        }
        setup();
}

void init()
{
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("kongtong yin", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                         
        message_sort(HIR "\n$N" HIR "托起手中的崆峒印，一道金光将$P" HIR "笼罩 ……\n" NOR, me);
                        
        if (me->query("per") >= 30)
        {
               me->add("mud_age", -86400);
               write(HIW "你看起来更加年亲了。\n");
        }
        else 
        {
                switch(random(2))
                {
                        case 0:
                           me->add("mud_age", -86400);
                           write(HIW "你看起来更加年亲了。\n" NOR);
                           break;
                           
                        case 1:
                           me->add("per", 1);
                           write(HIG "你看起来更加容光焕发了！\n" NOR);
                           break;
                           
                        default: break;
                }
        }
        me->save();

        destruct(this_object());

        return 1;
}
