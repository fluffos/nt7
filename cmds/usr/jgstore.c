#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goods_jungongd"
#endif

int help(object me);
int main(object me, string arg)
{
        string str1, str2;
        object tar;
        string me_id, tar_id;
        int amount;
        
        MYGIFT_D->check_mygift(me, "newbie_mygift/jgstore");  

        if( !arg || arg == "") return help(me);
        if( time()-query_temp("last_member", me)<3 )
                return notify_fail("系统忙，请稍后再试！\n");

        if( !wizardp(me) )
                set_temp("last_member", time(), me);

        if( sscanf(arg, "%s %s", str1, str2) != 2 )
                return help(me);

        switch(str1)
        {
        case "show":
                return GOODS_D->show_goods(me, str2);

        case "exchange":
                // 防止注册id刷物品
                /*
                if( query("combat_exp", me) < 1000000 && !MEMBER_D->is_valid_member(me) )
                        return notify_fail("你暂时还没有资格将军功兑换为物品！\n");
                */ 
                if( sscanf(str2, "%s %d", str2, amount) != 2 )
                        amount = 1;
                
                if( amount > 100 ) amount = 100;
                if( amount < 1 ) amount = 1;        
                if( !GOODS_D->exchange_goods(me, str2, amount))
                {
                        write("兑换失败！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        default:
                return help(me);
        }

        return 1;
}

int help (object me)
{
        int money;

        money = query("jungong", me);

        write(HIY "□ 您目前的军功为 " + money + " (NT)
" WHT "——————————————————————————————————

" HIM "输入指令：    jgstore show all                  查看所有商城的货物
输入指令：    jgstore exchange <代号> <数量>    兑换指定代号的商品

" WHT "<代号>  ：    可用物品的 name 或 编号
" WHT "——————————————————————————————————\n" NOR);

        return 1;
}

