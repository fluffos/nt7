// This program is a part of NT MudLIB
// goodsd.c
// Written by Lonely@nitan.org

#include <ansi.h>
#include <command.h>

inherit F_SAVE;
inherit F_DBASE;

#define NAME            0
#define ID              1
#define VALUE           2
#define TYPE            3
#define FILE            4
#define DESC            5

#define VIP1_RATE       95
#define VIP2_RATE       88
#define VIP3_RATE       80
#define ACTS_RATE       80
#define GOODS_FILE      CONFIG_DIR "goods_list"

string query_save_file() { return DATA_DIR "goodsd"; }

class goods {
        string id;
        string name;
        int value;
        string file;
        string type;
        string desc;
        int number;
}

int rate = 100;
mapping sp_items = ([]);
nosave string *actions = ({});
nosave class goods *all_goods = ({});
void init_goods();
void init_actions();
int clean_up() { return 1; }
void set_rate(mixed r)
{
        if( stringp(r) ) rate = to_int(r);
        else if( intp(r) ) rate = r;
        else rate = 100;
}

void set_item_value(string arg, int value)
{
        sp_items[arg] = value;
}

int query_rate() { return rate; }

void remove() { save(); }

void create()
{
        seteuid(ROOT_UID);
        set("name", "王者商城");
        restore();
        init_goods();
        init_actions();
}

void init_goods()
{
        class goods item;
        string *all, *tmp;
        string file;
        string line;
        int i, n;

        all_goods = ({});

        if( file_size(GOODS_FILE) <= 0 ) {
                log_file("static/goods",sprintf("GOODS_D: GOODS_FILE no exits or havn't content.%s\n",
                        ctime(time())));
                return;
        }

        file = read_file(GOODS_FILE);
        if( !stringp(file) ) return;

        file = replace_string(file, "\r", "");
        all =  filter_array(explode(file, "\n") - ({ "" }), (: $1[0] != '#' :));
        if( !n = sizeof(all) ) {
                log_file("static/goods",sprintf("GOODS_D: Have not valid goods. %s\n",
                        ctime(time())));
                return;
        }

        for( i=0;i<n;i++ ) {
                reset_eval_cost();
                line = all[i];

                //line = remove_fringe_blanks(line);
                while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                tmp = explode(line, ":");
                if( sizeof(tmp) < 4 ) {
                        log_file("static/goods", sprintf("%s isn't a full line.\n", line));
                        break;
                }

                item = new(class goods);
                item->name = tmp[NAME];
                item->id = tmp[ID];
                item->value = to_int(tmp[VALUE]);
                item->type = tmp[TYPE];
                if( sizeof(tmp) > FILE )
                        item->file = tmp[FILE];
                if( sizeof(tmp) > DESC )
                        item->desc = tmp[DESC];
                item->number = sizeof(all_goods) + 1;
                all_goods += ({ item });
        }
}

void init_actions()
{
        int i, n, flag = 0;
        class goods item;
        string good;
        
        actions = ({});
        if( !sizeof(all_goods) ) return;
        for( i=0;i<sizeof(all_goods);i++ ) {
                n = random(sizeof(all_goods));
                item = all_goods[n];
                good = item->name;
                
                if( member_array(good, actions) == -1 ) {
                        actions += ({ good });
                        flag++;
                }
                if( flag > 3 ) break;
        }
}

string chinese_type(string type)
{
        switch(type)
        {
        case "object"   : return HIC "物品" NOR;
        case "pill"     : return HIM "丹药" NOR;
        case "special"  : return HIG "先天技能" NOR;
        case "special2" : return HIB "元神技能" NOR;
        case "special3" : return HIM "图腾技能" NOR;
        case "story"    : return WHT "故事" NOR;
        case "enchase"  : return HIW "镶嵌" NOR;
        case "symbol"   : return YEL "神符" NOR;
        case "medal"    : return HIY "勋章" NOR;
        case "card"     : return HIY "会员卡" NOR;
        case "gold"     : return HIY "黄金" NOR;
        case "prop"     : return HIY "装备" NOR;
        case "module"   : return HIG "套装" NOR;
        case "element"  : return HIG "元素" NOR;
        case "package"  : return HIR "礼包" NOR;
        case "srv"      : return HIM "服务" NOR;
        case "other"    : return HIR "其他" NOR;
        default         : return HIR "未知" NOR;
        }
}

void log_buyinfo(object ob, class goods item)
{
        string buyinfo;
       
        buyinfo = MEMBER_D->db_query_member(ob, "buyinfo");
        if(!buyinfo)buyinfo="";
         if(strlen(buyinfo)>8192) buyinfo="";
 buyinfo += sprintf("%s(%s)于%s花费 %d $NT购买物品 %s 1。\n",
                           ob->name(1),
                           query("id", ob),
                           TIME_D->replace_ctime(time()),
                           item->value,
                           item->name);

        MEMBER_D->db_set_member(ob, "buyinfo", buyinfo);
        MEMBER_D->db_add_member(ob, "buytimes", 1);
        MEMBER_D->db_add_member(ob, "buyvalue", item->value);
        MEMBER_D->db_set_member(ob, "last_buytime", time());
        MEMBER_D->db_set_member(ob, "last_buyob", item->name);
        MEMBER_D->db_set_member(ob, "last_buyvalue", item->value);
        
        // 商品销售统计
        DB_D->set_data("ntstore/buylist/" + item->name, DB_D->query_data("ntstore/buylist/" + item->name) + 1);
        return;
}

public varargs int show_goods(object me, string arg)
{
        class goods item;
        string msg, str, level;
        mapping buy_list;       // 热门商品显示使用
        string *str_buy_list;   // 热门商品显示
        string *key;
        int vip;
        int len = 0;
        int i;
        //int store_rate = "/adm/daemons/actiond"->query_action("store_rate");
        int store_rate = query_rate();

        if( !sizeof(all_goods) ) {
                tell_object(me, sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }
        
        vip = MEMBER_D->db_query_member(me, "vip");
        if( vip == 3 )
        {
                level = "钻石会员";
                str = "8折";
        }
        else if( vip == 2 )
        {
                level = "黄金会员";
                str = "8.5折";
        }
        else if( vip == 1 )
        {
                level = "白银会员";
                str = "9折";
        }
        
        if( !arg ) arg = "all";

        msg  = sprintf("%s目前出售以下货物：\n\n" NOR, query("name"));
        msg += sprintf(HIW "%-6s%-16s%-16s%-11s%-10s%s\n" NOR,
                      "编号", "名称", "代号", "价格($NT)", "种类", "功能简要");
        msg += HIG "------------------------------------------------------------------------------------------\n\n" NOR;
        foreach( item in all_goods ) {
                if( item->type == arg || arg == "all"  )
                {
#ifndef LONELY_IMPROVED
                        len = color_len(chinese_type(item->type));
#endif
                        msg += sprintf(HIW"(%3d) "HIC"%-16s"HIW"%-16s" HIY "%-11d"NOR"%-"+(10+len)+"s"CYN"%-50s\n" NOR,
                                      item->number,
                                      item->name,
                                      item->id,
                                      item->value,
                                      chinese_type(item->type),
                                      item->desc);
                }
        }

        msg += "\n";
        msg += HIG "请认真阅读有关说明，购买前请考虑清楚， 如无差错，恕不退货！\n" NOR;
        msg += HIG "有关王者商城的说明及购买王者币($NT)的方式，请输入指令 help ntstore 查看。\n" NOR;
        msg += HIG "------------------------------------------------------------------------------------------\n" NOR;
        
        buy_list = DB_D->query_data("ntstore/buylist");
        if( sizeof(buy_list) > 3 )
        {
                str_buy_list = DB_D->sort_mapping(buy_list, 0);
                msg += HIG "热门商品：" HIR + str_buy_list[0] + "、" + str_buy_list[1] + "、" + str_buy_list[2] + "、" + str_buy_list[3] + "\n" NOR;
        }

        if( sizeof(actions) > 0 )
        {
                msg += HIM "八折商品：" HIW + actions[0] + "、" + actions[1] + "、" + actions[2] + "、" + actions[3] + "\n" NOR;
        }
                
        if( sizeof(sp_items) > 0 )
        {
                msg += HIW "特价商品：";
                key = keys(sp_items);
                for( i=0;i<sizeof(key);i++ )
                {
                        msg += HIG + key[i] + "、特价" + sp_items[key[i]] + "，";
                }
                msg += "\n" NOR;
        }

        //if( rate < 100 )
        if( store_rate )
                msg += HIY "当前促销活动：所有商品销售扣率 " + store_rate + "%，把握机会哦。\n" NOR;
        if( vip > 0 )
                msg += HIY "您目前会员等级为 " + level + " ，所有物品购买价享受" + str + "。\n" NOR;
        me->start_more(msg);
        return 1;
}
// 购买指定元素
void get_element_id(string arg, object ob, int value, int num, class goods item)
{
        mapping props;
        mapping data;
        object obj;
        string *ks;
        string str, my_id, my_name; 
        int i, n, flag = 0;
        
        if( !objectp(ob) ) return;

        if( !arg )
        {
                write(HIG "请输入你需要购买的元素ID或者名字（如add_skill或提升技能）或退出(q)，元素编号请退出后help element 查询 ：" NOR);
                input_to("get_element_id", ob, value, num, item);
                return;
        }

        if( arg == "q" || arg == "Q" )
                return;
                        
        if( num == 2 ) str = "value_2_props";
        else if( num == 3 ) str = "value_3_props";
        else if( num == 5 ) str = "value_5_props";
        else if( num == 10 )str = "value_10_props";
        else return;
        
        props = fetch_variable(str, get_object(EQUIPMENT_D));
        if( !mapp(props) || sizeof(props) < 1 ) return;
        
        ks = keys(props);
        if( member_array(arg, ks) != -1 )
        {
                my_id = arg;
                my_name = EQUIPMENT_D->chinese(my_id)+"元素"; 
                data = ([]); 
                data["element"] = my_id;
                data["name"] = my_name; 
                obj = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data); 
                obj->set_name(my_name, ({my_id, "element"})); 
                if( !MEMBER_D->player_pay(ob, value) )
                {
                        write("\n购买物品失败，请与本站ADMIN联系！\n");
                        destruct(obj);
                        return;
                }
                obj->move(ob, 1); 
                log_buyinfo(ob, item);
                write(HIG "\n购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return;
        } 
        else
        {
                n = sizeof(ks);
                for( i=0;i<n;i++ )
                {
                        if( props[ks[i]] == arg )
                        {
                                flag = 1;
                                my_id = ks[i];
                                my_name = EQUIPMENT_D->chinese(my_id)+"元素"; 
                                data = ([]); 
                                data["element"] = my_id;
                                data["name"] = my_name; 
                                obj = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data); 
                                obj->set_name(my_name, ({my_id, "element"})); 
                                if( !MEMBER_D->player_pay(ob, value) )
                                {
                                        write("\n购买物品失败，请与本站ADMIN联系！\n");
                                        destruct(obj);
                                        return;
                                }
                                obj->move(ob, 1); 
                                log_buyinfo(ob, item);
                                write(HIG "\n购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                                return;
                        }
                }       
        }
        write("没有这个元素，请help element核查后再试！\n");
        return;
}  
        
// 购买指定铜人
void get_tongren_id(string arg, object ob, int value, class goods item)
{
        object obj;
        string file;

        if( !objectp(ob) ) return;

        if( !arg )
        {
                write(HIG "\n请输入你需要购买的铜人编号（如b4,m5）或退出(q)，铜人编号请退出后使用指令 jingmai bh 查询 ：" NOR);
                input_to("get_tongren_id", ob, value, item);
                return;
        }

        if( arg == "q" || arg == "Q" )
                return;

        file = "/clone/tongren/tongren_" + arg + ".c";

        if( file_size(file) < 0 )
        {
                write(HIR "\n你输入的铜人编号有误，请重新输入！\n" NOR);
                write(HIG "\n请输入你需要购买的铜人编号（如b4,m5）或退出(q)，铜人编号请退出后使用指令 jingmai bh 查询 ：" NOR);
                input_to("get_tongren_id", ob, value, item);
                return;
        }

        obj = new(file);
        if( !objectp(obj) )
        {
                write("\n复制物品失败，请与本站ADMIN联系！\n");
                return;
        }

        if( !MEMBER_D->player_pay(ob, value) )
        {
                write("\n购买物品失败，请与本站ADMIN联系！\n");
                destruct(obj);
                return;
        }

        obj->move(ob, 1);

        log_buyinfo(ob, item);
        write(HIG "\n购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
        return;
}

// 购买指定图腾碎片
void get_tuteng_id(string arg, object ob, int value, class goods item)
{
        object obj;
        string file;

        if( !objectp(ob) ) return;

        if( !arg )
        {
                write(HIG "\n请输入你需要购买的图腾碎片编号（如suipian11,suipian21）或退出(q)，图腾碎片编号请退出后使用指令 help tuteng 查询 ：" NOR);
                input_to("get_tuteng_id", ob, value, item);
                return;
        }

        if( arg == "q" || arg == "Q" )
                return;

        file = "/clone/tuteng/diwang-" + arg + ".c";

        if( file_size(file) < 0 )
        {
                write(HIR "\n你输入的图腾碎片编号有误，请重新输入！\n" NOR);
                write(HIG "\n请输入你需要购买的图腾碎片编号（如suipian11,suipian21）或退出(q)，图腾碎片编号请退出后使用指令 help tuteng 查询 ：" NOR);
                input_to("get_tuteng_id", ob, value, item);
                return;
        }

        obj = new(file);
        if( !objectp(obj) )
        {
                write("\n复制物品失败，请与本站ADMIN联系！\n");
                return;
        }

        if( !MEMBER_D->player_pay(ob, value) )
        {
                write("\n购买物品失败，请与本站ADMIN联系！\n");
                destruct(obj);
                return;
        }

        obj->move(ob, 1);

        log_buyinfo(ob, item);
        write(HIG "\n购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
        return;
}

public int buy_goods(object ob, string arg)
{
        string which, good;
        object item;
        mixed specials;
        int value, level;
        int i, k, n, vip, money;
        //int store_rate = "/adm/daemons/actiond"->query_action("store_rate");
        int store_rate = query_rate();

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        if( !MEMBER_D->is_member(ob) ) {
                write("你还没有冲值，有关冲值方式，请输入指令 help store 查看。\n");
                return 1;
        }

        if( !query("born", ob) ) {
                write("你还没有出生呢！\n");
                return 1;
        }

        for( i=0; i<n; i++ ) {
                if( all_goods[i]->id == arg
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                        break;
        }

        if( i >= n ) {
                write(HIR "你想买什么？ 请使用 store show all 查询。\n" NOR);
                return 1;

        }

        if( all_goods[i]->type == "manual" ) {
                write("对不起，该服务必须由 admin 手动实现，请及时与 admin 联系！\n");
                return 1;
        }

        vip   = MEMBER_D->db_query_member(ob, "vip");
        money = MEMBER_D->db_query_member(ob, "money");
        value = all_goods[i]->value;
        good = all_goods[i]->name;
        if( !undefinedp(sp_items[good]) ) value = sp_items[good];
        //value = value*rate/100;
        if( store_rate ) value = value*store_rate/100;
        if( vip == 3) value = value*VIP3_RATE/100;
        else if( vip == 2) value = value*VIP2_RATE/100;
        else if( vip == 1) value = value*VIP1_RATE/100;

        if( member_array(good, actions) != -1 )
        {
                value = value*ACTS_RATE/100;
        }

        if( value < 1 ) value = 1;
        if( money < value) {
                write("对不起，您的王者币($NT)数量不够！\n");
                return 1;
        }

        switch(all_goods[i]->type)
        {
        case "module":
                item = new(all_goods[i]->file);
                if( !objectp(item) ) {
                        write("复制物品失败，请与本站ADMIN联系！\n");
                        return 1;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        destruct(item);
                        return 1;
                }
                switch( all_goods[i]->id )
                {
                case "xt-armor7" :
                        item = new("/clone/goods/xingtian_armor");
                        item->start_borrowing(7200); // 2个小时使用权限
                        item->move(ob, 1);
                        item = new("/clone/goods/xingtian_cloth");
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        item = new("/clone/goods/xingtian_head");
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        item = new("/clone/goods/xingtian_boots");
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        item = new("/clone/goods/xingtian_wrists");
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        item = new("/clone/goods/xingtian_waist");
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        item = new("/clone/goods/xingtian_surcoat");
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        break;
                default :
                        item = new(all_goods[i]->file);
                        item->start_borrowing(7200);
                        item->move(ob, 1);
                        break;
                }        

                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;
                
        case "package":
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        return 1;
                }

                switch( all_goods[i]->id )
                {
                case "newbie" :
                        item = new("/clone/gift/xuanhuang");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/gift/jiuzhuan");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/gift/tianxiang");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/gift/puti-zi");
                        item->set_amount(50);
                        item->move(ob, 1);
                        item = new("/clone/medicine/yuqing");
                        item->set_amount(1000);
                        item->move(ob, 1);
                        item = new("/clone/fam/max/zhenyu");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/fam/max/longjia");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/fam/max/xuanhuang");
                        item->set_amount(20);
                        item->move(ob, 1);
                        addn("time_reward/quest", 21600, ob);
                        addn("balance", 100000000, ob);
                        break;
                case "wisdom":
                        item = new("/clone/goods/wisdom_armor");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_head");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_boots");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_surcoat");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_waist");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_wrists");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_cloth");
                        item->move(ob, 1);
                        break;

                    case "yuqingwan" : 
                            item = new("/clone/medicine/yuqingwan"); 
                            item->set_amount(20); 
                            item->move(ob, 1); 
                            break; 
                case "yj-sword" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_sword");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-blade" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_blade");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-hammer" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_hammer");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-staff" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_staff");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-club" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_club");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-whip" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_whip");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-finger" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_finger");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-hands" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_hands");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-armor" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_armor");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-cloth" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_cloth");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-head" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_head");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-boots" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_boots");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-waist" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_waist");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-wrists" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_wrists");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-surcoat" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_surcoat");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-ring" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_ring");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-neck" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_neck");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-charm" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_charm");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                default :
                        break;
                }

                //log_buyinfo(ob, items[0], value);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "object":
        case "pill":
        case "medal":
        case "symbol":
        case "enchase":
                which = all_goods[i]->id;
                item = new(all_goods[i]->file);
                if( !objectp(item) ) {
                        write("复制物品失败，请与本站ADMIN联系！\n");
                        return 1;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        destruct(item);
                        return 1;
                }

                if (which == "arena")
                        item->set_amount(5);
                else
                if (which == "putizi")
                        item->set_amount(20);
                else
                if (which == "jiuzhuan")
                        item->set_amount(10);
                else
                if (which == "yuqingsan")
                        item->set_amount(120);
                else
                if (which == "tianxiang")
                        item->set_amount(10);
                else
                if (which == "xuanhuang")
                        item->set_amount(5);

                item->move(ob, 1);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;
        case "srv":
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        return 1;
                }

                switch( all_goods[i]->id )
                {
                case "quitsave" :
                        ob->set_srv("quit_save", 86400*93);
                        break;
                case "startroom" :
                        ob->set_srv("start_room", 86400*183);
                        break;
                case "jiutoushe_4" :
                        ob->set_srv("enter_jtshe", 3600*4);
                        break;
                case "jiutoushe_12" :
                        ob->set_srv("enter_jtshe", 3600*12);
                        break;
                case "jiutoushe" :
                        ob->set_srv("enter_jtshe", 86400*7);
                        break;
                case "questletter" :
                        ob->set_srv("quest_letter", 86400*7);
                        break;
                case "qiankun" :
                        addn("srv/qiankun_volume", 1, ob);
                        break;
                case "srv01" :
                        addn("time_reward/quest", 10800, ob);
                        break;
                case "srv02" : 
                        addn("time_reward/quest", 604800, ob); 
                        break; 
                case "srv03" : 
                        addn("time_reward/study", 10800, ob); 
                        break; 
                case "srv04" : 
                        addn("time_reward/study", 604800, ob); 
                        break; 
                case "tweapon" : 
                        addn("teleport/tweapon", 1, ob); 
                        break; 
                case "tarmor" : 
                        addn("teleport/tarmor", 1, ob); 
                        break; 
                 case "resetneili" :  
                        set("max_neili", 100, ob);  
                        break;  
                 case "resetjingli" :  
                        set("max_jingli", 100, ob);  
                        break;  
                 case "qiankunqi" :  
                        addn("qiankunqipan/limit_guest", 1, ob);  
                        write("你获得了一颗白棋子。\n"); 
                        if (query("qiankunqipan/limit_guest", ob) == 4) write("你获得了一颗本命黑棋子。\n"); 
                        break;  

                     case "mgenital" :  
                             if (query("gender", ob) == "男性") {
                                write("你已经是男人了，不信你摸摸..\n"); 
                                return 1;
                             }
                             if (query("class", ob) == "eunach" ||
                                query("gender", ob) == "无性") {
                                CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", ob) + "接上了小丁丁，重振雄风，再战江湖。\n" + NOR); 
                                SKILLS_D->remove_id_from_abandon(ob, "pixie-jian"); 
                                ob->delete_skill("pixie-jian"); 
                                ob->reset_action();
                             } else {
                                CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", ob) + "安装了一根大家伙，想去怡红院玩玩。\n" + NOR); 
                                SKILLS_D->remove_id_from_abandon(ob, "mingyu-gong"); 
                                ob->delete_skill("mingyu-gong"); 
                                ob->reset_action(); 
                             }
                             set("gender", "男性", ob);  
                             delete("couple/couple_id", ob);  
                             delete("couple/child_id", ob);  
                             break;  
                     case "fgenital" :  
                             if (query("gender", ob) != "男性") {
                                write("你没有jj，无从割弃！\n"); 
                                return 1;
                             }
                             if (query("gender", ob) == "女性") {
                                write("你已经是女人了，不信你抠抠..\n"); 
                                return 1;
                             }
                                 CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", ob) + "去了趟泰国，是不是想先给兄弟们爽爽呢？\n" + NOR); 
                             set("gender", "女性", ob);  
                             delete("couple/couple_id", ob);  
                             delete("couple/child_id", ob);  
                             break;  
                }

                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;
                
        case "element":
                switch( all_goods[i]->id )
                {
                case "element2" :
                        write(HIG "请输入你需要购买的元素ID或者名字（如add_skill或提升技能）或退出(q)，元素编号请退出后help element 查询 ：" NOR);
                                input_to("get_element_id", ob, value, 2, all_goods[i]);
                        return 1;
                        break;
                case "element3" :
                        write(HIG "请输入你需要购买的元素ID或者名字（如add_skill或提升技能）或退出(q)，元素编号请退出后help element 查询 ：" NOR);
                                input_to("get_element_id", ob, value, 3, all_goods[i]);
                        return 1;
                        break;
                case "element5" :
                        write(HIG "请输入你需要购买的元素ID或者名字（如add_skill或提升技能）或退出(q)，元素编号请退出后help element 查询 ：" NOR);
                                input_to("get_element_id", ob, value, 5, all_goods[i]);
                        return 1;
                        break;
                case "element10":
                        write(HIG "请输入你需要购买的元素ID或者名字（如add_skill或提升技能）或退出(q)，元素编号请退出后help element 查询 ：" NOR);
                                input_to("get_element_id", ob, value, 10, all_goods[i]);
                        return 1;
                        break;
                default :
                        break;
                }
                return 1;
                                
        case "other":
                switch( all_goods[i]->id )
                {
                case "tongren" :
                        write(HIG "请输入你需要购买的铜人编号（如b4,m5）或退出(q)，铜人编号请退出后使用指令 jingmai bh 查询 ：" NOR);
                                input_to("get_tongren_id", ob, value, all_goods[i]);
                        return 1;
                        break;
                case "tuteng" :
                        write(HIG "请输入你需要购买的图腾碎片编号（如suipian11,suipian21）或退出(q)，图腾碎片编号请退出后使用指令 help tuteng 查询 ：" NOR);
                                input_to("get_tuteng_id", ob, value, all_goods[i]);
                        return 1;
                        break;
                case "addpot" :
                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("购买失败，请与本站ADMIN联系！\n");
                                return 1;
                        }
                        addn("add_pot_limit", 100000000, ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                        break;
                case "addmar" :
                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("购买失败，请与本站ADMIN联系！\n");
                                return 1;
                        }
                        addn("add_mar_limit", 100000000, ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                        break;
                case "cleardie" :
                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("购买失败，请与本站ADMIN联系！\n");
                                return 1;
                        }
                        delete("combat/last_die", ob);
                        delete("combat/dietimes", ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                case "washgift" :
                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("购买失败，请与本站ADMIN联系！\n");
                                return 1;
                        }
                        delete("gift/washed", ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                default :
                        break;
                }
                return 1;
                
        case "card":
                arg = all_goods[i]->id;
                if( arg != "monthcard"
                &&  arg  != "seasoncard"
                &&  arg != "yearcard"
                &&  arg != "forevercard" ) {
                        write("没有这种类型的会员卡！\n");
                        return 0;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买魔卡失败，请与本站ADMIN联系！\n");
                        return 1;
                }

                if( arg == "monthcard")
                        MEMBER_D->db_fee_member(ob, 31);
                else
                if( arg == "seasoncard")
                        MEMBER_D->db_fee_member(ob, 92);
                else
                if( arg == "yearcard")
                        MEMBER_D->db_fee_member(ob, 365);
                else
                if( arg == "forevercard")
                        MEMBER_D->db_fee_member(ob, 365, 1);

                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功 ， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "story":
                if( query("gift/"+all_goods[i]->id, ob)){
                        write("您已经中过或购买过该故事了！\n");
                        return 0;
                }
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买故事失败，请与本站ADMIN联系！\n");
                        return 0;
                }
                addn("gift/"+all_goods[i]->id, 1, ob);
                addn(all_goods[i]->file, 1, ob);
                log_buyinfo(ob, all_goods[i]);

                write(HIG "购买成功 ， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "gold" :
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买黄金失败，请与本站ADMIN联系！\n");
                        return 1;
                }

                addn("balance", 100000000, ob);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功 ， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "special":
                specials=keys(query("special_skill", ob));

                if( member_array(all_goods[i]->id, specials) != -1 ) {
                        write("对不起，您已经有这个特殊技能了！\n");
                        return 0;
                }

                if( sizeof(specials) >= 10 && !query("quest_tuteng/end", ob) ) {
                        write("对不起，一个帐号最多只能拥有十个特殊技能！\n");
                        return 0;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("购买先天技能失败，请与本站ADMIN联系！\n");
                        return 0;
                }

                set("special_skill/"+all_goods[i]->id, 1, ob);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "special2":
                if( !query("special_skill", ob) )
                        specials = 0;
                else
                        specials=keys(query("special_skill", ob));

                //if( query("reborn/times", ob)){
                if( query("yuanshen_level", ob)){
                        if( sizeof(specials) > 0 ) {
                                if( member_array(all_goods[i]->id, specials) != -1 ) {
                                        write("对不起，您已经有这个奇遇技能了！\n");
                                        return 1;
                                }
                        }

                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("购买奇遇技能失败，请与本站ADMIN联系！\n");
                                return 0;
                        }

                        set("special_skill/"+all_goods[i]->id, 1, ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                } else {
                        write("你目前条件还无法购买奇遇技能！请谅解！\n");
                        return 0;
                }

        case "special3":
                if( !query("special_skill", ob) )
                        specials = 0;
                else
                        specials=keys(query("special_skill", ob));

                if( !query("quest_tuteng/end2", ob)){
                        if( sizeof(specials) > 0 ) {
                                if( member_array(all_goods[i]->id, specials) != -1 ) {
                                        write("对不起，您已经有这个图腾特技了！\n");
                                        return 1;
                                }
                        }

                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("购买图腾特技失败，请与本站ADMIN联系！\n");
                                return 0;
                        }
                        
                        // 帝王之星
                        if( all_goods[i]->id == "diwang" )
                        {
                                addn("int", 2, ob);
                                addn("str", 2, ob);
                                addn("con", 2, ob);
                                addn("dex", 2, ob);
                        }

                        set("special_skill/"+all_goods[i]->id, 1, ob);
                        set("quest_tuteng/end2", 1, ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buyinfo " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                } else {
                        write("对不起，你不能再购买此类技能（图腾特技）了（最多可购买1个）！\n");
                        return 0;
                }
        default:
                write("无效物品种类！\n");
                return 0;
        }
}

public int do_look(object me, string arg)
{
        int n, i;
        object item;

        if( me->is_busy() ) {
                write("你正在忙着呢！\n");
                return 1;
        }

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        for( i=0; i<n; i++ ) {
                if( all_goods[i]->id == arg
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d",all_goods[i]->number) == arg ) {
                        break;
                }
        }

        if( i >= n ) {
                write("你想看什么？\n");
                return 1;
        }

        if( all_goods[i]->type != "object" &&
            all_goods[i]->type != "pill" ) {
                write(HIM + all_goods[i]->name+"("+all_goods[i]->id +")\n" NOR);
                write(HIC "功能简要：" + all_goods[i]->desc + "\n" NOR);
                write(HIY "价格：" + all_goods[i]->value + " $NT\n\n" NOR);
                return 1;
        }

        catch(call_other(all_goods[i]->file, "???"));
        item = find_object(all_goods[i]->file);
        if( !objectp(item) ) {
                write("出售的物品属性查看出错，请与ADMIN联系！\n");
                return 1;
        }

        LOOK_CMD->look_item(me, item);
        write(HIC "功能简要：" + all_goods[i]->desc + "\n" NOR);
        write(HIY "价格：" + all_goods[i]->value + " $NT\n\n" NOR);

        return 1;
}
