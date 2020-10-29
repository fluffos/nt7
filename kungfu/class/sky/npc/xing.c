#include <ansi.h>

inherit NPC;
string ask_tianjidao();

void create()
{
        set_name(HIW "星君眼" NOR, ({ "xingjun yan", "xingjun", "yan"}));
        set("long", HIW "一个长相奇特的老者，看样子不像是人界中人。\n" NOR);         
        set("title", HIY "天界守护者" NOR);
        set("gender", "男性");
        set("age", 999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("per", 35);

        set("max_qi", 9999999);
        set("max_jing", 9999999);
        set("max_neili", 999999);
        set("neili", 999999);
        set("jiali", 2500);
        set("combat_exp", 8000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.bafa" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 420);
        set_skill("parry", 420);
        set_skill("hand", 440);
        set_skill("unarmed", 440);
        set_skill("shou-yin", 440);
        set_skill("wudu-shu", 420);
        set_skill("force", 400);
        set_skill("changsheng-jue", 400);
        set_skill("blade", 320);
        set_skill("jingzhong-bafa", 420);
        set_skill("literate", 400);
        set_skill("martial-cognize", 400);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "jingzhong-bafa");
        map_skill("dodge", "wudu-shu");
        map_skill("parry", "jingzhong-bafa");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");
        set("inquiry", ([
                "天极道" : (: ask_tianjidao :),
                
        ]));
        prepare_skill("hand", "shou-yin");

        setup();

        carry_object(__DIR__"obj/cloth2")->wear();
}

string ask_tianjidao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if (me->query("int") < 32 ||
            me->query("con") < 32 ||
            me->query("str") < 32 ||
            me->query("dex") < 32)
            return "你的先天属性还不足以修炼天极道，我看你还是先回去吧。\n";


        if (! me->query("scborn/ok"))
                return "走开，走开，没看我正忙吗？\n";
        
        if (me->query_skill("yinyang-shiertian", 1) && ! me->query("thborn/ok"))
                return "阁下武功已经独步天下，何必如此贪心?\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此贪心！\n";
                                        
        // 已经完成任务
        if (me->query("lunhui-sword_quest/tianjidao/finish"))
                return "呵呵，不错不错，上次那些天蚕丝解了老夫燃眉之急啊。\n";

        // 分配任务
        if (! me->query("lunhui-sword_quest/tianjidao/give_quest"))
        {
                command("shake");
                command("say 不久前，老夫将借来的一件天蚕宝甲给弄丢了，不知如何是好？");
                command("say 如果能搜集到30根天蚕丝，老夫倒是有办法重新制作一。");
                command("不过……");
                command("tan");
                command("say 那天蚕丝并非凡物，只有天山顶峰的天蚕身才有，看来这次真是闯大祸了！");
                command("look " + me->query("id"));
                command("say 阁下如果能搜集到30根天蚕丝给老夫，老夫这里倒是有一些厉害的武功可以传授给你。");
                tell_object(me, this_object()->name() + HIG "让你帮他搜集30根天蚕丝，赶快去吧！\n" NOR);
                me->set("lunhui-sword_quest/tianjidao/give_quest", 1);
                me->save();
                return "怎么样，考虑考虑？";
        }
        
        // 完成任务
        
        if (! objectp(ob_hlp = present("tiancan si", me)))
                return "怎么样，30根天蚕丝搜集够了吗？\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/cansi2")
                return "怎么样，30根天蚕丝搜集够了吗？\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hlp) >= 30)
        {
                for (i = 1; i <= 30; i++)
                {
                        destruct(ob_hlp);
                        ob_hlp = present("tiancan si", me);
                }
        }
        else
        {
                return "怎么样，30根天蚕丝搜集够了吗？\n";
        }
        
        command("hehe");
        command("nod");
        command("say 既然你帮我了这个忙，好！老夫也遵守诺言，传你「天极道」……");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                     "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                     "对刚才的疑虑有所顿悟。\n", this_object(), me);
                             
        tell_object(me, HIG "恭喜你领悟了「天极道」剑法，目前等级为10级。\n");
        me->set_skill("tianji-dao", 10);
        me->set("lunhui-sword_quest/tianjidao/finish", 1);
        
        return "多谢了！";
        
                
}
