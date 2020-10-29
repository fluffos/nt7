// Code of ShenZhou
// Ryu, 12/5/96

inherit ITEM;
#include <ansi.h>;

void init();
void wear(int);

int worn;

void create()
{
        set_name(HIR"一堆火焰"NOR,({"huo yan"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR"火焰高约尺，"+GRN+"色作纯碧，"+BLU+"鬼气森森，"+HIR+"和寻常火焰大异。\n"NOR);
                set("unit", "堆");
                set("value", 1);
                set("no_get", 1);
                set("no_drop", 1);
        }
        
        setup();
}

void init()
{
        worn = 0;
        call_out("wear", 100, 1); 
        add_action("do_kick","ti");
        add_action("do_kick","kick");
}


int do_kick(string arg){

        object ob, me, armor, temp_ob;
        mapping myfam;
        int exp1, exp2, damage;
        me=this_player();
        if( !arg || me != this_player(1)) return 0;
        ob = present(arg, environment(me));  
        
        damage = me->query_skill("feixing-shu",1);
        if(!ob) 
        {
               tell_object(me,"这里没有" + arg + "这个生物。\n");
               return 1;
        }

        exp1=atoi(count_div(query("combat_exp", me),100));
        exp2=atoi(count_div(query("combat_exp", ob),100));
        
        if(!ob->is_character() || !me->is_fighting(ob) )
        {
                tell_object(me,"只能对战斗中的对手使用。\n");
                return 1;
        }
        
        if (me->is_busy())
        {
               tell_object(me,"你正忙着呢。\n");
                return 1;
        }

        if ((damage<150)){
                message_vision(HIR"\n$N嘻嘻一笑，提起脚来，向火焰踢去，结果一声惨叫，被火焰烧伤。\n"NOR,me);
                set_temp("die_reason", "给星宿毒火烧死了", me);
                me->receive_wound("qi", random(500));
                destruct(this_object());
                me->start_busy(random(2)+2);
                return 1;
        } else {
                
                addn("neili", -damage, me);
                message_vision(HIR"\n$N脸色一变，身形一晃，已经转到$n身后。举起右脚，微微一挑，将火焰向$n拨去。\n"NOR,me,ob);
                me->start_busy(random(2)+2);
                if (ob->query_skill_mapped("parry") == "dragon-strike" &&
                    !query_temp("weapon", ob) && 
                    ob->query_skill("dragon-strike",1) > damage/2 + random(damage/2))
                {
                        message_vision(HIW"\n$N一声怒吼，双掌收至胸口随即缓缓推出，一道气墙汹涌而起，却是威霸江湖的「降龙十八掌」！\n"NOR,ob);
                        message_vision(HIR"\n火焰在彭湃的气浪冲击下，顷刻间以更快的速度向$N飞卷而去。\n"NOR,me);
                        temp_ob = ob;
                        ob = me;
                        me = temp_ob;
                        damage = me->query_skill("dragon-strike",1);
                }
                if(random(exp1)>random(exp2))
                {
                        if( query_temp("armor/cloth", ob)){
                                armor=query_temp("armor/cloth", ob);
                                if( query("id", armor) != "armor"){
                                        message_vision(HIR"\n只见$N身上的$n"+HIY+"被火焰烧得四散而飞。\n"NOR, ob, armor);
                                        armor->unequip();
                                        armor->move(environment(ob));
                                        armor->set_name("烧焦的"+query("name", armor));
                                        set("value", 0, armor);
                                        set("armor_prop/armor", 0, armor);
                                        ob->reset_action();
                                }
                        }
                        
                        message_vision(HIR"\n只听见一声惨叫，$n躲闪不及，被火焰烧中。\n"NOR,me,ob);
                        set_temp("die_reason", "给星宿毒火烧死了", ob);
                        ob->receive_wound("qi", damage, me);
                        ob->start_busy(random(2)+1);
                        destruct(this_object());
                        return 1;
                } else {
                        message_vision(HIY"\n$n大惊之下闪开，火光下只见$N微微冷笑。\n"NOR,me,ob);
                        destruct(this_object());
                        return 1;
                }
        }
        
}

void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", HIR"火焰熊熊燃烧着，"+GRN+"色作纯碧，"+BLU+"鬼气森森，"+HIR+"和寻常火焰大异。\n"NOR);
                call_out("wear", 100, phase+1); 
                break;
        case 2:
                set("long", RED"火势越来越弱，几乎快烧完了。\n"NOR);
                call_out("wear", 30, phase+1); 
                break;
        case 3:
                message("vision",RED"火焰渐渐地熄灭了。\n"NOR, environment(this_object()));
                destruct(this_object());
                break;
        }       
}

// End of File 
