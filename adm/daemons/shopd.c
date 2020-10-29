// This program is a part of NT MudLIB
// 商业系统总控程序
// edit by smallfish 2002.3.17
// Updated by Vin for heros.cn
// Updated by Jjgod.
// Updated by Lonely@nitan.org

#include <ansi.h>
#include <config.h>
#include <getconfig.h>

/*
本文件为商业系统中店铺的主干程序
本文件提供以下文件调用：
/cmds/usr/shop.c                        店铺查询管理指令
/inherit/char/waiter.c                  伙计程序接口文件
/inherit/room/shop.c                    店铺程序接口文件

店铺以及伙计的程序存放路径：/clone/shop
店铺伙计继承文件：/inherit/char/waiter.c

店铺继承文件：/inherit/room/shop.c
店铺伙计产用 *.o 格式的文件存储，存储文件存放于：/data/shop
店铺主要变量：
string owner:           主人ID
int shop_type：         店铺状态(0 表示关闭)
mapping vendor_goods:           货物价格，keys 为货物的 base_name
mapping vendor_goods_num:       单个货物数量，keys 为货物的 base_name
int all_vendor_goods:           所有货物数量总和
mapping invite:                 贵宾的折扣，keys 为贵宾的 id
string *ban:                    黑户列表，keys 为黑户 id
*/

public mapping *query_shop();                                  // 返回店铺列表
public int is_inited();                                        // 返回店铺是否全部初始化
private int check_owner(string arg);                           // 检查店铺主人和店铺伙计主人是否相同
public int change_owner(object me,string arg,string owner);    // 修改店铺店主（店铺主人和店铺伙计主人）
public int is_owner(string owner);                             // 查看玩家 owner 是否店铺店主
public int close_all(object me);                               // 关闭所有店铺
public int close_shop(object me,string arg);                   // 关闭指定店铺
public int open_all(object me);                                // 开放所有店铺
public int open_shop(object me,string arg);                    // 开放指定店铺
public int reset_all(object me);                               // 初始化所有店铺
public int reset_shop(object me,string arg);                   // 初始化指定店铺
public int list_shop(object me);                               // 查询店铺
public string do_modify(object obj, object me, string arg);    // 修改店铺伙计的属性
public string do_stock(object ob, object me, string arg);      // 标价并出售货物
public string do_unstock(object ob, object me, string arg);    // 取下货物
public string do_list(object ob, object me, string arg);       // 查询货物
public int do_listall(object me);                              // 查所有商店货物
public int do_buy(object obj, object me, string arg);          // 购买货物
private int player_pay(object who, object target, int amount); // 付款，计算商业评价以及税率
public string do_jiezhang(object ob, object me);               // 结帐（店铺主人不在线时候的店铺收入）
public string list_invite(object ob, object me);               // 查询贵宾列表
public string do_invite(object ob, object me, string arg);     // 设置|取消 贵宾
public string list_ban(object ob, object me);                  // 查询黑户列表
public string do_ban(object ob, object me, string arg);        // 设置|取消 黑户
public string list_order(object ob,object me);                 // 店主显示预约
public string do_order(object ob,object me,string arg);        // 预约物品
private void destruct_it(object ob);
public void reset_goods(object obj);                              // 检查玩家摆摊物品
string makeup_space(string s,int max);
string *special_props = ({ "short", "long" });
string top;                                                     //最大销售额店铺名(例如清香园)

nosave mapping *all_shop = ({
        ([
                "id":             "扬州",
                "name":           "通天阁",
                "start_room":     "yangzhou_shop",
                "type":           "shop",
                "price":          800,
        ]),
        ([
                "id":             "北京",
                "name":           "瑞蚨祥",
                "start_room":     "beijing_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "长安",
                "name":           "同盛祥",
                "start_room":     "changan_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "洛阳",
                "name":           "天寰阁",
                "start_room":     "luoyang_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "成都",
                "name":           "清香园",
                "start_room":     "chengdu_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "襄阳",
                "name":           "聚义堂",
                "start_room":     "xiangyang_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "苏州",
                "name":           "采芝斋",
                "start_room":     "suzhou_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "杭州",
                "name":           "颐香斋",
                "start_room":     "hangzhou_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "福州",
                "name":           "聚春园",
                "start_room":     "fuzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "无锡",
                "name":           "聚丰园",
                "start_room":     "wuxi_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "开封",
                "name":           "福兴斋",
                "start_room":     "kaifeng_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "延平",
                "name":           "双溪楼",
                "start_room":     "yanping_shop",
                "type":           "shop",
                "price":          50000,
        ]),
        ([
                "id":             "泉州",
                "name":           "福人颐",
                "start_room":     "quanzhou_shop",
                "type":           "shop",
                "price":          50000,
        ]),
        ([
                "id":             "佛山",
                "name":           "天海楼",
                "start_room":     "foshan_shop",
                "type":           "shop",
                "price":          50000,
        ]),
        ([
                "id":             "衡阳",
                "name":           "祝融居",
                "start_room":     "hengyang_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "中州",
                "name":           "百鹤斋",
                "start_room":     "zhongzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "大理",
                "name":           "拨云堂",
                "start_room":     "dali_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "武昌",
                "name":           "悦新昌",
                "start_room":     "wuchang_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "灵州",
                "name":           "同福居",
                "start_room":     "lingzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "伊犁",
                "name":           "牛大碗",
                "start_room":     "yili_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "荆州",
                "name":           "五华楼",
                "start_room":     "jingzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
});

public mapping *query_shop()
{
        return all_shop;
}

public string query_top()
{
        return top;
}

public int is_inited()
{
        int i, is_ok;
        object shop;

        is_ok = 1;

        for (i = 0; i < sizeof(all_shop); i++)
        {
                shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

                if( query("short", shop) == query_top())continue;
                if( !shop || query("shop_type", shop) )
                {
                        is_ok = 0;
                        break;
                }
                else
                {
                        if( (query("vendor_goods", shop) &&
                             sizeof(query("vendor_goods", shop))>0) ||
                             query("all_vendor_goods", shop) ||
                             query("owner", shop) != "VOID_SHOP" )
                        {
                                is_ok = 0;
                                break;
                        }
                }
        }
        return is_ok;
}

private int check_owner(string arg)
{
        int i, have_it;
        object the_shop;
        string shop_owner;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }

        // 没有找到指定的店铺
        if (! have_it)
                return 0;

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (! the_shop)
                return 0;

        shop_owner = query("owner", the_shop);
        return 1;
}

public int change_owner(object me, string arg, string owner)
{
        int i, have_it;
        object the_shop;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }

        if (! have_it)
        {
                tell_object(me, "对不起，" + arg + "店铺并不存在。\n");
                return 1;
        }

        if (! check_owner(arg))
        {
                tell_object(me, "警告：" + arg + "店铺主人和店铺伙计主人数据异常，请仔细检查。\n");

                log_file("static/shop", sprintf("%s店铺数据异常，时间：%s。\n", arg, ctime(time())));
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("owner", owner, the_shop);
                the_shop->save();
                tell_object(me, arg + "店铺店主修改完毕。\n");
        } else
        {
                tell_object(me, arg + "店铺文件不存在，请仔细查看。\n");
                return 1;
        }

        return 1;
}

public int is_owner(string owner)
{
        int i;
        object shop;

        for (i = 0; i < sizeof(all_shop); i ++)
        {
                shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

                if (! objectp(shop))
                        return 0;

                if( query("owner", shop) == owner )
                        return 1;
        }
        return 0;
}

public int close_all(object me)
{
        int i;

        for (i = 0; i < sizeof(all_shop); i++)
        {
                close_shop(me, all_shop[i]["id"]);
        }

        return 1;
}

// 关闭店铺是修改店铺的 shop_type 为 0
public int close_shop(object me, string arg)
{
        int i, have_it;
        object the_shop;

        have_it = 0;

        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }

        if (! have_it)
        {
                tell_object(me, "对不起，" + arg + "店铺并不存在。\n");
                return 1;
        }

        if (! check_owner(arg))
        {
                tell_object(me, "警告：" + arg + "店铺主人和店铺伙计主人数据异常，请仔细检查。\n");
                log_file("static/shop",sprintf("%s店铺数据异常，时间：%s。\n", arg, ctime(time())));
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("shop_type", 0, the_shop);
                the_shop->save();
                tell_object(me, arg + "店铺成功关闭。\n");
        } else
        {
                tell_object(me, arg + "店铺文件不存在，请仔细查看。\n");
                return 1;
        }
        return 1;
}

public int open_all(object me)
{
        int i;
        for (i = 0; i < sizeof(all_shop); i++)
                open_shop(me, all_shop[i]["id"]);
        return 1;
}

// 开放店铺是修改店铺的 shop_type 为 1
public int open_shop(object me, string arg)
{
        int i, have_it;
        object the_shop;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (! have_it)
        {
                tell_object(me, "对不起，" + arg + "店铺并不存在。\n");
                return 1;
        }

        if (! check_owner(arg))
        {
                tell_object(me, "警告：" + arg + "店铺主人和店铺伙计主人数据异常，请仔细检查！\n");
                log_file("static/shop", sprintf("%s店铺数据异常，时间：%s。\n", arg, ctime(time())));
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("shop_type", 1, the_shop);
                the_shop->save();
                tell_object(me, arg + "店铺成功开放！\n");
        }
        else
        {
                tell_object(me, arg + "店铺文件不存在，请仔细查看！\n");
                return 1;
        }
        return 1;
}

public int reset_all(object me)
{
        int i;
        int topscore;
        object the_shop;

        topscore = 0;
        for (i=0; i<sizeof(all_shop);i++)
        {
                the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);
                if( query("score", the_shop)>topscore )
                {
                        topscore=query("score", the_shop);
                        top=query("short", the_shop);
                }
                reset_shop(me, all_shop[i]["id"]);
        }
        return 1;
}

// 初始化店铺包括：
// 关闭店铺
// 设置店铺和伙计的主人为空值
// 清除伙计的货物以及伙计的存款
// 清除伙计的贵宾和黑户
public int reset_shop(object me, string arg)
{
        int i, have_it;
        string *props, prop;
        object the_shop, the_waiter;
        mapping m;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (! have_it)
        {
                tell_object(me,"对不起，" + arg + "店铺并不存在。\n");
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("shop_type", 0, the_shop);
                set("owner", "VOID_SHOP", the_shop);
                set("balance", 0, the_shop);
                delete("vendor_goods", the_shop);
                delete("vendor_goods_num", the_shop);
                delete("all_vendor_goods", the_shop);
                delete("invite", the_shop);
                delete("ban", the_shop);
                delete("waiter", the_shop);
                delete("score", the_shop);

                the_shop->save();

                tell_object(me, arg + "店铺成功初始化！\n");
        } else
        {
                tell_object(me, arg + "店铺文件不存在，请仔细查看！\n");
                return 1;
        }

        the_waiter = present("huo ji", the_shop);
        if (the_waiter)
        {
                if( arrayp(m=query("waiter", the_shop)) &&
                        sizeof(props = keys(m)))
                {
                        foreach (prop in props)
                        {
                                if (prop == "name")
                                        the_waiter->set_name("店铺伙计", ({ "huo ji", "huo", "ji" }));
                                if (prop == "long")
                                        set("long", "他就是这家店铺的伙计。\n", the_waiter);
                                delete(prop, the_waiter);
                        }
                        delete("waiter", the_shop);
                }
                tell_object(me, arg + "伙计成功初始化！\n");
        } else
        {
                tell_object(me, arg + "店铺伙计不存在，请仔细查看！\n");
                return 1;
        }
        return 1;
}

public int list_shop(object me)
{
        int i;
        string arg, na, msg;
        object ob, the_shop;
        string str;

        msg = WHT "当前" + LOCAL_MUD_NAME() + "的店铺列表如下：\n" NOR;
        msg += HIC"≡" HIY "------------------------------------------------------------------------" HIC "≡\n" NOR;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                arg = all_shop[i]["id"];

                if (! check_owner(arg))
                        continue;

                the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

                if (! the_shop)
                        continue;

                if( objectp(ob=find_player(query("owner", the_shop))) &&
                        this_player()->visible(ob))
                        na=HIR+query("name", ob);
                else
                {
                        na = GRN "离线玩家";
                }

                msg += sprintf(WHT " 店铺：" HIG "%s[" HIW "%s" HIG "] " NOR ,
                                all_shop[i]["name"], arg);

               str=(query("shop_type", the_shop) &&
                               query("owner", the_shop) != "VOID_SHOP")?
                               HIG " 营业中 " NOR : HIY "暂不营业" NOR,
               msg += sprintf(HIG"%8s%s"NOR,str,makeup_space(str,8));

               msg += WHT " 销售积分：" HIC ;
               if( query("score", the_shop) <= 0 )
               str = HIY"暂无"NOR;
               else
               str=sprintf("%d",query("score", the_shop));
               msg += sprintf("%-6s%s",str,makeup_space(str,6));

               str=query("owner", the_shop) == "VOID_SHOP"?
                               HIC "风儿(系统)" NOR : na +
                               "("+query("owner", the_shop)+")"NOR,
               msg += sprintf(WHT "  店铺主人：" HIG "%-20s%s" NOR ,str,makeup_space(str,20));

               msg += "\n";
        }
        msg += HIC"≡"HIY"------------------------------------------------------------------------" HIC "≡\n" NOR;
        msg += WHT"总共有" + chinese_number(sizeof(all_shop)) + "家店铺。\n"NOR;
        tell_object(me, msg);
        return 1;
}

public string do_modify(object obj, object me, string arg)
{
        string item, msg;
        mapping dbase;
        object room;

        room = environment(obj);

        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if (! arg || sscanf(arg,"%s %s", item, msg) != 2)
                return "设定格式为：modify <项目> <内容>\n";

        if (CHINESE_D->check_control(msg))
                return "描述不可有控制符。\n";

        if (CHINESE_D->check_space(msg))
                return "描述必需不含空格。\n";

        if (CHINESE_D->check_return(msg))
                return "描述必需不含回车键。\n";

        msg = trans_color(msg, 1);
        msg = replace_string(msg, "$S$", BLINK);

        switch(item)
        {
        case "short":
                if (CHINESE_D->check_length(msg) > 10)
                        return "你所设定的名称太长了。\n";

                if (! is_chinese(filter_color(msg, 1)))
                        return "店铺的名称只能用中文。\n";

                set("apply/short", msg, room);

                room->save();
                return WHT "你为店铺重新设定好了名称。\n" NOR;

        case "long":
                if (CHINESE_D->check_length(msg) > 200)
                        return "你所设定的描述太长了。\n";

                set("apply/long", msg+NOR"\n", room);

                room->save();
                return WHT "你为店铺重新设定好了描述。\n" NOR;

        case "desc":
                if (CHINESE_D->check_length(msg) > 200)
                        return "你所设定的描述太长了。\n";

                set("long", sort_msg(msg+NOR"\n"), obj);
                set("waiter/long", sort_msg(msg+NOR"\n"), room);

                room->save();
                return WHT "你为店铺伙计设定好了描述。\n" NOR;

        case "nickname" :
                if (CHINESE_D->check_length(msg) > 20)
                        return "你所设定的描述太长了。\n";

                set("nickname", msg+NOR, obj);
                set("waiter/nickname", msg+NOR, room);

                room->save();
                return WHT "你为店铺伙计设定好了绰号。\n" NOR;

        case "title" :
                if (CHINESE_D->check_length(msg) > 20)
                        return "你所设定的描述太长了。\n";

                set("title", msg+NOR, obj);
                set("waiter/title", msg+NOR, room);

                room->save();
                return WHT "你为店铺伙计设定好了头衔。\n" NOR;

        case "name" :
                if (CHINESE_D->check_length(msg) > 10)
                        return "你所设定的描述太长了。\n";

                if (! is_chinese(filter_color(msg, 1)))
                        return "店铺伙计的姓名只能用中文。\n";

                dbase = obj->query_entire_dbase();
                dbase["name"] = msg;

                set("waiter/name", msg, room);

                room->save();
                return WHT "你为店铺伙计设定好了名字。\n" NOR;

        case "gender" :
                if (msg != "男性" && msg != "女性" && msg != "无性")
                        return "性别只能是男性、女性或无性，没有其他性别的说。\n";

                set("gender", msg, obj);
                set("waiter/gender", msg, room);

                room->save();
                return WHT "你为店铺伙计设定好了性别。\n" NOR;
        }
        return "你要修改什么？\n";
}

/*
public string do_stock(object ob, object me, string arg)
{
        object obj, goods, obj2;
        mixed value;
        mapping all_goods, all_goods_num;
        object room;
        mapping data;

        room = environment(ob);

        // intp(value) 为gold, stringp(value) 为$NT
        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if (! arg || (sscanf(arg, "%s value %d", arg, value) != 2 &&
            sscanf(arg, "%s nt %s", arg, value) != 2) )
                return "指令格式：stock <货物> value * ( 其中 * 是以铜板作单位的价格 )或\n"
                       "          stock <货物> nt * ( 其中 * 是以 $NT 作单位的价格 )\n";

        if (! value)
                return "指令格式：stock <货物> value * ( 其中 * 是以铜板作单位的价格 )或\n"
                       "          stock <货物> nt * ( 其中 * 是以 $NT 作单位的价格 )\n";

        if (intp(value) && value > 100000000 && !wizardp(me))
                return "店铺最多标价一万两黄金，你就别那么心黑了吧。\n";

        if (stringp(value) && to_int(value) < 0 || to_int(value) > 1000000)
                return "店铺最多标价一百万$NT，你就别那么心黑了吧。\n";

        if (! (goods = present(arg, me)) || ! objectp(goods))
                return "你身上并没有这个货物啊！\n";

        if( query("no_sell", goods) )
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        if( query("no_get", goods) || query("no_drop", goods) ||
            query("no_put", goods) || query("no_beg", goods) ||
            query("no_steal", goods) || query("no_drop", goods) ||
            query("item_make", goods) || query("owner", goods) )
                return "这个东西摆不上货架，就暂时别拿出来卖啦。\n";

        if (goods->is_item_make())
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        if( query("wiz_only", goods) && !wizardp(me) )
                return "这个东西只能在巫师商店里卖。\n";

        if (goods->is_character())
                return "你不能贩卖活物。\n";

        if( query("money_id", goods) )
                return "你把钱也拿来出售？\n";

        if( query("all_vendor_goods", room) >= 80 )
                return "你店铺上的东西太多了，先收几种货物再摆吧。\n";

        if (goods->is_dynamic_equip()) //动态物品保留data
                data = goods->query_entire_dbase();

        all_goods=query("vendor_goods", room);

        if (! all_goods)
                all_goods = ([ ]);

        all_goods_num=query("vendor_goods_num", room);
        if (! all_goods_num) all_goods_num = ([ ]);

        // 动态物品处理不能以base_name为依据

        all_goods[base_name(goods)] = value;
        all_goods_num[base_name(goods)] += 1;

        set("vendor_goods", all_goods, room);
        set("vendor_goods_num", all_goods_num, room);
        addn("all_vendor_goods", 1, room);

        message_vision(HIW "$N" HIW "将『" HIG + goods->name(1) + HIW "』标上" HIY +
                (intp(value) ? MONEY_D->price_str(value) : value+"$NT") + HIW "的价格开始出售。\n" NOR, me);
        room->save();
        if (goods->query_amount() && goods->query_amount() > 1)
        {
                goods->set_amount((int)goods->query_amount() - 1);
                obj2 = new(base_name(goods));
                obj2->set_amount(1);
                destruct(obj2);
        }
        else destruct(goods);
        return "你摆置好了货物。\n";
}

public string do_unstock(object ob, object me, string arg)
{
        object obj, goods, room;
        int i, amount, value, have_it = 0;
        mapping all_goods, all_goods_num;
        string *goods_key, ob_file;

        seteuid(getuid());
        room = environment(ob);
        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if (! arg)
                return "指令格式：unstock <货物>\n";

        if( !query("all_vendor_goods", room) )
                return "你现在还没有摆上任何货物。\n";

        all_goods=query("vendor_goods", room);
        all_goods_num=query("vendor_goods_num", room);

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED && !wizardp(me))
                return "你身上的东西太多了，没法从货架上取东西。\n";

        all_goods=query("vendor_goods", room);

        if (! all_goods)
                all_goods = ([ ]);

        all_goods_num=query("vendor_goods_num", room);

        if (! all_goods_num)
                all_goods_num = ([ ]);

        goods_key = keys(all_goods);

        if (arrayp(goods_key))
        {
                for (i = 0; i < sizeof(goods_key); i++)
                {
                        if (goods_key[i]->id(arg))
                                ob_file = goods_key[i];
                        else

                        if (filter_color(goods_key[i]->name(1)) == arg)
                                ob_file = goods_key[i];
                }
        }

        if (! ob_file)
                return "现在"+query("short", environment(ob))+"的货架上并没有这样货物。\n";

        goods = new(ob_file);
        goods->set_amount(1);

        addn("all_vendor_goods", -1, room);
        all_goods_num[base_name(goods)] -= 1;

        if (all_goods_num[base_name(goods)] == 0)
        {
                map_delete(all_goods, base_name(goods));
                map_delete(all_goods_num, base_name(goods));
        }

        message_vision(HIW "$N" HIW "将『" HIG + goods->name(1) + HIW"』从货架上取下来不卖了。\n" NOR, me);

        set("vendor_goods", all_goods, room);
        set("vendor_goods_num", all_goods_num, room);
        room->save();

        if (! goods->move(me))
        {
                goods->move(environment(me));
                tell_object(me, "可是你已经拿不动了，只好把" + goods->name(1) + NOR "放在地上。\n");
        }
        return "你取好了货物。\n";
}

public string do_list(object ob, object me, string arg)
{
        mapping goods, goods_num;
        string *gks;
        object *obs, *inv, room;
        string msg;
        int i, have_vendor = 0;

        mapping price;
        mapping unit;
        mapping count;
        string  short_name;
        string  prefix;
        string  *dk;

        room = environment(ob);
        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if( query("ban", room) &&
                member_array(query("id", me),query("ban", room)) != -1 )
                return "你是这家店铺不受欢迎的人物，无法购买东西。\n";

        if( !query("all_vendor_goods", room) )
                return "现在"+query("short", room)+"目前并没有出售任何货物。\n";

        goods=query("vendor_goods", room);

        if (! goods)
                goods = ([]);

        goods_num=query("vendor_goods_num", room);

        if (! goods_num)
                goods_num = ([]);

        count   = ([]);
        unit    = ([]);
        price   = ([]);

        gks = keys(goods);
        for (i = 0; i < sizeof(gks); i++)
        {
                object gob;
                call_other(gks[i], "???");

                if (! objectp(find_object(gks[i])))
                {
                        log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                        continue;
                }

                gob = find_object(gks[i]);
                short_name=gob->name(1)+"("+query("id", gob)+")";

                if( query("base_unit", gob) )
                        prefix = "base_";
                else
                        prefix = "";

                unit+=([short_name:query(prefix+"unit", gob)]);
                price += ([ short_name : goods[gks[i]] ]);
                count += ([ short_name : goods_num[gks[i]] ]);
        }

        msg = "该店铺目前出售以下物品：\n";
        msg += "-------------------------------------------------------\n";
        dk = sort_array(keys(unit), 1);

        for (i = 0; i < sizeof(dk); i++)
        {
                mixed p;
                p = price[dk[i]];
                msg += sprintf("%" + sprintf("%d", (30 + color_len(dk[i])) ) + "-s：每%s%s" CYN "(现货%s)\n" NOR,
                               dk[i], unit[dk[i]],
                               intp(p) ? MONEY_D->price_str(p) : (p + "$NT"),
                               chinese_number(count[dk[i]]) + unit[dk[i]]);
        }

        msg += "-------------------------------------------------------\n";

        if( query("id", me) == query("owner", room) )
                msg+="总共"+chinese_number(query("all_vendor_goods", room))+"件货物。\n";

        if( query("invite/"+query("id", me, room)) )
                msg+=WHT"您是本店贵宾，购买所有货物均享受"HIW+chinese_number(query("id", room, query("invite/"+me)))+HIW"折"NOR+WHT"的优惠。\n"NOR;
        return msg;
}

public int do_buy(object obj, object me, string arg)
{
        mapping goods,goods_num;
        int amount;
        int val_factor;
        mixed value;
        string ob_file, *goods_key;
        object *obs,ob, env;
        string my_id;
        int i;
        object room;

        room = environment(obj);
        if( !query("shop_type", room) )
        {
               tell_object(me, "对不起，该店铺目前已经被巫师关闭。\n");
               return 1;
        }

        if( query("ban", room) &&
                member_array(query("id", me),query("ban", room)) != -1 )
        {

               tell_object(me, "你是这家店铺不受欢迎的人物，无法购买东西。\n");
               return 1;
        }

        if(me->is_busy())
        {
                tell_object(me, "什么事都得等你忙完再说吧！\n");
                return 1;
        }

        if (! arg)
        {
                tell_object(me, "你要买什么东西？\n");
                return 1;
        }

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
        {
                tell_object(me, "你身上的东西太多了，先处理一下再买东西吧。\n");
                return 1;
        }

        goods=query("vendor_goods", room);

        if (! goods) goods = ([ ]);

        goods_num=query("vendor_goods_num", room);

        if (!goods_num) goods_num = ([]);

        goods_key = keys(goods);

        if (arrayp(goods_key))
        {
                for (i = 0; i < sizeof(goods_key); i++)
                {
                        if (goods_key[i]->id(arg)) ob_file = goods_key[i];
                        else
                                if (filter_color(goods_key[i]->name(1)) == arg)
                                        ob_file = goods_key[i];
                }
        }

        if (! ob_file)
        {
                tell_object(me, "该店铺并没有出售这样货物。\n");
                return 1;
        }

        value = goods[ob_file];

        // 如果是贵宾，则有优惠
        if( query("invite/"+query("id", me, room)) )
        {
                if (intp(value))
                        value=value*query("invite/"+query("id", me, room))/10;
                else
                        value=to_string(to_int(value)*query("invite/"+query("id", me, room))/10);
        }

        ob = new(ob_file);
        call_out("destruct_it", 0, ob);

        if (intp(value))
        {
                switch (player_pay(me, obj, value))
                {
                case 0:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "冷笑道：穷光蛋，一边呆着去。\n" NOR);
                        return 1;

                case 2:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "皱眉道：您还有没有零钱啊？银票我可找不开。\n" NOR);
                        return 1;

                default:
                        if (ob->query_amount())
                        {
                                message_vision("$N从$n那里买下了" + ob->short() + "。\n", me, obj);
                        }
                        else
                        {
                                message_vision("$N从$n那里买下了一"+query("unit", ob)+query("name", ob)+"。\n",me,obj);
                        }

                        ob->move(me, 1);
                        goods_num[ob_file] -= 1;

                        if (goods_num[ob_file] == 0)
                        {
                                map_delete(goods, ob_file);
                                map_delete(goods_num, ob_file);
                        }

                        set("vendor_goods", goods, room);
                        set("vendor_goods_num", goods_num, room);
                        addn("all_vendor_goods", -1, room);
                }
        } else
        {
                if (!MEMBER_D->player_pay(me, to_int(value), obj))
                {
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "冷笑道：你没有足够的$NT，还是先去冲值吧。\n" NOR);
                        return 1;
                }
                if (ob->query_amount())
                {
                        message_vision("$N从$n那里买下了" + ob->short() + "。\n", me, obj);
                }
                else
                {
                        message_vision("$N从$n那里买下了一"+query("unit", ob)+query("name", ob)+"。\n",me,obj);
                }

                ob->move(me, 1);
                goods_num[ob_file] -= 1;

                if (goods_num[ob_file] == 0)
                {
                        map_delete(goods, ob_file);
                        map_delete(goods_num, ob_file);
                }

                set("vendor_goods", goods, room);
                set("vendor_goods_num", goods_num, room);
                addn("all_vendor_goods", -1, room);
        }
        me->start_busy(1);
        room->save();
        return 1;
}
*/
public int player_pay(object who, object target, int amount)
{
        object t_ob, g_ob, s_ob, c_ob, owner;
        int tc, gc, sc, cc, left;
        int v;
        int pay_amount;

        seteuid(getuid());

        if (amount >= 100000 && t_ob = present("cash_money", who))
                tc = t_ob->query_amount();
        else
        {
                tc = 0;
                t_ob = 0;
        }

        if (g_ob = present("gold_money", who))
                gc = g_ob->query_amount();
        else
                gc = 0;

        if (s_ob = present("silver_money", who))
                sc = s_ob->query_amount();
        else
                sc = 0;

        if (c_ob = present("coin_money", who))
                cc = c_ob->query_amount();
        else
                cc = 0;

        v = cc + sc * 100 + gc * 10000;

        if (amount < 100000 && v < amount)
        {
                if (present("cash_money", who))
                        return 2;
                else
                        return 0;
        }

        v += tc * 100000;

        if (v < amount)
                return 0;
        else {
                left = v - amount;
                if (tc)
                {
                        tc = left / 100000;
                        left %= 100000;
                }
                gc = left / 10000;
                left = left % 10000;
                sc = left / 100;
                cc = left % 100;

                if (t_ob && ! g_ob && gc)
                {
                        g_ob = new(GOLD_OB);
                        g_ob->move(who, 1);
                }

                if (t_ob)
                        t_ob->set_amount(tc);

                if (g_ob)
                        g_ob->set_amount(gc);
                else
                        sc += (gc * 100);

                if (s_ob)
                {
                        s_ob->set_amount(sc);
                } else
                if (sc)
                {
                        s_ob = new(SILVER_OB);
                        s_ob->set_amount(sc);
                        s_ob->move(who, 1);
                }

                if (c_ob)
                {
                        c_ob->set_amount(cc);
                } else
                if (cc)
                {
                        c_ob = new(COIN_OB);
                        c_ob->set_amount(cc);
                        c_ob->move(who, 1);
                }
                /*
                // 计算税率，每 10 两黄金加收 10% 的税
                if (amount >= 500000)
                        pay_amount = amount * 5 / 10;
                else if (amount >= 400000)
                        pay_amount = amount * 6 / 10;
                else if (amount >= 300000)
                        pay_amount = amount * 7 / 10;
                else if (amount >= 200000)
                        pay_amount = amount * 8 / 10;
                else if (amount >= 100000)
                        pay_amount = amount * 9 / 10;
                else
                        pay_amount = amount;
                */
                pay_amount = amount * 99 / 100;

                if( owner=query("owner", find_player(environment(target))) )
                {
                        addn("balance", pay_amount, owner);
                        addn("trade_balance", pay_amount, owner);

                        if (query_ip_number(owner) != query_ip_number(who))
                                addn("vendor_score", pay_amount/10000, owner);
                        addn("score", pay_amount/10000, environment(target));
                } else
                {
                        addn("balance", pay_amount, environment(target));
                        addn("score", pay_amount/10000, environment(target));
                }
                log_file("shop_log",sprintf("%-20s在%6s花%9i买下",query("name", who)+"("+query("id", who)+")",query("short", environment(who)),amount));
                return 1;
        }
}

public string do_jiezhang(object ob, object me)
{
       int amount;
       object room;

       room = environment(ob);
       if( !query("shop_type", room) )
               return "对不起，该店铺目前已经被巫师关闭。\n";

       amount=query("balance", room);

       if (amount < 1) return "您不在的时候还没有任何的收入。\n";

       addn("balance", amount, me);
       addn("trade_balance", amount, me);
       addn("vendor_score", amount/10000, me);

       tell_object(me, HIY"您不在线时共有"+MONEY_D->price_str(amount)+HIY"的收入，现已全部转入您的银号。\n"NOR);
       set("balance", 0, room);
       room->save();
       return "结帐完毕，请即时核对数目。\n";
}

public string list_invite(object ob, object me)
{
        int i;
        string msg, *invite_key;
        mapping invite;
        object room;

        room = environment(ob);
        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        invite=query("invite", room);

        if (! invite || sizeof(invite) < 1)
                return "您并没有设定任何的贵宾。\n";

        msg = HIC "您所定义的贵宾有以下几位：\n" NOR;
        msg += HIC "≡" HIY "------------------------" HIC "≡\n" NOR;
        invite_key = sort_array(keys(invite), 1);

        for (i = 0; i < sizeof(invite_key); i++)
        {
                msg += sprintf(CYN "%-20s  " WHT "%s折\n" NOR,
                               invite_key[i], chinese_number(invite[invite_key[i]]));
        }

        msg += HIC "≡" HIY "------------------------" HIC "≡\n" NOR;
        msg += HIC "总共有 " HIY + sizeof(invite) + HIC " 个贵宾。\n" NOR;
        return msg;
}

public string do_invite(object ob, object me, string arg)
{
        int num;
        object body, room;

        room = environment(ob);

        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if (! sscanf(arg, "%s %d", arg, num) == 2)
                return "指令格式：invite <id> <折数>\n";

        if (num < 1 || num > 10)
                return "指令格式：invite <id> <折数>\n";

        if (num == 10)
        {
                if( !query("invite/"+arg, room) )
                        return CYN + ob->name(1) + NOR + CYN "对你说道：老板，那 " + arg + " 本来就不是我们店的贵宾啊。\n" NOR;

                delete("invite/"+arg, room);
                room->save();
                return CYN + ob->name(1) + NOR + CYN "翻开帐簿用划了划，奸笑道：老板，已经按照你的吩咐取消掉 " + arg + " 的贵宾资格了。\n" NOR;
        }

        if( sizeof(query("invite", room)) >= 30 )
                return "您已经设定了三十个贵宾，把不常来的先划掉吧。\n";

        set("invite/"+arg, num, room);
        room->save();

        return CYN + ob->name(1) + NOR + CYN "翻开帐簿边写边说道：老板，已经按照你的吩咐对 " WHT + arg + CYN " 实行" + HIY + chinese_number(num) + "折" + NOR + CYN "优惠。\n" NOR;
}

public string list_ban(object ob, object me)
{
        int i;
        string msg, *ban;
        object room;

        room = environment(ob);

        if( !query("shop_type", room) )
               return "对不起，该店铺目前已经被巫师关闭。\n";

        ban=query("ban", room);

        if (! ban || sizeof(ban) < 1)
        {
                msg = "您并没有设定任何的黑户。\n";
                return msg;
        }
        msg = HIC "您所定义的黑户有如下玩家：\n" NOR;
        msg += HIC "≡" HIY "------------------------" HIC "≡\n" NOR;
        for (i = 0;i < sizeof(ban);i++)
        {
                msg += sprintf(CYN "  %s\n" NOR, ban[i]);
        }
        msg += HIC "≡" HIY "------------------------" HIC "≡\n" NOR;
        msg += HIC "总共有 " HIY + sizeof(ban) + HIC " 个黑户。\n" NOR;
        return msg;
}

public string do_ban(object ob, object me, string arg)
{
        string the_id, type, *ban;
        object room;

        room = environment(ob);

        if( !query("shop_type", room) )
               return "对不起，该店铺目前已经被巫师关闭。\n";

        ban=query("ban", room);

        if (! ban)
                ban = ({ });

        if (sscanf(arg, "%s %s", type, the_id) == 2 && type == "-")
        {
                if (member_array(the_id, ban) == -1)
                        return CYN + ob->name(1) + NOR + CYN "对你说道：老板，那 " + arg + " 本来就不是我们店的黑户啊。\n" NOR;

                ban -= ({ the_id });
                set("ban", ban, room);
                room->save();
                return CYN + ob->name(1) + NOR + CYN "翻开帐簿划了划，对你赔笑道：老板，已经取消了 " + the_id + " 黑户身份。\n" NOR;
        }

        if (member_array(arg, ban) != -1)
                return CYN + ob->name(1) + NOR + CYN "奸笑着道：老板，您忘记了？那" + arg + "早已被列为黑户啦。\n" NOR;

        if( sizeof(query("ban", ob)) >= 30 )
                return "您已经设定了三十个黑户，还是先划掉一些吧。\n";

        ban += ({ arg });
        set("ban", ban, room);
        room->save();
        return CYN + ob->name(1) + NOR + CYN "翻开帐簿边写边说道：老板，已经按照你的吩咐将 " WHT + arg + CYN " 列为了黑户。\n"NOR;
}

public string do_order(object ob,object me,string arg)
{
        object room;
        string str;
        string ab;
        string buyer,obname;
        string *clist;

        room = environment(ob);

        if( !query("shop_type", room) )
               return "对不起，该店铺目前已经被巫师关闭。\n";

        if( query("id", me) == query("owner", room) )
        {
                //店主操作
                if (sscanf(arg,"%s %s",ab,buyer)!=2)
                        return "删除订单内容命令： order - 顾客id [某一商品]\n";

                if (ab!="-")
                        return "删除订单内容命令： order - 顾客id [某一商品]\n";


                if (sscanf(buyer,"%s %s",buyer,obname)==2)
                {
                        if( !arrayp(query("order/"+buyer, room)) )
                        return "顾客"+buyer+"并没有定购过商品。\n";
                        clist=query("order/"+buyer, room);
                        if (member_array(obname,clist)==-1)
                                return "顾客"+buyer+"并没有定购过"+HIC+obname+NOR+"这样商品。\n";
                        clist -= ({ obname });
                        if (sizeof(clist)>0)
                        set("order/"+buyer, clist, room);
                        else delete("order/"+buyer, room);
                        room->save();
                        return "清除顾客"+buyer+"定购"+HIC+obname+NOR+"的消息。\n";
                }
                else
                {
                        if( !arrayp(query("order/"+buyer, room)) )
                        return "顾客"+buyer+"并没有定购过商品。\n";
                        delete("order/"+buyer, room);
                        room->save();
                        return "清除顾客"+buyer+"的所有定购消息。\n";
                }
        }
        else
        {
                buyer=query("id", me);
                clist=query("order/"+buyer, room);
                if (sscanf(arg,"- %s",arg)==1)
                {
                        if (!arrayp(clist) || member_array(arg,clist)==-1)
                        return "你并没有定购这样商品。\n";
                        clist -= ({arg});
                        if (sizeof(clist)>0)
                        set("order/"+buyer, clist, room);
                        else delete("order/"+buyer, room);
                        room->save();
                        return "清除定购"+HIC+arg+NOR+"的消息。\n";
                }
                if (arrayp(clist))
                {
                        if (member_array(arg,clist)>=0)
                        return "你已经定购过了"+arg+"。\n";
                        if (sizeof(clist)>20)
                        return "你在这个店铺定购的东西已经很多了，等店主先处理完吧。\n";
                }
                else clist = ({});
                clist += ({ arg });
                set("order/"+buyer, clist, room);
                room->save();
                tell_object(find_player(query("owner", room)),"店里有新的定购消息了，快去处理吧。\n");
                return "你在"+query("short", room)+"定购商品"+arg+"成功，请等待店主处理。\n";
        }
}
public string list_order(object ob,object me)
{
        mapping orders;
        int i;
        string str;
        string *korder;
        object room;
        string *clist;

        room = environment(ob);
        if( !query("shop_type", room) )
               return "对不起，该店铺目前已经被巫师关闭。\n";

        if( query("id", me) != query("owner", room) && !wizardp(me) )
        {
                clist = query("order/"+query("id", me), room);
                if (!arrayp(clist) || sizeof(clist)<1)
                return "你想定购什么？order 商品名称\n";
                str=HIW"你已经在"+query("short", room)+"定购了以下物品：\n"NOR;
                str += implode(clist,"\n");
                str += "\n";
                return str;
        }

        if( !mapp(orders=query("order", room)) || sizeof(orders)<1 )
                return "目前没有任何定购消息。\n";

        str = HIG"当前店铺定购消息如下：\n"NOR;
        korder = keys(orders);
        for (i=0;i<sizeof(orders);i++)
        {
                if (arrayp(orders[korder[i]]))
                {
                        str += HIW"玩家"+korder[i]+"要求购买：\n"NOR;
                        str += implode(orders[korder[i]],"\n");
                        str += "\n";
                }
        }
        str += HIC"处理顾客定购消息请用 order - 顾客id [商品名称]\n"NOR;
        return str;
}

private void destruct_it(object ob)
{
        if (! ob || environment(ob))
                return;

        destruct(ob);
}
public string do_list_all(object me,string arg)
{
        mapping goods, goods_num;
        string *gks;
        string name;
        object *obs, *inv, ob, obj, *all_user;
        string msg, err;
        int i, j, have_vendor = 0;
        int is_ok = 0;
        int have_it = 0;

        mapping price;
        mapping unit;
        mapping count;
        string  short_name;
        string  prefix;
        string  *dk;

        msg = WHT "泥潭所有店铺，查询货物 " + arg + " 的结果如下：\n" NOR;
        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;

        for (j = 0; j < sizeof(all_shop); j++)
        {
                have_it = 0;
                name = all_shop[j]["name"] + "(" + all_shop[j]["id"] + ") ：";
                ob = get_object(SHOP_DIR + all_shop[j]["start_room"]);
                if (! ob) continue;
                if( !query("shop_type", ob) )
                {
                        // destruct(ob);
                        continue;
                }
                if( query("ban", ob) &&
                    member_array(query("id", me),query("ban", ob)) != -1 )
                {
                        // destruct(ob);
                        continue;
                }

                if( !query("all_vendor_goods", ob) )
                {
                        // destruct(ob);
                        continue;
                }

                goods=query("vendor_goods", ob);
                if (! goods) goods = ([]);
                goods_num=query("vendor_goods_num", ob);
                if (! goods_num) goods_num = ([]);

                count   = ([]);
                unit    = ([]);
                price   = ([]);

                gks = keys(goods);
                for (i = 0; i < sizeof(gks); i++)
                {
                        object gob;
                        is_ok = 0;
                        err = call_other(gks[i], "???");
                        if (err)
                        {
                                log_file("user_vendor", sprintf("%s ERROR ** \n%s\n", gks[i], err));
                                continue;
                        }
                        if (! objectp(find_object(gks[i])))
                        {
                                log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                                continue;
                        }
                        gob = find_object(gks[i]);

                        if (gob->id(arg))
                        {
                                is_ok = 1;
                                have_it = 1;
                        }
                        else if (filter_color(gob->name(1)) == arg)
                        {
                                is_ok = 1;
                                have_it = 1;
                        }

                        if (! is_ok)
                                continue;

                        short_name=gob->name(1)+"("+query("id", gob)+")";
                        if( query("base_unit", gob) )
                                prefix = "base_";
                        else
                                prefix = "";
                        unit+=([short_name:query(prefix+"unit", gob)]);
                        price += ([ short_name : goods[gks[i]] ]);
                        count += ([ short_name : goods_num[gks[i]] ]);
                }
                // destruct(ob);
                if (! have_it) continue;
                dk = sort_array(keys(unit), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        int p;
                        p = price[dk[i]];
                        msg += sprintf(" %-6s%" + sprintf("%d", (30 + color_len(dk[i]))) +
                               "-s：每%s" HIY "%s\n" NOR,
                               name, dk[i], unit[dk[i]], MONEY_D->price_str(p));
                }
                msg += "------------------------------------------------------------------------\n";
        }
        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;

        msg += WHT "泥潭所有小贩子查询货物 " + arg + " 结果如下：\n" NOR;

        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;
        all_user=filter_array(users(),(:query_temp("on_bantan", $1):));
        if (sizeof(all_user))
        {
                for (j = 0;j < sizeof(all_user);j ++)
                {
                        obj = all_user[j];
                        goods=query("vendor_goods", obj);

                        if (! goods) continue;

                        gks = keys(goods);
                        for (i = 0;i < sizeof(gks);i++)
                        {
                                if (! present(query("id", get_object(gks[i])), obj))
                                        map_delete(goods,gks[i]);
                        }

                        set("vendor_goods", goods, obj);
                        goods=query("vendor_goods", obj);

                        if (! goods) continue;

                        gks = keys(goods);
                        for (i = 0; i < sizeof(gks); i++)
                        {
                                object gob;
                                is_ok = 0;
                                call_other(gks[i], "???");
                                if (! objectp(find_object(gks[i])))
                                {
                                        log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                                        continue;
                                }
                                gob = find_object(gks[i]);


                                if (gob->id(arg))
                                {
                                        is_ok = 1;
                                        have_it = 1;
                                }
                                else if (filter_color(gob->name(1)) == arg)
                                {
                                        is_ok = 1;
                                        have_it = 1;
                                }

                                if (! is_ok)
                                        continue;

                                short_name=gob->name(1)+"("+query("id", gob)+")";
                                if( query("base_unit", gob) )
                                        prefix = "base_";
                                else
                                        prefix = "";
                                unit+=([short_name:query(prefix+"unit", gob)]);
                                price += ([ short_name : goods[gks[i]] ]);
                        }

                        if (! is_ok) continue;

                        name = obj->name();
                        name += "(" + (environment(obj)?environment(obj)->short():"不明") + ")：";
                        dk = sort_array(keys(unit), 1);
                        for (i = 0; i < sizeof(dk); i++)
                        {
                                int p;
                                p = price[dk[i]];
                                msg += sprintf(" %-20s%" + sprintf("%d", (30 + color_len(dk[i]))) +
                                                "-s：每%s%s" CYN "\n" NOR,
                                                name, dk[i], unit[dk[i]], MONEY_D->price_str(p));
                        }
                        msg += "------------------------------------------------------------------------\n";
                }
        }

        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;

        return msg;
}

public string check_shop_status()
{
        int i, profit, tax, all_profit, all_tax;
        object the_shop;
        string msg;

        all_profit = 0;
        all_tax = 0;

        msg = "\n" + HIC + LOCAL_MUD_NAME() + "所有商店，本届营业状况列表如下：\n" NOR;
        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;
        msg += sprintf(HIC " %-14s%-30s%s\n" NOR,"店名","利润","交税");
        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;
        for (i = 0;i < sizeof(all_shop);i++)
        {
                the_shop = get_object(SHOP_DIR + all_shop[i]["start_room"]);

                if (! the_shop) continue;

                profit=query("check_shop_profit", the_shop)/10000*10000;
                all_profit += profit / 10000;
                tax=query("check_shop_tax", the_shop)/10000*10000;
                all_tax += tax / 10000;

                msg += sprintf(HIW " %-14s" HIY "%-30s%s\n" NOR,
                               all_shop[i]["name"] + "店铺",
                               profit ? MONEY_D->money_str(profit) : "零",
                               tax ? MONEY_D->money_str(tax) : "零");

                // destruct(the_shop);
        }
        msg += HIC "≡" HIY "--------------------------------------------------------------------" HIC "≡\n" NOR;
        msg += sprintf(HIC "%-14s%-30s%s\n\n" NOR,
                       chinese_number(sizeof(all_shop)) + "家店铺",
                       chinese_number(all_profit) + "两黄金",
                       chinese_number(all_tax) + "两黄金");
        return msg;
}


public void reset_goods(object obj)
{
        mapping goods;
        string *gks;
        object ob;
        int i;

        if (! obj ) return;
        goods=query("vendor_goods", obj);
        if (! goods ) return;
        gks = keys(goods);
        for (i = 0; i < sizeof(gks); i++)
        {
                if (!objectp(ob = find_object(gks[i]))  ||
                    !objectp(environment(ob)) ||
                     environment(ob) != obj )
                map_delete(goods, gks[i]);
        }
        set("vendor_goods", goods, obj);
}
string makeup_space(string s,int max)
{
        string *ansi_char = ({
                BLK,   RED,   GRN,   YEL,   BLU,   MAG,   CYN,   WHT,
                BBLK,  BRED,  BGRN,  BYEL,  BBLU,  BMAG,  BCYN,
                       HIR,   HIG,   HIY,   HIB,   HIM,   HIC,   HIW,
                       HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                NOR
        });

        string space = s;
        int i, space_count;

        for (i = 0; i < sizeof(ansi_char); i ++)
                space = replace_string(space, ansi_char[i], "", 0);

        space_count = sizeof(s) - sizeof(space);
        if (sizeof(s) >= max)
                space_count = max - sizeof(space);

        space = "";

        for (i = 0; i < space_count; i ++) space += " ";
        return space;
}
