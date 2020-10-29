// wei.c

#include <ansi.h>;

inherit NPC;

void create()
{
        set_name("韦小宝", ({ "wei xiaobao", "wei", "xiaobao" }));
        set("title", HIC"大清国抚远大将军"HIY"一等鹿鼎公"NOR);
        set("nickname", HIW"小白龙"NOR);
        set("gender", "男性");
        set("age", 18);
        set("str", 20);
        set("int", 30);
        set("con", 30);
        set("dex", 20);
        set("per", 28);
        set("long", 
"这位少年将军头戴红顶子，身穿黄马褂，眉花眼笑，贼忒兮
兮，左手轻摇羽扇，宛若诸葛之亮，右手倒拖大刀，俨然关
云之长，正乃韦公小宝是也。见你看着他，“哈哈哈”，仰
天大笑三声，学足了戏文中曹操的模样，你顿时忍不住凑个
趣，问一句：“将军为何发笑？”\n");
        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("max_qi", 2500);
        set("max_jing", 1000);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 50);

        set_skill("force", 20);
        set_skill("parry", 20);
        set_skill("hand", 20);
        set_skill("dodge", 20);
        set_skill("shenxing-baibian", 20);
        set_skill("yunlong-shengong", 20);
        set_skill("qianye-shou", 90);

        map_skill("force", "yunlong-shengong");
        map_skill("parry", "qianye-shou");
        map_skill("dodge", "shenxing-baibian");
        map_skill("hand", "qianye-shou");
        prepare_skill("hand", "qianye-shou");
        set("inquiry", ([
            "天地会"  : "别烦我！\n",
            "陈近南"  : "那是我师父！\n",
            "茅十八"  : "就是那十八个毛虫啊？他还没死吧！\n",
            "独臂神尼": "那是我美貌尼姑师父！\n",
            "韦春芳"  : "我娘做婊子生意越来越差了，现在改行作老鸨了！\n",
            "康熙"    : "那是我皇帝师父！\n",
            "小玄子"  : "那是我皇帝师父！\n",
            "小桂子"  : "别提这个名字了，我怕怕！\n",
            "阿珂"    : "她是我明媒正娶的大老婆！\n",
            "双儿"    : "你认识她？大功告成，亲个嘴儿！\n",
            "曾柔"    : "我老婆你问那么多干嘛？皇上洪福齐天，我艳福齐天！\n",
            "方怡"    : "我老婆你问那么多干嘛？皇上洪福齐天，我艳福齐天！\n",
            "苏荃"    : "我老婆你问那么多干嘛？皇上洪福齐天，我艳福齐天！\n",
            "沐剑屏"  : "我老婆你问那么多干嘛？皇上洪福齐天，我艳福齐天！\n",
            "建宁公主": "这个骚娘皮，亲厚不及双儿、美貌不及阿珂、武功不
及苏荃、机巧不及方怡、天真纯善不及沐剑屏、温柔斯文不及曾柔，
差有一日之长者，不过横蛮泼辣而已！\n",
        ]) );

        setup();
        carry_object("/d/city/obj/cloth")->wear();
        if (! clonep(this_object()))
        {
                move("/d/city/lichunyuan");
                message_vision("$N笑嘻嘻道：来了来了，我来了。\n", this_object());
                move("/d/city/lichunyuan");
        }
}

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
                if( time()-query_temp("ask_wei_time", ob)<2 )
                {
                        tell_object(ob, HIY "韦小宝朝你一瞪眼睛：『别吵！问问题是吧？问那么急干嘛？』\n" NOR);
                        return 1;
                }
                
                set_temp("ask_wei_time", time(), ob);
                obs = livings();
                obs = filter_array(obs, (: filter_color($1->name(1)) == $2 && environment($1) :), topic);
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
                        set_temp("pending/ask_wei", topic, ob);
                        /*
                        message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n"
                                CYN "小声道：『没有问题，不过得要一两黄"
                                "金，不二价！』\n" NOR, this_object(), ob);
                        */
                        tell_object(ob, CYN "韦小宝嘿嘿奸笑两声，对你"
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

        set_temp("pending/ask_wei", topic, ob);
        /*
        message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n"
                       CYN "小声道：“没有问题，不过得要10两"
                       "白银，不二价！”\n" NOR, this_object(), ob);
        */
        tell_object(ob, CYN "韦小宝嘿嘿奸笑两声，对你"
                        CYN "小声道：“没有问题，不过得要10两"
                        "白银，不二价！”\n" NOR);
        return 1;
}

int accept_object(object me, object ob)
{
        string wid;

        if (clonep(this_object()))
        {
                command("hehe");
                command("say 我是真韦小宝，如假包换啊！");
                return 1;
        }

        if( !stringp(query("money_id", ob)) )
        {
                switch(query_temp("wei_refused", me) )
                {
                case 0:
                        command("heihei");
                        command("say 这种破烂你留着吧。");
                        set_temp("wei_refused", 1, me);
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

                addn_temp("wei_refused", 1, me);
                me->move("/d/city/nandajie2");
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

        delete_temp("wei_refused", me);
        if( stringp(wid=query_temp("pending/ask_wei", me)) )
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

                delete_temp("pending/ask_wei", me);

                if (wid[0] > 160)
                {
                        obs = livings();
                        obs = filter_array(obs, (: filter_color($1->name(1)) == $2 && environment($1) :) ,wid);
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
                                       "刚才在" + environment(obs[i])->short() + "。\n";
                        destruct(ob);
                        obs = 0;
                        command("whisper "+query("id", me) + " " + msg);
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
                command("whisper "+query("id", me)+
                        " 据可靠消息，这个人刚才在" +
                        environment(fob)->short() + "。");
                return 1;
        }

        message_vision("$N乐得合不拢嘴，连忙接过" + ob->name() + 
                       "，点头哈腰的对$n道：好！好！\n", this_object(), me); 

        destruct(ob);
        return 1;
}
