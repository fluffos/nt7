// This program is a part of NT MudLIB

#include <ansi.h>
#define GIFT_NAME "新手礼品盒"
inherit ITEM;

int do_fen(string arg);

void create()
{
        set_name(HIR + GIFT_NAME + NOR, ({"giftbox", "box"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", @LONG
可以不用留学而获得原有留学增加的先天天赋，方便新手。
打开的指令为open box，解密的帮助文件help add_gift。
LONG );
                set("value", 1);
                set("auto_load", 1);
                /*
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_put", 1);
                set("no_sell", 1);
                set("no_drop", 1);
                */
        }
        setup();
}

void init()
{
        object me = this_player();

        if( me == environment() )
        {
                add_action("do_open", "open");
        }
}

int do_open(string arg)
{
        object me = this_player();

        if( !arg || (arg != "box" && arg != "giftbox") )
                return notify_fail("指令格式：open box\n");

        if( query("welcomegift", me) )
                return notify_fail("你已经使用过新手礼品盒了！\n");
        
        message_vision("$N充满憧憬地拆开了一个新手礼品盒，顿时铺天盖地的红光将$N笼罩在内。\n", me);
        
        if( !query("sl_gift/yzc", me) )
        {
                addn("con", 1, me);
                set("sl_gift/yzc", 1, me); // 般若掌
                tell_object(me, HIM "你获得原需要学习般若掌才能获得１点先天悟性。\n" NOR);
        }

        if( !query("sl_gift/int", me) )
        {
                addn("int", 1, me);
                set("sl_gift/int", 1, me); // 禅宗心法
                tell_object(me, HIM "你获得原需要学习禅宗心法才能获得１点先天悟性。\n" NOR);
        }
                
        if( !query("sl_gift/con", me) )
        {
                addn("con", 1, me);
                set("sl_gift/con", 1, me); // 一指禅
                tell_object(me, HIM "你获得原需要学习一指禅才能获得１点先天根骨。\n" NOR);
        }

        if( !query("sl_gift/str", me) )
        {
                addn("str", 1, me);
                set("sl_gift/str", 1, me); // 金刚拳
                tell_object(me, HIM "你获得原需要学习金刚拳才能获得１点先天臂力。\n" NOR);
        }       

        if( !query("sl_gift/zg", me) )
        {
                addn("dex", 1, me);
                set("sl_gift/zg", 1, me); // 无常杖
                tell_object(me, HIM "你获得原需要学习醉棍才能获得１点先天身法。\n" NOR);
        }

        if( query("gender", me) == "男性" && !query("sl_gift/huoyandao", me) )
        {
                addn("con", 1, me);
                set("sl_gift/huoyandao", 1, me); // 火焰刀
                tell_object(me, HIM "你获得原需要学习火焰刀才能获得１点先天根骨。\n" NOR);
        }

        if( query("gender", me) == "女性" && !query("sl_gift/mhyn", me) )
        {
                addn("dex", 1, me);
                set("sl_gift/mhyn", 1, me); // 大乘涅磐功
                tell_object(me, HIM "你获得原需要学习大乘涅磐功才能获得１点先天身法。\n" NOR);
        }                
                                        
        set("welcomegift", 1, me);
        me->save();
        
        tell_object(me, HIM"你获得了原来需要留学才能获得的先天奖励，这些先天奖励可以通过help add_gift了解。\n"NOR);
        message_vision("红光慢慢退去，$N好像发生了一些变化。\n", me);
        return 1;
}

void owner_is_killed() { destruct(this_object()); }

