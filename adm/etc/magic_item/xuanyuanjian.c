// 上古十大神器之 轩辕剑
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

#include <weapon.h>
inherit SWORD;

int is_magic_item() { return 1; }

mapping skills = ([
        "egui-dao"     :   "饿鬼道",
        "xiuluo-dao"   :   "修罗道",
        "renjian-dao"  :   "人间道",
        "chusheng-dao" :   "畜生道",
        "tianji-dao"   :   "天极道",
        "diyu-dao"     :   "地狱道",
        "lun"          :   "真·六道轮回",
]);

void create()
{
        set_name(HIY "轩辕剑" NOR, ({ "xuanyuan jian", "xuanyuan", "jian" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", HIY "此乃上古神器之首，拥有着无穷的力量，据说"
                                "拥有此剑者可驰骋人、魔、神三界，势不可挡。\n"
                                "上面刻满了各种奇怪的文字，像是佛教经文。\n"
                                "转世后可从此剑中领悟(lingwu)出转世奇学—六道轮回剑。\n"
                                "lingwu ?　可查看可领悟的招式。\n" NOR);
                set("material", "gold");
                set("wield_msg", HIY "$N" HIY "一声轻呼，两条神龙自天而下，拥着一把周身泛着\n"
                                 "金光的神剑，刹那间此剑犹如一道流星划过，落入$N" HIY "手中。\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "心意一转，轩辕剑已归鞘。\n" NOR);
                set("stable", 100);

        }
        init_sword(500);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;
        
        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(20 + random(20));
                return HIY "$N" HIY "挥舞着手中的轩辕剑，万道彩光自中而出，直逼得"
                           "$n" HIY "连连后退。\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "反转手中轩辕剑，猛然间，数道金光划向$n" HIY "，$n" HIY
                           "正惊异间，却已中剑。\n" NOR;

        }
        return damage_bonus;
}

void init()
{
        add_action("do_lingwu", "lingwu");       
}

int do_lingwu(string arg)
{
        object me;
        int i;
        string *str;        
               
        me = this_player();

        if(! objectp(present("xuanyuan jian", me)))return 0;
 
        // 转世后才能领悟
        if (! me->query("scborn/ok"))return 0;
                
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");

        if (! arg)return notify_fail("你要领悟什么？\n");
        
        str = keys(skills);
        if (arg == "?")
        {
                write(HIC "轩辕剑中记载着以下绝学：\n" NOR);
                for (i = 0; i < sizeof(str); i ++)
                        write(sprintf(HIC "%-20s %s\n", 
                              str[i], skills[str[i]]));
                              
                return 1;
                      
        }
        if (member_array(arg, str) == -1)       
                    return notify_fail("你要领悟什么(lingwu ?)？\n");

        if (me->query_skill("buddhism", 1) < 200)
                    return notify_fail("你翻来覆去的研究着上面经文，却始终看不明白。\n");
                                                        
        if (me->query_skill("literate", 1) < 200)
                    return notify_fail("你读书写字等级不够，很多意思你无法理解。\n");

        if (me->query_skill("sword", 1) < 300)
                    return notify_fail("你基本剑法火候不足，无法领悟出什么。\n");                    

        if (me->query_skill("force", 1) < 300)
                    return notify_fail("你基本内功修为不足，无法领悟出什么。\n");
                    
        if (me->query_skill("dodge", 1) < 300)
                    return notify_fail("你基本轻功修为不足，无法领悟出什么。\n");                    

        if (arg == "lun" && me->query_skill("liudao-jian", 1) < 450)
                    return notify_fail("你六道轮回剑法等级不够。\n");
                    
        else if (arg == "lun" && me->query_skill("force", 1) < 680)
                    return notify_fail("你内功修为不足。\n");

        else if (arg == "lun" && me->query("max_neili") < 20000)
                    return notify_fail("你内力修为不足。\n");        

        else
        {
                if (me->query_skill(arg, 1))
                       return notify_fail("你不已经会了这招了吗？\n");

                message_vision(HIM "$N" HIM "聚精会神地参悟着轩辕剑中的奥秘　……\n" NOR, me);
                
                switch(arg)
                {
                        case "lun":
                            write(HIG "你领悟出了绝招　真·六道轮回剑　。\n" NOR);
                            me->set("can_perform/liudao-jian/lun", 1);
                            destruct(this_object());
                            return 1;
                        
                        default :                            
                            write(HIC "你领悟出 " + skills[arg] + " 。\n" NOR);
                            me->set_skill(arg, 1); // 领悟出一级
                            destruct(this_object());
                            return 1;
                }
        }

        return 1;
}
