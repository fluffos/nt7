// qu.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name( "曲灵风" ,({ "qu lingfeng", "qu" }));
        set("gender", "男性");
        set("age", 46);
        set("long",
            "曲灵风是黄药师的大徒弟，也是黄药师最得意的徒儿。他对黄药师一贯\n"
            "忠心耿耿，尤其是性格古怪，象极了他师父的邪气。\n"
            "他身形修长，相貌英俊，白衣飘飘，形容潇洒。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 24);
        set("int", 31);
        set("con", 28);
        set("dex", 22);
        set("chat_chance", 1);
        set("chat_msg", ({
            "曲灵风说道：“师父疼爱小师妹，他的软猬甲一直由小师妹穿着。”\n",
            "曲灵风自言自语地说道：“这个桃花阵，嗨，不简单！”\n",
        }));
        set("max_qi", 4200);
        set("max_jing", 2100);
        set("neili", 4400);
        set("max_neili", 4400);
        set("jiali", 50);
        set("shen_type", 0);

        set("combat_exp", 1200000);
        set_skill("force", 160);             // 基本内功
        set_skill("luoying-xinfa", 160);     // 落英心法
        set_skill("unarmed", 150);           // 基本拳脚
        set_skill("xuanfeng-tui", 150);      // 旋风扫叶腿
        set_skill("strike", 140);            // 基本掌法
        set_skill("luoying-shenzhang", 140); // 落英神剑掌
        set_skill("dodge", 170);             // 基本躲闪
        set_skill("anying-fuxiang", 170);    // 暗影浮香
        set_skill("parry", 150);             // 基本招架
        set_skill("sword", 150);             // 基本剑法
        set_skill("luoying-shenjian", 150);  // 落英神剑
        set_skill("qimen-wuxing", 150);      // 奇门五行
        set_skill("literate", 180);          // 读书识字

        map_skill("force"  , "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike" , "luoying-zhang");
        map_skill("dodge"  , "anying-fuxiang");
        map_skill("parry"  , "luoying-shenjian");
        map_skill("sword"  , "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike" , "luoying-zhang");

        create_family("桃花岛", 2, "弟子");

        set("inquiry", ([
           "桃花岛":   "这儿就是桃花岛，你若不是本派弟子，要过桃花阵。",
           "桃花阵":   "往南就是了。",
           "东邪":     "家师人称东邪！呵呵。",
           "西毒":     "欧阳锋是与家师并世齐名的高手，人称老毒物。",
           "南帝":     "听家师说段王爷现在出家当了和尚，法名一灯。",
           "北丐":     "北丐洪七公是丐帮帮主，现在扬州城外。",
           "黄蓉":     "她是师父的爱女。",
           "黄药师":   "你要拜访家师？"
        ]));
        set("master_ob", 4);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian");
}

void attempt_apprentice(object ob)
{
        string master;
        if (! permit_recruit(ob))
                return;
        
        if( stringp(master=query_temp("taohua/master", ob)) )
        {
                if (master != name())
                {
                        command("say 家师不是让你拜" + master +
                                "的吗？你怎么来找我来了？");
                        return;
                }

                command("say 好吧，既然家师有令，我就收下你了，不过要好好遵守桃花岛的规矩。");
                command("recruit "+query("id", ob));
                delete_temp("taohua/master", ob);
                return;
        }

        if( query("family/master_name", ob) == "黄药师" && 
            query("family/family_name", ob) == "桃花岛" )
        {
                command("say 大家都是黄岛主的弟子，你就别和我寻开心了。");
                return;
        }

        command("shake");
        command("say 我可不敢擅自收徒，你还是找家师黄岛主吧！");
}

int accept_fight(object ob)
{
        command("wield jian");
        return 1;
}
