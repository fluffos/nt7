// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;  

#include <equipment.h>

int main(object me, string arg)  
{
        int status;
        object ob;
        string part;

        if( !arg )
        {
                string msg;
                object *equipments = me->query_equipment_objects();
                
                if( !sizeof(equipments) )
                        return notify_fail(pnoun(2, me)+"目前身上没有任何装备。\n");

                msg = pnoun(2, me)+"目前身上的装备如下：\n";
                
                foreach(ob in me->query_equipment_objects())
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

        if( arg == "all" )
        {
                foreach(ob in all_inventory(me))
                {
                        part = me->query_equipping_part(ob);
                        if( me->unequip(ob, ref status) )
                                msg("$ME卸除了装备在「"+part+"」部位上的"+ob->query_idname()+"。\n", me, 0, 1);
                }
                                
                return 1;
        }

        if( !objectp(ob = present(arg, me)) )
                return notify_fail(pnoun(2, me)+"的身上并没有 "+arg+" 这个物品。\n");

        part = me->query_equipping_part(ob);
        if( !me->unequip(ob, ref status) )
        {
                switch(status)
                {
                        // 1: 并无装备此物件
                        // 2: 无法解除此项装备
                        
                        // should not happen
                        case 1: return notify_fail(pnoun(2, me)+"并未装备"+ob->query_idname()+"。\n"); break;
                        case 2: return notify_fail(pnoun(2, me)+"无法卸除这项装备。\n"); break;
                }
        }
        else
                msg("$ME卸除了装备在「"+part+"」部位上的"+ob->query_idname()+"。\n", me, ob, 1);
        return 1;
}

int help(object me)
{
        string help = @HELP
    卸除装备物品的指令，无论是武器、衣物、座骑、装饰品、团体武装都
是利用此指令进行卸除装备的动作。

unequip '物品'           卸除装备某项物品
unequip all              卸除装备所有物品

HELP;
        write(help);
        return 1;
}
