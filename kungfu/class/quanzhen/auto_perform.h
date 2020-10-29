// /kungfu/class/quanzhen/autoperform.h
// for quanzhen npc's autoperform
// by sdong 08/01/98
// auto perform function (dispatched by chat_combat_msg)

int auto_perform()
{
        object me = this_object();
        object target = me->select_opponent();
        objectweapon=query_temp("weapon", me);


        //if ( !objectp(target) ) return 0;



        if( !is_busy() && !is_fighting() && !objectp(target) )
        {
                if( query("eff_qi",1, me)<query("max_qi", me) && query("eff_qi",1, me)>query("max_qi", me)/2 )
                {
                        command("yun heal");
                        command("yun heal");
                        command("yun recover");
                        return 1;
                }

                command("dazuo 500");
                return 1;
        }




        if( objectp(weapon) && query("skill_type", weapon) == "sword" )
        {

                  if( query("eff_qi",1, me)>query("max_qi", me)/2 && 
                        query("eff_qi",1, me)<query("max_qi",1, me)*2/3 )
                  {
                        command("halt");
                        command("yun heal");
                        command("yun heal");
                        command("yun heal");
                        command("yun recover");
                  }
                  else if( query("neili", me)<150 && query("eff_qi",1, me)<query("max_qi", me)/2 )
                        perform_action("sword.tonggui");
                  else
                  {
                        if( !query_temp("sanqing", me) )
                                return perform_action("sword.sanqing");
                        else if( query("id", me) == "wangchongyang" )
                        {
                                command("yunshentong"+query("id", target));
                        }
                        else return perform_action("sword.sanqing");
                  }


        }
        else if( objectp(weapon) && query("skill_type", weapon) == "whip" )
        {
                return perform_action("whip.riyue");
        }
        else
        {
                if( !query_temp("sanhua",1, me) )
                        return perform_action("strike.sanhua");
                else if( query("id", me) == "wangchongyang" )
                {command("yunshentong"+query("id", target));
                }
                else return perform_action("cuff.lianhuan");
        }
}

