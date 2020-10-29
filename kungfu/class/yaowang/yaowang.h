// yaowang.h
#include <ansi.h>
int permit_recruit(object ob)
{
        command("say 暂不开放！");
        return 0;
        if( query("detach/药王谷", ob) || 
            query("betrayer/药王谷", ob) )
        {
                command("say 你既然已经离开了药王谷，干嘛又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 阁下不忠不信，我们药王谷虽小，但却不收弃师之徒。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "药王谷" )
        {
                command("say 你既有了名师指点，就要勤下苦功，勿要三心二意！");
                return 0;
        }

        return 1;
}



/*
void kill_ob(object ob)
{
        set_temp("my_killer",ob);
        remove_call_out("check");
        call_out("check",1);
        ::kill_ob(ob);
}
*/

int accept_fight(object ob)
{
        command("say 我没有兴趣陪你打架。");
        return 0;
}

int accept_hit(object ob)
{
        command("heng");
        command("command 你要找死么？");
        remove_call_out("check");
        call_out("check",1);
        return 1;
}

int accept_kill(object ob)
{
        command("haha");
        command("say 来的好！我就要你死个痛快！");
        remove_call_out("check");
        call_out("check",1);
        return 1;
}

void check()
{
        object ob=this_object();
//        object me=query_temp("my_killer");
        object me=this_player();
        if(! present(me,environment()) )
        {
                remove_call_out("check");
                return;
        }
        if( me->is_ghost() )
        {
        remove_call_out("check");
        return;
        }
      
        switch(random(4))
        {        
        case 0:
        {
        message_vision(HIR"$N双手一挥，一支断肠花直冲$n而去！\n",ob,me);

        if(random(2))
        
                {
                message_vision(HIR"$N只觉一股淡香袭来,顿时脑中一阵麻木！\n"NOR,me,ob);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("flower_poison", 30 +
                                    (int)me->query_condition("flower_poison"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N轻而易举的躲过了$n的断肠花！\n"NOR,me,ob);
                call_out("check",2+random(3));
                }
        }
        break;

        case 1:
        {

        message_vision(HIR"$N双手一搓，空气中水珠化作冰块向$n去！\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"只见冰块自空中直冲而下，钻入$N体中不见了！\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("iceshock", 30 +
                                    (int)me->query_condition("iceshock"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N迎着冰块而去，用内力将冰块击得粉碎!\n"NOR,me);
                call_out("check",2+random(3));
                
                }
        }
        break;

        case 2:
        {

        message_vision(HIR"$N把手中养生丹向$n递去\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"$N接过养生丹，吃了下去！\n"NOR,me);
                message_vision(HIR"$N只觉肚子「咕咕咕」叫个不停，随后放了个奇臭"
                                "无比的屁！\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                set("food", 0, me);
                set("water", 0, me);
                me->apply_condition("hunger", 5 +
                                    (int)me->query_condition("hunger"));
                remove_call_out("check");
                message_vision(HIR"$N饿得快死了。\n"NOR,me);
                message_vision(HIR"$N渴得要虚脱了。\n"NOR,me);
                }
        else
                {
                message_vision(HIR"$N接过养生丹，吃了下去！\n"NOR,me);
                message_vision(HIR"$N只感疲劳一扫而空，再也不觉得饥饿。\n"NOR,me);
                if( query("food", me)<400 )
                        set("food", 400, me);

                if( query("water", me)<400 )
                        set("water", 400, me);
                call_out("check",2+random(3));
                }
        }
        break;
        
        case 3:
        {

        message_vision(HIR"$N右手一甩，一支透骨针直向$n飞去！\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"$N顿时血流如注，顷刻染红了全身！\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("tougu_zhen", 30 +
                                    (int)me->query_condition("tougu_zhen"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N顺着透骨针的方向，纵身跃起，躲过这致命一击！\n"NOR,me);
                call_out("check",2+random(3));
                
                }
        }
        break;

        }
/*
        if( random(10) == 9 )
//      这个地方留待中七星海棠毒，但条件NPC必须是无嗔、石万嗔。        
*/

}


