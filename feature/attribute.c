// This program is a part of NT MudLIB
// attribute.c
// Written by Lonely@mud123.com

#include <skill.h>

int query_equipment_buff(string key)
{
        mapping data, props;
        string *apply;
        int i, fullsuit;
        int buff = 0;
        
        // 套装系统加成
        if( data = query_temp("fullsuit", this_object()) )
        {
                fullsuit = 1;
                apply = keys(data);

                for( i = 0; i < sizeof(apply); i++ )
                {
                        props = data[apply[i]];
                        if( !undefinedp(props[key]) )
                                buff += props[key];
                }
        }
        
        // 装备本身加成        
        foreach(object ob in this_object()->query_equipment_objects())
        {
                if( !objectp(ob) ) continue;
                buff += query("armor_prop/" + key, ob) + query("weapon_prop/" + key, ob) + query("rare/apply_prop/" + key, ob) +
                        query("enchase/apply_prop/" + key, ob) + query("qianghua/apply_prop/" + key, ob) + 
                        query("qiling/apply_prop/" + key, ob);
                
                //if( fullsuit )
                if( query_temp("mod_active", ob)  )
                        buff += query("enchase/mod_prop/" + key, ob);
        }
        
        return buff;
}
        
int query_skillmix_buff(string key)
{
        int buff;
        
        buff = query("skillmix/"+key);
        
        return buff;
}

int query_yuanshen_buff(string key)
{
        int buff;
        
        buff = query("yuanshen/"+key);
        
        return buff;
}

int query_jingmai_buff(string key)
{
        int buff;
        
        if( query("jingmai/finish") )
                buff = ZHOUTIAN_D->query_jingmai_buff(key);
        else 
                buff = query("jingmai/"+key);
        
        return buff;
}

int query_ability_buff(string key)
{
        int buff;
        
        buff = query("ability1/"+key) + query("ability2/"+key);
        
        return buff;
}

int query_talent_buff(string key)
{
        int buff;
        
        buff = query("talent/"+key);
        
        return buff;
}

int query_all_buff(string key)
{
//      int max_qi,max_jing;
        int value;
        
        if( undefinedp(value = query_temp("buff_cache/"+key)) )
        {
                value = query_equipment_buff(key) + query_skillmix_buff(key) +
                        query_yuanshen_buff(key) + query_jingmai_buff(key) + 
                        query_ability_buff(key) + query_talent_buff(key);      
                
                set_temp("buff_cache/"+key, value);
        }
        value += query_temp("buff/"+key) + query_temp("apply/"+key) + query_temp("bonus/"+key);
               
        return value;
}

void reset_buff_cache()
{
        delete_temp("buff_cache");
}

int query_str()
{
        mapping sk;
        int str;
        int ability = 0;
        int lx = 0;

        str = query("str");
        if( !mapp(sk = query_skills()) )
                return str + query_all_buff("str");
        ability = (int)sk["unarmed"];
        if( ability < (int) sk["cuff"] ) ability = sk["cuff"];
        if( ability < (int) sk["finger"] ) ability = sk["finger"];
        if( ability < (int) sk["strike"] ) ability = sk["strike"];
        if( ability < (int) sk["hand"] ) ability = sk["hand"];
        if( ability < (int) sk["claw"] ) ability = sk["claw"];
        lx = (int)sk["longxiang-gong"] / 30;
        if( lx >= 13 ) lx = 15;
        return str + (ability / 10) + lx + query_all_buff("str");
}

int query_int()
{
        mapping sk;
        int str;
        int ability = 0;

        str = query("int");
        if( !mapp(sk = query_skills()) )
                return str + query_all_buff("int");
        ability = (int)sk["literate"];
        return str + (ability / 10) + query_all_buff("int");
}

int query_con()
{
        mapping sk;
        int str;
        int ability = 0;

        str = query("con");
        if( !mapp(sk = query_skills()) )
                return str + query_all_buff("con");
        ability = (int)sk["force"];
        return str + (ability / 10) + query_all_buff("con");
}

int query_dex()
{
        mapping sk;
        int str/*, scale*/;
        int ability = 0;

        //scale = (this_object()->query_encumbrance()*100)/this_object()->query_max_encumbrance();
        str = query("dex");
        if( !mapp(sk = query_skills()) )
                return str + query_all_buff("dex");
        ability = (int)sk["dodge"];
        return str + (ability / 10) + query_all_buff("dex");
}

int query_kar()
{
        return (int)query("kar") + query_all_buff("kar");
}

int query_per()
{
        int per;
        int age;
        int ac;

        per = (int)query("per") + query_all_buff("per");
        if (query("special_skill/youth"))
                return per;

        age = query("age");

        ac = query_skill("art-cognize", 1);
        if (ac < 100)
        {
                if (age > 70) per -= 6; else
                if (age > 60) per -= 5; else
                if (age > 50) per -= 4; else
                if (age > 40) per -= 3; else
                if (age > 30) per -= 2;
        }

        per += ac / 20;
        return per;
}