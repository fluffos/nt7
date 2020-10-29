// wear.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i, count;

        if (! arg) return notify_fail("你要穿戴什么？\n");

        if( me->is_busy() ) return notify_fail(BUSY_MESSAGE);
        if (arg == "all")
        {
                inv = all_inventory(me);
                for(count = 0, i = 0; i < sizeof(inv); i++)
                {
                        if( query("equipped", inv[i]))continue;
                        if (do_wear(me, inv[i])) count++;
                }
                if (! count)
                        write("你什么都没有穿上。\n");
                else
                        write("你穿好了。\n");
                return 1;
        }

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上没有这样东西。\n");

        if( query("equipped", ob) )
        {
                inv = all_inventory(me) - ({ ob });
                for(count = 0, i = 0; i < sizeof(inv); i++)
                {
                        if (! inv[i]->id(arg)) continue;
                        if( query("equipped", inv[i]))continue;
                        if (do_wear(me, inv[i]))
                        {
                                count++;
                                break;
                        }
                }
                if (! count)
                        return notify_fail("你已经装备著了。\n");

                return 1;
        }

        return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
        string str;
        mapping p;
        mixed notice;

        if( notice=query_temp("no_wear", ob) )
        {
                if (stringp(notice)) write(notice);
                return notify_fail("还是试试别的吧！\n");
        }

        if( query("female_only", ob) && 
            query("gender", me) == "男性" )
                return notify_fail("这是女人的衣衫，你一个大男人也想穿，羞也不羞？\n");

        switch (ob->wear())
        {
        case 0:
                return 0;

        case -1:
                return 1;

        default:
                if( !stringp(str=query("wear_msg", ob)) )
                        switch(query("armor_type", ob) )
                        {
                                case "cloth":
                                case "armor":
                                case "boots":
                                        str=YEL"$N穿上一"+query("unit", ob)+"$n"YEL"。\n"NOR;
                                        break;
                                case "head":
                                case "neck":
                                case "wrists":
                                case "hands":
                                        str=YEL"$N戴上一"+query("unit", ob)+"$n"YEL"。\n"NOR;
                                        break;
                                case "waist":
                                        str=YEL"$N将一"+query("unit", ob)+"$n"YEL"绑在腰间。\n"NOR;
                                        break;
                                default:
                                        str = YEL "$N装备$n" YEL "。\n" NOR;
                        }
                if( query_temp("daub", ob) && 
                    query("armor_type", ob) != "hands" )
                        DAUB_CMD->check_poison(me, ob);

                message_vision(str, me, ob);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式：wear <装备名称>
 
这个指令让你装备某件防具。
 
HELP );
        return 1;
}
