// derive.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int deriving(object me);
int halt_deriving(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where;
        int point;
        string skill;

        seteuid(getuid());
        where = environment(me);
        
        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( me->is_busy() || query_temp("pending/deriving", me) )
                return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("战斗中还是好好的凝神对敌吧。\n");

        if( query("combat_exp", me)<100000 )
                return notify_fail("你的实战经验太浅，还无法领会通过实战获得的心得。\n");

        if( query("experience", me)<query("learned_experience", me)+60 )
                return notify_fail("你现在积累的实战体会还太少。\n");

        if( query("qi", me)<query("max_qi", me)*7/10 )
                return notify_fail("你现在没有充足的体力用来吸收实战的心得。\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("你现在精神不济，难以抓住实战体会中的秘要！\n");

        if( query("no_fight", environment(me)) && 
            (query("doing", me) != "scheme" || this_player(1)) )
                return notify_fail("你无法在这个地方安心吸收通过实战得到的心得。\n");

        if (arg && sscanf(arg, "%d %s", point, skill) == 2 ||
            arg && sscanf(arg, "%d", point) == 1)
        {
                if( query("experience", me)-query("learned_experience", me)<point )
                        return notify_fail("你并没有积累这么多实战体会。\n");

                if (point < 60)
                        return notify_fail("似乎没有必要为吸收这点体会下功夫。\n");
        } else
        {
                point = -1;
                if (arg)
                        sscanf(arg, "%s", skill);
        }

        if (! stringp(skill)) skill = "martial-cognize";
        if( skill != "martial-cognize" && skill != "sword-cognize" && skill != "force-cognize")
        {
                return notify_fail("你目前只能汲取修养类的技能。\n");
                if( me->query_skill(skill, 1) < 200 )
                        return notify_fail("你并不会这种功夫。\n");
        }

        write("你默默的想了想先前一段时间和对手交手时的情形，开始吸收汲取其中的心得。\n");

        set_temp("pending/deriving", 1, me);
        set_temp("derived_point", point, me);
        set_temp("derived_skill", skill, me);
        me->set_short_desc("正在演练招式。");
        message_vision("$N慢慢放开姿势，忽前忽后，手舞足蹈，似乎在思索什么。\n", me);
        me->start_busy(bind((:call_other, __FILE__, "deriving" :), me),
                       bind((:call_other, __FILE__, "halt_deriving" :), me));
        return 1;
}

int deriving(object me)
{
        int improve;
        int cost;
        string skl_id, skl_name;
        object weapon;
        string skill;
        int r;
        int n;
        int vip_level;

        skill = query_temp("derived_skill", me);

        if( skill == "sword-cognize" && 
            (!objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword") )
                skl_id = "martial-cognize";
                
        else skl_id = skill;
 
        if( file_size(SKILL_D(skl_id)+".c") < 0 ) skl_id = "martial-cognize";
        skl_name = to_chinese(skl_id);
                        
        if (! me->can_improve_skill(skl_id))
        {
                write("你感觉自己的实战经验还有欠缺，还无法"
                      "领会更高境界的" + skl_name + "。\n");
                message("vision", me->name() + "轻轻的叹了口气，怔怔"
                        "的发了一会儿的呆。\n", environment(me), ({ me }));
                delete_temp("pending/deriving", me);
                me->set_short_desc(0);
                return 0;
        }

        cost = me->query_skill(skl_id, 1) + 1;
        cost+=me->query_all_buff("derive_times");
                
        if( query("special_skill/musha", me) )
                cost += cost * 50 / 100;

        if( n = ACTION_D->query_action("jiqu_speed") )
                cost *= n;

        if( cost+query("learned_experience", me)>query("experience", me) )
                cost=query("experience", me)-query("learned_experience", me);

        // gain martial-cognize & combat_exp, potential
        improve = cost * (1 + random(5 + me->query_skill(skl_id, 1) / 10));

        if( intp(r=me->query_all_buff("derive_effect")) )
                improve += improve * r / 100;

        // 转世技能群邪辟易提升汲取效果
        if( query("special_skill/nopoison", me) )
                improve += improve * 50 / 100; 

        if( query("special_skill/musha", me) )
                improve += improve * 50 / 100; 
        
        if( query("time_reward/study", me) )
                improve += improve * 25 / 100;

        vip_level = me->query_viplevel();
        if( vip_level < 1 )
                ;
        else if( vip_level < 2 )
                improve += improve * 10 / 100;
        else if( vip_level < 3 )
                improve += improve * 30 / 100;
        else if( vip_level < 4 )
                improve += improve * 60 / 100;
        else if( vip_level < 5 )
                improve += improve;
        else if( vip_level < 6 )
                improve += improve * 150 / 100;
        else if( vip_level < 7 )
                improve += improve * 2;
        else
                improve += improve * 3;
                                
        // 帮派荣誉点
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "jiqu") )
                improve += improve * 20 / 100;

        if( me->query_family() && BUNCH_D->query_family_efficient(me->query_family(), "jiqu") )
                improve += improve * 20 / 100;
                
        if (me->can_improve_skill(skl_id))
                me->improve_skill(skl_id, improve);

        addn("combat_exp", 1+random(2), me);

        if (random(2))
                // not limit by potential limit
                addn("potential", 1, me);

        // cost experience
        if( me->add("learned_experience",cost) >= query("experience", me) )
        {
                write("你将实战中获得的体会心得充分的消化吸收了。\n");
                message("vision", me->name() + "微微一笑，看来内心颇为喜悦。\n",
                        environment(me), ({ me }));
                delete_temp("pending/deriving", me);
                delete_temp("derived_point", me);
                delete_temp("derived_skill", me);
                me->set_short_desc(0);
                return 0;
        }

        if( query_temp("derived_point", me)>0 )
        {
                if( me->add_temp("derived_point",-cost)<1 )
                {
                        write("你消化吸收了一些实战中获得的体会心得。\n");
                        message("vision", me->name() + "微微一笑，看来内心颇为喜悦。\n",
                                environment(me), ({ me }));
                        delete_temp("pending/deriving", me);
                        delete_temp("derived_point", me);
                        delete_temp("derived_skill", me);
                        me->set_short_desc(0);
                        return 0;
                }
        }

        switch (skl_name)
        {
        case "武学修养":
                switch (random(20))
                {
                case 0:
                        write("你凝思良久，对内功方面又有了新的体会。\n");
                        break;
        
                case 1:
                        write("你默默思索，对拳脚功夫又想通了一些关节。\n");
                        break;
        
                case 2:
                        write("你静心琢磨，对轻身功夫又添了一层理解。\n");
                        break;
        
                case 3:
                        write("你总结了见识过的种种兵器功夫，又想通了其中的一些奥秘。\n");
                        break;
                }
                break;

        case "剑道修养":
                switch (random(20))
                {
                case 0:
                        write("你轻挥长剑，细细揣摩剑道精微之处。\n");
                        break;
        
                case 1:
                        write("你手中长剑点抹切削，暗暗分析各种手法的不同。\n");
                        break;
        
                case 2:
                        write("你静心琢磨，仿佛又明白了一点剑术上攻守进退的技巧。\n");
                        break;
        
                case 3:
                        write("你眼前浮现出不同门派的各式剑法，似有所悟。\n");
                        break;
                }
                break;
                
        case "内功修养":
                switch (random(20))
                {
                case 0:
                        write("你凝思良久，对内功方面又有了新的体会。\n");
                        break;
                case 1:
                        write("你默默思索，对内功方面又想通了一些关节。\n");
                        break;
        
                case 2:
                        write("你静心琢磨，对内功方面又添了一层理解。\n");
                        break;
        
                case 3:
                        write("你总结了见识过的种种内功功夫，又想通了其中的一些奥秘。\n");
                        break;
                }
                break;
        }

        if( random(2) && query("total_hatred", me)>0 )
        {
                // addn("total_hatred", -random(1 + cost), me);
                addn("total_hatred", -(random(10) + 1), me);
                tell_object(me, CYN "你只觉一阵清气透入肺腑，胸中杀意渐消。\n" NOR);
                if( query("total_hatred", me)<0 )
                        set("total_hatred", 0, me);
        }

        return 1;
}

int halt_deriving(object me)
{
        tell_object(me, "你心随意转，收回念头，不再思索武学秘奥。\n");
        tell_room(environment(me), me->name() + "唯一皱眉，收住了姿势。\n", me);
        delete_temp("pending/deriving", me);
        delete_temp("derived_point", me);
        delete_temp("derived_skill", me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : derive [<点数>] [ 技能 ]

    这个指令可以让你吸收汲取实战中的体会，当你充分的消化了其
中的秘奥以后，可以提升自己的武学修养。这是一门艰深的学问，是
所有武学的基础，身为一代宗师，武学修养是必不可少的。如果你装
备了剑这种武器，而且指定了技能名为 sword-cognize，则将获得剑
道修养。

HELP );
        return 1;
}
