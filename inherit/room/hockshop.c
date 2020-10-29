// hockshop.c
// by Find.

#define sell_rate       7/10
#define pawn_rate       6/10

inherit ROOM;
inherit F_SAVE;

int do_sellt(object ob,object me);
mapping pawned_objects = ([]);

nosave int max_items = 60;
nosave int mudday_in_realtime_second = 1440;

/* 避免存物品 dummy 的出现。
 * 鉴于此服务的高系统负担，也不允许纯粹聊天
 * 类不稳定玩家占用高额系统资源。
 * 正式开放稳定后这两项标准还应提高，
 * 窃以为 age : 18, exp : 50000 较为合适。
 */
nosave int min_age = 15;        // 15岁以前不能典当。
nosave int min_exp = 20000;     // exp < 20000 不能典当
nosave int min_value = 1000;    // 价值小于 10 两银子的物品当铺不收

#ifdef WIZARD_FLAG
private int check_pawn_object(object me,object ob)
{
        string name;

        if(!objectp(me) || !objectp(ob))
                return 0;

        /* 无论是卖到当铺还是当到当铺的东西玩家均可以通过正常渠道接触到
           因此只要是 wiz_ob 物品就不允许流入当铺，无论动作人是不是巫师
        */
        if(ob->query_wiz_flag())
        {
                name = ob->name();
                log_file("shop",sprintf("%s 在 %s %s %s 被没收. %s\n",
                        geteuid(me),to_chinese(domain_file(base_name(this_object()))),
                        (ob->is_pawn_stamp())?"使用巫师动过手脚的当票":"卖巫师物品",
                        base_name(ob),ctime(time())));
                notify_fail(ob->name()+"是巫师物品被没收了，请立刻向天神发信做出解释！\n");
                destruct(ob);
                return 0;
        }
        else
                return 1;
}
#endif

string query_save_file()
{
        string name;

        name = base_name(this_object());
        if(name[0..0] == "/")
                name = name[1..];
        name = replace_string(name,"/","_");

        return DATA_DIR+"hockshop/"+name;
}

void setup()
{
        ::setup();
        seteuid(getuid());
        restore();
}

void init()
{
        add_action("do_value", ({"value", "gujia"}) );
        add_action("do_pawn", ({"pawn", "dang"}) );
        add_action("do_sell", "sell");
        add_action("do_retrieve", ({"redeem", "shu", "shuhui"}) );
        add_action("do_list", "list");
        add_action("do_buy", ({"buy","mai"}));
}

int do_value(string arg)
{
        object ob;
        int value;

        if( !arg || !(ob = present(arg, this_player())) )
                return notify_fail("你要拿什么物品给当铺估价？\n");

        if( query("money_id", ob) )
                return notify_fail("这是「钱」，你没见过吗？\n");

        if(ob->is_food())
                return notify_fail("食品留着自己吃吧。\n");
        if(ob->is_corpse())
                return notify_fail("这是谁的尸首快搬走，我们这还要做生意呢。\n");
        if(ob->is_weapon())
                return notify_fail("兵器小店可不敢收，你去铁匠铺问问吧。\n");
        if(ob->is_character())
                return notify_fail("小店奉公守法，不敢贩卖人口。\n");
        if(ob->is_ctl_ob() || ob->is_iron_class_res() || ob->is_self_object())
                return notify_fail("这样东西小铺可是不敢保存。\n");
        if(ob->is_poison())
                return notify_fail("毒物小店可不敢收！\n");
        if( query("no_drop", ob) )
                return notify_fail("这样东西本店不收。\n");
        if( query("no_sell", ob) )
                return notify_fail("这样东西本店不收。\n");

#ifdef WIZARD_FLAG
        if(!check_pawn_object(this_player(),ob))
                return 0;
#endif

        if(ob->query_credit_point_flag())
                return notify_fail(sprintf("%s一文不值。\n",query("name", ob)));

        value=query("value", ob);
        if(!value)
                value = ob->value();

        if( !value )
                return notify_fail(sprintf("%s一文不值。\n",query("name", ob)));
        if(value < min_value)
                return notify_fail(query("name", ob)+"价值太低，这不收。\n");

        else
        {
                value = value*price_ratio(this_object())/100;

                printf("%s价值%s。\n如果你要典当(pawn)，可以拿到%s及一张当票。\n如果卖断(sell)，可以拿到%s。\n",
                        query("name", ob),chinese_value(value),
                        chinese_value(value*pawn_rate), chinese_value(value*sell_rate));
        }
        return 1;
}

int do_pawn(string arg)
{
        object ob, stamp,me = this_player();
        int value,real_value,year,month,day,last_days,how;
        string time,redeem_time;

        if( !arg || !(ob = present(arg, me)) )
                return notify_fail("你要典当什么物品？\n");

        if( query("age", me)<min_age )
                return notify_fail("你年龄还太小，等长大一点再说吧。\n");
        if( query("combat_exp", me)<min_exp )
                return notify_fail("你的江湖阅历还太浅，等以后有了信誉再说吧。\n");

        if(PAWN_D->query_being_meeting())
                return notify_fail("『拍卖大会』期间暂时不办理典当、赎当事宜。\n");

        if( query("money_id", ob) )
                return notify_fail("这是「钱」，你没见过吗？\n");
        if(ob->is_food())
                return notify_fail("食品留着自己吃吧。\n");
        if(ob->is_corpse())
                return notify_fail("这是谁的尸首快搬走，我们这还要做生意呢。\n");
        if(ob->is_weapon())
                return notify_fail("兵器小店可不敢收，你去铁匠铺问问吧。\n");
        if(ob->is_character())
                return notify_fail("小店奉公守法，不敢贩卖人口。\n");
        if(ob->is_ctl_ob() || ob->is_iron_class_res() || ob->is_self_object())
                return notify_fail("这样东西小铺可是不敢保存。\n");
        if(ob->is_poison())
                return notify_fail("毒物小店可不敢收！\n");
        if( query("no_drop", ob) )
                return notify_fail("这样东西本店不收。\n");
        if( query("no_sell", ob) )
                return notify_fail("这样东西本店不收。\n");

#ifdef WIZARD_FLAG
        if(!check_pawn_object(me,ob))
                return 0;
#endif

        if(ob->query_credit_point_flag())
                return notify_fail(sprintf("%s一文不值。\n",query("name", ob)));

        if(!PAWN_D->can_pawn_ob(geteuid(me)))
                return notify_fail("你典当的东西还有很多没有赎回，小铺本小利微，不敢收你的当。\n");

        value=query("value", ob);
        if(!value)
                value = ob->value();

        if( !value )
                return notify_fail(sprintf("%s一文不值。\n",query("name", ob)));
        if(value < min_value)
                return notify_fail(query("name", ob)+"价值太低，这不收。\n");

        real_value = value;
        value = value*price_ratio(this_object())/100;
        value = value*pawn_rate;
        /*
                需记录数据：
                时间、地点、人物、物品
        */

        year = query_year();
        month = query_month();
        day = query_day_in_month();
        time = sprintf("%s创世%s年%s月%s日",MUD_NAME,(!year)?"元":chinese_number(year),
                chinese_number(month),chinese_number(day));
        month += 6;
        if(month > 12)
        {
                year += 1;
                month -=12;
                last_days = query_day( ({month,day}) ) + (365 - query_day(0));
        }
        else
                last_days = query_day( ({month,day}) ) - query_day(0);
        redeem_time = sprintf("%s创世%s年%s月%s日",MUD_NAME,(!year)?"元":chinese_number(year),
                chinese_number(month),chinese_number(day));


        stamp = new(__DIR__"obj/pawn_stamp");

        stamp->use_this_stamp(
                ({
                geteuid(me),
                base_name(ob),
                time()+mudday_in_realtime_second*last_days,
                base_name(this_object()),
                sprintf("兹收到：\n%s典当的破烂不堪%s一%s\n应于%s以前赎回\n赎回应付%s\n\n\t%s\n\t%s\n",
                        me->name(1),ob->name(),
                        query("unit", ob),redeem_time,chinese_value(real_value),
                        to_chinese(domain_file(file_name(this_object())))+
                        this_object(query("short", )),time )
                })
        );

        how = PAWN_D->pawn_one_object(stamp);

        if(!how)        // PAWN_D 出现错误。
        {
                destruct(stamp);
                return notify_fail("本点由于资金周转困难，暂时不收当了，请到别处看看吧。\n");
        }

        if(how == -1)
        {
                destruct(stamp);
                return notify_fail("你典当的东西还有很多没有赎回，小铺本小利微，不敢收你的当。\n");
        }

        stamp->move(me);
        pay_player(me, value);
        message_vision("$N把身上的"+query("name", ob)+"拿出来典当了"
                + chinese_value(value) + "，换得一张当票。\n", me);

        destruct(ob);
        return 1;
}

int do_sellob_filter(object ob)
{
        if(!objectp(ob))
                return 0;
        if( query("money_id", ob) )
                return notify_fail("这是「钱」，你没见过吗？\n");
        if(ob->is_food())
                return notify_fail("食品留着自己吃吧。\n");
        if(ob->is_corpse())
                return notify_fail("这是谁的尸首快搬走，我们这还要做生意呢。\n");
        if(ob->is_weapon())
                return notify_fail("兵器小店可不敢收，你去铁匠铺问问吧。\n");
        if(ob->is_character())
                return notify_fail("小店奉公守法，不敢贩卖人口。\n");
        if( query("no_drop", ob) )
                return notify_fail("这样东西本店不收。\n");
        if( query("no_sell", ob) )
                return notify_fail("这样东西本店不收。\n");
        else
                return 1;
}

int do_sell(string arg)
{
        object ob,*inv,me;
        int i;

        me=this_player();

        if(!arg)
                return notify_fail("你要卖断什么物品？\n");
        if(arg!="all")
        {
                if(!(ob = present(arg,me)))
                        return notify_fail("你要卖断什么物品？\n");

                if(!do_sellob_filter(ob))
                        return 0;

#ifdef WIZARD_FLAG
                if(!check_pawn_object(me,ob))
                        return 0;
#endif

                return do_sellt(ob,me);
        }

        else
        {
                inv = all_inventory(me);
                if(!sizeof(inv))
                        return notify_fail("你身上没有任何东西。\n");
                for(i=0; i<sizeof(inv); i++)
                {
                        if(!do_sellob_filter(ob))
                                continue;

#ifdef WIZARD_FLAG
                        if(!check_pawn_object(me,ob))
                                return 0;
#endif

                        else
                                do_sellt(inv[i],me);
                }
        }
        return 1;
}

int do_sellt(object ob,object me)
{
        int value;
        string file;

        if(!objectp(ob) || !objectp(me))
                return 0;

        value=query("value", ob);
        if(!value)
                value = ob->value();
        if(!value)
                return notify_fail(sprintf("%s一文不值。\n",query("name", ob)));
        if(value < min_value)
                return notify_fail(query("name", ob)+"价值太低，这不收。\n");

        value = value*price_ratio(this_object())/100;
        value = value * sell_rate;

        message_vision("$N把身上的"+query("name", ob)+"拿出卖了"+chinese_value(value)+"。\n",me);

        pay_player(me, value, ob->query_credit_point_flag()?1:0);

        if(ob->is_self_object() || ob->is_iron_class_res())
        {
                destruct(ob);
                return 1;
        }

        file = base_name(ob);

        if(!undefinedp(pawned_objects[file]))
        {
                if(pawned_objects[file] > 500)
                        pawned_objects[file] = 500;
                else if(pawned_objects[file] < 500)
                        pawned_objects[file]++;
        }

        else if(sizeof(pawned_objects) < max_items)
                pawned_objects += ([ file : 1 ]);
        else
        {
                map_delete(pawned_objects,keys(pawned_objects)[0]);
                pawned_objects += ([ file : 1 ]);
        }

        destruct(ob);
        save();

        return 1;
}

int do_retrieve(string arg)// 当票需进行 wiz_ob 检查
{
        object stamp, ob,me = this_player();
        int value,pay,flag;
        string ob_name;

        if(PAWN_D->query_being_meeting())
                return notify_fail("『拍卖大会』期间暂时不办理典当、赎当事宜。\n");

        if( !arg || arg=="" || !(stamp = present(arg, me)) )
                return notify_fail("你要赎回哪一张当票上的典物？\n");

        if( !stamp->is_pawn_stamp() )
                return notify_fail("这不是当票。\n");

#ifdef WIZARD_FLAG
        if(!check_pawn_object(me,stamp))
                return 0;
#endif

        if(stamp->query_master() != geteuid(me))
                return notify_fail("这张当票不是你的。\n");

        if( stamp->query_hockshop() != base_name(this_object()) )
                return notify_fail("这张当票不是咱这开出的，你去别的地方看看吧。\n");

        if(time() > stamp->query_rtime())
        {
                destruct(stamp);
                return notify_fail("这张当票上的物品已经过了赎当期。\n"+
                        "当铺的挡手把这张当票撕掉扔了。\n");
        }

        if( !(ob_name = stamp->query_pob_file())
        || !objectp(ob = new(ob_name)) )
                return notify_fail("没有这张当票上的物品，你的当票别是假的吧！\n"+
                        "当铺的挡手把这张当票撕掉扔了。\n");
        value=query("value", ob);
        if(!value)
                value = ob->value();
        if(!value)
        {
                destruct(ob);
                destruct(stamp);
                return notify_fail("没有这张当票上的物品，你的当票别是假的吧！\n"+
                        "当铺的挡手把这张当票撕掉扔了。\n");
        }

        pay = player_pay(me,value); // 赎回付全款
        if(!pay || pay == 2)
        {
                destruct(ob);
                return notify_fail(sprintf("赎回这张当票上的物品需要%s\n你身上的钱不够。\n",
                        chinese_value(value)));
        }

        flag = PAWN_D->redeem_one_object(stamp);
        if(!flag || flag == -1)
        {
                destruct(ob);
                destruct(stamp);
                return notify_fail("没有这张当票上的物品，你的当票别是假的吧！\n"+
                        "当铺的挡手把这张当票撕掉扔了。\n");
        }

        else
        {
                destruct(stamp);
                if(!flag = ob->move(me))
                {
                        ob->move(this_object());
                        write(sprintf("你拿不了更多的东西了，你赎回的%s给你放在地上了。\n",
                                ob->name()));
                }
                else
                        write(sprintf("这是你赎回的%s请收好。\n",ob->name()));
                return 1;
        }
}

int do_list(string arg)
{
        string msg,*items;
        int i,n,value;
        float rate;

        if(!sizeof(pawned_objects))
                return notify_fail("当铺里现在没有待出售的货物。\n");

        rate = price_ratio(this_object());

        msg = "当铺里现在有以下货物出售：\n";
        msg += sprintf(" %-26s%-10s%-10s\n","    商  品","  数量","   单  价");
        msg += "----------------------------------------------\n";

        items = keys(pawned_objects);
        n = sizeof(items);
        for(i=0;i<n;i++)
        {
                value=query("value", items[i]);
                if(!value)
                        value = items[i]->value();
                value = value*rate/100*9/10;
                msg += sprintf(" %-26s%-10s%s\n",clr_ansi(items[i]->short()),
                        sprintf("%-3d%s",pawned_objects[items[i]],query("unit", items[i])),
                        chinese_value(value));
        }

        msg += "\n";
        this_player()->start_more(msg);
        return 1;
}

int do_buy(string arg)
{
        int i,n,value,pay;
        object ob;
        string *items;

        if(!sizeof(pawned_objects))
                return notify_fail("当铺里现在没有待出售的货物。\n");

        if( !arg )
                return notify_fail("你要买什么东西？\n");

        items = keys(pawned_objects);
        n = sizeof(items);

        for(i=0;i<n;i++)
                if(items[i]->id(arg))
                        break;
        if( i >= sizeof(pawned_objects) )
                return notify_fail("你要买什么东西？\n");

        value=query("value", items[i]);
        if(!value)
                value = items[i]->value();

        value = value*price_ratio(this_object())/100*9/10;

        pay = player_pay(this_player(),value);
        if(!pay || (pay == 2))
                return notify_fail("你身上的钱不够。\n");

        ob = new(items[i]);
        if(pay == 3)
                ob->set_credit_point_flag();

        if( --pawned_objects[items[i]] <= 0)
                map_delete(pawned_objects,items[i]);
        save();

        if(!ob->move(this_player()))
                ob->move(this_object());
        message_vision("$N掏出钱买下一"+query("unit", ob)+ob->name()+"。\n",
                this_player() );

        return 1;
}
