// jiuzhuan.c 九转金丹

#include <ansi.h>
#include "gift.h"

void create()
{
        set_name(HIY "九转金丹" NOR, ({ "jiuzhuan jindan", "dan" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一颗金色的仙丹，传说是太上老君"
                              "精心修炼的灵丹妙药。成功几率100%"
                            "增加先天各四点\n");
                set("base_value", 150000);
                set("base_weight", 200);
                set("base_unit", "颗");
                set("only_do_effect", 1);
        }       
        setup();
}

int do_effect(object me)
{
        int effect;

        /*
        log_file("static/using", sprintf("%s(%s) eat 九转金丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));
        */

        effect = 0;
        message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
                       "。\n", me);
        if( query("gift/int/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIM "你觉得自己的头脑更清醒了。\n" NOR);
                addn("gift/xiandan", 1, me);
                addn("gift/int/succeed", 1, me);
                addn("int", 1, me);
        }

        if( query("gift/dex/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIR "你觉得自己的腿脚更灵活了。\n" NOR);
                addn("gift/unknowdan", 1, me);
                addn("dex", 1, me);
                addn("gift/dex/succeed", 1, me);
        }

        if( query("gift/con/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIC "你觉得自己的内息更通畅了。\n" NOR);
                addn("gift/xisuidan", 1, me);
                addn("con", 1, me);
                addn("gift/con/succeed", 1, me);
        }

        if( query("gift/str/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIG "你觉得自己的膂力更强健了。\n" NOR);
                addn("gift/shenliwan", 1, me);
                addn("str", 1, me);
                addn("gift/str/succeed", 1, me);
        }

        write(HIM "冥冥中你有所感悟。只觉得灵台一片空明，纯净无比。\n" NOR);
        addn("magic_points", 1000+random(1000), me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}