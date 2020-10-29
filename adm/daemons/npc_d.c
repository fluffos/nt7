// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// npc_d.c

#include <ansi.h>

int set_npc_skill(object npc, int level);

object load_npc_data(string name)
{
        mapping family;
        mixed lines,tmp;
        mixed str;
        string file,key,value;
        string title;
        object npc, ob;
        int cexp,skill;
        int diff;
        int nl;
        int i,sz;
                        
        file = replace_string(read_file(name), "\r", ""); 
        lines = explode(file,"\n");
        sz = sizeof(lines);
        tmp = ([]);
        for( i=0;i<sz;i++ ) {
                if( !stringp(lines[i]) || lines[i]=="" || sscanf(lines[i],"%s=%s",key,value)!=2 ) 
                        continue;

                switch(key) {
                        case "name":
                        case "stunt_hit":
                        case "stunt_fail":
                                tmp[key] = trans_color(value, 3); 
                                break;
                        case "long":
                        case "stunt_msg":
                                tmp[key] = sort_msg(trans_color(value, 3))+"\n"; 
                                break;
                        //case "wields":                //只拿单武器
                        case "wears":
                                tmp[key] = explode(value,",");
                                break;
                        default :
                                tmp[key] = value;
                                break;
                }
        }
        
        npc = new("/kungfu/class/misc/boss");
        npc->setup_family(tmp["family"]);
        family = query("family", npc);
        title  = query("title", npc);
        npc->set_dbase(tmp);
        npc->set_name(tmp["name"], ({ tmp["id"] }));
        npc->setup();
        set("family", family, npc);

        diff = atoi(query("difficult", npc));
        if( diff < 3 ) {
                set("title", HIC"普通 "NOR+title, npc);
        } else if( diff < 6 ) {
                set("title", MAG"强壮 "NOR+title, npc);
        } else if( diff < 10 ) {
                set("title", HIG"精英 "NOR+title, npc);
        } else {
                set("title", HIR"君王 "NOR+title, npc);
                set("is_boss", 1, npc);
        }
        
        set("str", 100, npc);
        set("int", 100, npc);
        set("con", 100, npc);
        set("dex", 100, npc);
        
        cexp = atoi(query("basic_exp", npc))*(10+diff)/10;
        skill = to_int(pow(to_float(cexp/100),1.0/3))*10+1;
        //skill = to_int(exp(log(to_float(cexp))/3));
        set("combat_exp", cexp, npc);
        nl = skill * 10 + cexp / 100; 
        set("max_neili", nl, npc);  
        set("neili", nl*3/2, npc); 
        set("max_jingli", nl/2, npc); 
        set("jingli", query("max_jingli", npc), npc); 
        set("max_qi",(query("max_neili", npc)/2+100*skill*diff), npc); 
        set("qi", query("max_qi", npc), npc); 
        set("eff_qi", query("max_qi", npc), npc); 
        set("max_jing", query("max_jingli", npc)/2+40*skill*diff, npc);
        set("eff_jing", query("max_jing", npc), npc); 
        set("jiali", skill, npc);
        
        set_temp("apply/attack",  skill*diff,npc);
        set_temp("apply/defense", skill*diff,npc);
        addn_temp("apply/damage",  skill*diff,npc);
        addn_temp("apply/unarmed_damage", skill*diff,npc);
        set_temp("apply/armor", skill*diff,npc);

        set_temp("apply/double_damage", diff*10,npc);
        set_temp("apply/add_damage", diff*10,npc);
        set_temp("apply/add_freeze", diff*10,npc);
        set_temp("apply/add_forget", diff*10,npc);
        set_temp("apply/add_weak", diff*10,npc);
        set_temp("apply/add_busy", diff*10,npc);
        set_temp("apply/avoid_freeze", diff*10,npc);
        set_temp("apply/avoid_weak", diff*10,npc);
        set_temp("apply/avoid_busy", diff*10,npc);
        set_temp("apply/reduce_busy", diff*10,npc);
        set_temp("apply/reduce_damage", diff*10,npc);
        set_temp("apply/ap_power", diff*10,npc);
        set_temp("apply/dp_power", diff*10,npc);
        set_temp("apply/da_power", diff*10,npc);
        set_temp("apply/avoid_defense", diff*10,npc);
        set_temp("apply/avoid_parry", diff*10,npc);
        set_temp("apply/avoid_dodge", diff*10,npc);
        set_temp("apply/avoid_force", diff*10,npc);
        set_temp("apply/avoid_attack", diff*10,npc);


        if( !undefinedp(tmp["chatmsg"]) ) {
                set("chat_chance", 80, npc);
                set("chat_msg", ({
                        tmp["chatmsg"]+"\n", 
                }), npc);
        }

        set_npc_skill(npc, skill);
        
        if( str = query("wields", npc) ) {
                if( ob = new(str) ) {
                        ob->move(npc);
                        ob->wield();
                }
        }

        str = query("wears", npc);
        if( !undefinedp(str) && arrayp(str) ){
                foreach( string line in str ) {
                        if( ob = new(line) ) {
                                ob->move(npc);
                                ob->wear();
                        }
                }
        }

        return npc;
}

int set_npc_skill(object npc, int level)
{
        string basic_skill, advance_skill;
        mapping skills;
        string skill;

        if( !npc )
                return 0;
        
        if( mapp(skills = npc->query_skills()) ) 
        {
                foreach( skill in keys(skills) ) 
                        npc->set_skill(skill, level);
        }
        
        if( query("poison_name", npc) )
                npc->set_skill("poison", level);
        
        basic_skill = query("basic_skill", npc);
        advance_skill = query("advance_skill", npc);
        if( !basic_skill || !advance_skill )
                return 1;

        npc->set_skill(basic_skill, level);
        npc->set_skill(advance_skill, level);
        npc->map_skill(basic_skill, advance_skill);
        npc->prepare_skill(basic_skill, advance_skill);
        
        return 1;
}

void create()
{
}

