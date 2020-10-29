#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping dbase;
        string *msg = ({});
        object ob;

        if( arg && wizardp(me) )
                ob = find_player(arg);

        if( !ob )
                ob = me;

        dbase = copy(ob->query_entire_dbase());

        if( sizeof(dbase["stock"]) )
        {
                mapping stocks = STOCK_D->query_stocks();
                float ownstockvalue, curstockvalue, gain;
                string stockcolor, stockdesc;

                foreach(string num, mapping data in dbase["stock"])
                {
                        ownstockvalue = data["value"];
                        if( undefinedp(stocks[num]) ) continue;
                        curstockvalue = stocks[num]["现价"];

                        gain = (curstockvalue - ownstockvalue)*100. / ownstockvalue;

                        if( stocks[num]["涨跌"] < 0 )
                        {
                                stockcolor = HIG;

                                if( stocks[num]["状态"] == "t3g2" )
                                        stockcolor += BGRN;

                                stockdesc = " □"+sprintf("%.2f", -stocks[num]["涨跌"]);
                        }
                        else if( stocks[num]["涨跌"] > 0 )
                        {
                                stockcolor = HIR;

                                if( stocks[num]["状态"] == "t3r2" )
                                        stockcolor += BRED;

                                stockdesc = " ▲"+sprintf("%.2f", stocks[num]["涨跌"]);
                        }
                        else
                        {
                                stockcolor = HIW;
                                stockdesc = " —";
                        }
                        msg += ({ HIY"股"NOR YEL"票" });
                        msg += ({ sprintf(NOR" %-12s %12s %-12s%-19s %12s\n", HIM+num + NOR" "HIW +stocks[num]["股票名称"]+NOR, WHT +(data["amount"]) +NOR" 张", NOR YEL"持股 "HIW+sprintf("%.2f", ownstockvalue||0.0)+NOR, NOR YEL"现价 "+stockcolor+sprintf("%6.2f", curstockvalue||0.0)+stockdesc+NOR, NOR YEL"利润 "+(curstockvalue>ownstockvalue?HIR:curstockvalue<ownstockvalue?HIG:HIW)+(gain>0?"+":gain==0.?" ":"")+sprintf("%.2f", gain||0.0)+"%"+NOR ) });
                }

        }
        else

                msg += ({ NOR"手上没有持有任何股票" });

        me->start_more(implode(msg, ""));
        return 1;
}

int help()
{
        write("\n此命令可以列出你的股票情况。\n\n");
        return 1;
}
