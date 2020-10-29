// jiangong 监工

#include <ansi.h>

inherit NPC;

mixed ask_mine();
mixed ask_transit();
int  do_move(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("监工", ({ "jian gong", "jiangong" }));
        set("long", "这是一个监工，手持长鞭，眼光一眨不眨的"
                    "盯着众人，口中吆喝个不停。\n");
        set("gender", "男性");
        set("age", 32);
        set_skill("unarmed", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);

        set("combat_exp", 500000);
        set("shen_type", 1);
        set("inquiry", ([
            "job"  : "你是想采矿(mine)啊，还是运货(transit)？",
            "工作" : "你是想采矿(mine)啊，还是运货(transit)？",
            "采矿" : (: ask_mine :),
            "mine" : (: ask_mine :),
            "运货" : (: ask_transit :),
            "transit" : (: ask_transit :),
        ]));
        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
                "监工喝道：快！快给我干！\n",
                "监工一扬鞭子，骂道：他奶奶的，你给我放老实点。\n",
                "监工打量着四周，不知道在打什么主意。 \n",
                "监工狠狠的抽了一个人几下，骂道：怎么把矿石掉到地上了，你这笨蛋。\n",
        }));

        carry_object("clone/weapon/changbian")->wield();
}

void init()
{
        add_action("do_mine", "mine");
}

mixed ask_mine()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/mine", me) )
                return "不是让你去采么？你干完了？少在我面前玩花样！";

        if( query("combat_exp", me)<800000 )
                return "滚开，就你这点本事，下井被砸死都不知道。";

        if( query("qi", me)<120 )
                return "我看你已经快死了，还是快滚吧！";

        if (me->query_str() < 28)
                return "我说你有多点力气，也来凑热闹？";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/mine", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "现在已经有" + obs[0]->name() + "干活呢，你歇着吧。";

        set_temp("job/mine", 1, me);
        return "好，你下井去采(mine)些矿石上来，放到那边的车上，干了活官府自然会给钱。";
}

int do_mine(string arg)
{
        object me;
        object *obs;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，别着急。\n");

        if( !query_temp("job/mine", me) )
                return notify_fail("你又没领活，瞎忙活啥？\n");

        // 查看当时采矿的有多少人
        obs = filter_array(all_inventory(environment(me)),
                           (:userp($1) && query_temp("job/step", $1):));
        if (sizeof(obs) >= 10)
                return notify_fail("现在采矿的人好多，排"
                                   "队等着下井，你只好先等会儿。\n");

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "你开始工作。\n");
        return 1;
}

int working(object me)
{
        string msg;
        int finish;
        int b;
        object bonus;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/mine", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        switch(query_temp("job/step", me) )
        {
        case 1:
                me->receive_damage("qi", 1);
                msg = "$N快步的朝井上走去。";
                break;
        case 2:
                me->receive_damage("qi", 1);
                msg = "$N走到井口，道：我是来采矿石的。";
                break;
        case 3:
                me->receive_damage("qi", 1);
                msg = "井口几个人看了看$N，一个人摆了摆手，让你坐到篮子里。";
                break;
        case 4:
                me->receive_damage("qi", 1);
                msg = "$N坐在篮中，井口的人开始放绳，只听吱吱嘎嘎的，你慢慢的向下坠去。";
                break;
        case 5:
                me->receive_damage("qi", 1);
                msg = "$N眼前越来越黑，可是绳子还是放个不停。";
                break;
        case 6:
                me->receive_damage("qi", 1);
                msg = "忽然$N的眼前一亮，原来是一盏油灯，昏暗的火焰不断的跳动。";
                break;
        case 7:
                me->receive_damage("qi", 1);
                msg = "绳子还是不断的向下放，漫漫似乎没有尽头。";
                break;
        case 8:
                me->receive_damage("qi", 1);
                msg = "篮子忽然停住了，看来是到了地方，$N不禁松了一口气。";
                break;
        case 9:
                me->receive_damage("qi", 3);
                msg = "$N看到有一些人正在努力的干活，$N连忙赶上去，也拿起铲子。";
                break;
        case 10:
                me->receive_damage("qi", 6);
                msg = "$N慢慢的收集蓝色的矿石，将它们放到篮中。";
                break;
        case 11:
                me->receive_damage("qi", 8);
                msg = "$N觉得分量差不多了，跨进篮中，拉了拉绳子。";
                break;
        case 12:
                me->receive_damage("qi", 1);
                msg = "等了片刻，篮子忽然晃了晃，$N渐渐的向上升了上去。";
                break;
        case 13:
                me->receive_damage("qi", 1);
                msg = "光线越来越亮，终于到了洞口，只见井口几个人忙得满头大汗。";
                break;
        case 14:
                me->receive_damage("qi", 7);
                msg = "$N不及道谢，连忙扛起篮子，奔大车去了。";
                break;
        case 15:
                me->receive_damage("qi", 6);
                msg = "$N赶到大车旁边，“哗啦啦”将矿石撒到车中。";
                break;
        default:
                me->receive_damage("qi", 4);
                msg = "$N摸了摸了汗，看看空篮子，总算是干完一趟了。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                if (me->query_str() >= 35)
                        msg += "$n看了$N采上来的矿石，点点头道：很好"
                               "！这一趟弄了不少啊！\n";
                else
                        msg += "$n看了$N搬的石料，道：还行，马马虎虎"
                               "吧。走，那边领工钱去。\n";

                // 本地矿石增多
                environment(me)->improve_product_amount("cuprum_ore",
                                                        10 + (me->query_str() - 28));

                delete_temp("job/mine", me);
                delete_temp("job/step", me);

                if( query("combat_exp", me)<5000000 )
                {
                        b = 1000 + random(1700);
                        GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));
                        me->improve_skill("unarmed", (b + 1) / 2);
                }

                bonus = new("/clone/money/coin");
                bonus->set_amount(150 + (me->query_str() - 28) * 10);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);
        if (finish)
        {
                tell_object(me, "你去管事的那里领到了工钱。\n");
                bonus->move(me, 1);
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N摇摇头，没说话，只是不干了。\n", me);
        delete_temp("job/mine", me);
        delete_temp("job/step", me);
        return 1;
}

mixed ask_transit()
{
        string startroom;
        int c;
        object ob;
        object me;
        int amount;

        if (! stringp(startroom = query("startroom")) ||
            find_object(startroom) != environment())
                // not in start room
                return "我...我有点头晕...";

        me = this_player();

        if( query("score", me)<1000 )
                return "我看你这人阅历太浅啊，可不敢让你运货。";

        if( query("combat_exp", me)<150000 )
                return "不行不行，你这人本事太差，路上别把货都丢了！";

        if( objectp(query_temp("job/hz_cart", me)) )
                return "上次让你送的你完事了么？快去！少和我罗嗦！";

        if( (amount=query("job/hz_cuprum_ore", me))>0 )
        {
                amount = (amount + 99) / 100;
                // 五天(MUD时间)内如果货物还没有送达，则不能领
                message_sort("$N冷笑一声，对$n道：“" + me->name(1) +
                             "，上次你送的货...哼！看在你本事"
                             "低微的份上，我不多加追究了，可"
                             "是那车铜矿石岂能就这样白白的丢"
                             "了？你先赔了" + chinese_number(amount) +
                             "两黄金，冲抵铜价再说！”\n",
                             this_object(), me);
                return 1;
        }

        c = environment(me)->query_product_amount("cuprum_ore");
        if (c < 300)
                return "现在还没有多少矿石呢，不忙运走，你等等吧。";
        else
        if (c < 800)
                message_vision("$N看了看$n，道：“也好，虽然"
                               "现在还不多，不过也差不多了。”\n",
                               this_object(), me);
        else
        if (c < 1000)
                message_vision("$N点点头，对$n道：“好吧，就"
                               "快满一车了，就发了吧。”\n",
                               this_object(), me);
        if (c < 3000)
                message_vision("$N看到$n，招呼道：“正好，正"
                               "打算发车呢，就你来吧！”\n",
                               this_object(), me);
        else
        if (c < 8000)
                message_vision("$N连忙道：“快准备吧，这里已"
                               "经有好几车了！”\n",
                               this_object(), me);
        else
                message_vision("$N看到$n，大喜道：“正好！眼"
                               "看这库里就要满了，你来的正好！”\n",
                               this_object(), me);

        if (c > 1000) c = 1000;
        environment(me)->improve_product_amount("cuprum_ore", -c);

        // 生成交通工具
        ob = new("/clone/misc/cart");
        set_temp("goods/name", "铜矿石", ob);
        set_temp("goods/id", "cuprum_ore", ob);
        set_temp("goods/unit", "斤", ob);
        set_temp("goods/amount", c, ob);
        message_sort("$N一声呼喊，叫人推过一"+query("unit", ob)+
                     ob->name() + "来，这才对" + me->name() +
                     "道：“你把这车货物送到长安工部铜厂去，"
                     "你给我听好了：这可是朝廷的东西！丢了我"
                     "要你的脑袋！去吧！运到了自有赏格！”\n",
                     this_object(), me);
        tell_object(me,YEL+name()+"交给你一"+query("unit", ob)+
                        ob->name() + "。\n" NOR);
        ob->move(environment(me));
        ob->set_owner(me);

        // 记录这次任务的信息
        set("job/hz_cuprum_ore", c, me);
        set_temp("job/hz_cart", ob, me);
        set_temp("job/info", "hz_cuprum_ore", ob);
        set_temp("job/owner", me, ob);

        return 1;
}

int accept_object(object who, object ob)
{
        int amount;

        if( !query("money_id", ob) )
                return 0;

        if( (amount=query("job/hz_cuprum_ore", who))>0 )
        {
                amount = (amount + 99) / 100;
                if (ob->value() < amount * 10000)
                {
                        message_vision("$N看了看$n递过来的钱，大喝"
                                       "道：“就这点？一边儿去！”\n",
                                       this_object(), who);
                        return 0;
                }

                message_vision("$N鼻子哼了一声，接过" + ob->name() +
                               "，道：“算了，就不追究你了。”\n",
                               this_object(), who);
                delete("job/hz_cuprum_ore", who);
        } else
        {
                message_vision("$N眉开眼笑，把" + ob->name() +
                               "接了过来，收入包囊，却不理会$n。\n",
                               this_object(), who);
        }

        destruct(ob);
        return -1;
}
