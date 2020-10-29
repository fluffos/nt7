
// This program is a part of NT MudLIB

#include <equip.h>

nosave mapping equipments = allocate_mapping(0);

//
// 回传所有装备资讯
//
mapping query_equipments()
{
        return equipments;
}

//
// 回传所有装备物件
//
object *query_equipment_objects()
{
        return implode(values(equipments), (: $1+$2 :)) || allocate(0);
}

//
// 解除某个物件装备
//
// 1: 并无装备此物件
// 2: 无法解除此项装备
//
int unequip(object ob, int ref status)
{
        foreach(string partid, object *eqs in equipments)
        {
                if( member_array(ob, eqs) != -1 )
                {
                        // 无法解除此项装备
                        if( !ob->valid_unequip(this_object()) )
                        {
                                status = 2;
                                return 0;
                        }
                        
                        ob->delete_equipping(this_object());
                        
                        equipments[partid] -= ({ ob });
                        if( !sizeof(equipments[partid]) )
                                map_delete(equipments, partid);
                        
                        if( query("mod_level", ob) )
                                MODULE_D->unequip_module(ob, this_object());

                        this_object()->reset_buff_cache();
                        return 1;
                }
        }

        // 并无装备此物件
        status = 1;
        return 0;
}

//
// 1: 此物件不是装备
// 2: 无法装备在此物件上
// 3: 不知此物件该装备在何处
// 5: 已经装备在其他的部位上
//
int equip(object ob, int ref status)
{
        string *partset;
        int partamount;
        string partid;
        string type;
        

        // 此物件不是装备
        if( !ob->is_equipment() )
        {
                status = 1;
                return 0;       
        }

        // 无法装备在此物件上
        if( !ob->valid_equip(this_object()) )
        {
                status = 2;
                return 0;
        }

        // 不知此物件该装备在何处
        type = query("armor_type", ob);
        if( !type ) 
        {
                if( query("flag", ob) == 1 )
                        type = "twohand";       // 双手
                else    type = "hand";          // 单手
        }
       
        if( !undefinedp(part_set[type]) )
        {
                partset = part_set[type];
        }
        else 
        {
                status = 3;
                return 0;
        }

        if( !arrayp(partset) )
        {
                status = 3;
                return 0;
        }
        
        partid = partset[PART_ID];
        partamount = to_int(partset[PART_AMOUNT]);
        
        // 已经无法再装备更多同种类的装备
        if( !undefinedp(equipments[partid]) && sizeof(equipments[partid]) >= partamount )
        {
                status = 4;
                return 0;
        }

        foreach(string p, object *eqs in equipments)
        {
                // 装备部位存在冲突
                if( member_array(p, partset[PART_CONFLICT]) != -1 )
                {
                        status = 4;
                        return 0;
                }

                if( member_array(ob, eqs) != -1 )   // 已经装备上该装备
                {
                        status = 5;
                        return 0;
                }
        }
        
        if( undefinedp(equipments[partid]) )
                equipments[partid] = allocate(0);
        
        equipments[partid] |= ({ ob });

        ob->set_equipping(this_object());

        if( query("mod_level", ob) )
                MODULE_D->equip_module(ob, this_object());

        this_object()->reset_buff_cache();

        return 1;
}



//
// 解除所有装备
//
object *unequip_all()
{
        object ob;
        object *all_equipments = allocate(0);
        
        foreach(string partid, object *eqs in equipments)
        {
                foreach(ob in eqs)
                {
                        ob->delete_equipping(this_object());

                        delete_temp("mod_equip", ob);   // 取消套装装备标记
                        delete_temp("mod_active", ob);  // 取消套装激活标记
                }
                
                all_equipments += eqs;
        }
        
        equipments = allocate_mapping(0);
        
        delete_temp("fullsuit", this_object());  // 删除套装资料 
        delete_temp("module", this_object());  // 删除套装资料 
        this_object()->reset_buff_cache();

        return all_equipments;
}



//
// 解除某个部位的所有装备
//
// 1: 此部位并无任何装备
// 2: 无法解除此项装备
//
object *unequip_part(string partid)
{
        object *unequipped_equipments = allocate(0);

        if( undefinedp(equipments[partid]) )
                return 0;
        
        foreach( object ob in equipments[partid] )
        {
                // 无法解除这项装备
                if( !ob->valid_unequip(this_object()) )
                        continue;
        
                ob->delete_equipping(this_object());
                
                if( query("mod_level", ob) )
                        MODULE_D->unequip_module(ob, this_object());

                unequipped_equipments |= ({ ob });
        }
        
        map_delete(equipments, partid);
        this_object()->reset_buff_cache();
        return unequipped_equipments;
}



//
// 检查此物件是否正在装备
//
int is_equipping_object(object ob)
{
        foreach(string part, object *eqs in equipments)
                if( member_array(ob, eqs) != -1 )
                        return 1;
        
        return 0;
}


//
// 检查某部位是否有装备
//
int is_equipping_part(string part)
{
        if( !undefinedp(equipments[part]) )
                return 1;

        return 0;
}



//
// 回传某部位的装备物件
//
object *query_equipping_object(string partid)
{
        if( !undefinedp(equipments[partid]) )
                return equipments[partid];

        return 0;
}


//
// 回传某部位的装备物件的第n个物件
//
varargs object query_equipped_object(string partid, int n)
{
        object ob, *obs;
        
        if( undefinedp(equipments[partid]) )
                return 0;

        obs = equipments[partid];
        if( !n ) n = 1;
        if( sizeof(obs) < n )
                return 0;

        ob = obs[n-1];

        return ob;
}

//
// 回传某装备的部位
//
string query_equipping_part(object ob)
{
        foreach(string part, object *eqs in equipments)
                if( member_array(ob, eqs) != -1 )
                        return part;
        return 0;
}


