#include <ansi.h>
#include <medical.h>

inherit NPC;
inherit F_DEALER;

string ask_job();
int do_peiyao(string arg);
int working(object me);
int halt_working(object me);
int ask_me();
int ask_riyue();
int do_join(string arg);
int do_unjoin(string arg);
int do_identify();
int do_decide();

void create()
{
        set_name("平一指", ({ "ping yizhi", "ping", "yizhi" }));
        //set("title", "药铺老板");
        set("title", HIW"炼药师协会"HIR"会长"NOR);
        set("nickname", HIB "杀人神医" NOR);
        set("gender", "男性");
        set("long", "他就是医术高超的「杀人神医」平一指。可是他性格古\n"
                    "怪，不是什么人都医的。\n");
        set("age", 65);

        set("int", 38);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("shen_type", 1);

        set("combat_exp", 500000);
        set("attitude", "heroism");

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 60);
        set_skill("liandan-shu", 2200);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 50);
        set("inquiry", ([
                "配药"   : (: ask_job :),
                "工作"   : (: ask_job :),
                "job"    : (: ask_job :),
                "疗伤"   : (: ask_me  :),
                "日月神教" : (: ask_riyue :),
                "入会"     : "在我这里，可以加入(" HIY "join" NOR +
                             CYN ")炼药师协会。\n" NOR,
                "加入"     : "在我这里，可以加入(" HIY "join" NOR +
                             CYN ")炼药师协会。\n" NOR,
                "鉴定"     : "在我这里，可以鉴定(" HIY "jianding" NOR +
                             CYN ")炼药师品级。\n" NOR,
                "炼药师协会" : "在我这里，可以加入(" HIY "join" NOR +
                             CYN ")炼药师协会。\n" NOR,
        ]));

        set("vendor_goods", ({
                HERB("chaihu"),         // 柴胡
                HERB("chenpi"),         // 陈皮
                HERB("chongcao"),       // 虫草
                HERB("chuanwu"),        // 川乌
                HERB("dahuang"),        // 大黄
                HERB("dangui"),         // 当归
                HERB("duhuo"),          // 独活
                HERB("fangfeng"),       // 防风
                HERB("fuzi"),           // 附子
                HERB("gsliu"),          // 干石榴
                HERB("guiwei"),         // 归尾
                HERB("hafen"),          // 蛤粉
                HERB("heshouwu"),       // 何首乌
                HERB("honghua"),        // 红花
                HERB("huangqi"),        // 黄芪
                HERB("lurong"),         // 鹿茸
                HERB("xiongdan"),       // 熊胆
                HERB("juhua"),          // 菊花
                HERB("lanhua"),         // 兰花
                HERB("lingxian"),       // 灵仙
                HERB("lingzhi"),        // 灵芝
                HERB("mahuang"),        // 麻黄
                HERB("moyao"),          // 没药
                HERB("niuhuang"),       // 牛黄
                HERB("niuxi"),          // 牛膝
                HERB("qianjinzi"),      // 千金子
                HERB("renshen"),        // 人参
                HERB("ruxiang"),        // 乳香
                HERB("shadan"),         // 鲨胆
                HERB("shancha"),        // 山茶花
                HERB("shanjia"),        // 山甲
                HERB("shengdi"),        // 生地
                HERB("shenglg"),        // 生龙骨
                HERB("sumu"),           // 苏木
                HERB("taoxian"),        // 桃仙
                HERB("tenghuang"),      // 藤黄
                HERB("tianqi"),         // 田七
                HERB("tugou"),          // 土狗
                HERB("wulingzhi"),      // 五灵脂
                HERB("xiefen"),         // 蝎粉
                HERB("xijiao"),         // 犀角
                HERB("xionghuang"),     // 雄黄
                HERB("xuejie"),         // 血竭
                HERB("xuelian"),        // 雪莲
                HERB("yanwo"),          // 燕窝
                HERB("yjhua"),          // 洋金花
                HERB("yuanzhi"),        // 远志
                HERB("zihua"),          // 紫花
                HERB("zzfen"),          // 珍珠粉
                HERB("hugu"),           // 虎骨
                "/clone/misc/yanbo",    // 研钵
                "/clone/drug/tianqi-san",
                "/d/city/obj/shanshen",
                "/clone/medicine/jinmisan",
                "/clone/book/medical_book",
        }));

        setup();
        add_money("silver", 50);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_peiyao", "peiyao");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_join", "join");
        add_action("do_decide", "decide");
        add_action("do_identify", "jianding");
        add_action("do_unjoin", "unjoin");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/peiyao", me) )
                return "让你干的活你干完了么？";

        if( query("combat_exp", me)>300000 )
                return "让你干这活，也太屈就你了吧。";

        if( query("combat_exp", me)<30000 )
                return "就这点经验，连一百五都没有，我看你来药臼都端不起来！";

        if( query("qi", me)<5 )
                return "你还是先歇歇吧，万一累出人命来我可负担不起。";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/peiyao", $1) &&
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "我这已经有" + obs[0]->name() + "在干活了，你等等吧。";

        set_temp("job/peiyao", 1, me);
        return "好，你就帮我配药(peiyao)吧！喏，就这几味。";
}

int do_peiyao(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，别着急。\n");

        if( !query_temp("job/peiyao", me) )
        {
                message_vision("$N刚想抓几味药配制，就听见$n怒喝道："
                               "给我放下，别乱动。\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "你开始工作。\n");
        return 1;
}

int working(object me)
{
        object ob;
        string msg;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/peiyao", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("qi", 1);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N东挑西拣，选好了一些药材。";
                break;
        case 2:
                msg = "$N把药材放进药臼，使劲捣了起来。";
                break;
        case 3:
                msg = "药材渐渐化作粉屑，混在一起。";
                break;
        case 4:
                msg = "粉屑在$N的捣弄下越来越细，逐渐变成了粉末。";
                break;
        default:
                msg = "$N把药材包好，递给$n。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n看了$N配的药，点头道：不错，不错！"
                       "这是给你的报酬！\n";
                delete_temp("job/peiyao", me);
                delete_temp("job/step", me);

                b = 5000 + random(800);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                ob = new("/clone/money/coin");
                ob->set_amount(10);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/wrists", me) && random(10) == 1)
                {
                        msg = "$n对$N嘿嘿一笑，道：干得不赖，有点"
                              "意思，这个神之祝福护腕就算是我送给你的礼物吧。\n";
                        message_vision(msg, me, this_object());
                        ob = new("/clone/goods/zhufu_wrists");
                        ob->move(me, 1);
                        tell_object(me, HIM "\n你获得了一个" + ob->name() +
                                        HIM "！\n" NOR);
                        set("zhufu_mod/wrists", 1, me);
                }
                else
                if (random(1000) == 1)
                {
                        msg = "$n对$N嘿嘿一笑，道：干得不赖，有点"
                              "意思，这个丹玉磨就算是我送给你的礼物吧。\n";
                        message_vision(msg, me, this_object());
                        ob = new("/clone/misc/dymo");
                        ob->move(me, 1);
                        tell_object(me, HIM "\n你获得了一个" + ob->name() +
                                        HIM "！\n" NOR);
                }

                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N把手中的活一甩，嚷嚷道：不干了，不干了！\n",
                       me);
        delete_temp("job/peiyao", me);
        delete_temp("job/step", me);
        return 1;
}

int accept_object(object who, object ob)
{
        object obj ;
        if( !query_temp("何首乌", who) )
        {
        message_vision("平一指对$N说：医一人，杀一人，老夫不收钱！\n", who);
                return 0 ;
        }
        if( query("money_id", ob) && ob->value() >= 50000 )
        {
                destruct(ob);
                message_vision("平一指收下了$N的钱，给了$N一株何首乌！\n" , who);
                delete_temp("何首乌", this_player());
                obj=new(__DIR__"obj/shouwu");
                obj->move(this_player());
        }
        return 1;
}

int ask_me()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "日月神教" )
        {
                command("say 老夫医一人杀一人，不怕死就来吧。\n");
                return 1;
        }
        if( query("eff_qi", ob) == query("max_qi", ob) )
        {
                command("say 你又没有受伤，来逍遣老夫吗？\n");
                return 1;
        }
        else
        {
                message_vision("平一指手指微屈，单指一弹，一粒药丸疾射入$N的咽喉，$N"
                                "不由“咕噜”一声吞入腹中，顿感神清气爽，精神饱满。\n", ob);
                set("eff_qi",query("max_qi",  ob), ob);
                set("eff_jing",query("max_jing",  ob), ob);
                command("say 哼，我日月神教武功独霸武林，你好好去学学，别再丢人现眼了，快滚吧。\n");
                return 1;
        }
}

int ask_riyue()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "日月神教" )
                return notify_fail("我日月神教他日必一统江湖。\n");

        message("vision", "平一指飞起一脚，已将" + ob->name() + "踢得无影无踪。\n", environment(ob), ob);
        ob->move("/d/heimuya/midao7");
        tell_object(ob, "平一指飞起一脚，将你踢进了秘道。\n");
        return 1;
}

int do_join(string arg)
{
        object me = this_player();

        if (! arg || arg != "炼药师协会")
                return notify_fail(CYN "平一指一楞，说道：你要加入什么？我"
                                   "这里是炼药师协会。\n" NOR);

        if( me->query_skillo("liandan-shu", 1) < 300 )
                return notify_fail(CYN "平一指皱了皱眉，说道：想加入炼药师"
                                   "协会，必须具备一品炼药师资格，你可以先"
                                   "从我这里学点炼丹技艺(liandan-shu)。\n" NOR);

        if( query("is_alchemy", me) )
                return notify_fail(CYN "平一指皱了皱眉，说道：你不是已经加"
                                   "入炼药师协会了么？\n" NOR);

        if( query("bad_alchemy", me) )
                return notify_fail(CYN "平一指冷笑一声，说道：既然你已经脱"
                                   "离了炼药师协会，又回来作甚？\n" NOR);

        tell_object(me, CYN "\n平一指点了点头，说道：你真的打算(" HIY "dec"
                        "ide" NOR + CYN ")加入炼药师协会么？可考虑清楚了？"
                        "\n" NOR);
        set_temp("want_join", 1, me);
        return 1;
}

int do_unjoin(string arg)
{
        object me = this_player();

        if (! arg || arg != "炼药师协会")
                return notify_fail(CYN "平一指皱了皱眉，说道：你打算脱离什"
                                   "么？说话不清不楚的。\n" NOR);

        if( !query("is_alchemy", me) )
                return notify_fail(CYN "平一指冷笑一声，没理你。\n" NOR);

        tell_object(me, CYN "\n平一指叹了口气，说道：如果脱离炼药师协会，以后"
                        "可不能反悔。你真打算(" HIY "decide" NOR + CYN ")"
                        "这么做么？\n" NOR);
        set_temp("want_tuoli", 1, me);
        return 1;
}

int do_decide()
{
        object ob, me;
        int level;
        string *pro;
        me = this_player();

        if( query_temp("want_join", me) )
        {
                message_vision(HIC "$N" HIC "对着$n" HIC "微笑道：炼药师"
                               "可是最荣耀的职业，以后好好干吧。\n" NOR,
                               this_object(), me);

                level = me->query_skillo("liandan-shu", 1);
                set("is_alchemy", level/300, me);
                delete_temp("want_join", me);

                ob = new("/clone/misc/yaoshi-zheng");
                set("level", level/300, ob);
                ob->enable();
                ob->move(this_object());
                command("give yaoshi zheng to "+query("id", me));

                set("bindable", 3, ob);
                set("bind_owner",query("id", me), ob);
                set("owner",query("id", me), ob);
                set("no_store", 1, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);

                pro = query("profession", me);
                if( !pro ) pro = ({});
                pro += ({ "alchemy" });
                set("profession", pro, me);
                return 1;
        } else
        if( query_temp("want_tuoli", me) )
        {
                message_vision(HIC "$N" CYN "对着$n" HIC "点点头，人各有"
                               "志，从此以后你我再无瓜葛。\n" NOR,
                               this_object(), me);

                delete("is_alchemy", me);
                set("bad_alchemy", 1, me);
                delete_temp("want_tuoli", me);

                pro = query("profession", me);
                pro -= ({ "alchemy" });
                set("profession", pro, me);

                if (objectp(ob = present("yaoshi zheng", me)));
                {
                        message_vision(HIR "$N" HIR "将$n" HIR "的" NOR +
                                       ob->name(1) + HIR "注销了。\n" NOR,
                                       this_object(), me);
                        destruct(ob);
                }
                return 1;
         }

         return notify_fail(CYN "平一指瞄了你一眼，皱了皱眉，没理你。\n" NOR);
}

int do_identify()
{
        int level;
        object ob, me = this_player();

        if( query("bad_alchemy", me) )
                return notify_fail(CYN "平一指不耐烦道：走开，走开。你又回"
                                   "来作甚？\n" NOR);

        if( !query("is_alchemy", me) )
                return notify_fail(CYN "平一指瞄了你一眼，没理你。\n" NOR);

        if( objectp(ob = present("yaoshi zheng", me)) )
                destruct(ob);

        level = me->query_skillo("liandan-shu", 1);
        set("is_alchemy", level/300, me);

        ob = new("/clone/misc/yaoshi-zheng");
        set("level", level/300, ob);
        ob->enable();
        ob->move(this_object());
        command("give yaoshi zheng to "+query("id", me));

        set("bindable", 3, ob);
        set("bind_owner",query("id", me), ob);
        set("owner",query("id", me), ob);
        set("no_store", 1, ob);
        set("auto_load", 1, ob);
        set("set_data", 1, ob);

        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if (skill != "liandan-shu")
                return 0;

        if (ob->query_skillo("liandan-shu", 1) >= 300)
        {
                write(CYN "平一指点了点头，说道：炼丹技艺的提"
                      "高需要不断从实践中来提升的，炼丹技艺的\n"
                      "基本功我就教到这里，剩下看你的天赋和修行了。\n" NOR);
                return -1;
        }
        return 1;
}
