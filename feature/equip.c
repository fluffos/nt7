// This program is a part of NITAN MudLIB
// equip.c

#include <ansi.h>
#include <dbase.h>
#include <weapon.h>

//nosave object* equipping = allocate(0);
nosave object equipping = 0;

int is_equipment()
{
	return 1;
}

object query_equipping()
{
	return equipping;	
}

int is_equipping()
{
	return query("equipped");
}

int query_equipping_buff(string key)
{
        mapping data, props;
        string *apply;
        int i, fullsuit;
        int buff = 0;
        
        if( !equipping ) return 0;
        
        // 套装系统加成
        if( data = query_temp("fullsuit", equipping) )
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
        foreach(object ob in equipping->query_equipment_objects())
        {
                if( !objectp(ob) ) continue;
                buff += query("armor_prop/" + key, ob) + query("weapon_prop/" + key, ob) + 
                        query("enchase/apply_prop/" + key, ob) + query("qianghua/apply_prop/" + key, ob) + 
                        query("qiling/apply_prop/" + key, ob);
                
                if( fullsuit )
                        buff += query("enchase/mod_prop/" + key, ob);
        }
        
        return buff;
}

void resetup_char(object ob)
{
        mapping applied_prop;
        string *apply;
        int max_qi, max_jing;
        int i, flag = 0;
        string *app_props = ({
                "int", "str", "con", "add_skill", "max_qi", "max_jing",
        });

        if( !playerp(ob) && !ob->is_baby() ) return;
        // 战场上无效
        if( query_temp("warquest", ob) ) return;
        
        if( !undefinedp(query("armor_prop")) ) {
                applied_prop = query("armor_prop");
                apply = keys(applied_prop);
                for( i=0; i<sizeof(apply); i++ )
                {
                        if( member_array(apply[i], app_props) != -1 )
                        {
                                flag = 1; 
                                break;
                        }
                }
        }
        
        if( !flag && !undefinedp(query("weapon_prop")) ) {
                applied_prop = query("weapon_prop");
                apply = keys(applied_prop);
                for( i=0; i<sizeof(apply); i++ )
                {
                        if( member_array(apply[i], app_props) != -1 )
                        {
                                flag = 1; 
                                break;
                        }
                }
        }
        
        if( !flag && !undefinedp(query("enchase/apply_prop")) ) {
                applied_prop = query("enchase/apply_prop");
                apply = keys(applied_prop);
                for( i=0; i<sizeof(apply); i++ )
                {
                        if( member_array(apply[i], app_props) != -1 )
                        {
                                flag = 1; 
                                break;
                        }
                }
        }

        if( !flag && !undefinedp(query("qianghua/apply_prop")) ) {
                applied_prop = query("qianghua/apply_prop");
                apply = keys(applied_prop);
                for( i=0; i<sizeof(apply); i++ )
                {
                        if( member_array(apply[i], app_props) != -1 )
                        {
                                flag = 1; 
                                break;
                        }
                }
        }
        
        if( !flag && !undefinedp(query("qiling/apply_prop")) ) {
                applied_prop = query("qiling/apply_prop");
                apply = keys(applied_prop);
                for( i=0; i<sizeof(apply); i++ )
                {
                        if( member_array(apply[i], app_props) != -1 )
                        {
                                flag = 1; 
                                break;
                        }
                }
        }
               
        if( flag )
        {
                ob->reset_buff_cache(); 
                max_qi = query("max_qi", ob);
                max_jing = query("max_jing", ob);
                CHAR_D->setup_char(ob);
                if( query("eff_qi", ob) >= max_qi )
                        max_qi = query("max_qi", ob) - max_qi;
                else
                        max_qi = 0;
                if( query("eff_jing", ob) >= max_jing )
                        max_jing = query("max_jing", ob) - max_jing;
                else
                        max_jing = 0;
                addn("eff_qi", max_qi, ob);
                addn("eff_jing", max_jing, ob);
        }
}
        
void set_equipping(object ob)
{
        equipping = ob;
        
        if( query("armor_type") )
                set("equipped", "worn");
        else
                set("equipped", "wielded");
        
        if( query("armor_type") )
                set_temp("armor/"+query("armor_type"), this_object(), ob);

        else if( query("skill_type") )
        {
                if( !query_temp("weapon", ob) ) 
                        set_temp("weapon", this_object(), ob);
                else
                        set_temp("secondary_weapon", this_object(), ob);

                if( query("flag") & TWO_HANDED )
                        set_temp("secondary_weapon", this_object(), ob);

                ob->reset_action();
        }

        resetup_char(ob);
}

void delete_equipping(object ob)
{
        int status;
        object weapon;

        equipping = 0;
        delete("equipped");

        if( query("armor_type") )
                delete_temp("armor/"+query("armor_type"), ob);

        else if( query("skill_type") )
        {
                if( query_temp("weapon", ob) == this_object() ) 
                {
                        delete_temp("weapon", ob);
                        if ( query_temp("secondary_weapon", ob) == this_object() )
                                delete_temp("secondary_weapon", ob);

                        if( objectp(weapon = query_temp("secondary_weapon", ob)) )
                        {
                                ob->unequip(weapon, ref status);
                                ob->equip(weapon, ref status);
                        }
                }
                else if ( query_temp("secondary_weapon", ob) == this_object() )
                {
                        delete_temp("secondary_weapon", ob);
                }
                ob->reset_action();
        }

        resetup_char(ob);
}

int valid_equip(object user)
{
        mapping require;
        mixed no_wield;
        
        if( query("no_identify") )
                return notify_fail(this_object()->name() + "需要鉴定后才可以使用。\n");
        
        if( query("consistence") < 1 )
                return notify_fail(this_object()->name() + "现在损坏太严重了，不能继续装备了。\n");
        
        if( no_wield = query("no_wield") ) {
                // can not wield
                if( stringp(no_wield) )
                        return notify_fail(no_wield);
                else
                        return notify_fail("这样东西无法装备。");
        }

        if( query("ultimate/121") )
                //if( this_object()->item_owner() != query("id", user) )
                if( this_object()->item_owner() != "lonely" )
                        return notify_fail("太古神器只能本人装备。");
              
        return 1;
}

int valid_unequip(object user)
{
	return 1;
}

int wear()
{
        object owner, weapon;
        string type;
        int status;

        if( !objectp(this_object()) ) return 0;
        // Only character object can wear armors.
        owner = environment();
        if( !owner || !owner->is_character() ) return 0;

        // If already worn, just recognize it.
        if( query("equipped") ) return 1;

        // If handing it now, stop handing
        if( query_temp("handing", owner) == this_object() )
                delete_temp("handing", owner);

        // Check if we have "armor_prop" defined.
        if( !mapp(query("armor_prop")) ||
            !stringp(type = query("armor_type")) )
                return notify_fail("你只能穿戴可当作护具的东西。\n");
        
        /*
        if( (type == "hands" || type == "finger") )
        {
                if( owner->query_equipping_object("hand") > 1 )
                        return notify_fail("你必须空出一只手来才能装备"+this_object()->name()+"。\n");

                if( weapon = owner->query_equipped_object("hand") ) {
                        if( query("flag", weapon)&TWO_HANDED )
                                return notify_fail("你必须空出一只手来才能装备"+this_object()->name()+"。\n");
                }
        
                if( query("flag") & TWO_HANDED ) {
                        if( sizeof(owner->query_equipping_object("hand")) > 0 )
                                return notify_fail("你必须空出一只手来才能装备"+this_object()->name()+"。\n");
                }
        }
        */
        
        if( !owner->equip(this_object(), ref status) )
                return notify_fail("无法装备该物品。\n");
  
        if( query("bindable") && query("bindable") == 1 &&
            !query("bind_owner") && userp(owner) ) {
                set("bind_owner",query("id", owner));
                set("set_data", 1);
                tell_object(owner, HIM "你内心深处隐隐约约的感应到" + this_object()->name() +
                                   HIM "与你融为一体。\n" NOR);
        }

        return 1;
}

int wield()
{
        object owner, weapon, old_weapon;
        int flag;
        int status;

        if( !objectp(this_object()) ) return 0;
        // Only character object can wear armors.
        owner = environment();
        if( !owner || !owner->is_character() ) return 0;

        // If already wielded, just recognize it.
        if( query("equipped") ) return 1;

        if( query("skill_type") == "throwing" )
                return notify_fail("暗器只能拿在手里，无需装备。\n");

        // If handing it now, stop handing
        if( query_temp("handing", owner) == this_object() )
                delete_temp("handing", owner);

        // Check if we have "weapon_prop" defined.
        if( !mapp(query("weapon_prop")) ||
            !stringp(query("skill_type")) )
                return notify_fail("你只能装备可当作武器的东西。\n");

        /*
        flag = query("flag"); // 双手武器标志 1:必须双手才能装备,2:可以不同手装备

        if( sizeof(owner->query_equipping_object("hand")) > 1 )
                return notify_fail("你必须空出一只手来才能装备"+this_object()->name()+"。\n");
        
        if( weapon = owner->query_equipped_object("hand", 1) ) {
                if( query("flag", weapon)&TWO_HANDED )
                        return notify_fail("你必须空出一只手来才能装备"+this_object()->name()+"。\n");
        }
 
        if( flag & TWO_HANDED ) {
                if( sizeof(owner->query_equipping_object("hand")) > 0 )
                        return notify_fail("你必须空出一只手来才能装备"+this_object()->name()+"。\n");
        } 
        */
        
        if( !owner->equip(this_object(), ref status) )
                return notify_fail("无法装备该物品。\n");
                       
        // bindable == 1 装备绑定
        if( query("bindable") && query("bindable") == 1 &&
            !query("bind_owner") && userp(owner) ) {
                set("bind_owner",query("id", owner));
                set("set_data", 1);
                tell_object(owner, HIM "你内心深处隐隐约约的感应到" + this_object()->name() +
                                   HIM "与你融为一体。\n" NOR);
        }

        return 1;
}

int unequip()
{
        object owner, weapon;
        string equipped;
        int status;

        if( !environment() ) return 0;

        owner = environment();
        if( !owner || !owner->is_character() )
                return 0;

        if( !stringp(equipped = query("equipped")) )
                return notify_fail("你目前并没有装备这样东西。\n");

        if( !owner->unequip(this_object(), ref status) )
                return notify_fail("无法解除该物品。\n");

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed foo;

        foo = this_object()->weapon_hit_ob(me, victim, damage_bonus);
        
        ITEM_D->enchase_attack(this_object(), me, victim, damage_bonus);
        ITEM_D->reduce_consistence(this_object(), me, victim, damage_bonus);

        if (! mapp(query_temp("daub")))
                return foo;

        COMBAT_D->hit_with_poison(me, victim, this_object());
        return foo;
}

// other one hit me as an armor
mixed valid_damage(object me, object victim, int damage_bonus)
{
        ITEM_D->enchase_attack(this_object(), me, victim, damage_bonus);
        ITEM_D->reduce_consistence(this_object(), me, victim, damage_bonus);

        if( !mapp(query_temp("daub")) )
                return;

        if( query_temp("weapon", me) || query_temp("remote_attack", me) ||
            query("not_living", me)){
                // the attacker has weapon, or remote attack, or not living,
                // he won't be poisoned by my cloth or armor
                return;
        }

        COMBAT_D->hit_poison(me, victim, this_object());
        return;
}
