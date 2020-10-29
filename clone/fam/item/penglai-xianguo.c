#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(HIM "蓬莱仙果" NOR, ({"penglai xianguo", "penglai", "xianguo", "guo"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIM "\n这是一颗晶莹红透的仙果，据说服用后能功力大增。\n"
                                      "*服用(fuyong xianguo)需消耗吸灵壶，可获得30万经验，25万潜能，1000点贡献及20万体会（双倍奖励服务加倍）。\n"
                                      "*每服用一个蓬莱仙果会消耗一个吸灵壶，吸灵壶可从商城购买。\n" NOR);
                set("unit", "颗");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "fuyong");       
}

int do_use(string arg)
{
        object me, ob;
        int exp, ys_exp, pot, tihui, gongxian;
                
        me = this_player();
        
        if(! objectp(present("penglai xianguo", me)))return 0;
        
        if(! objectp(ob = present("xiling hu", me)))
        {
                return notify_fail("你身上没有吸灵壶，无法服用蓬莱仙果。\n");
        }
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                 
        // 使用描述
        message_vision(HIY + "\n$N" HIY "一抬头服下一颗蓬莱仙果，万道金光闪过，功力大增 ……\n" NOR, me);

        exp = 300000;
        pot = 250000;
        tihui = 200000;
        gongxian = 1000;
        
        // 活动期间
        if (MEMBER_D->is_double_reward(me)) 
        {
                exp *= 2;
                pot *= 2;
                tihui *= 2;
                gongxian *= 2;
        }
        
        tell_object(me, HIG "你服下蓬莱仙果后获得了" + chinese_number(exp) + "经验，" + chinese_number(pot) + "潜"
                            "能，" + chinese_number(gongxian) + "门派贡献及" + chinese_number(tihui) + "体会。消耗吸灵壶一个。\n\n" NOR);

        // 消耗吸灵壶
        destruct(ob);
        
        // 元神增加经验
        if( query("yuanshen_level", me) && query("yuanshen_exp", me)<2000000000 )
        {
                ys_exp = exp / 5;
                exp -= ys_exp;
                addn("yuanshen_exp", ys_exp, me);
        }
        
        if( query("potential", me)>2000000000 || query("learned_points", me)>2000000000 )
        {
                set("potential",query("potential",  me)-query("learned_points", me), me);
                set("learned_points", 0, me);
        }
        if( query("experience", me)>2000000000 || query("learned_experience", me)>2000000000 )
        {
                set("experience",query("experience",  me)-query("learned_experience", me), me);
                set("learned_experience", 0, me);
        }
        if( query("combat_exp", me) <= 200000000000 )
        {
                addn("combat_exp", exp, me);
        }
        if( query("potential", me)<200000000000 )
        {
                addn("potential", pot, me);
        }
        if( query("experience", me)<200000000000 )
        {
                addn("experience", tihui, me);
        }
        
        addn("family/gongji", gongxian, me);
        
        me->save();
        
        log_file("xianguo",query("id", me)+" at "+ctime(time())+" use penglai xianguo.\n");
        
        destruct(this_object());
        
        return 1;
}
