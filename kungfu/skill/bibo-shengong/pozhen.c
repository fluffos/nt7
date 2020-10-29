// Code of JHSH        
// pozhen.c

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        object env,owner;
        string msg;
        
        return notify_fail("暂时不开放。\n");
        env = environment(me);
        if (!env)
                return notify_fail("这里什么地方也不是！\n");
        if( !query("th_buzhen", env) )
                return notify_fail("这里并无布有奇门阵法。\n");
        
        if( !objectp(owner=find_player(query("th_zhen_owner", env))) || 
            environment(owner) != env)
        {
                set("long",query("org_desc",  env), env);
                set("exits",query("org_exits",  env), env);
                set("cost",query("org_cost",  env), env);
                delete("org_desc", env);
                delete("org_cost", env);
                delete("org_exits", env);
                delete("th_buzhen", env);
                delete("th_pozhen", env);
                delete("th_zhen_owner", env);
        
                tell_object(env, CYN"一阵青雾升腾而起又四散而去，四面景致猛然一变。\n"NOR);
                return 1;
        }

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所用的内功与「奇门阵法」心法相悖！\n");

        if( me->query_skill("bibo-shengong", 1) < 80 )
                return notify_fail("你的内功修为火候未到，还未领悟「奇门阵法」！\n");

        if( query("jingli", me)<query("max_jingli", me)*80/100 )
                return notify_fail("你的精力不够，不足以破解「奇门阵法」！\n");

        if( query("jing", me)<query("max_jing", me)*80/100 )
                return notify_fail("你的精不够，不足以破解「奇门阵法」！\n");

        if( me->query_skill("qimen-wuxing", 1) < 80 )
                return notify_fail("你的奇门五行修为不够，还未领悟「奇门阵法」！\n");

        set("jing",query("max_jing",  me)/2, me);
        set("jingli",query("max_jingli",  me)/2, me);

        if( query("id", me) != query("th_zhen_owner", env) && 
        me->query_skill("qimen-wuxing",1)<query("th_pozhen", env)*3/4){
                message_vision(CYN"$N坐在地上冥思苦想，突然脸色大变，口吐鲜血！\n"NOR,me);
                me->unconcious();
                return 1;
        }

        msg = HIW"$N凝思片刻，阵法的种种生克变化已全盘了然于胸，仰天一声长笑，袍袖一拂，\n";
        msg += "掠入阵中，掌劈脚挑，顿时飞沙走石，不一刻，阵中阴霾戾气已消散得无影无踪！\n"NOR;
        message_vision(msg, me);
        
        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        return 1;
}