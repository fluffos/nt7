// Written by Lonely@nitan.org
// xiaofeng.c 萧峰(乔峰)

#include <ansi.h>
inherit NPC;

string *quest_msg = ({
        "乔峰见到你说道：你实在是一个伟大的朋友！我乔某这辈子，交定你了！\n",
        "乔峰饱经风霜的脸上，泛起一丝难得的笑意。\n",
        "我们现在可以走了，阿朱姑娘深受重伤，暂时就躺在车中。放心，我们一定会胜利的。\n",
        "阿朱，你也一定会没事的，等你伤好了，我们就去塞外一起牧马放羊，再也不回来了。\n",
        "走吧！\n"
});

void quest_stage(object ob, int stage);

void create()
{
        set_name("乔峰", ({"qiao feng", "qiao", "feng"}));
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
        set("per", 19);
        set("dex", 30);
        set("chat_chance", 1);
        set("chat_msg", ({
                "萧峰叹了口气道：“唉……想不到我萧峰大好男儿，居然保护不了一个阿朱！\n",
        }));

        set("qi", 4000000);
        set("max_qi", 4000000);
        set("jing", 1500000);
        set("max_jing", 1500000);
        set("neili", 4000000);
        set("max_neili", 4000000);
        set("jiali", 1000);

        set("combat_exp", 1800000000);
        set("shen", 200000);

        set_skill("force", 1200);             // 基本内功
        set_skill("huntian-qigong", 1200);    // 混天气功
        set_skill("unarmed", 1200);           // 基本拳脚
        set_skill("xianglong-zhang", 1200);   // 降龙十八掌
        set_skill("dodge", 1200);             // 基本躲闪
        set_skill("xiaoyaoyou", 1200);        // 逍遥游
        set_skill("parry", 1200);             // 基本招架
        set_skill("begging", 500);            // 叫化绝活
        set_skill("checking", 500);           // 道听途说

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");

        //set("master_ob", 4);
        set("auto_perform", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                if( (int)ob->query_temp("juxianzhuang_step") == 11 )
                {
                        call_out("quest_stage", 1, ob, 0);
                        return;
                }

                if( base_name(environment()) == "/maze/juxianzhuang/damen" )
                {
                        this_object()->set_leader(0);
                        message_vision("$n和$N以及阿朱一行来到聚贤庄门前，徐长老迎面上来，出于故人之情，劝$N离开。\n"
                                       "然而$N一心只想为阿朱疗伤，就是上刀山下火海也在所不惜。\n"
                                       "$N抱着阿朱直接闯进了聚贤庄。\n",
                                       this_object(), ob);
                        ob->set_temp("juxianzhuang_step", 13);
                        destruct(this_object());
                }
        }
}

void quest_stage(object ob, int stage)
{
        remove_call_out("quest_stage");

        if (! ob || ! present(ob)) return;

        tell_object(ob, HIW + quest_msg[stage] + NOR);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        ob->set_temp("juxianzhuang_step", 12);
        this_object()->set_leader(ob);
        message_vision("$N决定开始跟随$n一起行动。\n", this_object(), ob);
        return;
}
