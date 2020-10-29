// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me,string arg)
{
        int amount;
        object target;
        string who, tar_name;

        if( me->is_busy() ) {
                write(BUSY_MESSAGE);
                return 1;
        }

        if( !arg ) {
                write(HIG "目前泥潭基金数量为： " HIY + MONEY_D->money_str(DB_D->query_data("fund/balance")) + "。\n" NOR);
                return 1;
        }

        if( sscanf(arg, "juan %d", amount) == 1 ) {
                if( amount <= 0 ) {
                        write("数量必须为正。\n");
                        return 1;
                }

                if( query("balance", me) < amount ) {
                        write("你银行的存款没有这么多。\n");
                        return 1;
                }
                addn("balance", -amount, me);
                addn("weiwang", amount/10000, me);
                DB_D->add_data("fund/balance", amount);
                if( amount >= 100000000 )
                CHANNEL_D->channel_broadcast("chat", HIW + me->name(1) + "(" +
                              me->query_id() + ")" HIC" 为泥潭基金捐助 "  + HIY + MONEY_D->money_str(amount) + HIC "。\n" NOR);
                write("非常感谢你为泥潭所做的贡献！\n");

                me->start_busy(1);
                return 1;
        } else
        if( sscanf(arg, "fenpei %s %d", who, amount) == 2 ) {
                if( !wizardp(me) && query("viremploy/job", me) != "新手导师" )
                        return 1;

                if( who == me->query_id(1) ) {
                        write("不能给自己分配基金。\n");
                        return 1;
                }

                if( amount <= 0 ) {
                        write("数量必须为正。\n");
                        return 1;
                }

                if( amount > 1000000000 ) {
                        amount = 1000000000;
                        write("最多分配十万两黄金。\n");
                }

                if( DB_D->query_data("fund/balance") < amount ) {
                        write("泥潭基金不足。\n");
                        return 1;
                }

                target = UPDATE_D->global_find_player(who);

                if( !objectp(target) ) {
                        write("无此玩家。\n");
                        UPDATE_D->global_destruct_player(target, 1);
                        return 1;
                }

                tar_name = target->name(1);
                addn("balance", amount, target);
                DB_D->add_data("fund/balance", -amount);

                target->save();

                UPDATE_D->global_destruct_player(target, 1);

                // 记录
                log_file("fund", me->query_id(1) + " 于 " + ctime(time()) + " 从泥潭基金分配 " +
                          amount + " 给 " + who + "。\n");

                // 发布
                CHANNEL_D->channel_broadcast("chat", HIW + me->name(1) + "(" +
                              me->query_id(1) + ")" HIC "从泥潭基金中分配 "  + HIY +
                              MONEY_D->money_str(amount) + HIC " 给 " + tar_name + " 。\n" NOR);

                return 1;
        }

        return notify_fail("格式错误。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : fund <参数>
fund                              显示泥潭基金数量
fund juan <数量>                  捐助泥潭基金
fund fenpei <玩家ID> <数量>       分配泥潭基金给某位玩家
HELP );
        return 1;
}
