//Cracked by Kafei


int auto_perform()
{
        object me=this_object();
        object weapon=query_temp("weapon", me);
        object target=me->select_opponent();
        
        if( query("combat_exp", target)<500000 )
        return 0;

        switch(query("real_menpai", me)){
        case "huashan" :

        if( query("qi", me)<10 || query("jing", me)<10 || query("jingli", me)<10)return 0;

        if ( !me->is_fighting() ) {
                if( query("eff_qi", me)<query("max_qi", me) )
                me->exert_function("heal");
                return 1;
                }

                if ( objectp(weapon) ) {
                        if( query("skill_type", weapon) == "sword" && random(4) == 0 )
                        return perform_action("sword.jianzhang"); 
                        else if( query("skill_type", weapon) == "blade" && random(4) == 0 )
                        return perform_action("blade.sanshen");
                }
        else if( !query_temp("leidong", me) && random(4) == 0){
                return perform_action("cuff.leidong");
        }
        else if( !query_temp("wuji", me) && target->query_condition("hyz_damage") <= 5 && random(4) == 0){
                return  perform_action("strike.wuji");
        }
        
        if ( !me->is_fighting() ) {
                if( query("eff_qi", me)<query("max_qi", me) )
                        exert_function("heal");
                return 1;
        }

                break;
                
        case "dajin" :
        if ( !objectp(target)
                 || !random(query("combat_exp", me)*2
                /query("combat_exp", target)+1))return 0;

        if( !objectp(query_temp("weapon",target)) || query_temp("chan/"+target->name(),me))
                command("unwield sword");
        else
                command("wield sword");

        if( !query_temp("taiji", me) && random(3) == 0 && query("combat_exp", me)>2000000 )
                command("exert taiji");
/*else if( present("feibiao",me) && random(2) == 0 && !query_temp("armor/embed", target)){
        command("hehe");
        command("throwbiaoat"+query("id", target));
        target->remove_killer(me);
        target->fight_ob(me);
        return 1;
        }
*/
        else if( objectp(weapon) && query("skill_type", weapon) == "sword" )
        {
                me->map_skill("parry", "taiji-jian");
                me->reset_action();

                if( !target->is_busy() )
                        return perform_action("sword.chan");
                else
                        return perform_action("sword.shenmen");
        }
        else
        {
                me->map_skill("parry", "taiji-quan");
                me->reset_action();

                switch( random(2) )
                {
                        case 0:
                                if( target != query_temp("nian", me) )
                                        return perform_action("cuff.nian");
                                else
                                        return perform_action("cuff.luanhuan");
                                break;
                        case 1:
                                return perform_action("cuff.luanhuan");
                                break;
                }
        }

                break;

        case "shaolin" :

        if ( !objectp(target)
                 || !random(query("combat_exp", me)*2
                /query("combat_exp", target)+1))return 0;


        if ( objectp(weapon) ) {
                switch(query("skill_type", weapon)){
        
                case "whip" : 
                return perform_action("whip.chanrao");
                break ;
        
                case "club" :
                if (me->query_skill_mapped("club") == "zui-gun")
                        return perform_action("club.zuida");
                else
                        return 0;
                        
                break;

                case "sword" :
                if (me->query_skill_mapped("sword") == "damo-jian" && random(3) == 0)
                return perform_action("sword.sanjue");
                else 
                return 0;
                break;  
                }       
        }
        else
        {       
                command("exert jingang");

                if (me->query_skill_prepared("strike") == "banruo-zhang" && random(3) == 0)
                {
                me->reset_action();
                return perform_action("strike.san");
                }
                
                if (me->query_skill_prepared("finger") == "nianhua-zhi" && random(2) == 0 )
                {
                me->map_skill("parry", "nianhua-zhi");
                me->reset_action();
                return perform_action("finger.fuxue");
                }               

                if (me->query_skill_prepared("finger") == "yizhi-chan" && random(2) == 0 )
                {
                me->map_skill("parry", "yizhi-chan");
                me->reset_action();
                return perform_action("finger.jingmo");
                }
                
                if (me->query_skill_prepared("cuff") == "jingang-quan")
                {
                me->map_skill("parry", "jingang-quan");
                me->reset_action();
                return perform_action("cuff.jingang");
                }
                return 0;
                                
        }
                break;
                
        case "xiyu" :
        if ( !objectp(target)
                 || !random(query("combat_exp", me)*2
                /query("combat_exp", target)+1))return 0;

        if( !query_temp("reverse", me) )
                command("exert reverse");
        else if( !query_temp("powerup", me) )
                command("exert powerup");
        else if( !objectp(weapon) && random(2) == 0 )
                        return perform_action("strike.puji");
                break;
                
        case "mizong" :
        if ( !objectp(target)
           || !random(query("combat_exp", me)*2
                   /query("combat_exp", target)+1))return 0;
        if( !query_temp("longxiang", me) && random(2) == 0 )
                command("exert longxiang");
        else if( !query_temp("shielded", me) && random(2) == 0 )
                command("exert shield");

        else if( objectp(weapon) && query("skill_type", weapon) == "blade" )
        {
                me->reset_action();
                if( !target->is_busy() )
                        return perform_action("blade.shendao");
        }

        return perform_action("strike.fen");
                break;

        case "miaojiang" :
        if ( !objectp(target)
           || !random(query("combat_exp", me)*2
                   /query("combat_exp", target)+1))return 0;

        command("get corpse");
        if (present("corpse", me) ){
        command("throwcorpseat"+query("id", target));
        target->remove_killer(me);
        target->fight_ob(me);
        return 1;
        }

        if( !query_temp("huagong", target) && random(2) == 0 )
                command("perform sanyin");
        else if( random(2) == 0 )
                command("yunqisuck"+query("id", target));

        if (present("bilin zhen", me) && random(2) == 1){
        command("throwzhenat"+query("id", target));
        target->remove_killer(me);
        target->fight_ob(me);
        return 1;
        }
        else if ( present("lianxin dan", me)){
        command("throwdanat"+query("id", target));
        target->remove_killer(me);
        target->fight_ob(me);
        return 1;
        }
                break;

        default:
                return 0;
        }
}
