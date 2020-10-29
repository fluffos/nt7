// drop.c

#include <weapon.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old;
        object weapon;
        string str;

        if (! arg)
                return notify_fail("你要拿出什么东西？\n");

        if (arg == "none" || arg == "nothing")
        {
                if( !objectp(ob=query_temp("handing", me)) )
                        return notify_fail("你本来就什么都没有拿啊？\n");

                if( !stringp(str=query("unhand_msg", ob)) )
                        str = "$N把$n收回包囊。\n";
                message_vision(str, me, ob);
                delete_temp("handing", me);
                return 1;
        }

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上没有这样东西。\n");
                
        if( ob->is_pet() || ob->is_warcraft() || query("ridable", ob) )
                return notify_fail("宠物或者坐骑不可以拿在手上。\n");
                
        if( objectp(old=query_temp("handing", me)) )
        {
                if (old == ob)
                        return notify_fail("你不是正拿着它吗？\n");

                if( !stringp(str=query("unhand_msg", old)) )
                        str = "$N收回手中的$n。\n";
                message_vision(str, me, old);
                delete_temp("handing", me);
        }

        if( (ob->query_amount()?query("base_weight", ob):ob->query_weight())>20000 )
                return notify_fail(ob->name() + "太重了，你单手拿不住。\n");

/*
        weapon=query_temp("weapon", me);
        if (weapon &&
            ((query("flag", weapon))&TWO_HANDED || 
             query_temp("secondary_weapon", me) || 
             query_temp("armor/hands", me) || 
             query_temp("armor/finger", me)) )
        {
                // none of two hand is free
                return notify_fail("你双手都拿着武器，没有办法"
                                   "再拿着" + ob->name() + "了。\n");
        }

        if( query_temp("armor/hands", me) && 
            query_temp("armor/finger", me) )
        {
                // none of two hand is free
                return notify_fail("你双手都戴着武器，没有办法"
                                   "再拿着" + ob->name() + "了。\n");
        }
*/
        if( query("equipped", ob) )
                return notify_fail("你正装备着它呢！\n");

        set_temp("handing", ob, me);
        if( !stringp(str=query("hand_msg", ob)) )
                str = "$N拿出" + (old && ob->name() == old->name() ? "另外" : "") +
                      // "一" + (ob->query_amount() ? ob->query("base_unit")
                      "一"+(ob->query_amount()?query("unit", ob )
                                                 :query("unit", ob))+
                      "$n，握在手中。\n";
        message_vision(str, me, ob); 
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : hand <物品名称> | nothing
 
这个指令可以让你拿出一样你所携带的物品，随时准备使用。
 
HELP );
    return 1;
}
 
