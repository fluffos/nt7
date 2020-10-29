#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goodsd"
#endif

int help(object me);
int main(object me, string arg)
{
        string str1, str2;
        object tar;
        string me_id, tar_id;
        int amount;
        mapping buy_list;
        string *str_buy_list;
        int i;
        
        MYGIFT_D->check_mygift(me, "newbie_mygift/ntstore");  

        if( !arg || arg == "") return help(me);
        if( time()-query_temp("last_member", me)<3 )
                return notify_fail("系统忙，请稍后再试！\n");

        if( !wizardp(me) )
                set_temp("last_member", time(), me);
        
        if( arg == "buylist" && wizardp(me) )
        {
                buy_list = DB_D->query_data("ntstore/buylist");
                
                str_buy_list = DB_D->sort_mapping(buy_list, 0);

                write(HIG " --== 商城销售统计简表（统计时间：2013年1月1日起） ==--\n" NOR);
                write(HIC "---------------------------------------------------------\n" NOR);
                write(sprintf(HIW "%-30s%-20s\n" NOR, "商品名称", "累计购买"));
                write(HIC "---------------------------------------------------------\n" NOR);
                for( i = 0; i < sizeof(str_buy_list); i ++)
                {
                        if( buy_list[str_buy_list[i]] <= 5 )continue;
                        write(sprintf(HIY"%-30s%-20d\n" NOR, str_buy_list[i], buy_list[str_buy_list[i]]));
                }
                write(HIC "---------------------------------------------------------\n" NOR);

                return 1;
        }
          
        if( sscanf(arg, "%s %s", str1, str2) != 2 )
                return help(me);

        switch(str1)
        {
        case "show":
                return GOODS_D->show_goods(me, str2);

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if( !GOODS_D->buy_goods(me, str2))
                {
                        write("购买失败！\n");
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
        int money, buyvalue;

        money = MEMBER_D->db_query_member(me, "money");
        buyvalue = MEMBER_D->db_query_member(me, "buyvalue");

        write(HIY "□ 您目前的王者币为 " + money + " (NT)
" WHT "——————————————————————————————————

" HIM "输入指令：    ntstore show all                  查看所有商城的货物
输入指令：    ntstore show object               显示所有商城物品类
输入指令：    ntstore show pill                 显示所有商城丹药类
输入指令：    ntstore show special              显示所有商城特技类
输入指令：    ntstore show story                显示所有商城故事类
输入指令：    ntstore show symbol               显示所有商城符文类
输入指令：    ntstore show medal                显示所有商城勋章类
输入指令：    ntstore show enchase              显示所有商城镶嵌类
输入指令：    ntstore show prop                 显示所有商城装备类
输入指令：    ntstore show other                显示所有商城其他类
输入指令：    ntstore show srv                  显示所有商城服务类
输入指令：    ntstore buy <代号>                购买指定代号的商品
输入指令：    ntstore look <代号>               查看指定物品的属性

" WHT "<代号>  ：    可用物品的 name 或 id 或 编号
" WHT "——————————————————————————————————
" HIC "淘宝冲值链接地址: " HIR "http://shop61698067.taobao.com\n
" HIY "您总共在游戏商城消费 " + buyvalue + " (NT)。
" HIY "目前游戏商城的折扣是 " + "/adm/daemons/goodsd.c"->query_rate() + "%，把握机会哦。

" HIG "相关参考文件：help member\n\n" NOR);

        return 1;
}
