// xu.c

#include <ansi.h>;
inherit NPC;

string *quest_msg1 = ({
        "徐长老说道：久仰少侠大名，今日一见果然名不虚传，失敬失敬！\n",
        "这次的武林大会，唉，我该从何说起呢，家门不幸啊！\n",
        "其实这本是我们丐帮自己的事情，我也不相信这这杀父、杀母、杀师的恶行，会是乔峰所为，可是……\n",
        "徐惊雷看着你迷惑的表情，继续说道。\n",
        "现在铁证如山，乔峰这番邦贼子，在契丹人身份被揭穿，叛出丐帮之后，杀害了自己的义父义母，\n"
        "又杀害了自己的授业恩师玄苦大师，犯下了弥天大罪！他妄图掩饰自己的契丹人身份，谁料却越抹越黑！\n",
        "虽然乔峰这厮为丐帮也曾立下汗马功劳，但国家大义所在，丐帮也难以回护于他。\n",
        "游氏兄弟和薛神医召开武林大会，就是为了聚众讨伐乔峰。群龙无首，大家都希望可以请到江湖上德高\n"
        "望重的前辈或者是朝廷的人来做大家的领袖，毕竟这已经不是普通的家恨，还有国仇了……\n",
        "我们商议之后，觉得大理镇南王段正淳就是最合适的人选。我知道你和他很是熟悉，希望你能出面，请他来主持这次武林大会。\n",
});

string *quest_msg2 = ({
        "徐长老说道：想不到镇南王竟置民族大义于不顾，真是令人痛心啊。\n",
        "这也难怪，镇南王是大理人，不会了解契丹人对大宋造成了多么深重的伤害。\n",
        "乔峰杀父、杀母、杀师三件大罪，我虽没有亲眼见到，但少林寺守律僧的话，难道会是假的？\n",
        "罢了，罢了，既然段王爷说的这么明白了，我们也不好强人所难。\n",
        "说到少林寺，再麻烦你去一趟少林寺，邀请少林寺玄慈方丈参加聚贤庄大会吧。\n",
        "我知道，玄慈方丈心里有一些难解的结，他是不会来参加武林大会的，但如果能请到玄难大师、玄寂\n"
        "大师来聚贤庄，也能让天下英雄有个主心骨了。毕竟，天下武功出少林嘛。\n",
});

int ask_juxianzhuang();
int do_report();

void create()
{
        set_name("徐长老", ({"xu zhanglao", "xu", "zhanglao"}));
        set("gender", "男性");
        set("age", 85);
        set("long", "白须飘动，穿着一身补丁累累的鹑衣，是个年纪极高的老丐。\n");
        set("title", "丐帮九袋长老");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);
        set("no_get", "1");

        set("str", 24);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("qi", 900000);
        set("max_qi", 900000);
        set("jing", 100000);
        set("max_jing", 10000);
        set("neili", 1500000);
        set("max_neili", 1500000);
        set("jiali", 1000);

        set("combat_exp", 100000000);
        set("score", 20000);

        set_skill("force", 950);            // 基本内功
        set_skill("huntian-qigong", 900);   // 混天气功
        set_skill("hand", 900);             // 基本手法
        set_skill("suohou-hand", 850);      // 锁喉擒拿手
        set_skill("staff", 900);            // 基本杖法
        set_skill("fengmo-zhang", 850);     // 疯魔杖法
        set_skill("dodge", 900);            // 基本躲闪
        set_skill("xiaoyaoyou", 950);       // 逍遥游
        set_skill("parry", 850);            // 基本招架
        set_skill("staff", 900);            // 基本棍杖
        set_skill("strike",850);  // 基本掌法
        set_skill("lianhua-zhang",850); // 莲花掌
        set_skill("xianglong-zhang",850);

        map_skill("strike","lianhua-zhang");
        prepare_skill("strike","lianhua-zhang");

        map_skill("force", "huntian-qigong");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "fengmo-zhang");
        map_skill("hand", "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("hand", "suohou-hand");

        set("inquiry", ([
                "英雄贴": (: ask_juxianzhuang :),
                "武林大会": (: ask_juxianzhuang :),
        ]) );

        //set("party/party_name", HIC"丐帮"NOR);
        //set("party/rank", RED"九袋长老"NOR);
        //set("party/level", 9);
        create_family("丐帮", 18, "长老");

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() &&
            ob->query_temp("juxianzhuang_step") == 5 ) {
                add_action("do_report", "report");
        }
}

int ask_juxianzhuang()
{
        object me = this_player();

        if( (int)me->query_temp("juxianzhuang_step") != 1 )
        {
                tell_object(me, "徐长老看了看你，又摇了摇头。\n");
                return 1;
        }

        call_out("quest_stage", 0, me, 0);
        return 1;
}

void quest_stage(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg1[stage] + NOR);
        if (++stage < sizeof(quest_msg1))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 2);
}

void quest_stage2(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg2[stage] + NOR);
        if (++stage < sizeof(quest_msg2))
        {
                call_out( "quest_stage2", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 4);
}

int do_report()
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( (int)me->query_temp("juxianzhuang_step") != 5 )
                return 0;

        message_vision("$n详细地向$N汇报了去少林寺请玄慈方丈的经过。\n", ob, me);

        command("say 既然玄难大师和玄寂大师两位高僧要来聚贤庄，那天下英雄就不会群龙无首了。\n");
        command("say 多谢你了，你近日如果无事，可以和聚贤庄内的英雄们结交一下。\n");
        me->set_temp("juxianzhuang_step", 6);
        return 1;
}

int accept_object(object me, object ob)
{
        if( ob->query("id") != "letter" )
                return 0;

        if( !ob->query("send_to")
        ||  ob->query("send_to") != query("id")
        ||  !ob->query("send_from")
        ||  ob->query("send_from") != me->query("id") )
        {
                return 0;
        }

        if( (int)me->query_temp("juxianzhuang_step") != 3 )
                return 0;

        call_out("quest_stage2", 0, me, 0);
        destruct(ob);
        return 1;
}
