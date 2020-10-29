// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// dealer.c 商人
// 需加入价格变动体系price_ratio

// #pragma save_binary

#include <config.h>
#include <command.h>
#include <dbase.h>
#include <name.h>

class goods
{
        mapping data; // 动态物品数据
        string name;
        string id;
        string *ids;
        string type;
        string file;
        string unit;
        //int carry;
        int amount;  // 数量
        int value;   // 价格
        int number;  // 编号
}

nosave int uptime;
nosave int no_trade = 0;
nosave int load_goods = 0;

protected class goods *all_goods = ({});
protected void init_goods();
protected int add_one_good(string file, int price, int amount);
int is_vendor() { return 1; }

/*
void setup()
{
        init_goods();
        ::setup();
        if( !uptime )
                uptime = time();
}

void init()
{
        //add_action("do_sell", ({ "sell" }) );
        add_action("do_buy", ({ "mai", "buy" }) );
        add_action("do_list", "list");
        add_action("do_look", ({"guankan", "kan"}));
}
*/

protected void init_goods()
{
        string *ks, file;
        mixed item;
        int price = 0;
        int amount = -1;
        int i;

        no_trade = 1;
        all_goods = ({});

        item = this_object()->query("vendor_goods");
        if( !arrayp(item) && !mapp(item) || !sizeof(item) )
        {
                no_trade = 0;
                load_goods = 1;
                return;
        }

        ks = mapp(item) ? keys(item) : item;
        for( i=0; i<sizeof(ks);i++ )
        {
                file = ks[i];
                if( mapp(item) ) // string为价格，int为数量
                {
                        if( intp(item[ks[i]]) && item[ks[i]] > 0 )
                                amount = item[ks[i]];
                        else if( stringp(item[ks[i]]) )
                                price = to_int(item[ks[i]]);
                }
                add_one_good(file, price, amount);
        }

        no_trade = 0;
        load_goods = 1;
}

protected int add_one_good(mixed obj, int price, int amount)
{
        string file;
        object ob, obn;
        class goods item;
        string type;
        int i, n;

        if( !stringp(obj) && !objectp(obj) )
                return 0;

        if( stringp(obj) ) file = obj;
        else file = base_name(obj);

        if( objectp(obj) )
                ob = obj;
        else
        {
                if( catch(call_other(file, "???"))
                ||  !objectp(ob = find_object(file)) ) {
                        log_file("static/dealer",
                                 sprintf("vendor good file:%s of %s does not exist\n",
                                         file, base_name(this_object())));
                        return 0;
                }
        }

        if( ob->is_weapon() )           type = "武器";
        else if( ob->is_armor() )       type = "防具";
        else if( ob->is_liquid() )      type = "饮具";
        else if( ob->is_food() )        type = "食物";
        else if( ob->is_container() )   type = "容器";
        else if( ob->is_book() )        type = "书籍";
        else                            type = "其它";

        if( objectp(obj) )
        {
                mapping data, temp;
                string id, name;

                id = obj->query("id");
                name = obj->query("name");
                data = obj->query_entire_dbase();
                catch(obn = new(file));
                if( !obn ) return;
                temp = obn->query_entire_dbase();
                destruct(obn);

                n = sizeof(all_goods);
                for( i = 0; i < n; i++ )
                {
                        if( all_goods[i]->file == file &&
                            all_goods[i]->id == id &&
                            all_goods[i]->name == name ) {
                                if( obj->query_amount() || mapping_eqv(data, temp) )
                                {
                                        if( all_goods[i]->amount != -1 )
                                                all_goods[i]->amount += amount;
                                        destruct(obj);
                                        return 1;
                                }

                                if( all_goods[i]->data && mapping_eqv(data, all_goods[i]->data) )
                                {
                                        if( all_goods[i]->amount != -1 )
                                                all_goods[i]->amount += amount;
                                        destruct(obj);
                                        return 1;
                                }
                        }
                }
                item = new(class goods);
                item->name = name;
                item->id = id;
                item->ids = obj->my_id();
                item->type = type;
                item->file = file;
                item->unit = obj->query("base_unit") ?
                             obj->query("base_unit") : obj->query("unit");
                item->amount = amount;
                item->value = price ? price :
                        (obj->query("base_value") ? obj->query("base_value"):
                                                    obj->query("value"));
                item->number = sizeof(all_goods) + 1;
                if( !mapping_eqv(data, temp) )
                        item->data = copy(data);
                all_goods += ({ item });
                destruct(obj);
                return 1;
        }

        item = new(class goods);
        item->name = ob->query("name");
        item->id = ob->query("id");
        item->ids = ob->my_id();
        item->type = type;
        item->file = file;
        item->unit = ob->query("base_unit") ? ob->query("base_unit")
                                            : ob->query("unit");
        item->amount = amount;
        item->value = price ? price :
                        (ob->query("base_value") ? ob->query("base_value"):
                                                   ob->query("value"));
        item->number = sizeof(all_goods) + 1;

        all_goods += ({ item });
        // destruct(ob);
        return 1;
}

string is_vendor_good(object ob)
{
        string name, id, file;
        int i, n;

        n = sizeof(all_goods);
        if ( !n ) return "";

        id = ob->query("id");
        name = ob->query("name");
        file = base_name(ob);

        for( i=0;i<n;i++ )
        {
                if( all_goods[i]->id == id &&
                    all_goods[i]->file == file &&
                    all_goods[i]->name == name ) {
                        if( all_goods[i]->data ||
                            all_goods[i]->amount != -1 )
                                return "";

                        return all_goods[i]->file;
                }
        }

        return "";
}

void add_carried_good()
{
        object *obs;
        int i;
        int amount;

        if( obs = all_inventory() )
        {
                for( i = 0; i < sizeof(obs); i++ )
                {
                        if( obs[i]->query("equipped")
                        ||  obs[i]->query("money_id")
                        ||  obs[i]->is_item_make()
                        ||  obs[i]->is_character() )
                                continue;

                        amount = obs[i]->query_amount() ?
                                 obs[i]->query_amount() : 1;

                        add_one_good(obs[i], 0, amount);
                }
        }
}

varargs int do_list(string arg)
{
        string output, desc;
        class goods item;
        object me;

        me = this_player();

        if( no_trade )
                return notify_fail("现在正在盘库，请等一下再来。\n");

        if( !wizardp(me) && me->query_condition("killer") )
                return notify_fail(CYN "店铺不做杀人犯的生意！\n" NOR);

        if( me->is_busy() ) {
                write(BUSY_MESSAGE);
                return 1;
        }

        // 处理同房间有一个以上 dealer 的情况。
        if( arg && !id(arg) && arg != query("name") )
                return 0;

        if( !load_goods ) {
                init_goods();
                if (! uptime)
                        uptime = time();
        }

        add_carried_good();

        if( !sizeof(all_goods) ) {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        output = this_object()->name() + "目前出售以下物品：\n";
        /*
        output += sprintf("%5s%-30s%-10s%-10s\n","序 号", "    商  品","  单  价","       数  量");
        output += "----------------------------------------------------------------\n";
        */
        foreach( item in all_goods ) {
                if( item->amount < 0 ) desc = "大量供应";
                else if( item->amount == 0 ) desc = "暂时缺货";
                else if( item->amount < 11 )
                        desc = sprintf("仅剩%2d%2s", item->amount, item->unit);
                else if( item->amount < 31 )
                        desc = sprintf("还剩%2d%2s", item->amount, item->unit);
                else
                        desc = "货源充足";

                output += sprintf("(%3d)%" + sprintf("%d", (30 + color_len(item->name))) +
                                  "-s：每%s%s" CYN "(现货%s)\n" NOR,
                                  item->number,
                                  item->name + "(" + item->id + ")",
                                  item->unit,
                                  MONEY_D->price_str(item->value), desc);
        }

        write(output);
        return 1;
}

int do_buy(string arg)
{
        mapping room_obmap;
        string  bunch;
        object *obs;
        object  ob;
        object  room;
        object  me;
        mixed   value;
        int     amount;
        int     val_factor;
        int     i, j, n;
        string  my_id;
        string  start_room;

        if( !arg )
                return notify_fail("你想买什么？\n");

        if( (me = this_player())->is_busy() ) {
                write("你正在忙着呢！\n");
                return 1;
        }

        if( no_trade )
                return notify_fail("现在正在盘库，请等一下再来。\n");

        if( query_temp("busy") ) {
                write(CYN + name() + "不耐烦道：“没看见我这"
                      "儿正忙着么？”\n" NOR);
                return 1;
        }

        if( sscanf(arg,"%s from %s", arg, my_id) == 2 ) {
                if( !id(my_id) && my_id != query("name") )
                        return 0;
        }

        if( !query("carried_items") ) {
                if( stringp(start_room = query("startroom")) &&
                    (room = find_object(start_room)) != environment() ) {
                        // I am not in start room.
                        message_vision("$N大叫一声：“不好，我怎么跑到这儿来了？”\n"
                                       "说罢头也不回的急急忙忙的溜走了。\n", this_object());
                        if( !objectp(room) ||
                            !mapp(room_obmap = room->query_temp("objects")) ||
                            member_array(this_object(), values(room_obmap)) == -1 ) {
                                destruct(this_object());
                        } else
                                this_object()->move(room);
                        return 1;
                }
        }

        if( sizeof(filter_array(all_inventory(me),
                (: !$1->query("equipped") :))) >= MAX_ITEM_CARRIED ) {
                write("你身上的东西太多了，先处理一下再买东西吧。\n");
                return 1;
        }

        if( sscanf(arg, "%d %s", amount, arg) != 2 )
                // not indicate the amount of the items
                amount = 1;

        if( amount < 1 ) {
                write(CYN + name() + "疑惑的问道：“没见过这种买法，你到底想买几个单位呢？”\n" NOR);
                return 1;
        }

        if( amount > 5000 ) {
                write(CYN + name() + "忙道：“慢慢来，一次最多买五千个单位。”\n" NOR);
                return 1;
        }

        if( !load_goods ) {
                init_goods();
                if (! uptime)
                        uptime = time();
        }

        add_carried_good();

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        val_factor = 10;
        for( i = 0; i < n; i++ ) {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg) {
                        if( !(all_goods[i]->amount) ) {
                                command(sprintf("say 对不起，目前这%s" CYN "缺货，您过一段时间再来吧",
                                        all_goods[i]->name));
                                return 1;
                        }

                        if( all_goods[i]->amount > 0 ) {
                                val_factor = 12;

                                if( amount > all_goods[i]->amount )
                                        amount = all_goods[i]->amount;
                        }

                        if( !function_exists("query_amount", get_object(all_goods[i]->file)) ) {
                                if( amount > 100 ) {
                                        amount = 100;
                                        write("这类物品限制一次最多买一百个单位。\n");
                                }
                        }

                        break;
                }
        }

        if( i >= n ) {
                write("你想买什么？\n");
                return 1;
        }

        value = amount*all_goods[i]->value;
        value = value*val_factor/10;

        if( value > 1000000000 || value * val_factor / val_factor != value ) {
                write(CYN + name() + CYN "大惊失色道：这么大一笔生意？我"
                      "可不好做。\n" NOR);
                return 1;
        }

        if( stringp(bunch = me->query("bunch/bunch_name")) &&
            bunch == (string)this_object()->query("bunch/bunch_name") )
                value = value * 90/100;

        else if( SHOP_D->is_owner(me->query("id")) )
                value = value * 90/100;
        else if( me->query_skill("higgling", 1) > 99 ) {
                if( me->query_skill("higgling", 1) > 399 )
                        value = value * 80/100;
                else if (me->query_skill("higgling", 1) > 199)
                        value = value * 85/100;
                else if (me->query_skill("higgling", 1) > 99)
                        value = value * 90/100;
        }

        if( value < 1 )
                value = 1;


        switch (MONEY_D->player_pay(me, value))
        {
        case 0:
                write(CYN + name() + "冷笑道：“穷光蛋，一边呆着去！”\n" NOR);
                return 1;
        case 2:
                write(CYN + name() + "皱眉道：“您还有没有零"
                      "钱啊？银票我可找不开。”\n" NOR);
                return 1;
        case 3:
                write(CYN + name() + "皱眉道：“您还有没有零"
                      "钱啊？钻石我可找不开。”\n" NOR);
                return 1;
        default:
                set_temp("busy", 1);

                if (stringp(bunch = me->query("bunch/bunch_name")) &&
                    bunch == (string)this_object()->query("bunch/bunch_name")) {
                        BUNCH_D->add_bunch_info(bunch, "npc_money", value/5);
                        command("say 既然大家都是同帮兄弟，就给你打点折吧。");
                } else
                if( me->query_skill("higgling", 1) > 99 || SHOP_D->is_owner(me->query("id")) )
                {
                        switch (random(3))
                        {
                        case 0:
                                command("say 既然大家都是做买卖的，就给你打点折吧。");
                                break;
                        case 1:
                                command("say 也罢，既然是大老板光顾，就便宜点卖给你吧。");
                                break;
                        default:
                                command("say 呵呵。大老板又来采购么？那么就给你打点折吧。");
                                break;
                        }
                }

                if( function_exists("query_amount", get_object(all_goods[i]->file)) )
                {
                        ob = new(all_goods[i]->file);
                        ob->set_amount(amount);
                        ob->move(me, 1);
                } else
                {
                        for( j = 0; j < amount; j++ )
                        {
                                if( !all_goods[i]->data )
                                        ob = new(all_goods[i]->file);
                                else
                                {
                                        ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                        ob->set_name(ob->query("name"), all_goods[i]->ids);
                                }
                                ob->move(me, 1);
                        }
                }

                all_goods[i]->amount -= amount;
                message_vision(sprintf("$N从$n那里买下了%s%s%s%s。\n",
                        all_goods[i]->amount == 0 ? "最后" : "",
                        chinese_number(amount),
                        all_goods[i]->unit,
                        all_goods[i]->name), me, this_object());
        }

        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

        return 1;
}

void destruct_it(object ob)
{
        if( !ob || environment(ob))
                return;
        destruct(ob);
}

void enough_rest()
{
        delete_temp("busy");
}

int do_look(string arg)
{
        string who;
        object ob, me;
        int i, n;

        if( (me = this_player())->is_busy() )
        {
                write(BUSY_MESSAGE);
                return 1;
        }

        if( !arg || arg == "" )
        {
                write("你想看什么？\n");
                return 1;
        }

        // 处理同房间有一个以上 dealer 的情况。
        if( sscanf(arg,"%s from %s", arg, who) == 2 )
        {
                if( !id(who) && who != query("name"))
                        return 0;
        }

        if( !load_goods )
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }

        add_carried_good();

        n = sizeof(all_goods);
        if( !n )
        {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        for( i = 0; i < n; i++ )
        {
                if( all_goods[i]->amount == 0 )
                        continue;

                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                {
                        if( !all_goods[i]->data )
                        {
                                ob = get_object(all_goods[i]->file);
                                LOOK_CMD->look_item(me, ob);
                                //destruct(ob);
                                return 1;
                        }
                        else
                        {
                                ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                LOOK_CMD->look_item(me, ob);
                                destruct(ob);
                                return 1;
                        }
                }
        }

        if( i >= n )
        {
                write("你想看什么？\n");
                return 1;
        }
}

int do_value(string arg)
{
        object ob;
        int value;
        mixed ns;

        if( !arg || !(ob = present(arg, this_player())) )
        {
                return notify_fail("你要估什么的价？\n");
        }

        if( ob->query("money_id") )
        {
                write(CYN + name() + "道：你没用过钱啊？\n" NOR);
                return 1;
        }

        if( ob->is_character() )
        {
                write(CYN + name() + "道：这你也拿来估价？\n" NOR);
                return 1;
        }

        if( ob->query_amount() )
                value = ob->query("base_value");
        else
                value = ob->query("value");

        if( ob->query("consistence") )
                value = value * ob->query("consistence") / 100;

        if( value < 1 )
                write(CYN + name() + "道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        if( ob->query("no_drop") || (ns = ob->query("no_sell")) )
        {
                if( stringp(ns) )
                {
                        write(CYN + name() + "道：" + ns + "\n" NOR);
                        return 1;
                }
                write(CYN + name() + "道：“这东西有点古怪，我可不好估价。”\n" NOR);
        } else
                write(CYN + name() + "道：“" + ob->query("name") + CYN "值" +
                        MONEY_D->price_str(value * 50 / 100) + "。”\n" NOR);
        return 1;
}

int do_sell(string arg)
{
        object me;
        object ob;
        object nob;
        string my_id;
        int amount;
        int value;
        int res;
        int max_count;
        mixed ns;

        if( !arg )
                return notify_fail("你要卖什么？\n");

        if( sscanf(arg,"%s to %s", arg, my_id) == 2 )
        {
                if( !id(my_id) && my_id != query("name"))
                        return 0;
        }

        if( sscanf(arg, "%d %s", amount, arg) != 2 )
                // not indicate the amount of the goods
                amount = 1;

        if( amount < 1 )
        {
                write(CYN + name() + "疑惑的问道：“没见过这种卖法，你到底想卖几件呢？”\n" NOR);
                return 1;
        }

        me = this_player();
        if( !(ob = present(arg, me)) )
        {
                write("你身上没有这种东西啊！\n");
                return 1;
        }

        max_count = ob->query_amount();
        if( !max_count )
        {
                // not combined object
                if( amount > 1 )
                {
                        write(ob->name() + "这种东西不能拆开来卖。\n");
                        return 1;
                }
                max_count = 1;
        } else
        {
                // is combined object
                if( amount > max_count )
                {
                        write("你身上没有这么多" + ob->name() + "。\n");
                        return 1;
                }
        }

        if( ob->query("money_id") )
        {
                write(CYN + name() + "道：“哈哈哈哈！你想卖「钱」？？”\n" NOR);
                return 1;
        }

        if( ob->is_character() )
        {
                write(CYN + name() + "道：“哼！我这里做正经生"
                      "意，不贩卖这些！”\n" NOR);
                return 1;
        }

        if( ob->query("unique")
        ||  ob->is_no_clone()
        ||  ob->query("no_pawn")
        ||  ob->query("replica_ob")
        ||  ob->query("bindable") )
        {
                write(CYN + name() + "摇摇头，道：“这种东西我"
                      "不识货，不敢要。”\n" NOR);
                return 1;
        }

        if( ob->query("no_drop") ||
            (ns = ob->query("no_sell")) )
        {
                if( stringp(ns) )
                {
                        command("say " + ns);
                        return 1;
                }
                write(CYN + name() + "摇摇头，道：“这种东西我"
                      "不识货，不敢要。”\n" NOR);
                return 1;
        }

        if( is_vendor_good(ob) != "" )
        {
                write(CYN + name() + "笑道：“我卖给你好不好？”\n" NOR);
                return 1;
        }

        if( ob->query("food_supply") )
        {
                write(CYN + name() + "不屑道：“嘿嘿，剩菜剩饭留给"
                      "您自己用吧。”\n" NOR);
                return 1;
        }

        if( ob->query("shaolin") )
        {
                write(CYN + name() + "惊道：“小的胆子很小，可"
                      "不敢买少林庙产。”\n" NOR);
                return 1;
        }

        if( ob->query("mingjiao") )
        {
                write(CYN + name() + "忙摇头道：“小的只有一个脑袋，可"
                      "不敢买魔教的东西。”\n" NOR);
                return 1;
        }

        if( ob->query("consistence") )
                value = value * ob->query("consistence") / 100;

        if( max_count > 1 )
        {
                if( ob->query("base_value") * amount / amount != ob->query("base_value") )
                {
                        write(CYN + name() + CYN "大惊失色道：这么大一笔生意？我"
                              "可不好做。\n" NOR);
                        return 1;
                }
                value = ob->query("base_value") * amount;
        }
        else
                value = ob->query("value");

        if( value < 2 )
                write(CYN + name() + "随手一扔，道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        {
                if( max_count == amount )
                        res = ob->move(this_object());
                else
                {
                        nob = new(base_name(ob));
                        nob->set_amount(amount);
                        if( res = nob->move(this_object()) )
                                ob->add_amount(-amount);
                        else
                                destruct(nob);
                }

                if( res )
                {
                        message_vision("$N卖掉了一" + ob->query("unit") +
                                       ob->query("name") + "给$n。\n",
                                       this_player(), this_object());
                        MONEY_D->pay_player(this_player(), (value / 2));
                        ob->sold();
                } else
                        write(CYN + name() + "摇摇头，道：“对不起，"
                              "我现在不收货了。”\n" NOR);
        }
        //destruct(ob);
        return 1;
}

void reset()
{
        int i, t;
        object *obs;

        t = time();
        if( !uptime )
                uptime = t;

        if( t - uptime >= 3600 ) {
                uptime = t;
                init_goods();
        }

        obs = all_inventory();
        for( i = 0; i < sizeof(obs); i++ )
                if( i >= 100 || obs[i]->query_weight() >= 1000000 )
                        destruct(obs[i]);
}
