// 上古十大神器之 盘古斧 
// Create by Rcwiz for Hero.cn 2003/08

#include <ansi.h>

#include <weapon.h>
inherit HAMMER;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + WHT + "盘古斧" NOR, ({ "pangu fu", "pangu", "fu" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", NOR + WHT "这是一把巨大的斧头，周身泛着眩目的光华，据说\n"
                                      "此斧乃盘古开天辟地时辟开混沌天地时所用。\n"
                                      "可用之来辟开(pi)太虚，进入太虚境界。\n" NOR);
                set("material", "steel");
                set("wield_msg", NOR + WHT "$N" NOR + WHT "将盘古斧握在手中，犹如"
                                           "盘古再现，威风凛凛。\n" NOR);
                set("unwield_msg", NOR + WHT "$N" NOR + WHT "将手中盘古斧收回。\n" NOR);
                set("stable", 100);

        }
        init_hammer(400);
        setup();
}

void init()
{
        add_action("do_pi", "pi");       
}

int do_pi(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("pangu fu", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("你得先到户外去。\n");
                 
        message_sort(NOR + WHT + "\n$N" NOR + WHT "双手挥舞着手中的盘古巨斧，用力劈下，"
                     "刹那间天空中露出一道裂痕，盘古斧化做一道奇异的光芒将$N" NOR + WHT +
                     "卷进太虚之中。\n" NOR, me);
                
        me->move("/kungfu/class/sky/taixu");
        destruct(this_object());

        return 1;
}
