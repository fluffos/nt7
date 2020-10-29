// sserver.c

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
        me->clean_up_enemy();
        return me->select_opponent();
}

int attack_power(object me, string skill)
{
        int result, imp;
        object ob = offensive_target(me);
        if( ob && query_temp("immortal", ob) &&
            ob->query_skill_mapped("dodge") == "lingbo-weibu" )
                return 0;

        result = SKILLS_D->attack_power(me, skill);
        imp = COMBAT_D->famsk_buff(me, skill, 1);
        result += result * imp / 100;
        if( me->query_viplevel() == 9 ) result *= 3;
        else if( me->query_viplevel() == 8 ) result *= 2;
        return result;
}

int defense_power(object target, string skill)
{
        int result, imp;
        result = SKILLS_D->defense_power(target, skill);
        imp = COMBAT_D->famsk_buff(target, skill, 2);
        result += result * imp / 100;
        if( target->query_viplevel() == 9 ) result *= 3;
        else if( target->query_viplevel() == 8 ) result *= 2;
        return result;
}

int damage_power(object me, string skill)
{
        return SKILLS_D->damage_power(me, skill);
}

int improve_power(object me, string skill, int usage)
{
        return COMBAT_D->famsk_buff(me, skill, usage);
}
