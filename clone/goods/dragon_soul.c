#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "龙晶" NOR, ({ "dragon soul" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long","这是龙的内丹，鸡蛋大小，如火焰般赤红。用法：reset\n");
                set("unit", "颗");
                set("value", 50000);
                set("no_drop", 1);
        }
        set("auto_load", 1);
        setup();
}

void init()
{
        if( this_player() == environment() )
                add_action("do_reset", "reset");
}

int do_reset()
{
        object ob = this_player();
        int times, n;

        if( !query("ability1", ob) && !query("ability2", ob) )
        {
                addn("max_neili", -50, ob);
                message_vision(HIR "$N试图吸纳龙晶，但身体承受不了，结果适得其反，受到内力反噬！\n" NOR, ob);
                destruct(this_object());                 
                return 1;
        }
        
        addn("use_dragon_soul", 1, ob);
        n = query("use_dragon_soul", ob);
        times = query("reset_ability", ob);
        
        if( times > 24 ) times = 24;
        if( n > times ) 
        {
                delete("use_dragon_soul", ob);
                addn("reset_ability", 1, ob);

                message_vision(HIY "$N运劲吸纳龙晶，只见$N面色赤红如火，体内真气源源而生，能力点（ability）重置。\n" NOR, ob);
                
                delete("ability1", ob);
                delete("ability2", ob);
                delete("ability_count", ob);
                delete("learned_ability", ob);
                
                ob->save(); 
                
                destruct(this_object());                 
                return 1;
        }
        message_vision(HIY "$N运劲吸纳龙晶，只见$N面色赤红如火，体内真气源源而生，但似乎吸纳龙晶的能量不足以让能力点（ability）重置。\n" NOR, ob);
        destruct(this_object());
        return 1;
}


