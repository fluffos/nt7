// lu.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;                                                                    
inherit F_MASTER;

void create()
{
        set_name( "陆乘风" ,({ "lu chengfeng", "lu" }));
        set("gender", "男性");
        set("age", 52);
        set("long",
            "陆乘风是黄药师的第四个徒弟。\n"
            "他的鬓角已微见白发，但身材魁梧，双眼有神。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 24);
        set("int", 30);
        set("con", 25);
        set("dex", 21);

        set("max_qi", 4000);
        set("max_jing", 2000);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 50);
        set("shen_type",1);

        set("combat_exp", 1500000);

        set_skill("force", 170);            // 基本内功
        set_skill("luoying-xinfa", 170);    // 落英心法
        set_skill("unarmed", 160);          // 基本拳脚
        set_skill("xuanfeng-tui", 160);     // 旋风扫叶腿
        set_skill("strike", 160);           // 基本掌法
        set_skill("luoying-shenzhang", 160);// 落英神剑掌
        set_skill("dodge", 150);            // 基本躲闪
        set_skill("anying-fuxiang", 150);   // 暗影浮香
        set_skill("parry", 160);            // 基本招架
        set_skill("sword", 160);            // 基本剑法
        set_skill("luoying-shenjian", 160); // 落英神剑
        set_skill("literate", 140);         // 读书识字

        map_skill("force"  , "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike" , "luoying-zhang");
        map_skill("dodge"  , "anying-fuxiang");
        map_skill("parry"  , "luoying-shenjian");
        map_skill("sword"  , "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike" , "luoying-zhang");

        set("jinbing", 10);
        create_family("桃花岛", 2, "弟子 归云庄主");

        set("inquiry", ([
           "桃花岛":   "这儿就是桃花岛，你若不是本派弟子，要过桃花阵。",
           "桃花阵":   "往南就是了。",
           "东邪":     "家师人称东邪！呵呵。",
           "西毒":     "欧阳锋是与家师并世齐名的高手，人称老毒物。",
           "南帝":     "听家师说段王爷现在出家当了和尚，法名一灯。",
           "北丐":     "北丐洪七公是丐帮帮主，现在扬州城外。",
           "黄蓉":     "她是师父的爱女。",
           "黄药师":   "你要拜访家师？"
        ]) );
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

int accept_object(object who, object ob)
{
        int exp;
        if (query("jinbing") < 0)
        {
                command("say " + RANK_D->query_respect(who) + "我很累，你回头再来领赏吧。");
                return 0;
        }
        if( strsrch(query("name", ob),"完颜康的头颅")<0 && 
            strsrch(query("name", ob),"完颜洪烈的头颅")<0 && 
            strsrch(query("name", ob),"欧阳锋的头颅")<0 && 
            strsrch(query("name", ob),"欧阳克的头颅")<0 && 
            strsrch(query("name", ob),"彭连虎的头颅")<0 && 
            strsrch(query("name", ob),"梁子翁的头颅")<0 && 
            strsrch(query("name", ob),"灵智上人的头颅")<0 && 
            strsrch(query("name", ob),"沙通天的头颅")<0 && 
            strsrch(query("name", ob),"侯通海的头颅")<0 && 
            strsrch(query("name", ob),"沈青刚的头颅")<0 && 
            strsrch(query("name", ob),"吴青烈的头颅")<0 && 
            strsrch(query("name", ob),"马青雄的头颅")<0 && 
            strsrch(query("name", ob),"钱青健的头颅")<0 && 
            strsrch(query("name", ob),"大金兵的头颅")<0 && 
            strsrch(query("name", ob),"段天德的头颅")<0 )
        {
                command("say 给我这些东西有什么用？\n");
                return 0;
        }
        else
        {
                command("say 不错不错，我一直想杀这些金狗，谢你代劳了。");
        }
        exp = 20+random(30);
        addn("jinbing", -1);
        tell_object(who,HIW"陆乘风奖励了你\n"+chinese_number(exp)+"点实战经验\n"NOR);
        return 1;
}
