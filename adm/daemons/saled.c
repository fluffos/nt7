// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org
// saled.c

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <config.h>

inherit F_SAVE;
inherit F_DBASE;

#define MAX_OBS    20
#define TAX        5

void create()
{
        mapping data;

        seteuid(ROOT_UID);
        restore();
        data = query_entire_dbase();
        if( !mapp(data) || undefinedp(data["data"]) )
        {
                set("data", ([]));
                save();
        }
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

public string query_save_file() { return DATA_DIR "saled"; }

protected void log_buyinfo(object ob, string which, int value)
{
        string buyinfo;

        buyinfo = MEMBER_D->db_query_member(ob, "buyinfo");
        buyinfo += sprintf("%s(%s)于%s花费 %d $NT购买物品 %s 1。\n",
                           ob->name(1),
                           query("id", ob),
                           TIME_D->replace_ctime(time()),
                           value,
                           which);

        MEMBER_D->db_set_member(ob, "buyinfo", buyinfo);
        MEMBER_D->db_add_member(ob, "buytimes", 1);
        MEMBER_D->db_add_member(ob, "buyvalue", value);
        MEMBER_D->db_set_member(ob, "last_buytime", time());
        MEMBER_D->db_set_member(ob, "last_buyob", which);
        MEMBER_D->db_set_member(ob, "last_buyvalue", value);
        return;
}

public string do_stock(object me, string arg)
{
        object ob, obj;
        int n, value;
        string file, id, key, str, db;
        mapping data;

        id=query("id", me);
        if( !arg || sscanf(arg, "%s value %d", arg, value) != 2 )
                return "指令格式：stock <货物> value * (其中 * 是以泥潭币($NT)作单位的价格)\n";

        if( !value || value < 0 )
                return "指令格式：stock <货物> value * (其中 * 是以泥潭币($NT)作单位的价格)\n";

        if( value > 100000000 )
                return "最多标价一亿泥潭币($NT)，你就别那么心黑了吧。\n";

        if( !objectp(ob = present(arg, me)) )
                return "你身上并没有这个货物啊！\n";

        if( query("no_sell", ob) || query("id", ob) == "key" )
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

           if ( query("value", ob) && query("value", ob) < 2 )
         return "这东西一文不值！\n";
        if( query("task_ob", ob) )
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        if( ob->is_item_make() || query("unique", ob) )
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        if( sscanf(base_name(ob), "/data/%*s") )
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        file = file_name(ob);
        if( strsrch(file, "#") == -1 )
                return "对不起，该物品不可以寄售！\n";

        if( ob->is_character() )
                return "你不能贩卖活物。\n";

        if( query("money_id", ob) )
                return "你把钱也拿来出售？\n";

        if( query("bindable", ob) )
                delete("bind_owner", ob);

        key = "data/" + id + "/";
        if( sizeof(query(key+"objects")) >= MAX_OBS )
                return "对不起，你已经寄售了" + query(key + "cnt") +
                       "件物品了。不能再寄售更多的东西了。\n";

        str=query("unit", ob);
        if( !str ) str = "个";
        if( n = ob->query_amount() )
                db = "";
        else {
                obj = new(base_name(ob));
                if( !mapping_eqv(ob->query_entire_dbase(), obj->query_entire_dbase()) )
                        db = save_variable(ob->query_entire_dbase());
                else
                        db = "";
                destruct(obj);
        }
        if( n < 1 ) n = 1;
        data = ([
                "file" : file,
                "name":query("name", ob),
                "id":query("id", ob),
                "ids" : ob->my_id(),
                "unit" : str,
                "num" : n,
                "value" : value,
                "dbase" : db,
        ]);

        n = query(key + "cnt");
        n++;
        set(key + "cnt", n);
        set(key + "objects/" + n, data);

        message_vision(HIW "$N" HIW "将『" HIG + ob->name(1) +
                       HIW "』标上" HIY + value +
                       HIW "NT价格开始出售。\n" NOR, me);
        destruct(ob);

        if( objectp(ob) ) {
                set(key + "cnt", n - 1);
                delete(key + "objects/" + n);
                save();
                return "错误！寄售失败，请联系管理员。\n";
        } else {
                save();
                return data["name"] + "已经寄售好了！编号：" + n + " 。\n";
        }
}

public string do_unstock(object me, string arg)
{
        string kid,*ks,id;
        string file="";
        object ob;
        mapping data;
        int i,flag=0;
        id=query("id", me);

        if( !arg || arg == "" )
                return "指令格式：unstock <物品> | <物品编号>\n";

        arg = lower_case(arg);
        kid = "data/" + id + "/objects";
        data = query(kid);
        if( sizeof(data) < 1 )
                return "你什么物品都没有寄售着，还想拿走什么？\n";

        if( sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED )
                return "你身上的东西太多了，没法从货架上取东西。\n";

        ks = keys(data);
        for( i = 0; i < sizeof(ks); i++ ) {
                if( ks[i] == arg || data[ks[i]]["id"] == arg ) {
                        data = data[ks[i]];
                        flag = 1;
                        break;
                }
        }

        if( flag ) {
                file = data["file"];
                sscanf(file, "%s#%*s", file);
                ob = new(file);
                if( data["dbase"] ) {
                        ob->set_dbase(restore_variable(data["dbase"]));
                        ob->set_name(query("name", ob),data["ids"]);
                }

                if( objectp(ob) ) {
                        ob->set_amount(data["num"]);
                        ob->move(me, 1);
                        delete(kid+"/"+ks[i]);
                        save();
                        message_vision( HIW "$N" HIW "将『" HIG + ob->name(1) +
                                        HIW "』从货架上取下来不卖了。\n" NOR, me );
                        return "你从寄售柜取出了"+data["name"]+"("+data["id"]+") 。\n";
                }
        }
        return "现在" + environment(me)->short() + "的货架上并没有这样货物。\n";
}

public string do_list(object me, string arg)
{
        string k, msg, *ks;
        mapping data, m, om;
        int i, j, w;
        string id;

        data = query("data");
        if( !mapp(data) || sizeof(data) < 1 )
                return "目前并没有出售任何货物。\n";

        msg = "该寄售店目前出售以下物品：\n";
        msg += "-------------------------------------------------------\n";
        ks = keys(data);
        j=0;
        w=wizardp(me);
        for( i = 0; i < sizeof(ks); i++ ) {
                if( mapp(m = data[ks[i]]["objects"]) && sizeof(m) > 0 ) {
                        foreach(k in keys(m)) {
                                om = m[k];
                                j++;
                                msg+=sprintf("第%d个物品 编号%5s ： %20s(%10s) 数量：%5d 售价：%8d$NT (%s) %s\n",
                                             j,k,om["name"],om["id"],om["num"],om["value"],ks[i],(w?om["file"]:""));
                        }
                }
        }

        msg += "-------------------------------------------------------\n";

        msg += "总共" + chinese_number(j) + "件货物。\n";

        // me->start_more(msg);
        return msg;
}

public string do_buy(object me, string arg)
{
        string kid, *ks, id;
        string file;
        object ob;
        mapping data;
        int value, money, fees;
        int i, flag = 0;
        int m;

        if( me->is_busy() )
                return "什么事都得等你忙完再说吧！\n";

        if( !arg || sscanf(arg, "%s from %s", arg, id) != 2 )
                return "buy <某物> from <id>\n";

        if( sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED )
                return "你身上的东西太多了，先处理一下再买东西吧。\n";

        arg = lower_case(arg);
        kid = "data/" + id + "/objects";
        data = query(kid);
        if( sizeof(data) < 1 )
                return "他什么物品都没有寄售着。\n";

        ks = keys(data);
        for( i = 0; i < sizeof(ks); i++ ) {
                if( ks[i] == arg || data[ks[i]]["id"] == arg ) {
                        data = data[ks[i]];
                        flag = 1;
                        break;
                }
        }

        if( flag ) {
                value = data["value"];
                money = MEMBER_D->db_query_member(me, "money");
                if( money < value )
                        return "对不起，您的泥潭金币数量不够，请冲值后再来！\n";

                fees = (int)value * TAX / 100;
                if( fees > 0 ) {
                        if( !MEMBER_D->player_pay(me, fees) ||
                            !MEMBER_D->player_pay(me, (value - fees), id) )
                                return "购买物品失败，请与本站巫师联系！\n";
                }
                else
                {
                        if( !MEMBER_D->player_pay(me, value, id) )
                                return "购买物品失败，请与本站巫师联系！\n";
                }

                file = data["file"];
                sscanf(file, "%s#%*s", file);
                ob = new(file);
                if( data["dbase"] ) {
                        ob->set_dbase(restore_variable(data["dbase"]));
                        ob->set_name(query("name", ob),({query("id", ob)}));
                }

                if( objectp(ob) ) {
                        ob->set_amount(data["num"]);
                        if( ob->query_amount() )
                                message_vision("$N买下了" + ob->short() + "。\n", me);
                        else
                                message_vision("$N那里买下了一"+query("unit", ob)+
                                                query("name", ob)+"。\n",me);

                        ob->move(me, 1);
                        delete(kid+"/"+ks[i]);
                        save();
                        me->start_busy(1);
                        log_buyinfo(me, data["name"], value);
                        return "你从寄售柜取出了"+data["name"]+"("+data["id"]+") 。\n";
                }
        }
        return "现在" + environment(me)->short() + "的货架上并没有这样货物。\n";
}
