 // labazhou.c
 // By Plzw 2004-08-29
 
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "腊八粥" NOR, ({ "laba zhou", "zhou" }) );
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "只见热粥蒸气上冒，兀自在一个个气泡从粥底钻将上来，一碗粥尽作深绿之色，瞧上去说不出的诡异。\n" NOR);
                set("value", 1);
                set("unit", "碗");
                set("only_do_effect", 1); 
        }
}

int do_effect(object me)
{
        // 已经喝过
        if( query("gift/labazhou", me) )
        {
                message_vision(HIY "$N" HIY "端气粥碗，喝了个碗底朝天，但是觉得没有什么作用。\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        // 产生效果
        if( query("story/labazhou", me) )
        {
                message_vision(HIY "$N" HIY "端起粥碗，只觉药气刺鼻，入口却甜甜的并不难吃，顷刻间便喝了个碗底朝天。\n" NOR, me);
                if (random(10) == 1) 
                {
                        message_vision(HIC "$N" HIC "觉得这粥甜甜的，非常好喝。\n"NOR, me);
                        destruct(this_object());
                        return 1;  // 10% 的几率没有效果
                }

                set("gift/labazhou", 1, me);

                message_vision(HIC "$N" HIC "胸中一股热气涌现上来，登时觉得精神为之一振。\n" NOR, me);

                destruct(this_object());
                return 1;
        }
        else
        // 没有中故事的不能喝
                return notify_fail("这碗粥深绿如此，只映得人面俱碧，药气刺鼻，其毒可知，你忍不住便要呕吐。\n");
}