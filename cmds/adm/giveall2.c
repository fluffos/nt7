// giveall2.c
// redl 2014

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object ob;
        int count;
        string target, gift_file, str;
        int countplayer = 0;
        string tname;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
                return notify_fail("giftall 派礼物给在线玩家，命令格式： giftall </路径/../目标文件名> <数量>\n\n");

        if (sscanf(arg, "%s %d", target, count) != 2)
                target = arg;

        if (sscanf(target, "%*s.c") != 1)
                target += ".c";
        gift_file = target;

        if (file_size(gift_file) == -1)
                return notify_fail("路径不正确，无法找到物品。\n");

        seteuid(getuid());

        tname = query("name", get_object(target));

        foreach(object player in users())
        {
                if (wiz_level(player) > 1) continue;
                if( !interactive(player) ) continue;  // 断线的包括计划的都排除掉

                tell_object(player, HIW "\n\n忽然从极高极远的天空中极速降下一只浑身烈焰的"HIR"火凤"HIW"，周身闪耀七彩光芒。\n" NOR);

                if (time() - query_temp("logon_time", player) < 5400) {
                        tell_object(player, HIW "它对着你清鸣几声，似乎是在说：很遗憾，你连线短于90分钟。\n"HIR"火凤"HIW"在你头上盘旋几圈，然后径直飞走了。\n\n" NOR);
                        continue;
                }

                if (!query("family/master_id", player) || query("family/master_id", player)=="") {//还未拜师
                        tell_object(player, HIW "它对着你清鸣几声，似乎是在说：很遗憾，你还没有拜师门派。\n"HIR"火凤"HIW"在你头上盘旋几圈，然后径直飞走了。\n\n" NOR);
                        continue;
                }

                ob = new(target);

                if( count>1 && query("base_unit", ob) )
                        ob->set_amount(count);

                ob -> move(player);

                tell_object(player, HIW "它爪下似乎抓着什么东西，突然"HIR"火凤"HIW"松开脚爪，" + NOR + tname + NOR + HIW + "向你掉落下来。\n" NOR);
                tell_object(player, HIG "你猛一提气纵身一跃丈高将此物抓在手中，又潇洒的飘落地面。\n\n" NOR);
                countplayer += 1;
        }
        str=sprintf("共有%d位玩家得到了%s。\n\n",countplayer,tname);
        me->start_more(str);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：giveall 物品路径

给在线的所有玩家一件物品，排除无门派的，和连线时间太短的大米。
HELP
        );
        return 1;
}


