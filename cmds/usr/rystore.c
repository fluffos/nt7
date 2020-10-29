
#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goods_honord"
#endif

int help(object me);
int main(object me, string arg)
{
        string str1, str2;
        object tar;
        string me_id, tar_id;
        int amount;
        
        MYGIFT_D->check_mygift(me, "newbie_mygift/rystore");  

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
                if( !GOODS_D->exchange_goods(me, str2))
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

        money = query("honors", me);

        write(HIY "□ 您目前的荣誉为 " + money + " (NT)
" WHT "——————————————————————————————————

" HIM "输入指令：    rystore show all                  查看所有商城的货物
输入指令：    rystore exchange <代号>           兑换指定代号的商品

" WHT "<代号>  ：    可用物品的 name 或 编号
" WHT "——————————————————————————————————\n" NOR);

        return 1;
}

