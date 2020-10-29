#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goodsd"
#endif

int paying;
int help(object me);

int main(object me, string arg)
{
        string str1, str2;
        string info;
        object tar;
        string me_id, tar_id;
        int amount;

        if( time()-query_temp("last_member", me)<3 && 
            arg != "?" && ! wizardp(me))
                return notify_fail("系统忙，请稍后再试！\n");

        if (arg != "?" && ! wizardp(me))
                set_temp("last_member", time(), me);

        // 仅允许非会员使用member ?, member ??, member stats, member show goods指令
        if( !MEMBER_D->is_member(query("id", me)) )
        {
                if (! arg)return help(me);
                if (arg == "?")return help(me);
                if (arg == "??")return help(me);
                if (arg == "stats")
                        return MEMBER_D->show_all_members(0);

                if (sscanf(arg, "%s %s", str1, str2) != 2)
                        return 0;

                if (str1 != "look" && (str1 != "show" || str2 != "goods"))
                        return 0;
        }

        if (! arg)
        {
                MEMBER_D->show_member_info(me, "info");
                return 1;
        }

        if (arg == "?") return help(me);
        if (arg == "??") return help(me);
        if (arg == "stats")
        {
                return MEMBER_D->show_all_members(0);
        }

        if (sscanf(arg, "%s %s", str1, str2) != 2)
                return help(me);

        switch(str1)
        {
        case "show":
                if (str2 == "info")
                {
                        MEMBER_D->show_member_info(me, "info");
                        return 1;
                }
                else if (str2 == "payinfo")
                {
                        MEMBER_D->show_member_info(me, "payinfo");
                        return 1;
                }
                else if (str2 == "buyinfo")
                {
                        MEMBER_D->show_member_info(me, "buyinfo");
                        return 1;
                }
                else if (str2 == "goods" || str2 == "all")
                {
                        MEMBER_D->show_member_info(me, "goods");
                        return 1;
                }
                else if (str2 == "zhuaninfo")
                {
                        MEMBER_D->show_member_info(me, "transferinfo");
                        return 1;
                }
                else return help(me);

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if (! GOODS_D->buy_goods(me, str2))
                {
                        write("购买失败！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "zhuan":
                if (sscanf(str2, "%d to %s", amount, tar_id) != 2)
                        return help(me);

                me_id=query("id", me);

                if (me_id == tar_id)
                        return notify_fail("你白痴啊，给自己转帐！\n");

                if (amount < 1 || amount > 100000)
                        return notify_fail("每次转帐的单位必须在 1 至 100000 之间！\n");

                if (! MEMBER_D->db_transfer_member(me_id, tar_id, amount))
                {
                        write("转帐失败！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "check":
                if (wiz_level(me) < 4)
                        return help(me);

                if (sscanf(str2, "%s %s", tar_id, info) != 2)
                        tar_id = str2;

                // 检查对方是否为会员
                if (! MEMBER_D->is_member(tar_id))
                        return notify_fail("目标为非会员，无法查询！\n");

                tar = UPDATE_D->global_find_player(tar_id);
                if (! objectp(tar))
                        return notify_fail("没有这个玩家！\n");

                if( !info ) info = "info";
                MEMBER_D->show_member_info(tar, info);

                UPDATE_D->global_destruct_player(tar, 1);

                return 1;

        case "remove":
                if (wiz_level(me) < 5)
                        return help(me);

                if (! MEMBER_D->db_remove_member(str2))
                {
                        write("删除会员失败！\n");
                        return 1;
                }
                write("OK.\n");
                return 1;

        default:
                return help(me);
        }

        return 1;
}

int help (object me)
{
        write(WHT "——————————————————————————————————

" HIM "输入指令： member show info                     显示会员系统面板界面
输入指令： member show payinfo                  显示历史充值交费信息
输入指令： member show buyinfo                  显示历史购买物品信息
输入指令： member show zhuaninfo                显示历史转帐记录信息
输入指令： member show goods                    显示王者商店出售物品
输入指令： member check <id>                    巫师指令检查会员信息
输入指令： member stats                         列出所有会员名单信息
输入指令： member zhuan <amount> to <id>        转帐王者币给其他的ID

" WHT "——————————————————————————————————
" HIC "淘宝冲值链接地址:
" HIR "http://shop61698067.taobao.com\n
" HIG "相关参考文件：help ntstore, help member\n" NOR);

        return 1;
}
