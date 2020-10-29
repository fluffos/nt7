#include <ansi.h>

inherit F_CLEAN_UP;
#include <equip.h>
#include <equipment.h>

int main(object me, string arg)
{
        string *partset;
        string partid;
        string type;
        int status;
        object ob, *obs;
        int equip_from_environment;
        int num;

        if( !arg )
        {
                string msg;
                object *equipments = me->query_equipment_objects();

                if( !sizeof(equipments) )
                        return tell(me, pnoun(2, me)+"目前身上没有任何装备。\n");

                msg = pnoun(2, me)+"目前身上的装备如下：\n";

                foreach(ob in me->query_equipment_objects())
                        //msg += "．"HIW"["NOR+me->query_equipping_part(ob)+HIW"] "+ob->query_idname()+"\n"NOR;
                        msg += "．"HIW"["NOR+me->query_equipping_part(ob)+HIW"] "+ob->query_idname()+"\n"NOR;

                tell(me, msg+"\n");
                return 1;
        }

        //忙碌中不能下指令
        if( me->is_busy() )
        {
                tell(me, BUSY_MESSAGE);
                me->show_prompt();
                return 1;
        }

        if( sscanf(arg, "-s %d", num) == 1 )
        {
                if( num < 1 || num > 5 )
                        return tell(me, "最多只能设定 5 组套装。\n");

                set("equipment_set/"+num, map(me->query_equipment_objects(), (: base_name($1) :)), me);
                me->save();

                tell(me, pnoun(2, me)+"将目前的装备设定为第 "+num+" 号套装。\n");
                return 1;
        }
        else if( sscanf(arg, "-d %d", num) == 1 )
        {
                if( !query("equipment_set/"+num, me) )
                        return notify_fail(pnoun(2, me)+"原本并没有设定第 "+num+" 号套装。\n");

                delete("equipment_set/"+num, me);
                me->save();

                tell(me, pnoun(2, me)+"将第 "+num+" 号套装设定删除。\n");
                return 1;
        }
        else if( sscanf(arg, "-l %d", num) == 1 )
        {
                string msg;
                string *equipment_set = query("equipment_set/"+num, me);

                if( !arrayp(equipment_set) )
                        return notify_fail(pnoun(2, me)+"原本并没有设定第 "+num+" 号套装。\n");

                msg = pnoun(2, me)+"所设定的 "+num+" 号套装如下：\n";

                foreach(string basename in equipment_set)
                {
                        ob = load_object(basename);
                        if( !objectp(ob) ) continue;
                        msg += "．"HIW"["NOR+me->query_equipping_part(ob)+HIW"] "+ob->query_idname()+"\n"NOR;
                }

                tell(me, msg);
                return 1;
        }
        else if( sscanf(arg, "%d", num) == 1 )
        {
                int index;
                string *equipment_set = query("equipment_set/"+num, me);

                if( time() - query_temp("last_equip", me) < 10 )
                        return notify_fail("系统气喘嘘地叹道：请稍后再使用equip换装。\n");

                if( !arrayp(equipment_set) )
                        return notify_fail(pnoun(2, me)+"并没有设定第 "+num+" 号套装。\n");

                obs = all_inventory(me);
                obs = filter_array(obs, (: $1->is_equipment() :));

                /*
                foreach(ob in obs)
                {
                        if( me->is_equipping_object(ob) )
                        {
                                me->unequip(ob, ref status);

                                //      msg("$ME卸除了装备在「"+me->query_equipping_part(ob)+"」部位上的"+ob->query_idname()+"。\n", me, 0, 1);
                        }
                }
                */
                me->unequip_all();
                foreach(ob in obs)
                {
                        //reset_eval_cost();
                        index = member_array(base_name(ob), equipment_set);

                        if( index == -1 ) continue;

                        equipment_set = equipment_set[0..index-1] + equipment_set[index+1..];

                        if( me->equip(ob, ref status) )
                                msg("$ME将"+ob->query_idname()+"装备在「"+me->query_equipping_part(ob)+"」的部位上。\n", me, 0, 1);
                        else
                        {
                                switch(status)
                                {
                                        // 1: 此物件不是装备
                                        // 2: 无法装备在此物件上
                                        // 3: 不知此物件该装备在何处
                                        // 4: 已经有同种类的装备
                                        // 5: 已经装备在其他的部位上

                                        case 1: tell(me, ob->query_idname()+"无法用来装备。\n"); break;
                                        case 2: tell(me, pnoun(2, me)+"似乎没有足够的能力来装备这个物品。\n"); break;
                                        case 3: tell(me, pnoun(2, me)+"不了解"+ob->query_idname()+"该装备在何处。\n"); break;
                                        case 4: tell(me, pnoun(2, me)+"身上该部位上已经装备着其他物品。\n"); break;
                                        case 5: tell(me, ob->query_idname()+"已经装备在其他的部位上了。\n"); break;
                                        default: error("装备物品发生错误。\n"); break;
                                }
                        }
                }
                set_temp("last_equip", time(), me);

                return 1;
        }

        if( arg == "all" )
        {
                foreach(ob in all_inventory(me))
                {
                        if( !ob->is_equipment() ) continue;
                        if( query_temp("no_wear", ob) ) continue;
                        if( me->is_equipping_object(ob) )
                                tell(me, pnoun(2, me)+"已经将"+ob->query_idname()+"装备在「"+me->query_equipping_part(ob)+"」的部位上了。\n");
                        if( me->equip(ob, ref status) )
                                msg("$ME将"+ob->query_idname()+"装备在「"+me->query_equipping_part(ob)+"」的部位上。\n", me, 0, 1);
                }

                return 1;
        }

        if( !objectp(ob = present(arg, me)) )
        {
                if( objectp(ob = present(arg, environment(me))) && !ob->is_living() )
                {
                        equip_from_environment = 1;
                }
                else
                        return notify_fail("这附近并没有 "+arg+" 这个物品。\n");
        }

        if( query_temp("no_wear", ob) )
        {
                return notify_fail("还是试试别的吧！\n");
        }

        if( me->is_equipping_object(ob) )
                return notify_fail(pnoun(2, me)+"已经将"+ob->query_idname()+"装备在「"+me->query_equipping_part(ob)+"」的部位上了。\n");

        if( !me->equip(ob, ref status) )
        {
                switch(status)
                {
                        // 1: 此物件不是装备
                        // 2: 无法装备在此物件上
                        // 3: 不知此物件该装备在何处
                        // 4: 已经有同种类的装备
                        // 5: 已经装备在其他的部位上

                        case 1: return notify_fail(ob->query_idname()+"无法用来装备。\n"); break;
                        case 2: return notify_fail(pnoun(2, me)+"似乎没有足够的能力来装备这个物品。\n"); break;
                        case 3: return notify_fail(pnoun(2, me)+"不了解"+ob->query_idname()+"该装备在何处。\n"); break;
                        case 4: return notify_fail(pnoun(2, me)+"身上该部位已经装备着其他物品。\n"); break;
                        case 5: return notify_fail(ob->query_idname()+"已经装备在其他的部位上了。\n"); break;
                        default: error("装备物品发生错误。\n"); break;
                }
        }
        else
        {
                msg("$ME将"+ob->query_idname()+"装备在「"+me->query_equipping_part(ob)+"」的部位上。\n", me, 0, 1);

                if( equip_from_environment )
                        ob->move(me, 1);
        }
        return 1;
}

int help(object me)
{
        string help = @HELP
    装备物品的指令，无论是武器、防具、装饰品、团体武装都
是利用此指令进行装备动作。

equip '物品'            - 装备某项物品
equip -s 2              - 将目前身上装备之所有物品设定为 2 号套装
equip -d 2              - 删除 2 号套装设定
equip -l 2              - 查询 2 号套装设定
equip 2                 - 将身上装备换装为 2 号套装
HELP;
        write(help);
        return 1;
}
