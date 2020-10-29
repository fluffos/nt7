// 店铺继承
// Create by smallfish.
// Update by jjgod.
// Update by Lonely@nitan.org

inherit ROOM;
inherit F_SAVE;

#include <ansi.h>
#include <config.h>

class goods
{
        mapping data; // 动态物品数据
        string name;
        string id;
        string *ids;
        string type;
        string file;
        string unit;
        int amount;  // 数量
        mixed value;   // intp为gold，stringp为$NT
        int number;  // 编号
}

class goods *all_goods = ({});

mixed query_goods() { return all_goods; }
void init_goods() { all_goods = ({}); }
int clean_up() { return 1; }

int add_one_good(object obj, mixed price, int amount)
{
        mapping data, temp;
        string id, name;
        string file;
        object obn;
        class goods item;
        string type;
        int i, n;

        if( !objectp(obj) )
                return 0;

        if( obj->is_weapon() )           type = "武器";
        else if( obj->is_armor() )       type = "防具";
        else if( obj->is_liquid() )      type = "饮具";
        else if( obj->is_food() )        type = "食物";
        else if( obj->is_container() )   type = "容器";
        else if( obj->is_book() )        type = "书籍";
        else                             type = "其它";

        file = base_name(obj);
        id=query("id", obj);
        name=query("name", obj);
        data = obj->query_entire_dbase();
        obn = new(file);
        temp = obn->query_entire_dbase();
        destruct(obn);

        if( !all_goods ) all_goods = ({});
        n = sizeof(all_goods);
        for( i = 0; i < n; i++ )
        {
                if( all_goods[i]->file == file &&
                    all_goods[i]->id == id &&
                    all_goods[i]->name == name ) {
                        if( obj->query_amount() || mapping_eqv(data, temp) )
                        {
                                all_goods[i]->amount += amount;
                                all_goods[i]->value = price;
                                destruct(obj);
                                return 1;
                        }

                        if( all_goods[i]->data && mapping_eqv(data, all_goods[i]->data) )
                        {
                                all_goods[i]->amount += amount;
                                all_goods[i]->value = price;
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
        item->unit=query("base_unit", obj)?
                     query("base_unit", obj):query("unit", obj);
        item->amount = amount;
        item->value = price ? price :
                     (query("base_value", obj)?query("base_value", obj):
                                                 query("value", obj));
        item->number = sizeof(all_goods) + 1;
        if( !mapping_eqv(data, temp) )
                item->data = copy(data);
        all_goods += ({ item });
        destruct(obj);
        return 1;
}

public string do_stock(object ob, object me, string arg)
{
        object obj, item;
        mixed value;
        object room;
        string name;

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

        if (! (item = present(arg, me)) || ! objectp(item))
                return "你身上并没有这个货物啊！\n";

        if( query("no_sell", item) )
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        if( query("no_get", item) || query("no_drop", item) || 
            query("no_put", item) || query("no_beg", item) || 
            query("no_steal", item) || query("no_drop", item) || 
            query("item_make", item) || query("owner", item) )
                return "这个东西摆不上货架，就暂时别拿出来卖啦。\n";

        if (item->is_item_make())
                return "这个东西太招摇了，还是别拿出来贩卖。\n";

        if( query("wiz_only", item) && !wizardp(me) )
                return "这个东西只能在巫师商店里卖。\n";

        if (item->is_character())
                return "你不能贩卖活物。\n";

        if( query("money_id", item) )
                return "你把钱也拿来出售？\n";

        switch(query("equipped", item)){
        case "worn":
                return item->name() + "必须先脱下来才能存放。\n";

        case "wielded":
                return item->name() + "必须先解除装备才能存放。\n";
        }

        if (sizeof(all_goods) >= 80)
                return "你店铺上的东西太多了，先收几种货物再摆吧。\n";

        if (item->query_amount() && item->query_amount() > 1)
        {
                obj = new(base_name(item));
                obj->set_amount((int)item->query_amount() - 1);
                item->set_amount(1);
                obj->move(me, 1);
        }

        name = item->name(1);
        add_one_good(item, value, 1);

        message_vision(HIW "$N" HIW "将『" HIG + name + HIW "』标上" HIY +
                (intp(value) ? MONEY_D->price_str(value) : (value+"NT")) + HIW "的价格开始出售。\n" NOR, me);
        room->save();

        return "你摆置好了货物。\n";
}

public string do_unstock(object ob, object me, string arg)
{
        object item, room;
        int i, n;

        seteuid(getuid());
        room = environment(ob);
        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if (! arg)
                return "指令格式：unstock <货物>\n";

        if (! (n = sizeof(all_goods)))
                return "你现在还没有摆上任何货物。\n";

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED && !wizardp(me))
                return "你身上的东西太多了，没法从货架上取东西。\n";

        for( i = 0; i < n; i++ )
        {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                {
                        if( !(all_goods[i]->amount) ) {
                                all_goods[i] = 0;
                                return "现在"+query("short", room)+"的货架上并没有这样货物。\n";
                        }

                        all_goods[i]->amount -= 1;

                        if( !all_goods[i]->data )
                                item = new(all_goods[i]->file);
                        else
                        {
                                item = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                item->set_name(query("name", ob),all_goods[i]->ids);
                        }

                        if( all_goods[i]->amount == 0 )
                                all_goods[i] = 0;
                        break;
                }
        }
        all_goods -= ({ 0 });

        message_vision(HIW "$N" HIW "将『" HIG + item->name(1) + HIW"』从货架上取下来不卖了。\n" NOR, me);

        room->save();

        if (! item->move(me))
        {
                item->move(environment(me));
                tell_object(me, "可是你已经拿不动了，只好把" + item->name(1) + NOR "放在地上。\n");
        }
        return "你取好了货物。\n";
}

public varargs string do_list(object ob, object me, string arg)
{
        string output, desc;
        class goods item;
        object room;

        if( !wizardp(me) && me->query_condition("killer") )
                return CYN "店铺不做杀人犯的生意！\n" NOR;

        if( me->is_busy() ) {
                return BUSY_MESSAGE;
        }

        room = environment(ob);
        if( !query("shop_type", room) )
                return "对不起，该店铺目前已经被巫师关闭。\n";

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
                return "你是这家店铺不受欢迎的人物，无法购买东西。\n";

        if( !sizeof(all_goods) ) {
                return "现在"+query("short", room)+"目前并没有出售任何货物。\n";
        }

        output = "该店铺目前出售以下物品：\n";

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
                                  stringp(item->value) ? item->value + "$NT" : MONEY_D->price_str(item->value),
                                  desc);
        }

        if (query("invite/" + query("id",me),room))
                output += WHT"您是本店贵宾，购买所有货物均享受"HIW+chinese_number(query("invite/"+query("id",me),room))+HIW"折"NOR+WHT"的优惠。\n" NOR;
        return output;
}

public int do_buy(object obj, object me, string arg)
{
        mixed value;
        object ob;
        int i, n;
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

        n = sizeof(all_goods);
        if( !n ) {
                tell_object(me, "目前%s没有可以卖的东西。\n");
                return 1;
        }


        {
                tell_object(me, "该店铺并没有出售这样货物。\n");
                return 1;
        }

        for( i = 0; i < n; i++ ) {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg) {
                        if( !(all_goods[i]->amount) ) {
                                tell_object(me, sprintf("目前这%s" CYN "缺货，您过一段时间再来吧",
                                        all_goods[i]->name));
                                return 1;
                        }
                        break;
                }
        }

        value = all_goods[i]->value;

        // 如果是贵宾，则有优惠
        if (query("invite/" + query("id",me),room))
        {
                if (intp(value))
                        value = value * query("invite/" + query("id",me),room) / 10; 
                else
                        value = to_string(to_int(value) * query("invite/" + query("id",me), room) / 10); 
        }

        if (intp(value))
        {
                switch (SHOP_D->player_pay(me, obj, value))
                {
                case 0:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "冷笑道：穷光蛋，一边呆着去。\n" NOR);
                        return 1;

                case 2:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "皱眉道：您还有没有零钱啊？银票我可找不开。\n" NOR);
                        return 1;

                default:
                        if( !all_goods[i]->data )
                                ob = new(all_goods[i]->file);
                        else
                        {
                                ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                ob->set_name(query("name", ob),all_goods[i]->ids);
                        }
                        all_goods[i]->amount -= 1;
                        if( all_goods[i]->amount = 0 )
                                all_goods[i] = 0;
                        if (ob->query_amount())
                        {
                                message_vision("$N从$n那里买下了" + ob->short() + "。\n", me, obj);
                        }
                        else
                        {
                                message_vision("$N从$n那里买下了一"+query("unit", ob)+query("name", ob)+"。\n",me,obj);
                        }

                        ob->move(me, 1);
                }
        } else
        {
                string owner=query("owner", environment(obj));
                if (!MEMBER_D->player_pay(me, to_int(value), owner))
                {
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "冷笑道：你没有足够的$NT，还是先去冲值吧。\n" NOR);
                        return 1;
                }
                if( !all_goods[i]->data )
                        ob = new(all_goods[i]->file);
                else
                {
                        ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                        ob->set_name(query("name", ob),all_goods[i]->ids);
                }

                all_goods[i]->amount -= 1;
                if( all_goods[i]->amount = 0 )
                                all_goods[i] = 0;
                if (ob->query_amount())
                {
                        message_vision("$N从$n那里买下了" + ob->short() + "。\n", me, obj);
                }
                else
                {
                        message_vision("$N从$n那里买下了一"+query("unit", ob)+query("name", ob)+"。\n",me,obj);
                }

                ob->move(me, 1);

        }
        all_goods -= ({ 0 });
        me->start_busy(1);
        room->save();
        return 1;
}

string short()
{
        if (stringp(query("apply/short")))
                return query("apply/short");

        return query("short");
}

string long()
{
        switch (query("shop_type"))
        {
        // 店铺关闭时的描述
        case 0  : return query("long");
        // 店铺开放时的描述
        default :
                if (stringp(query("apply/long")))
                        return sort_string(query("apply/long"), 60, 4);
                else
                // 默认描述
                if (! stringp(query("open_long")))
                        return @LONG
这里是一间装饰得非常豪华的店铺，铺面宽敞明亮，柜子
上摆满了各式各样、琳琅满目的货物。此时一位伙计正忙里忙
外地招呼着客人。
LONG;
                // 特殊描述
                else return query("open_long");
        }
}

void setup()
{
        object waiter, ob;
        string *props;
        string prop;
        mapping m;

        ::setup();
        if (! restore())
                save();

        ob = this_object();
        waiter = present("huo ji", ob);

        if (waiter)
        {
                if( !mapp(m=query("waiter", ob)))return ;
                props = keys(m);

                if (! props) return;
                foreach (prop in props)
                {
                        if (prop == "name")
                                waiter->set_name(query("waiter/"+prop, ob),
                                                 waiter->parse_command_id_list());
                        set(prop,query("waiter/"+prop,  ob), waiter);
                }
        }
}

string query_save_file()
{
        string id;

        sscanf(base_name(this_object()), "/%*s/%*s/%s_shop", id);

        if (! stringp(id)) return 0;

        return sprintf(DATA_DIR "/shop/%s", id);
}

int save()
{
        string file;

        if (stringp(file = this_object()->query_save_file()))
        {
                assure_file(file + __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if (stringp(file = this_object()->query_save_file()) &&
            file_size(file + __SAVE_EXTENSION__) > 0)
                return restore_object(file);

        return 0;
}
