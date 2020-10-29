// youxun.c
// pal 1997.05.28

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

nosave object *receiver;

object *query_receiver() { return receiver; }

int ask_fee();
int ask_bomb();
int ask_shedu();
int ask_duwan();
int ask_list();
int filter_listener(object user);

void create()
{
        set_name("游讯", ({ "you xun", "you", "xun", "youxun" }) );
        set("nickname", HIG "滑不留手" NOR);
        set("gender", "男性" );
        set("age", 42);
        set("long", "他就是专门打探、贩卖消息的游讯。\n");
        set("attitude", "friendly");

        set("max_jing", 500);
        set("max_qi", 500);
        set("str", 21);
        set("int", 29);
        set("con", 21);
        set("dex", 35);
        set("combat_exp", 250000);

        set("inquiry", ([
                "name" : "小的就是游讯，不知您要打听点什么？",
                "rumor": "不是小的吹牛，谁的谣言我都能查出来。",
                "fee"  : (: ask_fee :),
                "收费" : (: ask_fee :),
                "bomb" : (: ask_bomb :),
                "炸弹" : (: ask_bomb :),
                "蛇毒" : (: ask_shedu :),
                "毒药" : (: ask_duwan :),
                "核弹" : (: ask_list :),
                "打听" : "嘿嘿嘿，你想打听谁？鄙人消息那个灵通...",
                "核炸弹"   : (: ask_list :),
                "核子飞弹" : (: ask_list :),
                "核子炸弹" : (: ask_list :),
                "核子导弹" : (: ask_list :),
                "飞毛腿"   : (: ask_list :),
                "飞毛腿导弹": (: ask_list :),
                "矿泉水"    : "被飞弹炸了？来两瓶解解渴！",
                "发呆神功" : "想学么(idle-force)？鄙人教，不收钱的。",
        ]));

        set("vendor_goods", ({
                "/clone/gift/feidan",
                "/clone/gift/feimao",
                "/clone/gift/kuangquan",
        }));

        set("chat_chance", 1);
        set("chat_msg",({
                "游讯嘻嘻道：小的我没别的本事，就会打听消息，就算是巫师造谣，我也能知道。\n",
                "游讯亮出一指道：便宜啊，几两银子就能查条谣言，这可真是跳楼价。\n",
                "游讯贼眯眯的说：天算地算不如人算，可是再怎么算我游某都知道。\n",
        }));

        set_skill("dodge", 150);
        set_skill("unarmed", 50);
        set_skill("idle-force", 2100);

        setup();
        carry_object("d/city/obj/cloth")->wear();

        if (! clonep(this_object()))
        {
                move("/d/city/kedian");
                message_vision("$N笑嘻嘻道：来了来了，我来了。\n", this_object());
                set("startroom", "/d/city/kedian");
        }

        set_temp("bomb_count", 1);
}

/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/

mixed accept_ask(object ob, string topic)
{
        object fob, *obs;

        if( topic == query("id", ob) )
        {
                command("laugh " + topic);
                return 1;
        }

        if (topic[0] > 160)
        {
                if( time()-query_temp("ask_youxun_time", ob)<2 )
                {
                        tell_object(ob, HIY "游讯朝你一瞪眼睛：『别吵！问问题是吧？问那么急干嘛？』\n" NOR);
                        return 1;
                }

                set_temp("ask_youxun_time", time(), ob);
                obs = livings();
                obs -= users();
                obs = filter_array(obs, (: remove_ansi($1->name(1)) == $2 && environment($1) :), topic);
                if (sizeof(obs) > 4)
                {
                        obs = 0;
                        message_vision(CYN "$N" CYN "愤声暗骂，对$n"
                                CYN "瞪着眼睛道：『叫" + topic + "的人满大街都是，"
                                "自己不会找？』\n" NOR, this_object(), ob);
                        return 1;
                } else
                if (sizeof(obs) > 0)
                {
                        obs = 0;
                        set_temp("pending/ask_youxun", topic, ob);
                        /*
                        message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n"
                                CYN "小声道：『没有问题，不过得要一两黄"
                                "金，不二价！』\n" NOR, this_object(), ob);
                        */
                        tell_object(ob, CYN "游讯嘿嘿奸笑两声，对你"
                                        CYN "小声道：『没有问题，不过得要一两黄"
                                        "金，不二价！』\n" NOR);
                        return 1;
                } else
                        return;
        }

        fob = find_player(topic);
        if (! fob || ! ob->visible(fob)) fob = find_living(topic);
        if (! fob || ! ob->visible(fob) || ! environment(fob))
                return;

        set_temp("pending/ask_youxun", topic, ob);
        /*
        message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n"
                       CYN "小声道：“没有问题，不过得要10两"
                       "白银，不二价！”\n" NOR, this_object(), ob);
        */
        tell_object(ob, CYN "游讯嘿嘿奸笑两声，对你"
                        CYN "小声道：“没有问题，不过得要10两"
                        "白银，不二价！”\n" NOR);
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "idle-force")
        {
                if( me->add_temp("illegal_learn",1)>3 )
                {
                        command("say 滚！你烦不烦？！");
                        message_vision("$n一脚把$N踢出门外！\n",
                                       me, this_object());
                        set_temp("illegal_learn", 2, me);
                        me->move("/d/city/beidajie1");
                        me->unconcious();
                } else
                        command("say 我只教发呆神功，不传其它武功！");
                return -1;
        }

        message_vision("$N向$n请教发呆神功的诀窍。\n", me, this_object());

        if( query_temp("learned_idle_force", me) )
        {
                if( me->add_temp("too_many_xue",1)>3 )
                {
                        command("say 你好罗嗦！！！");
                        message_vision("$n飞起一脚把$N踢出门外！\n",
                                       me, this_object());
                        set_temp("too_many_xue", 1, me);
                        me->move("/d/city/beidajie1");
                        me->unconcious();
                } else
                        command("say 你先把我刚才教你的领悟好再说吧！");
                return -1;
        }

        command("say 听好了！发呆神功宗旨：!@#$%^&");

        if( query("potential", me)<query("learned_points", me)+10 )
        {
                write("你听得稀里糊涂，看来是潜能不够了。\n");
                return -1;
        }

        if (me->query_skill("idle-force", 1) > 2100)
        {
                write("你听完了心想，这些我都懂啊，看来游讯也就知道这么多了。\n");
                return -1;
        }

        set_temp("learned_idle_force", 1, me);
        addn("learned_points", 10, me);
        write(HIG "你听了心中颇有所得，马上进行发呆练习！\n" NOR);
        return -1;
}

void append_receiver(object ob)
{
        if (! receiver)
                receiver = ({ ob });
        else
                if (member_array(ob, receiver) == -1)
                        receiver += ({ ob });
}

int accept_object(object me, object ob)
{
        string wid;

        if (clonep(this_object()))
        {
                command("hehe");
                command("say 我是真游讯，如假包换啊！");
                return 1;
        }

        if (ob->id("visible bomb"))
        {
                command("say 不要了？那就还给我吧。");
                return 1;
        }

        if( !stringp(query("money_id", ob)) )
        {
                switch(query_temp("youxun_refused", me) )
                {
                case 0:
                        command("heihei");
                        command("say 这种破烂你留着吧。");
                        set_temp("youxun_refused", 1, me);
                        return 0;

                case 1:
                        message_vision("$N飞起一脚，把$n踢了出去，骂道：捣什么乱？\n",
                                       this_object(), me);
                        break;

                case 2:
                        message_vision("$N飞起一脚，狠狠的把$n踢了出去，骂道：还来捣乱？\n",
                                       this_object(), me);
                        me->receive_damage("qi", 100);
                        me->receive_wound("qi", 10);
                        break;

                default:
                        message_vision("$N大怒，一招万佛朝宗，就见$n像纸片一样飞了出去。\n",
                                       this_object(), me);
                        command("chat* heng "+query("id", me));
                        me->unconcious();
                        break;
                }

                addn_temp("youxun_refused", 1, me);
                me->move("/d/city/beidajie1");
                message_vision("只听“啪”的一声，$N狠狠的摔在了地上。\n", me);
                return -1;
        }

        if (ob->value() < 500)
        {
                message_vision("$N接过$n递过去的" + ob->name() +
                               "，皱了皱眉，道：就这点钱？算了，你不要就给我吧！\n",
                               this_object(), me);
                destruct(ob);
                return 1;
        }

        delete_temp("youxun_refused", me);
        if( stringp(wid=query_temp("pending/ask_youxun", me)) )
        {
                int    i;
                string msg;
                object fob, *obs;

                if (ob->value() < 1000 ||
                    (ob->value() < 10000 && wid[0] > 160))
                {
                        message_vision("$N冷笑一声道：“就这点钱？"
                                       "你还是打发鲁有脚还差不多。”\n",
                                       this_object());
                        return 0;
                }

                delete_temp("pending/ask_youxun", me);

                if (wid[0] > 160)
                {
                        obs = livings();
                        obs -= users();
                        obs = filter_array(obs, (: remove_ansi($1->name(1)) == $2 && environment($1) :) ,wid);
                        if (! sizeof(obs))
                        {
                                message_vision("$N挠挠头对$n道：“怪事... 刚"
                                               "才我还有他的消息呢，怎么这么一会儿...”\n",
                                               this_object(), me);
                                return 0;
                        }
                        msg = " \n据可靠消息，叫" + wid + "的一共有" +
                              chinese_number(sizeof(obs)) + "个人！\n";
                        for (i = 0; i < sizeof(obs); i++)
                                msg+=obs[i]->name(1)+"("+query("id", obs[i])+")"+
                                       "刚才在" + environment(obs[i])->short() + "。(" + LOOK_CMD->locate(base_name(environment(obs[i]))) + ")\n";
                        destruct(ob);
                        obs = 0;
                        //command("whisper " + me->query("id") + msg);
                        tell_object(me, WHT"游讯在你的耳边悄声说道：" + msg + "\n" NOR); 
                        return 1;
                }

                fob = find_player(wid);
                if (! fob || ! me->visible(fob)) fob = find_living(wid);
                if (! fob || ! me->visible(fob) || ! environment(fob))
                {
                        message_vision("$N挠挠头对$n道：“怪事... 刚"
                                       "才我还有他的消息呢，怎么这么一会儿...”\n",
                                       this_object(), me);
                        return 0;
                }

                destruct(ob);
                /*
                command("whisper"+query("id", me)+
                        " 据可靠消息，这个人刚才在" +
                        environment(fob)->short() + "。");
                */
                tell_object(me, WHT "游讯在你的耳边悄声说道：据可靠消息，这个人刚才在" +
                        environment(fob)->short() + "。\n" NOR);
                tell_object(me, HIC "游讯沉思了片刻，接着对你说道，听说"+LOOK_CMD->locate(base_name(environment(fob)))+"有这个地名。\n" NOR);
                return 1;
        }

        if( query_temp("receive_rumor_time", me)<time() )
                set_temp("receive_rumor_time", time(), me);
        addn_temp("receive_rumor_time", ob->value()/3000*60, me);
        message_vision("$N乐得合不拢嘴，连忙接过" + ob->name() +
                       "，点头哈腰的对$n道：好！好！\n", this_object(), me);
        command("tell "+query("id", me)+
                sprintf(" 要是 %d 分钟内有人造谣，我一定揭穿他的老底。",
                        (query_temp("receive_rumor_time", me)-time())/60));
        destruct(ob);
        append_receiver(me);
        return 1;
}

int ask_fee()
{
        int n;
        object me;

        me = this_player();
        if( query_temp("receive_rumor_time", me)<time() )
        {
                command("say 不贵不贵，三十两银子包管一分钟！");
                return 1;
        }

        n=query_temp("receive_rumor_time", me)-time();
        n /= 60;
        if (! n)
        {
                command("tell "+query("id", me)+
                        " 马上到时间啦，再想听消息，快点拿钱来啊！");
        } else
        {
        command("tell "+query("id", me)+
                        sprintf(" 你还能听 %d 分钟的消息。", n));
        }

        message("visoin", name() + "嘀嘀咕咕的对" + me->name() +
                          "说了一些话。\n", environment(me), ({ me }));
        return 1;
}

int ask_bomb()
{
        object ob;
        object me;
        int n;

        me = this_player();
        if (wizardp(me))
        {
                if (! objectp(ob = present("bomb", this_object())))
                        ob = new("/clone/gift/xianxing");
                command("say 等等，小的这就给你。");
                ob->move(me, 1);
                return 1;
        }

        n=(query_temp("receive_rumor_time", me))-time();
        if (n < 0) n = 0;
        n /= 60;
        if (! n)
        {
                command("shake");
                command("say 你问我这个干嘛？我不认识你。");
                return 1;
        }

        if (! (ob = present("visible bomb", this_object())) &&
           query_temp("bomb_count") <= 0)
        {
                command("say 可惜，我倒是想给你，可是手头没有啦！");
                return 1;
        }

        if (! ob) catch(ob = new("/clone/gift/xianxing"));

        if (! ob)
        {
                command("say 我的炸弹受潮... 给不了你了！");
                return 1;
        }

        command("heihei");
        command("say 看在你照顾我生意的面子上，我就给你一颗炸弹！");
        if (! environment(ob)) ob->move(this_object());
        command("give bomb to "+query("id", me));
        addn_temp("bomb_count", -1);
        remove_call_out("restore_bomb");
        call_out("restore_bomb", 150);
        return 1;
}

private void restore_bomb()
{
        set_temp("bomb_count", 1);
}

void receive_report(object user, string verb)
{
        string msg;

        msg = sprintf("听说%s(%s)又要发谣言了。",
                      query("name", user),query("id", user));
        if (random(100) < 7)
        {
                command("heihei");
                command("say " + msg);
        }

        if (! receiver)
                return;

        receiver = filter_array(receiver, (: filter_listener :));
        if (! sizeof(receiver))
        {
                receiver = 0;
                return 0;
        }

        message("vision", HIG "游讯悄悄的告诉你：" + msg + "\n",
                receiver, user);
}

private int filter_listener(object ob)
{
        if (! objectp(ob))
                return 0;

        if (present("rumor generator", ob))
                return 1;

        if( query_temp("receive_rumor_time", ob)>time() )
                return 1;

        delete_temp("receive_rumor_time", ob);
        return 0;
}

int ask_duwan()
{
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me) || wiz_level(me) < 2)
        {
                command("say 你... 你要毒药干什么？下毒可是犯法的！");
                return 1;
        }

        command("consider");
        command("shzi");
        catch(ob = new("/clone/misc/duwan"));
        if (! ob)
        {
                command("say 毒丸出了点问题，我暂时拿不出来了。");
                return 1;
        }
        ob->move(this_object());
        command("give "+query("id", ob)+" to "+query("id", me));
        command("say 这可是丁老怪做的，千万别我给漏了出去！");
        return 1;
}

int ask_shedu()
{
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me) || wiz_level(me) < 2)
        {
                command("say 你... 你要毒药干什么？下毒可是犯法的！");
                return 1;
        }

        command("heihei");
        command("shzi");
        catch(ob = new("/clone/misc/shedu"));
        if (! ob)
        {
                command("say 蛇毒出了点问题，我暂时拿不出来。");
                return 1;
        }
        ob->move(this_object());
        command("give "+query("id", ob)+" to "+query("id", me));
        command("say 这可是欧阳疯子弄的，可别说是我给你的啊！");
        return 1;
}

int ask_list()
{
        object me;

        me = this_player();
        if( query_temp("can_buy/youxun/nuclues-bomb", me) )
        {
                command("say 你咋这么罗嗦？好话不说二遍...");
                return 1;
        }
        command("shzi");
        command("whisper "+query("id", me)+
                " 我身上有不少好东西，便宜得很！核弹才五万两黄金一个！");
        set_temp("can_buy/youxun/nuclues-bomb", 1, me);
        return 1;
}

int do_list(string arg)
{
        if (arg && ! id(arg))
                return notify_fail("这里没有这个人。\n");

        if( query_temp("can_buy/youxun", this_player()) )
        {
                command("shzi");
                return ::do_list();
        }

        message_vision("$N两手忙摆，对$n道：“我只卖消息不卖货，嘿嘿。”\n",
                       this_object(), this_player());
        return 1;
}

int do_buy(string arg)
{
        object me;
        string my_id;

        if (arg && sscanf(arg, "%s from %s", arg, my_id) == 2 && ! id(my_id))
                return notify_fail("这里没有这个人。\n");

        me = this_player();
        if( !query_temp("can_buy/youxun", me) )
        {
                message_vision("$N急得双手乱摆，对$n道：“我说过了不卖"
                               "东西的，我可是老实人！”\n",
                               this_object(), this_player());
                return 1;
        }

        return ::do_buy(arg);
}
