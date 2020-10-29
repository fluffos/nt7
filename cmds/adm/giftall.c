// giveall.c

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object ob;
        int count;
        string target, gift_file, str;
        object pob;
        mapping ips;
        string ip, *ks;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
                return notify_fail("giftall 派礼物给在线玩家，命令格式： giftall </路径/../目标文件名> <数量>\n\n");

        if (sscanf(arg, "%s %d", target, count) != 2)
                target = arg;

        if (target != "nt" && sscanf(target, "%*s.c") != 1)
                target += ".c";
        gift_file = target;

        if (target != "nt" && file_size(gift_file) == -1)
                return notify_fail("路径不正确，无法找到物品。\n");

        seteuid(getuid());

        ips = ([ ]);
        foreach (pob in all_interactive())
        {
                if( wizardp(pob) || !query("born", pob) || 
                    ! living(pob) || ! environment(pob) ||
                    pob->is_ghost())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (sizeof(ips) >= 1)
        {
                ks = keys(ips);
                foreach(ip in ks)
                {
                        pob = ips[ip][random(sizeof(ips[ip]))];
                        if( target == "nt" ) {
                                if( MEMBER_D->is_member(pob) ) 
                                        MEMBER_D->db_pay_member(pob, count); 
                                else
                                        MEMBER_D->db_create_member(pob, count); 
                        }
                        else {
                        ob = new(target);

                        if( count>1 && query("base_unit", ob) )
                                ob->set_amount(count);

                        ob->move(pob);

                        tell_object(pob, HIW "\n\n忽然从极高极远的天空中极速降下一只浑身烈焰的"HIR"火凤"HIW"，周身闪耀七彩光芒。\n" NOR);
                        tell_object(pob, HIC "它爪下似乎抓着什么东西，突然"HIC"火凤"HIW"松开脚爪，有个东西直向你掉落下来。\n" NOR);
                        tell_object(pob, HIG "你猛一提气纵身一跃丈高将此物抓在手中，又潇洒的飘落地面。\n\n" NOR);
                        }

                }
                if( target == "nt" )
                str=sprintf("共有%d位玩家得到了nt。\n\n",sizeof(ks));
                else
                str=sprintf("共有%d位玩家得到了%s。\n\n",sizeof(ks),query("name", get_object(target)));
                me->start_more(str);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式：giftall 物品路径

给在线的每一个IP的玩家一件物品。
HELP
        );
        return 1;
}
