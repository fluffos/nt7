// Written by Lonely@nitan.org
// xiaofeng.c 萧峰(乔峰)

#include <ansi.h>
inherit NPC;

string *quest_msg = ({
        "萧峰见到你说道：我听说你的大名已久，今日一见当真是名不虚传！\n",
        "段老伯如此信任于我，我却没有保护好阿朱，让她受了重伤。\n",
        "现在阿朱的伤势只有薛神医才能医治，天可怜见，薛神医正好就在这聚贤庄上。\n",
        "萧峰和你一见如故，无所不言，大有相见恨晚之意。\n",
        "萧峰接着说道：我若悄悄潜入聚贤庄，将薛神医掳走，治疗阿朱之伤，当然是最稳妥的办法。\n",
        "但乔峰是顶天立地的汉子，其能做这种偷偷摸摸之事。\n",
        "我想先让聚贤庄上的人知道我要来，然后堂堂正正的带着阿朱进入聚贤庄，求薛神医医治。\n",
        "那时候即使乔峰这条性命不在，阿朱也必然能得到薛神医的治疗。\n",
        "鲍千灵、祁六、向望海三人现在就恰好在聚贤庄，帮我击败这三人，他们明天应该就会把我来到的消息告诉游氏兄弟和薛神医。\n"
});

int do_report(string arg);
void quest_stage(object ob, int stage);

void create()
{
        set_name("萧峰", ({"xiao feng", "xiao", "feng"}));
        set("gender", "男性");
        set("nickname",HIB"铁掌降龙"NOR);
        set("age", 28);
        set("long",
                "他就是丐帮前任帮主，因被发现是契丹人而众叛亲离。\n"
                "在江湖上与燕子坞的慕荣复并称为「北乔峰，南慕荣」。\n"
                "他身穿一件普通的粗布褂子，腰间用一条麻绳随便一系。\n"
                "他身高六尺有余，体格十分魁梧，长有一张线条粗旷、十\n"
                "分男性化的脸庞，双目如电，炯炯有神。\n");
        set("attitude", "peaceful");

        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("per",19);
        set("dex", 30);
        set("chat_chance", 1);
        set("chat_msg", ({
                "萧峰叹了口气道：“唉……想不到我萧峰大好男儿，居然保护不了一个阿朱！\n",
        }));

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);

        set("combat_exp", 180000);
        set("shen", 20000);

        set_skill("force", 120);             // 基本内功
        set_skill("huntian-qigong", 120);    // 混天气功
        set_skill("unarmed", 120);           // 基本拳脚
        set_skill("xianglong-zhang", 120);   // 降龙十八掌
        set_skill("dodge", 120);             // 基本躲闪
        set_skill("xiaoyaoyou", 120);        // 逍遥游
        set_skill("parry", 120);             // 基本招架
        set_skill("begging", 50);            // 叫化绝活
        set_skill("checking", 50);           // 道听途说

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");

        //set("master_ob", 4);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                if( (int)ob->query_temp("juxianzhuang_step") == 6 )
                {
                        call_out("quest_stage", 0, ob, 0);
                        return;
                }

                if( (int)ob->query_temp("juxianzhuang_step") == 10 )
                {
                        call_out("greeting", 1, ob);
                        return;
                }
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say( "萧峰说道：你已经打败鲍千灵、祁六、向望海他们三个人了吗(report)？\n" );
        add_action("do_report", "report");
}

void quest_stage(object ob, int stage)
{
        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg[stage] + NOR);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 7);
}

int do_report(string arg)
{
        object me;

        me = this_player();

        if( (int)me->query_temp("juxianzhuang_step") != 10 )
                return 0;

        tell_object(me, HIW "萧峰说道：你的帮助，乔某感激不尽。那明天一早，我们就在洛阳城东桥相见！\n" NOR );
        me->set_temp("juxianzhuang_step", 11);
        destruct(this_object());
        return 1;
}
