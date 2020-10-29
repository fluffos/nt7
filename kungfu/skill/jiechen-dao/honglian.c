// snowman
#include <ansi.h>

int check_fight(object me);
int remove_effect(object me);

int perform(object me)
{
        object weapon;

        if( !me->is_fighting() || !living(me))
                return notify_fail("「红莲火」只能在战斗中的使用。\n");

      if( !objectp(weapon=query_temp("weapon", me)) || 
          query("skill_type", weapon) != "blade" )
                return notify_fail("你先找把刀再说吧！\n");

        if( query_temp("honglian", me) )
                return notify_fail("你正在使用「红莲火」。\n");  

        if( query_temp("mz_lx", me) )
                return notify_fail("你正在使用「降妖伏魔咒」。\n");  

        if((int)me->query_skill("jiechen-dao", 1) < 180 )
                return notify_fail("你的戒尘刀不够娴熟，还不能领会「红莲火」之诀窍。\n");

        if (me->query_skill_mapped("blade") != "jiechen-dao")
                return notify_fail("你必须使用戒尘刀来施展「红莲火」。\n");   

        if( query("max_neili", me)<3500 )
                return notify_fail("你的内力修为太弱，使不出「红莲火」。\n");                

        if( query("neili", me)<800 )
                return notify_fail("你现在真气不够，使不出「红莲火」。\n");


        if(userp(me) && (int)me->query_skill("buddhism", 1) < 180 )
                return notify_fail("你对禅宗心法的领悟不够，无法使用「红莲火」。\n");

        if(userp(me) && me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("你的内功不对，根本不能使出「红莲火」。\n");
                                                                                     
        if( !query("jiali", me) )
                return notify_fail("「红莲火」全以内力为本。你不加力，是无法发挥出它的威力的。\n");

        message_vision(RED "\n$N祭起戒尘刀之「红莲火」绝技，精纯的内力呈红色缓缓涌出，\n"
                           "于身前三尺之处，便即停住不动，将这飘荡无定的真气定在半空，\n"
                           "它虽是虚无缥缈，不可捉摸，却能杀人于无形，实是厉害不过！\n" NOR, me);
        me->start_busy(1);
        set_temp("honglian", 1, me);
        addn("neili", -300, me);
        addn("jingli", -100, me);
        addn_temp("apply/parry", me->query_skill("jiechen-dao",1)/3, me);
        addn_temp("apply/arrmor", me->query_skill("jiechen-dao",1)/3, me);
        check_fight(me);
        return 1;
}

int check_fight(object me)
{
        object *enemy, target;
        int sz;        

        if (!me) return 0;

        if( me->is_ghost() || !living(me) || query("no_fight", environment(me)) || query_temp("weapon", me)){
           addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
           addn_temp("apply/arrmor", -me->query_skill("jiechen-dao",1)/3, me);
           delete_temp("honglian", me);
           return 0;
           }        

        addn("neili", -5, me);
        enemy = me->query_enemy();

        if( !enemy || !arrayp(enemy) ) remove_effect(me);
        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;
        if( sz > 0 ) target = enemy[random(sz)];
        else remove_effect(me);
        if( !query_temp("honglian", me))return 1;

        else if(!me->is_fighting())
        {
                if( !query_temp("stopped", me) )
                {
                    set_temp("stopped", 1, me);
                    call_out("check_fight", 2, me);
                }
                else remove_effect(me);
        }
        else if (userp(me))
        {
                  message_vision(HIY"$N一刀劈出，突然变招，竟然是完全不同的招数来！\n"NOR,me);
                  me->start_busy(1);
                  addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
                  addn_temp("apply/arrmor", -me->query_skill("jiechen-dao",1)/3, me);
                  delete_temp("honglian", me);
                  return 1;
        }   
       else if( query("neili", me) <= 10 || !target)remove_effect(me);
       else call_out("check_fight", 1, me);
       return 1;
}       

int remove_effect(object me)
{
   string msg;
   message_vision(HIY "\n$N回手一招红莲火使完，双手合十立于当地，示慈悲为怀。\n\n"NOR, me);
   addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
   addn_temp("apply/armor", -me->query_skill("jiechen-dao",1)/3, me);
   delete_temp("honglian", me);
   delete_temp("stopped", me);
   remove_call_out("check_fight"); 
   return 0;
}
