// smith.c

#include <ansi.h>
#include <mine_def.h>

inherit NPC;
inherit F_DEALER;

string ask_me();
int  do_gu(string arg);
int  do_dapi(string arg);
int  do_cuihuo(string arg);
int  do_repair(string arg);
void reward(object me);
protected void rong_he(object, object);
string identify_mine_stone(object who);
protected string *can_epurate = ({
        IRON_MINE,
        IRON_RES_CU,
        IRON_RES_JING,
        BLACK_IRON,
});

// no create_function: inherit by other NPC

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_look", ({"guankan", "kan"}));
        add_action("do_gu", "gu");
        add_action("do_dapi", "dapi");
        add_action("do_cuihuo", "cuihuo");
        add_action("do_repair", "repair");
        add_action("do_repair", "xiuli");
        add_action("do_epurate", "tilian");     // 提炼、精炼矿
        add_action("do_ronghe", "ronghe");
}

void setup()
{
        set("inquiry/job",    (: ask_me :));
        set("inquiry/工作",   (: ask_me :));
        set("inquiry/repair", "你想要修(repair)点什么？");
        set("inquiry/修理",   "你想要修(repair)点什么？");
        set("inquiry/鉴定",   (: identify_mine_stone :));

        ::setup();
}

string ask_me()
{
        object me = this_player();

        if (query("combat_exp", me) > 150000)
                return "让您老干这个未免屈尊了吧？";

        if (query("qi", me) < 50)
                return "你还是歇会儿吧！要是出了人命我可承担不起。";

        if (query_temp("smith/gu", me))
                return "让你鼓风箱，你怎么还磨蹭(gu)？";

        if (query_temp("smith/dapi", me))
                return "叫你打的坯你打了没有(dapi)？";

        if (query_temp("smith/cuihuo", me))
                return "干活怎么尽偷懒？快给我淬火去(cuihuo)！";

        switch(random(3))
        {
        case 0:
                set_temp("smith/gu", 1, me);
                return "好！你帮我鼓一会儿风箱(gu)。";

        case 1:
                set_temp("smith/dapi", 1, me);
                return "这样吧，你帮我打一下坯吧(dapi)！";

        case 2:
                set_temp("smith/cuihuo", 1, me);
                return "去帮我把这些刚出炉的淬一下火(cuihuo)。";
        }
}

int do_gu(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你现在正忙。\n");

        if (!query_temp("smith/gu", me))
        {
                message_vision("$n刚偷偷的拉起鼓风机，鼓了几阵风。"
                               "就听见$N对$n大喝道：滚开，乱搞什么。\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n拉起鼓风机拼命鼓了起来，$N看了点了点头。\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_dapi(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你现在正忙。\n");

        if (!query_temp("smith/dapi", me))
        {
                message_vision("$n拿起几块生铁，在手里掂了掂。"
                               "就听见$N对$n大喝道：放下，乱搞什么。\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n拿着锤子对刚出炉的火热的生铁用力敲打着，"
                        "$N“嗯”了一声，看上去有些满意。\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_cuihuo(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你现在正忙。\n");

        if (!query_temp("smith/cuihuo", me))
        {
                message_vision("$n刚抄起一个打造好的坯子，"
                               "就听见$N对$n大喝道：放下，别给我搞坏了。\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N用铁钳抄起一块火红的坯子，伸进了水"
                       "池，“哧”的一声轻烟四冒。\n",
                       me);
        reward(me);
        return 1;
}

void reward(object me)
{
        int exp, pot;
        object coin;
        object ob;

        delete_temp("smith/gu", me);
        delete_temp("smith/dapi", me);
        delete_temp("smith/cuihuo", me);

        coin = new("/clone/money/silver");
        coin->set_amount(1 + random(2));
        coin->move(this_object());
        message_vision("$N对$n道：这是给你的工钱。\n",
                       this_object(), me);
        command("give coin to " + query("id", me));
        if (! query("zhufu_mod/armor", me) && random(10) == 1)
        {
                ob = new("/clone/goods/zhufu_armor");
                //ob->move(this_object());
                message_vision("$N对$n嘿嘿一笑，道：干得不赖，有点意思，这个神之祝福护甲就算是我送给你的礼物吧。\n",
                               this_object(), me);
                ob->move(me, 1);
                //command("give zhufu armor to " + query("id", me));
                set("zhufu_mod/armor", 1, me);
        }
        if (query("combat_exp", me) < 100000)
        {
                exp = 2000 + random(300);
                pot = exp / 3;
                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
        }
        me->receive_damage("qi", 30 + random(20));
        me->start_busy(1);
}

int do_repair(string arg)
{
        object me;
        object ob;
        mixed  msg;
        int consistence;
        int cost;
        int max;
        mapping repair;

        if (! arg)
                return 0;

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上好像没有这样东西。\n");

        if (undefinedp(consistence = query("consistence", ob)))
                return notify_fail(ob->name() + "似乎不需要在这里修理吧？\n");

        if (undefinedp(max = query("max_consistence", ob)))
                max = 100;

        if (consistence == max)
                return notify_fail(ob->name() + "现在完好无损，修理做什么？\n");

        if (! undefinedp(msg = query("no_repair", ob)))
        {
                if (stringp(msg))
                        write(name() + "道：这我可修理不了。\n");
                else
                        write(name() + "道：" + msg);
                return 1;
        }

        if (mapp(repair = query_temp("pending/repair", me)) &&
            repair["item"] == ob)
        {
                if (me->is_busy())
                        return notify_fail("你现在正忙着呢！\n");

                notify_fail("你先带够了钱再说。\n");
                if (MONEY_D->player_pay(me, repair["cost"]) != 1)
                        return 0;

                message_vision("$n把" + ob->name() + "递给了$N。只见$N"
                               "拿起工具，东敲西补，将" + ob->name() +
                               "好好修了修。\n", this_object(), me);
                set("consistence", max, ob);
                message_vision("$N道：“好了！”随手把" + ob->name() +
                               "还给了$n，$n看了看，满意的掏出了一些钱"
                               "付了帐。\n", this_object(), me);
                me->start_busy(1 + random(max - consistence) / 20);
                delete_temp("pending/repair", me);
                return 1;
        }

        cost = (max - consistence) * query("value", ob) / 480;
        if (cost >= 100000) cost = ((cost - 100000) / 2 + 100000) / 10000 * 10000; else
        if (cost >= 10000)  cost = cost / 1000 * 1000; else
        if (cost >= 1000)   cost = cost / 100 * 100; else
        if (cost >= 100)    cost = cost / 10 * 10;

        msg = "$n拿出一" + query("unit", ob) + ob->name() +
              "，$N瞥了一眼，道：“要修好它得要" +
              MONEY_D->price_str(cost) + "才行。”\n";
        if (query("family/family_name", me) == "段氏皇族" &&
            ob->item_owner() == query("id", me))
        {
                cost /= 2;
                msg += "$n道：“呦，是您啊，不好意思，打个五折，就" +
                       MONEY_D->price_str(cost) + "吧！”\n";
        } else
        if (me->query_skill("higgling", 1) >= 30 && cost >= 50)
        {
                cost = cost * 500 / (me->query_skill("higgling", 1) + 500);
                switch (random(5))
                {
                case 0:
                        msg += "$n道：“大哥，看在我常年照顾你生意份上，还不给点折扣？”\n";
                        break;

                case 1:
                        msg += "$n道：“你们大老板可是我的熟人啊，这个，这个...”\n";
                        break;

                case 2:
                        msg += "$n道：“这位大哥好，您最近生意这么好... 给点折扣如何？”\n";
                        break;

                case 3:
                        msg += "$n道：“太贵了，我实在没这么多了，便宜点，便宜点就好。”\n";
                        break;

                case 4:
                        msg += "$n道：“我急修，这样吧，下次我一定给足，这次您就行个好，便宜点吧。”\n";
                        break;
                }

                if (cost >= 1000)
                        cost = cost / 100 * 100;
                else
                        cost = cost / 10 * 10;
                msg += "$N耸耸肩道：“算了，算了，那就" +
                       MONEY_D->price_str(cost) +
                      "好了。”\n";
        }

        message_vision(msg, this_object(), me);
        tell_object(me, YEL "如果你的确想修理这件物品，请再输入一次这条命令。\n" NOR);
        set_temp("pending/repair/item", ob, me);
        set_temp("pending/repair/cost", cost, me);
        return 1;
}

string identify_mine_stone(object who)
{
        object *inv;

        if(!who)
                return 0;

        if(!sizeof(inv = filter_array(all_inventory(who), (: $1->is_mine_stone() && !$1->query_check() :))))
                return "你身上没有需要鉴定的矿石。\n";

        inv->set_check_flag(1);
        return sprintf("都鉴定好了%s。\n",!random(3)?"，没什么值钱的东西":"");
}

int do_epurate(string arg)
{
        object tg, ob, me = this_player();
        string mcs, cmcs;
        int ew, value, rtn;

        if(this_object()->is_busy())
                return notify_fail(sprintf("%s说道：等会儿，正忙着呢。\n", name()));

        if(!arg || !objectp(ob = present(arg, me)))
                return notify_fail("你要提炼什么？\n");

        if(ob->is_mine_stone())         // 提炼矿石
        {
                if(!ob->query_check())
                        ob->set_check_flag(1);

                if( !(mcs = ob->query_mine_class())
                ||  !(cmcs = MINE_D->chinese_mine_class(mcs))
                ||  (member_array(mcs, can_epurate) == -1) )
                        return notify_fail(sprintf("%s摇摇头说道：这里不含任何矿物成份。\n", name()));

                if( (ew = ob->query_eff_weight()) < 1 )
                        return notify_fail(sprintf("%s摇摇头说道：这里含的%s太少了，没法提炼。\n", name(), cmcs));

                if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
                        return notify_fail(sprintf("%s摇摇头说道：这块矿石没法提炼。\n", name()));

                value = MINE_D->query_mine_class_value(tg->query_mine_class()) * ew * 3 / 10;
                if(value < 1)
                        value = 1;

                if(!(rtn=MONEY_D->player_pay(me,value)) || (rtn == 2))
                {
                        destruct(tg);
                        return notify_fail(sprintf("%s说道：提炼这块矿石里的%s需要%s。\n",
                                this_object()->name(), cmcs, MONEY_D->money_str(value)));
                }

                message_vision("$N朝着$n点点头说道：等一会儿。\n", this_object(), me);

                call_out("epurate_it", 1+random(2), me, ob, tg);
                return 1;
        }

        else if(ob->is_iron_class_res())        // 精炼
        {
                int upq;

                if( !(mcs = ob->query_mine_class())
                ||  !(cmcs = MINE_D->chinese_mine_class(mcs))
                ||  (member_array(mcs, can_epurate) == -1)
                ||  !(upq = MINE_D->query_mine_class_up_quantity(mcs)) )
                        return notify_fail(sprintf("%s摇摇头说道：这东西没法再精炼了。\n", this_object()->name()));

                if( (ew = ob->query_weight()/100) < upq )
                        return notify_fail(sprintf("%s摇摇头说道：对%s精炼至少需要 %d 两，这块%s不够。\n",
                                this_object()->name(),cmcs, upq, cmcs));

                if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
                        return notify_fail(sprintf("%s摇摇头说道：我这没法对%s进行精炼了。\n", this_object()->name(), cmcs));

                ew /= upq;
                value = (MINE_D->query_mine_class_value(tg->query_mine_class()) -
                        MINE_D->query_mine_class_value(mcs)*upq) * ew/2;

                if(value < 10)
                        value = 10;

                if(!(rtn=MONEY_D->player_pay(me,value)) || (rtn == 2))
                {
                        destruct(tg);
                        return notify_fail(sprintf("%s说道：对这块%s进行精炼需要%s。\n",
                                name(), cmcs, MONEY_D->money_str(value)));
                }

                destruct(ob);
                tg->set_weight(ew*100);
                if(!tg->move(me) && !tg->move(environment()))
                {
                        destruct(tg);
                        return notify_fail("异常超重，向巫师报告吧。\n");
                }

                rong_he(me, tg);
                write(sprintf("%s点点头说道：好了，拿去吧。\n", name()));
                return 1;
        }

        else
                return notify_fail(sprintf("%s摇摇头说道：这东西没法提炼。\n", name()));
}

protected void epurate_it(object me, object ob, object tg)
{
        int ew;

        if(!ob || !me || !tg || (environment(me) != environment()))
        {
                if(tg)
                        destruct(tg);
                return;
        }

        ew = ob->query_eff_weight()*9/10;
        if(ew < 1)
                ew = 1;

        if(ob->query_mine_class() == BLACK_IRON)
                tg->set_sum(ew);
        else
                tg->set_weight(ew*100);

        destruct(ob);
        if(!tg->move(me) && !tg->move(environment()))
                destruct(tg);

        rong_he(me, tg);
        message_vision("$N朝着$n点点头说道：提炼好了，拿去吧。\n", this_object(), me);
}

int do_ronghe(string arg)
{
        object me = this_player(), ob;

        if(!stringp(arg)
        || !sizeof(arg)
        || !objectp(ob = present(arg, me))
        || !ob->is_iron_class_res() )
                return notify_fail("你要熔合什么？\n");

        rong_he(me, ob);
        write(sprintf("%s点点头说道：好了。\n", name()));
        return 1;
}

protected void rong_he(object me, object ob)
{
        object *inv;
        string cms;
        int wt;

        if(!objectp(me)
        || !objectp(ob)
        || !ob->is_iron_class_res()
        || !(cms = ob->query_mine_class()) )
                return;

        if( !sizeof(inv = filter_array(all_inventory(me), (: ($1->is_iron_class_res())
                && ($1->query_mine_class() == $(cms))
                && ($1 != $(ob)) :))) )
                return;

        if(cms == BLACK_IRON)
        {
                foreach(object tmp in inv)
                {
                        wt += tmp->query_sum();
                        destruct(tmp);
                }

                ob->add_sum(wt);
                return;
        }

        foreach(object tmp in inv)
        {
                wt += tmp->query_weight();
                destruct(tmp);
        }

        wt += ob->query_weight();
        ob->set_weight(wt);
}
