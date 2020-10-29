// This program is a part of NT MudLIB
// pang.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_QUESTER;

mixed  ask_back();

void create()
{
        set_name("胖头陀", ({ "pang toutuo", "pang" ,"toutuo"}));
        set("title", HIY"神龙教"NOR"左护法");
        set("nickname",HIR "辽东胖尊者" NOR);
        set("long", "这头陀身材奇高，而且瘦得出奇；脸上皮包骨头、双\n"
                    "目深陷，当真便如僵尸一般。\n" );
        set("gender", "男性");
        set("age", 44);

        set("str", 32);
        set("int", 28);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 4700);
        set("qi", 4700);
        set("max_jing", 2400);
        set("jing", 2400);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 60);
        set("level", 20);
        set("combat_exp", 750000);
        set("no_get", "别人在做任务，你想把人搬到哪里去？\n");
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 160);
        set_skill("hand", 160);
        set_skill("strike", 160);
        set_skill("staff", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("yixing-bufa", 160);
        set_skill("shenlong-bashi", 160);
        set_skill("huagu-mianzhang", 160);
        set_skill("shenlong-xinfa", 160);
        set_skill("shedao-qigong", 160);

        map_skill("staff", "shedao-qigong");
        map_skill("force", "shenlong-xinfa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("dodge", "yixing-bufa");

        prepare_skill("hand", "shenlong-bashi");
        prepare_skill("strike", "huagu-mianzhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "strike.hua" :),
                (: perform_action, "hand.xian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 200);

        create_family("神龙教", 0, "闲散教众");

        set("inquiry", ([
                "神龙教" : "一般人是入不了我神龙教的(join shenlongjiao).\n",
                "入教"   : "一般人是入不了我神龙教的(join shenlongjiao).\n",
                "洪安通" : "教主脾气不好，要讨他欢心才好。\n",
                "教主"   : "教主脾气不好，要讨他欢心才好。\n",
                "口号"   : "万年不老！永享仙福！寿与天齐！文武仁圣！",
                "神龙岛" : (: ask_back :),
        ]));
        set("master_ob", 3);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
        add_money("silver", 10);
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "神龙教" )
        {
                message_vision("$N自顾自的赌博，好象没有听见$n在说什么。\n",
                               this_object(), me);
                return -1;
        }

        message_vision("$N猛然抬起头来，上上下下打量了一会"
                       "儿$n，眼角微微一动，\n放下手中的排九"
                       "，低声道：快跟我来。\n说罢，$N领"
                       "着$n急急忙忙的朝后面走去。\n", this_object(), me);
        tell_object(me, "你跟着" + name() + "急急的走着，来到了"
                    "一处秘道，" + name() + "指着前面道：“一直走"
                    "就行了，去吧！”\n");
        tell_object(me, HIW "你走了很久，越来越冷，忽然眼前一亮，"
                    "你已经看到了阳光，只见附近的野花映得眼花缭乱。\n" NOR);
        me->move("/d/shenlong/haitan");
        return -1;
}

void attempt_apprentice(object ob)
{
        command("say 慢来！慢来！你想拜师去找教主吧。");
}

void init()
{
        add_action("do_join", "join");
}

int do_join(string arg)
{
        if (arg != "shenlongjiao")
                return notify_fail("你要加入什么组织？\n");

        message_vision("$N摆了摆手，对$n道：“我可不敢收你入教，你还是去"
                       "关外神龙岛上去找我们教主好了”\n",
                       this_object(), this_player());
        return 1;
}

/*
void unconcious()
{
        die();
}

*/
