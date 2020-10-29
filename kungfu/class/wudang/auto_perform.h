//Cracked by Kafei
// auto perform function (dispatched by chat_combat_msg)

int auto_perform()
{
        object me = this_object();
        object target = me->select_opponent();
        object weapon=query_temp("weapon", me);

        if( !objectp(query_temp("weapon", target)))command("unwieldsword");
        else command("wield sword");
        if( !query_temp("taiji", me))command("exerttaiji");
        if( objectp(weapon) && query("skill_type", weapon) == "sword" )
        {
                me->map_skill("parry", "taiji-jian");
                me->reset_action();

                if( !target->is_busy() ) return perform_action("sword.chan");
        }
        else
        {
                me->map_skill("parry", "taiji-quan");
                me->reset_action();
                switch( random(2) )
                {
                        case 0:
                                if( target != query_temp("nian", me) )
                                        return perform_action("unarmed.nian");
                                else
                                        return perform_action("unarmed.luanhuan");
                                break;
                        case 1:
                                return perform_action("unarmed.luanhuan");
                                break;
                }
        }
}
