#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string target;
        int    money;
        int flower;
        object ob;
        
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg, "%s %d", target, money) != 2)
                return notify_fail("指令格式：recharge <id> <amount>。\n");
        
        if (! objectp(ob = UPDATE_D->global_find_player(target)))
                return notify_fail("没有这个人！\n");
                
        flower = money;
        addn("flowers/amount", flower, ob);
        if( ob ) tell_object(ob, HIC "你获得了 " + flower + " 张新手导师评价票。\n" NOR);

        
        UPDATE_D->global_destruct_player(ob, 1);
        write("ok.\n");
        return 1;
}
