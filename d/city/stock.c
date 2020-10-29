// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

#define PROCEDURE_FUND  0.01            // 1/100 的手续费
#define STOCK_VALUE     10000           // 一张股票价值

varargs string stockvalue_change_description(float change, string type)
{
        string bgcolor;

        switch(type)
        {
                case "t3g2":
                        bgcolor = BGRN;
                        break;

                case "t3r2":
                        bgcolor = BRED;
                        break;
                default:
                        bgcolor = "";
                        break;
        }

        change = to_float(change);

        if( change > 0 )
                return bgcolor+sprintf(HIR"▲%5.2f", change);
        else if( change < 0 )
                return bgcolor+sprintf(HIG"□%5.2f", -change);
        else
                return bgcolor+sprintf(HIW"  %5.2f", change);
}


int do_liststock(string arg)
{
        int count;
        mapping stocks = STOCK_D->query_stocks();
        string *stock_sort = sort_array(keys(stocks), 1);
        mapping data;
        int min, max;
        string *msg = allocate(0);
        //float percent = PROCEDURE_FUND - me->query_skill("stock", 1)/10000.;
        float percent = 0.01;
        object me = this_player();

        if( arg )
        {
                if( sscanf(arg, "%d %d", min, max) != 2 )
                        sscanf(arg, "%d", min);
        }

        msg = ({"代号    股票名称     现价    涨跌  涨跌幅度 开盘价 最高价 最低价 成交张数 \n"});
        msg += ({"—————————————————————————————————————————————\n"});

        foreach(string stock in stock_sort)
        {
                count++;

                if( max )
                {
                        if( to_int(stock) < min || to_int(stock) > max ) continue;
                }
                else
                {
                        if( min && to_int(stock) != min ) continue;
                }

                data = stocks[stock];

                if( !data["股票名称"] ) continue;

                msg += ({sprintf(HIM"%-6s"HIW"  %-8s "HIY"%8.2f"NOR" %-8s %7.2f%% "NOR WHT"%6.2f "HIB"%6.2f %6.2f  "NOR BYEL HIY"%d\n"NOR,
                        stock,
                        data["股票名称"],
                        data["现价"],
                        stockvalue_change_description(data["涨跌"], data["状态"]),
                        data["涨跌幅"],
                        data["开盘"],
                        data["最高"],
                        data["最低"],
                        data["成交张数"],
                )});
        }
        msg += ({"—————————————————————————————————————————————\n"});
        msg += ({MAG"共 "HIM+count+NOR MAG" 只上市股票，"YEL"股票单位为 "HIY"1"NOR YEL" 两黄金/张，"NOR RED"交易手续费为 "HIR+sprintf("%.2f%%", percent*100.)+NOR RED"。\n"NOR});
        msg += ({HIK"股票数据资料来自沪深A股，2 分钟更新一次，本次更新时间："+sprintf("%s\n", TIME_D->replace_ctime(STOCK_D->query_last_update_time()))+NOR});
        me->start_more(implode(msg, ""));
        return 1;
}

void confirm_buystock(object me, string num, int totalcost, int new_amount, float new_value, float cur_value, int amount, string stock_name, string arg)
{
        int td;

        if( !arg )
                return me->finish_input();

        arg = lower_case(arg);

        if( arg != "y" && arg != "yes" )
        {
                tell_object(me, "取消购入股票。\n");
                return me->finish_input();
        }

        if( query("balance", me)<totalcost )
        {
                tell_object(me, "你在银行的钱不足。\n");
                return me->finish_input();
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票资料更新中，请稍后再进行交易。\n");
                return me->finish_input();
        }

        td = time() / 86400;

        set("stock/"+num+"/amount", new_amount, me);
        set("stock/"+num+"/value", new_value, me);

        if( query("stock/"+num+"/limit/which_day", me) != td )
        {
                set("stock/"+num+"/limit/amount", amount, me);
                set("stock/"+num+"/limit/which_day", td, me);
        }
        else
        {
                addn("stock/"+num+"/limit/amount", amount, me);
        }

        CHANNEL_D->channel_broadcast("stock", me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股价购入「"HIW+stock_name+NOR RED"」股票 "+amount+" 张。"NOR);
        tell_object(me, "交易完成。\n");
        me->finish_input();

        addn("balance", -totalcost, me);
        //TOP_D->update_top_rich(me);
        me->save();
}

int do_buystock(string arg)
{

        mapping stocks = STOCK_D->query_stocks();
        string num;
        int amount;
        float old_value;
        float new_value;
        float cur_value;
        int old_amount;
        int new_amount;
        int cost;
        int cost_extra;
        int *nowtime = TIME_D->query_realtime_array();
        float percent;
        object me = this_player();

        //tell_object(me, "股票系统目前无法处理重新挂牌、除权、除息等问题，风险自负。\n");

        if( !wizardp(me) && (/*nowtime[2] < 1 || nowtime[2] > 6 ||*/ nowtime[1] < 9 || nowtime[1] >= 22) )
        {
                tell_object(me, "周一至周日的早上九点至晚上十点允许交易。\n");
                return 1;
        }

        if( STOCK_D->query_last_update_time() < time() - 48*60*60 )
        {
                tell_object(me, "股票资料尚未更新，无法进行交易。\n");
                return 1;
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票资料更新中，请稍后再进行交易。\n");
                return 1;
        }

        if( !arg || sscanf(arg, "%s %d", num, amount) != 2 )
        {
                tell_object(me, "请输入正确的格式，例：buy 000002 100。\n");
                return 1;
        }

        if( amount < 1 )
        {
                tell_object(me, "你至少必须购买一张股票。\n");
                return 1;
        }

        if( !mapp(stocks[num]) || !stocks[num]["股票名称"] )
        {
                tell_object(me, "没有 "+num+" 这一只股票。\n");
                return 1;
        }

        if( stocks[num]["状态"] == "t3r2" )
        {
                tell_object(me, "这档股票已经涨停，无法再买了。\n");
                return 1;
        }

        old_amount=query("stock/"+num+"/amount", me);
        new_amount = amount + old_amount;


        if( new_amount > 10000000 )
        {
                tell_object(me, "每只股票最多只能购买 10,000,000 张。\n");
                return 1;
        }

        old_value=to_float(query("stock/"+num+"/value", me));
        cur_value = stocks[num]["现价"];
        new_value = (old_value * old_amount + cur_value * amount) / (amount + old_amount);

        //percent = PROCEDURE_FUND - me->query_skill("stock", 1)/10000.;
        percent = 0.01;

        cost = to_int(to_int(cur_value*100) * STOCK_VALUE * amount / 100);
        cost_extra = to_int(cost * percent);

        if( cost + cost_extra < 1 )
        {
                tell_object(me, "资料计算错误，请通知巫师处理。\n");
                return 1;
        }

        tell_object(me,
                WHT"股票名称      "NOR HIW+num+" "+stocks[num]["股票名称"]+NOR"\n"
                "———————————————————\n"
                YEL"股票现在价格  "HIY+sprintf("%.2f", cur_value)+"\n"NOR
                GRN"欲购股票张数  "HIG+amount+"\n"NOR
                GRN"目前持股价格  "HIG+sprintf("%.2f", old_value)+"\n"NOR
                GRN"目前持股张数  "HIG+old_amount+"\n"NOR
                CYN"平均之后价格  "HIC+sprintf("%.2f", new_value)+"\n"NOR
                CYN"欲购股票总值  "HIC+cost+"\n"NOR
                CYN"交易手续费用  "HIC+cost_extra+HIR"("+sprintf("%.2f", percent*100.)+"%)\n"NOR
                CYN"购入总共花费  "HIC+(cost + cost_extra)+"\n"NOR
                "———————————————————\n"
                HIY"是否确定购入股票?"NOR YEL"(Yes/No)"NOR
        );

        input_to((: confirm_buystock, me, num, cost + cost_extra, new_amount, new_value, cur_value, amount, num+" "+stocks[num]["股票名称"] :));
        return 1;
}

void confirm_sellstock(object me, string num, int totalearn, int new_amount, float old_value, float cur_value, int amount, string stock_name, string arg)
{

        if( !arg )
                return me->finish_input();

        arg = lower_case(arg);

        if( arg != "y" && arg != "yes" )
        {
                tell_object(me, "取消贩卖股票。\n");
                return me->finish_input();
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票资料更新中，请稍后再进行交易。\n");
                return me->finish_input();
        }

        if( new_amount <= 0 )
                delete("stock/"+num, me);
        else
                set("stock/"+num+"/amount", new_amount, me);

        if( cur_value == old_value )
                CHANNEL_D->channel_broadcast("stock",
                        me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股价售出「"HIW+stock_name+NOR RED"」股票 "+amount+" 张。"NOR);
        else if( cur_value > old_value )
                CHANNEL_D->channel_broadcast("stock",
                        me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股价售出「"HIW+stock_name+NOR RED"」股票 "+amount+" 张，获利 "
                        HIY+to_int(to_int((cur_value-old_value)*100)*STOCK_VALUE/100*amount)+NOR RED"。" NOR);
        else
                CHANNEL_D->channel_broadcast("stock",
                        me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股价售出「"HIW+stock_name+NOR RED"」股票 "+amount+" 张，认赔 "
                        HIY+to_int(to_int((old_value-cur_value)*100)*STOCK_VALUE/100*amount)+NOR RED"。" NOR);
        tell_object(me, "交易完成。\n");

        me->finish_input();

        addn("balance", totalearn, me);
        //TOP_D->update_top_rich(me);
        me->save();
}

int do_sellstock(string arg)
{
        mapping stocks = STOCK_D->query_stocks();
        string num;
        int amount;
        int old_amount;
        int new_amount;
        float cur_value;
        float old_value;
        int earn, td, limit = 0;
        int *nowtime = TIME_D->query_realtime_array();
        object me = this_player();

        if( !wizardp(me) && (/*nowtime[2] < 1 || nowtime[2] > 6 ||*/ nowtime[1] < 9 || nowtime[1] >= 22) )
        {
                tell_object(me, "周一至周日的早上九点至晚上十点允许交易。\n");
                return 1;
        }

        if( STOCK_D->query_last_update_time() < time() - 48*60*60 )
        {
                tell_object(me, "股票资料尚未更新，无法进行交易。\n");
                return 1;
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票资料更新中，请稍后再进行交易。\n");
                return 1;
        }

        if( !arg || sscanf(arg, "%s %d", num, amount) != 2 )
        {
                tell_object(me, "请输入正确的格式，例：sell 000002 100。\n");
                return 1;
        }

        if( amount < 1 )
        {
                tell_object(me, "你至少必须出售一张股票。\n");
                return 1;
        }

        if( !mapp(stocks[num]) || !stocks[num]["股票名称"] )
        {
                tell_object(me, "没有 "+num+" 这一只股票。\n");
                return 1;
        }

        if( stocks[num]["状态"] == "t3g2" )
        {
                tell_object(me, "这档股票已经跌停，无法再卖了。\n");
                return 1;
        }

        td = time() / 3600;

        old_amount=query("stock/"+num+"/amount", me);

        // 当天购买的股票不可以卖出
        if( query("stock/"+num+"/limit/which_day", me) == td )
                limit=query("stock/"+num+"/limit/amount", me);

        new_amount = old_amount - amount;

        old_value=to_float(query("stock/"+num+"/value", me));
        cur_value = stocks[num]["现价"];

        if( old_amount < 1 )
        {
                tell_object(me, "你手上并没有 "+num+" 这只股票。\n");
                return 1;
        }

        if( new_amount < limit )
        {
                tell_object(me, "这只股票你手上只有 "+old_amount+" 张，可交易 "+(old_amount-limit)+" 张。\n");
                return 1;
        }

        earn = to_int(to_int(cur_value*100) * amount * STOCK_VALUE / 100);

        if( earn < 1 )
        {
                tell_object(me, "资料计算错误，请通知巫师处理。\n");
                return 1;
        }

        tell_object(me,
                WHT"股票名称      "NOR HIW+num+" "+stocks[num]["股票名称"]+NOR"\n"
                "———————————————————\n"
                YEL"股票现在价格  "HIY+sprintf("%.2f", cur_value)+"\n"NOR
                GRN"目前持股价格  "HIG+sprintf("%.2f", old_value)+"\n"NOR
                GRN"目前持股利润  "HIG+sprintf("%.2f%%", (cur_value - old_value) * 100. / old_value)+"\n"NOR
                GRN"欲售股票张数  "HIG+amount+"\n"NOR
                CYN"售出总共获得  "HIC+earn+"\n"NOR
                "———————————————————\n"
                HIY"是否确定售出股票?"NOR YEL"(Yes/No)"NOR
        );

        input_to((: confirm_sellstock, me, num, earn, new_amount, old_value, cur_value, amount, num+" "+stocks[num]["股票名称"] :));
        return 1;
}

void create()
{
        set("short", "证券交易所");
        set("long", @LONG
这是一家证券交易所，墙上挂着一个牌子(paizi)。
LONG );

        set("item_desc", ([
                "paizi" : @HELP
显示股市资讯
liststock              列出所有沪深A股市场资料
liststock 000002       列出代号000002股票的资料
buystock 000002 300    买入000002股票300张
sellstock 000002 100   卖出000002股票100张
istock                 列出自己购买的股票资料

HELP,
        ]));
        set("exits", ([
                "south": __DIR__"kedian",
        ]));
        set("no_fight", 1);
        set("coor/x", 20);
        set("coor/y", 0);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_liststock", "liststock");
        add_action("do_buystock", "buystock");
        add_action("do_sellstock", "sellstock");
}
