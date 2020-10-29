// warehouse.c
// Updated by Lonely

#define IN_OUT_RATE     80/100
#define BUSI_SAVE_DIR   "/data/business/"
#define MAX_TRADE       20000000 // 每笔最大的贸易额为 2 千万两白银
#undef IN_TEST

#include <ansi.h>

inherit F_SAVE;
inherit ROOM;
#include <price.h>

class ware
{
        string name;    /* 中文名字 */
        string id;      /* id */
        int value;      /* 当前单价(单位：银子) */
        int o_value;    /* 初始价格 */
        int amount;     /* 当前保有数量 */
        int o_amount;   /* 初始数量 */
        string unit;    /* 单位 */
}

nomask protected int valid_check();
nomask protected void init_wares();
nomask protected void get_shougou_amount(string arg,object me,class ware w);
nomask protected void get_paochu_amount(string arg,object me,class ware w);
nomask protected void output_list(string number,object who);
nomask protected string list_one_kind(string kind);
string query_save_file()
{ return sprintf("%s%s_bsave",BUSI_SAVE_DIR,domain_file(file_name(this_object())));}

mapping all_wares = ([]);
nosave int no_trade = 0;

int system_change = 0;  // 供系统调整用。change 的单位为黄金.

nosave int price_rate = 100;

// 恢复调整
// {
nosave int change_max = 20000000; /* silver */
nosave string *changed_class = ({});
// }

nomask int query_price_rate()
{
        return price_rate;
}

nomask varargs protected void do_count(string name,int silver)
{
        int i,n,change;
        int orig, cha;
        int rate;
        string domain,*kinds = keys(all_wares);

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                {
                        orig += oneitem->o_value * oneitem->o_amount; /* silver数 */
                        cha += (oneitem->o_amount -  oneitem->amount)*oneitem->o_value;
                }
        }

        rate = (cha+(system_change*100))/(orig/100);

        if(rate < -50)
                rate = -50;
        else if(rate > 50)
                rate = 50;

        if(stringp(name) && silver && (abs(silver) >= orig/100))
        {
                domain = to_chinese(domain_file(file_name(this_object())));
                change = abs((100+rate) - price_rate);

                if(change >= 5)
                {
                        if(silver > 0)
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("听说由于有人在%s大量收购%s致使当地物价飞涨。\n",domain,name));
                        else
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("听说由于有人在%s大量抛售%s致使当地物价飞速下滑。\n",domain,name));
                }
                else if(change >= 1)
                {
                        if(silver > 0)
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("听说由于有人在%s大量收购%s致使当地物价有所上扬。\n",domain,name));
                        else
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("听说由于有人在%s大量抛售%s致使当地有所下降。\n",domain,name));
                }
        }

        price_rate = 100 + rate;
}

// 此物件应受到最严格的检查。
nomask protected int valid_check()
{

        string fname,domain;
        int idx;

        if(clonep())
                return 0;
        if(!sscanf((fname = file_name(this_object())),"/d/%*s"))
                error("商栈物件必须存在于区域目录下。\n");
        idx = strsrch(fname, "/", -1);
        if(fname[idx+1..] != "business")
                error("商栈物件的文件名必须是'business'。\n");

        sscanf(fname,"/d/%s/business",domain);

        if(member_array(domain,BUSINESS_D->query_valid_domains()) == -1)
                error("此区域目前为非贸易区域，如需通商请向神申请。\n");

        return 1;
}

nomask void setup()
{
        if(!valid_check())
                return;

        if(!restore())
                init_wares();
        else
                do_count();
        set("channel_id", "商会");
        set("no_clean_up",1);
        ::setup();
}

nomask protected void init_wares()
{
        mapping wares = query("all_wares");
        mapping kinds = query("kind_rate");
        string *items;
        string kind;
        int i,n;

        items =  filter_array(explode(PRICES, "\n") - ({ "" }), (: $1[0] != '#' :));

        if(!items || !(n=sizeof(items)))
                return;

        for(i=0;i<n;i++)
        {
                class ware item;
                string name,id,unit;
                int value;

                if(sscanf(items[i],"%s %s %s %d",name,id,unit,value) == 4)
                {
                        item = new(class ware);
                        item->name = name;
                        item->id = id;
                        item->unit = unit;
                        item->o_value = value*(!undefinedp(kinds[id])?kinds[id]:100)/100;
                        item->value = item->o_value;
                        if(!undefinedp(wares[id]))
                                item->o_amount = wares[id];
                        else
                                item->o_amount = 0;
                        item->amount = item->o_amount;

                        all_wares[kind] += ({ item });
                }
                else
                {
                        kind = items[i];
                        all_wares[kind] = ({});
                }
                 this_object()->save();

        }
}

nomask void init()
{
        if(clonep())
                return;
        add_action("do_shougou",({ "shou","shougou" }));
        add_action("do_chakan",({ "chakan","list" }));
        add_action("do_paochu",({ "pao","paochu" }));
        add_action("do_check",({ "check" }));
        add_action("do_fasong","fasong");
}

nomask int do_fasong()
{
        this_player()->fasong_ware();
        return 1;
}

nomask int do_check()
{
        int i,n;
        int cha;
        int orig;
        string *kinds = keys(all_wares);

        if(!wizardp(this_player()))
                return 0;

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                {
                        orig += oneitem->o_value * oneitem->o_amount; /* silver数 */
                        cha += (oneitem->o_amount -  oneitem->amount)*oneitem->o_value;
                }
        }

        printf("此地初始总价值数为：%d 两白银\n当前数值差：%d 两白银\n当前总物价指数为：百分之 %d\n系统调整值：%d\n",
                orig, cha, price_rate,system_change );
        return 1;
}

nomask int do_chakan(string arg)
{
        string *kinds = keys(all_wares);
        int i,n;

        if(!n = sizeof(all_wares))
                return notify_fail("目前没有可贸易的货物。\n");

        if(stringp(arg))
        {
                n = sizeof(kinds);
                for(i=0;i<n;i++)
                        if(kinds[i] == arg)
                        {
                                output_list(sprintf("%d",(i+1)),this_player());
                                return 1;
                        }
                return notify_fail("你要查看哪类货物的价格？\n");
        }
        else
        {
                int l,bk;
                string out;
                kinds += ({ "所有类别" });
                n = sizeof(kinds);
                for(i=0;i<n;i++)
                        if(strlen(kinds[i]) > l)
                                l = strlen(kinds[i]);
                out = "请选择你要查看的货物类别：\n";
                bk = to_int(50/(l+5));
                l++;
                for(i=0;i<n;i++)
                        out += sprintf("%-3d%-"+(string)l+"s  %s",(i+1),kinds[i],(i%bk==(bk-1))||i==n-1?"\n":"" );
                write(out);
                input_to((: output_list :),this_player());
                return 1;
        }
}

nomask protected void output_list(string number,object who)
{
        int i,n;
        string output,*kinds = keys(all_wares);

        if(!objectp(who) || (number[0] == 'q'))
                return;

        if(!sscanf(number,"%d",n))
        {
                write("请选择你要查看的货物类别：\n");
                input_to((: output_list :),who);
                return;
        }

        n--;
        if( (n < 0 ) || (n > sizeof(kinds)) )
        {
                write("请选择你要查看的货物类别：\n");
                input_to((: output_list :),who);
                return;
        }

        if(n < sizeof(kinds))
        {
                output = sprintf("本货栈目前可以贸易的%s类货物：\n",kinds[n]);
                output += sprintf("%-8s%-20s %|8s%|6s%12s/%s\n","种类","货物名称","数量","单位","卖出价","买入价(单位：银子)");
                output += "-------------------------------------------------------------------------\n";
                output += list_one_kind(kinds[n]);
                write(output);
                return;
        }

        else
        {
                output = "本货栈目前所有可以贸易的货物：\n";
                output += sprintf("%-8s%-20s %|8s%|6s%12s/%s\n","种类","货物名称","数量","单位","卖出价","买入价(单位：银子)");
                output += "-------------------------------------------------------------------------\n";
                for(i=0;i<n;i++)
                        output += list_one_kind(kinds[i]);
                who->start_more(output);
                return;
        }
}

nomask protected string list_one_kind(string kind)
{
        int i,n;
        string output = "";
        class ware *items;

        if(!stringp(kind) || undefinedp(all_wares[kind]))
                return "";

        items = all_wares[kind];

        n = sizeof(items);
        for(i=0;i<n;i++)
        {
                int sell;

                if(items[i]->amount <1)
                        output += sprintf("%-8s%-20s%|14s    %8d/%-8d\n",
                                i==0?kind:"",
                                sprintf("%s(%s)",items[i]->name,items[i]->id),
                                "[无  货]",
                                (sell = to_int(items[i]->value*price_rate/100)),
                                sell*IN_OUT_RATE);
                else
                        output += sprintf("%-8s%-20s%8d%|6s    %8d/%-8d\n",
                                i==0?kind:"",
                                sprintf("%s(%s)",items[i]->name,items[i]->id),
                                items[i]->amount,items[i]->unit,
                                (sell = to_int(items[i]->value*price_rate/100)),
                                sell*IN_OUT_RATE);
        }
        return output;
}

nomask protected int do_shougou(string arg)
{
        class ware item;
        int n,i,num;
        string *kinds = keys(all_wares);

        if(no_trade)
                return notify_fail("现在正在盘库，请等一下再来。\n");

/*
#ifdef IN_TEST
        if(!wizardp(this_player()))
                return notify_fail("测试期间不允许玩家参与贸易。\n");
#else
        if(wizardp(this_player()))
                return notify_fail("正式运行期间不允许巫师参与贸易。\n");
#endif
*/

        if( !stringp(arg) || (arg == "") )
                return notify_fail("你要收购什么货物？\n");

        if(sscanf(arg,"%d %s",num,arg) == 2)
                if(num < 1)
                        return notify_fail("收购数量至少为 1。");

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                        if(oneitem->id == arg)
                        {
                                item = oneitem;
                                break;
                        }
        }

        if(!item)
                return notify_fail("你要收购什么货物？\n");

        if(item->amount < 1)
                return notify_fail(sprintf("最近本地%s已经断货了，您过一段时间在来看看吧。\n",
                        item->name));

        if(num > 0)
        {
                get_shougou_amount(sprintf("%d",num),this_player(),item);
                return 1;
        }

        write(sprintf("您要收购多少%s%s？",item->unit,item->name));
        input_to((: get_shougou_amount :),this_player(),item);
        return 1;
}

nomask protected void get_shougou_amount(string arg,object me,class ware w)
{
        int n,value,one;
        string domain;
        //object ob;

        if(!objectp(me) || (arg[0] == 'q'))
                return;

        if(!sscanf(arg,"%d",n))
        {
                write(sprintf("您要收购多少%s%s？",w->unit,w->name));
                input_to((: get_shougou_amount :),me,w);
                return;
        }

        if(n < 1)
        {
                write("收购数量至少为 1。");
                return;
        }

        if(n > 210000000)
        {
                write("收购数量不可大于 21 亿。");
                return;
        }

        if( n > w->amount )
        {
                write(sprintf("对不起，本地目前只有 %d %s%s，您过一段时间在来看看吧。\n",
                        w->amount,w->unit,w->name));
                return;
        }

        one = w->value*price_rate/100;
        if(n > (MAX_TRADE/one))
        {
                write(sprintf("对不起，本地商会规定每笔贸易额不能超过%s两白银。\n",
                        chinese_number(MAX_TRADE)));
                return;
        }

        value = n*one;

#ifndef IN_TEST
        //if(!pay_from_bank(me,value*100))
        if( query("balance", me)<value*100 )
        {
                write(sprintf("收购 %d %s%s 共需资金 %d 两银子，你的银行存款不够。\n",
                        n,w->unit,w->name,value));
                return;
        }

        addn("balance", -value*100, me);
#endif

        if(!me->buy_in(w->name,w->id,w->unit,n,one))
        {
                write("你的收购行为没有成功，本钱损失殆尽，请立刻向巫师通报。\n");
                log_file("warehouse",sprintf("%s(%s) 收购%s %d %s失败，损失本金 %d 两白银。%s\n",
                        me->name(),query("id", me),w->name,n,w->unit,value,ctime(time())));
                return;
        }

        domain = domain_file(base_name(this_object()));

        write(sprintf("\n你从%s商栈收购了 %d %s%s。\n商栈的账房先生在一个大本子上记了下来。\n\n",
                to_chinese(domain),n,w->unit,w->name));

        w->amount -= n;

        do_count(w->name,value);
        save();

#ifndef IN_TEST
        log_file("warehouse",sprintf("%s(%s)在%s以单价%d两白银收购%s%d%s。%s\n",
                me->name(),query("id", me),to_chinese(domain),one,w->name,n,w->unit,ctime(time())));
#endif

        return;
}

nomask protected int do_paochu(string arg)
{
        class ware item;
        int n,i,num;
        string *kinds = keys(all_wares);

        if(no_trade)
                return notify_fail("现在正在盘库，请等一下再来。\n");

/*
#ifdef IN_TEST
        if(!wizardp(this_player()))
                return notify_fail("测试期间不允许玩家参与贸易。\n");
#else
        if(wizardp(this_player()))
                return notify_fail("正式运行期间不允许巫师参与贸易。\n");
#endif
*/

        if( !stringp(arg) || (arg == "") )
                return notify_fail("你要抛出什么货物？\n");

        if(sscanf(arg,"%d %s",num,arg) == 2)
                if(num < 1)
                        return notify_fail("抛售数量至少为 1。");

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                        if(oneitem->id == arg)
                        {
                                item = oneitem;
                                break;
                        }
        }

        if(!item)
                return notify_fail("你要抛出什么货物？\n");

        if(num > 0)
        {
                get_paochu_amount(sprintf("%d",num),this_player(),item);
                return 1;
        }

        write(sprintf("您要抛出多少%s%s？",item->unit,item->name));
        input_to((: get_paochu_amount :),this_player(),item);
        return 1;
}

nomask protected void get_paochu_amount(string arg,object me,class ware w)
{
        int n,value,r,one;
        string domain;

        if(!objectp(me) || (arg[0] == 'q'))
                return;

        if(!sscanf(arg,"%d",n))
        {
                write(sprintf("您要抛出多少%s%s？",w->unit,w->name));
                input_to((: get_paochu_amount :),me,w);
                return;
        }


        if(n < 1)
        {
                write("抛售数量至少为 1。");
                return;
        }

        one = w->value*price_rate/100*IN_OUT_RATE;

        if(n > (MAX_TRADE/one))
        {
                write(sprintf("对不起，本地商会规定每笔贸易额不能超过%s两白银。\n",
                        chinese_number(MAX_TRADE)));
                return;
        }

        if(!(r = me->sell_out(w->id,n,one)))
        {
                write(sprintf("你在本地没有%s。\n",w->name));
                return;
        }

        if(r == -1)
        {
                write(sprintf("你在本地没有这么多数量的%s。\n",w->name));
                return;
        }

        domain = domain_file(base_name(this_object()));
        value = n*one;

#ifndef IN_TEST
        /*
        if( !save_to_bank(me,value*100) )
        {
                tell_object(me,"你的货款全部损失了，请向巫师报告。\n");
                log_file("warehouse",sprintf("%s(%s)由于银行存款超额抛售物品时损失了 %d 两银子。%s\n",
                        me->name(),query("id", me),value,ctime(time())));
                return 0;
        }
        */
        addn("balance", value*100, me);
#endif

        write(sprintf("你在本地抛售了 %d %s%s，\n应得货款 %d 两银子已存入您的银行账户。\n",
                n,w->unit,w->name,value));

        w->amount += n;
        do_count(w->name,-value);
        save();

#ifndef IN_TEST
        log_file("warehouse",sprintf("%s(%s)在%s以单价%d两白银抛出%s%d%s。%s\n",
                me->name(),query("id", me),to_chinese(domain),one,w->name,n,w->unit,ctime(time())));
#endif
}

// 系统控制的随机变动
nomask void random_change(int sum)
{

        /*
        if(!previous_object()
        || (geteuid(previous_object()) != ROOT_UID))
                return;
        */

        if(!sum)
                return;

        no_trade = 1;   // 变动期间禁止贸易

        system_change += sum;
        do_count("商品",sum*100);
        save();
        log_file("business",sprintf("%s: 商品价格随机变动 %s 涉及总金额 %d 两白银. %s\n",
                domain_file(base_name(this_object())),
                sum > 0 ? "上调" : "下跌",
                sum*100, ctime(time())));
        no_trade = 0;
}

// 系统控制的恢复
nomask void random_recover()
{
        string *cs;
//      string current_cs;
        int max,i/*,n*/,flag;
        // class ware *items;

/*
        if(!previous_object()
        || (geteuid(previous_object()) != ROOT_UID))
                return;
*/

        no_trade = 1;   // 变动期间禁止贸易

        if(sizeof(changed_class) >= sizeof(cs = keys(all_wares)))
                changed_class = ({});

        for(i=0;i<sizeof(cs);i++)
        {
        /*
                if(member_array(cs[i],changed_class) == -1)
                { current_cs = cs[i]; break; }

        changed_class += ({ current_cs });

        items = all_wares[current_cs];
        n = sizeof(items);
        */

        max = change_max;

        // foreach(class ware oneitem in all_wares[current_cs])
        foreach(class ware oneitem in all_wares[cs[i]])
        {
                int diff,ch;

                if(max < 50)
                        break;
                if(max < oneitem->o_value)
                        continue;

                if(!diff = oneitem->o_amount - oneitem->amount)
                        continue;
                ch = to_int(max/oneitem->o_value);
                if(abs(diff) < ch)
                        ch = abs(diff);
                max -= ch * oneitem->o_value;
                if(diff < 0)
                {
                        oneitem->amount -= ch;
                        flag = 1;
                }
                else
                        oneitem->amount += ch;
                log_file("business",sprintf("%s: 恢复调整 %s %s %d %s. %s\n",
                        domain_file(base_name(this_object())),
                        oneitem->id,
                        flag?"减少":"增加",
                        ch,
                        oneitem->unit,
                        ctime(time()),
                        ));
        }
        }

        do_count();
        save();

        no_trade = 0;
}
