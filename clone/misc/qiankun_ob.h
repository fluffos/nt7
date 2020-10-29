// Written by Lonely@chinamud.cn
// cruise_ob.c

#include <ansi.h>
#include <config.h>

inherit ITEM;
inherit F_NOCLONE;
inherit F_OBSAVE;

int is_cruise_ob() { return 1; }
int clean_up() { return 1; }
int store_item(object me, object ob, int amount);

class store {
        string name;
        string id;
        string *ids;
        string file;
        mapping data;
        mapping temp_data;
        int amount;
}
nosave class store *all = ({});
mixed query_store() { return all; }

void create()
{
        set_name(HIC"如意"HIM"乾坤袋" NOR, ({ "qiankun bag", "qiankun", "bag" }));
        set_weight(100);
        set("long", "一个四周边缘环绕着神秘光环的如意乾坤袋，大千世界尽可藏在其中。据说\n"
                    "可以将东西无限制的存（store）进去,不会丢失，且无论什么时候都可以取\n"
                    "（take）出来，最关键是还可以使用它将物品漫游到其他站。\n");

        set("unit", "个");
        set("no_sell", 1);
        set("no_get", 1);
        set("no_put", 1);
        set("no_give", 1);
        set("no_store", 1);
        setup();

        ::restore();
}

string extra_long()
{
        mixed ob_name_real_len;
        string msg;
        mapping in_data, en_data;
        string in_desc;

        if( !all || sizeof(all) < 1 )
                return "目前没有存放任何物品在如意乾坤袋里。\n";

        msg = HIW "\n目前你存放的物品有：\n编号  物品                            数量       属性\n"
                  "----------------------------------------------------------------\n" NOR;
        for( int i=0; i<sizeof(all); i++ ) {
#ifdef LONELY_IMPROVED
                ob_name_real_len = 0;
#else
                ob_name_real_len = color_len(all[i]->name + "(" + all[i]->id + ")");
#endif
                in_data = copy(all[i]->data);
                in_desc = "";
                if( sizeof(in_data) > 0 && !undefinedp(in_data["enchase"]) )
                {
                        en_data = copy(in_data["enchase"]);
                        if( !undefinedp(en_data["apply_prop"]) )
                        {
                                in_desc += "镶嵌属性：";
                                foreach( string key in keys(en_data["apply_prop"]) )
                                        in_desc += HIK + filter_color(EQUIPMENT_D->chinese(key, en_data["apply_prop"][key]),1) + NOR+",";
                        }
                        if( !undefinedp(en_data["weapon_prop"]) )
                        {
                                in_desc += "镶嵌兵器：";
                                foreach( string key in keys(en_data["weapon_prop"]) )
                                        in_desc += HIK + filter_color(EQUIPMENT_D->chinese(key, en_data["weapon_prop"][key]),1) + NOR+",";
                        }
                        if( !undefinedp(en_data["armor_prop"]) )
                        {
                                in_desc += "镶嵌防具：";
                                foreach( string key in keys(en_data["armor_prop"]) )
                                        in_desc += HIK + filter_color(EQUIPMENT_D->chinese(key, en_data["armor_prop"][key]),1) + NOR+",";
                        }
                        if( !undefinedp(en_data["rings_prop"]) )
                        {
                                in_desc += "镶嵌饰品：";
                                foreach( string key in keys(en_data["rings_prop"]) )
                                        in_desc += HIK + filter_color(EQUIPMENT_D->chinese(key, en_data["rings_prop"][key]),1) + NOR+",";
                        }
                        in_desc = in_desc[0..<2];
                }
                msg += sprintf("[%2d]  %-" + (26 + ob_name_real_len) + "s      %-11d%s\n",
                               i+1, all[i]->name + "(" + all[i]->id + ")",
                               all[i]->amount,in_desc);
                if( all[i]->amount == 0 )
                        all[i] = 0;
        }
        msg += HIW "----------------------------------------------------------------\n" NOR;
        all -= ({ 0 });
        return msg;
}

void init()
{
        add_action("do_store", ({ "store", "cun" }));
        add_action("do_take",  ({ "take",  "qu"  }));
}

int do_take(string arg)
{
        object me, ob;
        object *obs;
        int n, amount, num;
        mapping fun_data;
        string *ks;
        string k;
        string base_name;

        me = this_player();

        if( me->is_busy() ) return notify_fail("你正忙着呢。\n");

        if( !arg || sscanf(arg, "%d %d", n, amount) != 2 )
                return notify_fail("格式错误，请用 take 编号 数量 来取回物品。\n");

        if( amount < 1 || amount > 10000 )
                return notify_fail("每次取物品的数量不得小于一同时也不能大于一万。\n");

        if( n < 1 ) return notify_fail("你要取第几号物品？\n");

        if( !all || sizeof(all) < 1 || n > sizeof(all) )
                return notify_fail("你的如意乾坤袋里没有存放这项物品。\n");
        n--;
        if( amount > all[n]->amount )
                // return notify_fail("这样物品你没有那么多个。\n");
                amount = all[n]->amount;

        if( !(ob = new(all[n]->file)) ) {
                all[n] = 0;
                all -= ({ 0 });
                tell_object(me, "无法取出该物品，系统自动清除之。\n");
                return 1;
        }

        obs=filter_array(all_inventory(me),(:!query("equipped", $1):));
        if (sizeof(obs) >= MAX_ITEM_CARRIED &&
            ! ob->can_combine_to(me))
                return notify_fail("你身上的东西实在是太多了，没法再拿东西了。\n");

        base_name = base_name(ob);
        obs=filter_array(all_inventory(me),(:base_name($1) == $(base_name):));
        if( sizeof(obs) >= 3000 )
                return notify_fail("你身上的东西实在是太多了，没法再拿东西了。\n");

        if( me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance() ) {
                tell_object(me, "你的负重不够，无法一次取出这么多物品。\n");
                destruct(ob);
                return 1;
        }

        if( ob->query_amount() ) {
                all[n]->amount -= amount;
                if( all[n]->amount == 0 ) {
                        all[n] = 0;
                        all -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me, 1);
                save();

                message_vision("$N从如意乾坤袋里取出" + chinese_number(amount) +
                                query("base_unit", ob)+query("name", ob)+"。\n",me);
                return 1;
        }
        destruct(ob);

        if( amount > 100 ) amount = 100;
        all[n]->amount -= amount;
        num = amount;
        while( num-- ) {
                if( !all[n]->data && !all[n]->temp_data ) {
                        ob = new(all[n]->file);
                        ob->move(me, 1);
                        continue;
                }

                if( all[n]->data ) {
                           ob = TEMPLATE_D->create_object(all[n]->file, all[n]->id, all[n]->data);
                           ob->set_name(query("name", ob),all[n]->ids);
                }
                else
                           ob = new(all[n]->file);

                if( all[n]->temp_data )
                        ob->set_temp_dbase(all[n]->temp_data);

                if( mapp(fun_data=query("function", ob)) && sizeof(fun_data)){
                        ks = keys(fun_data);
                        foreach (k in ks)
                                call_other(ob, k, fun_data[k]);
                }

                if( query("bind_owner", ob) &&
                    query("bind_owner", ob) != query("id", me)){
                        all[n]->amount += amount;
                        tell_object(me, ob->name() + "已经绑定，无法移动。\n");
                        destruct(ob);
                        return 1;
                }

                if( query("equipped", ob))delete("equipped", ob);
                ob->move(me, 1);
        }

        message_vision("$N从如意乾坤袋里取出" + chinese_number(amount) +
                        query("unit", ob)+query("name", ob)+"。\n",me);

        if( !wizardp(me) && random(2) )
                me->start_busy(1);

        if( all[n]->amount == 0 ) {
                all[n] = 0;
                all -= ({ 0 });
        }
        save();
        return 1;
}

int do_store(string arg)
{
        int i, n, k, amount;
        string item;
        object me, ob1, ob2, *inv;

        me = this_player();

        if( !arg ) return notify_fail("你要存放什么东西？\n");

        if( me->is_busy() ) return notify_fail("你正在忙着呢！\n");

        n = 100;
        if( MEMBER_D->is_valid_member(me) )
                n += 200;
        if( k = me->qiankun_volume_srv() )
        {
                if( k > 3 ) k = 3;
                n += 200 * k;
        }
        if( sizeof(all) >= n )
        {
                return notify_fail("如意乾坤袋最多只能存入 " + n + " 个格子，请整理你的如意乾坤袋。\n");
        }

        if( arg == "all" ) {
                inv = all_inventory(me);
                inv -= ({ this_object() });
                inv -= ({ 0 });
                inv = filter_array(inv, (: !query("equipped", $1) :));
                n = sizeof(inv);
                if( n > 100 )
                {
                        tell_object(me, "你身上的物品太多了，很容易搞混，你还是一个一个存吧。\n");
                        return 1;
                }

                if( n < 1 )
                {
                        tell_object(me, "你身上没有任何物品。\n");
                        return 1;
                }

                for( i=0; i<n; i++ )
                {
                        do_store(query("id", inv[i]));
                }
                return 1;
        } else if (sscanf(arg, "%d %s", amount, item) == 2) {
                if( !objectp(ob1 = present(item, me)) )
                        return notify_fail("你身上没有这样东西。\n");

                if( !ob1->query_amount() )
                        return notify_fail(ob1->name() + "不能被分开存放。\n");

                if( amount < 1 )
                        return notify_fail("存东西的数量至少是一个。\n");

                if( amount > ob1->query_amount() )
                        return notify_fail("你没有那么多的" + ob1->name() + "。\n");

                if( amount == (int)ob1->query_amount() ) {
                        return store_item(me, ob1, amount);
                } else {
                        ob1->set_amount((int)ob1->query_amount() - amount);
                        ob2 = new(base_name(ob1));
                        ob2->set_amount(amount);
                        if( !store_item(me, ob2, amount) ) {
                                ob2->move(me, 1);
                                return 0;
                        }
                        return 1;
                }
        }

        if( !objectp(ob1 = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");

        if( ob1->query_amount() )
                return do_store(ob1->query_amount() + " " + arg);

        store_item(me, ob1, 1);
        return 1;
}

int store_item(object me, object ob, int amount)
{
        class store item;
        mapping data, temp_data;
        object obj;
        int i, n;
        string file, name, id;
        string unit;

        if( !objectp(ob) ) {
                error("no this object!\n");
                return 0;
        }

        if( file_size(base_name(ob) + ".c") < 0 )
                return 0;

        if( inherits(F_SILENTDEST, ob) ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，请你自己妥善处理。\n");
                return 0;
        }

        if( member_array(ITEM + ".c", deep_inherit_list(ob)) == -1 &&
            member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob)) == -1 ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，请你自己妥善处理。\n");
                return 0;
        }

        if( query("task_ob", ob) || query("unique", ob) ||
            query("no_store", ob) || ob->is_no_clone() || query("hj_game", ob) ||
            query("maze_item", ob) || ob->is_money() || query("no_put", ob)){
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，请你自己妥善处理。\n");
                return 0;
        }

        if( ob->is_character() || ob->is_item_make() || !clonep(ob) ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，请你自己妥善处理。\n");
                return 0;
        }

        if( sscanf(base_name(ob), "/data/%*s") && !ob->is_inlaid() ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，请你自己妥善处理。\n");
                return 0;
        }

        switch(query("equipped", ob)){
        case "worn":
                tell_object(me, ob->name() + "必须先脱下来才能存放。\n");
                return 0;
        case "wielded":
                tell_object(me, ob->name() + "必须先解除装备才能存放。\n");
                return 0;
        }

        if( sizeof(all_inventory(ob)) ) {
                tell_object(me,"请你先把"+query("name", ob)+"里面的东西先拿出来。\n");
                return 0;
        }

        name=query("name", ob);
        file = base_name(ob);
        id=query("id", ob);
        data = ob->query_entire_dbase();
        temp_data = ob->query_entire_temp_dbase();

        map_delete(data, "equipped");
        map_delete(data, "who_get");   // 去掉装备掉落时候get时间限制
        n = sizeof(all);
        obj = new(file);

        if( !ob->query_amount() && (query("set_data", ob) || !mapping_eqv(temp_data, obj->query_entire_temp_dbase())
        ||  !mapping_eqv(data, obj->query_entire_dbase())) ) {
                destruct(obj);
                unit = query("unit", ob);
                if( !undefinedp(data["shadow_ob"]) ) data["shadow_ob"] = 0;
                for( i=0;i<n;i++ ) {
                        if( all[i]->file == file &&
                            all[i]->id == id &&
                            all[i]->name == name ) {
                                if( mapping_eqv(data, all[i]->data) &&
                                    mapping_eqv(temp_data, all[i]->temp_data) ) {
                                        all[i]->amount += amount;
                                        save();
                                        message_vision("$N存入"+chinese_number(amount)+unit+
                                                        query("name", ob)+"到如意乾坤袋里。\n",me);
                                        destruct(ob);
                                        return 1;
                                }
                        }
                }

                item = new(class store);
                item->file = file;
                item->name = name;
                item->id = id;
                item->ids = ob->my_id();
                item->data = data;
                item->temp_data = temp_data;
                item->amount = amount;
                all += ({ item });
                save();
                message_vision("$N存入"+chinese_number(amount)+unit+
                                query("name", ob)+"到如意乾坤袋里。\n",me);
                destruct(ob);
                return 1;
        }
        destruct(obj);

        for( i=0;i<n;i++ ) {
                if( all[i]->file == file &&
                    all[i]->id == id &&
                    all[i]->name == name &&
                    !all[i]->data && !all[i]->temp_data ) {
                        all[i]->amount += amount;
                        save();
                        message_vision("$N存入"+chinese_number(amount)+(query("base_unit", ob)?query("base_unit", ob):query("unit", ob))+
                                        query("name", ob)+"到如意乾坤袋里。\n",me);
                        destruct(ob);
                        return 1;
                }
        }

        item = new(class store);
        item->file = file;
        item->name = name;
        item->id = id;
        item->ids = ob->my_id();
        item->amount = amount;
        all += ({ item });
        save();
        message_vision("$N存入"+chinese_number(amount)+(query("base_unit", ob)?query("base_unit", ob):query("unit", ob))+
                        query("name", ob)+"到如意乾坤袋里。\n",me);
        destruct(ob);
        return 1;
}

int receive_summon(object me)
{
        object env;

        if( (env = environment()) && env == me ) {
                write(name() + "不就在你身上嘛？你召唤个什么劲？\n");
                return 1;
        }

        if( env == environment(me) ) {
                message_vision(HIG "只见地上的" + name() +
                               HIG "化作一道光芒，飞跃至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else {
                if( env ) {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "化作一道"
                                HIG "光芒消失了！\n\n" NOR, env);

                        if( interactive(env = environment()) ) {
                                tell_object(env, HIM + name() +
                                                 HIM "忽然离你而去了！\n" NOR);
                        }
                }

                message_vision(HIG "一道光芒划过，只见$N"
                               HIG "掌中多了一个$n" HIG "！\n\n" NOR,
                               me, this_object());
        }

        //move(me, 1);
        if( !this_object()->move(me) )
                tell_object(me, HIR "由于你的负重太高，"+this_object()->name()+HIR "化作一道光芒，已然了无踪迹。\n" NOR);
        return 1;
}

int hide_anywhere(object me)
{
        if( query("jingli", me)<100){
                tell_object(me, "你试图令" + name() +
                            "遁去，可是精力不济，难以发挥它的能力。\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "轻轻一旋" + name() +
                       HIM "，已然了无踪迹。\n", me);
        save();
        destruct(this_object());
        return 1;
}

int receive_dbase_data(mixed data)
{
        if( !mapp(data) || sizeof(data) < 1 )
                return 0;

        if( data["all"] )
                all = data["all"];

        return 1;
}

mixed save_dbase_data()
{
        mapping data;

        data = ([]);

        if( sizeof(all) > 0 )
                data += ([ "all" : all ]);

        return data;
}
