// This program is a part of NITAN MudLIB
// yin.c 殷梨亭

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("殷梨亭", ({ "yin litin", "yin" }));
        set("nickname", "武当六侠");
        set("long",
                "他就是张三丰的六弟子殷梨亭。\n"
                "他今年三十岁，精明能干，嫉恶如仇，性如烈火。\n");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "heroism");
        set("shen_type", 1);
        set("str", 26);
        set("int", 30);
        set("con", 26);
        set("dex", 28);

        set("max_qi", 4200);
        set("max_jing", 2100);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 100);
        set("combat_exp", 1250000);
        set("score", 45000);

        set_skill("force", 165);
        set_skill("yinyun-ziqi", 165);
        set_skill("taiji-shengong", 165);
        set_skill("dodge", 175);
        set_skill("tiyunzong", 175);
        set_skill("unarmed", 170);
        set_skill("taiji-quan", 170);
        set_skill("strike", 165);
        set_skill("wudang-zhang", 165);
        set_skill("hand", 180);
        set_skill("paiyun-shou", 180);
        set_skill("parry", 175);
        set_skill("sword", 160);
        set_skill("wudang-jian", 160);
        set_skill("raozhi-roujian", 180);
        set_skill("taiji-jian", 160);
        set_skill("taoism", 120);
        set_skill("literate", 100);

        set("no_teach", ([
                "taiji-shengong" : "要想学习太极神功请向张真人请教。",
                "taiji-jian"     : "太极剑必须张真人亲传。",
                "taiji-quan"     : "太极拳必须张真人亲传。",
        ]));

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "raozhi-roujian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武当派", 2, "弟子");

        set("inquiry", ([
                "柔月穿空": (: ask_me :),
                "绝招"    : (: ask_me :),
                "天地同寿": (: ask_skill :),
        ]));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chuankong" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<8000 )
        {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi",1) < 70)
        {
                command("say 我武当派最注重内功心法" + RANK_D->query_respect(ob)+
                        "是否应该在氤氲紫气上多下点功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 70)
        {
                command("say 习武是为了强身健体，一味的练武是不可取的。");
                command("say 我看你还需要在修身养性方面多锻炼锻炼，以提"
                        "高你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 希望你能好好用功，消灭邪魔外道！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/raozhi-roujian/chuankong", me) )
                return "自己好好多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("raozhi-roujian", 1) < 1)
                return "你连绕指柔剑都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<250 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<15000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("force") < 150)
                return "你的内功的修为不够，练高了再来吧。";

        if (me->query_skill("raozhi-roujian", 1) < 100)
                return "你的绕指柔剑还不到家，要多练练！";

        message_vision(HIY "$n" HIY "点了点头，拔出腰间长剑突然向$N" HIY
                       HIY "刺来，途中剑法忽\n变，那柄长剑竟似成了一条软"
                       "带，轻柔曲折，飘忽不定，正\n是七十二招「绕指柔剑"
                       "」的最后一招「柔月穿空」。\n" NOR, me,
                       this_object());
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「柔月穿空」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("raozhi-roujian"))
                me->improve_skill("raozhi-roujian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/raozhi-roujian/chuankong", 1, me);
        addn("family/gongji", -250, me);

        return 1;
}

mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/tong", me) )
                return "自己好好多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<250 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<15000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("force") < 150)
                return "你的内功的修为不够，练高了再来吧。";

        if (me->query_skill("taiji-jian", 1) < 100)
                return "你的太极剑还不到家，要多练练！";

        message_sort(HIY "$n" HIY "点了点头道：既然$N" HIY "也是"
                     "我辈中人，那么我就将自晓芙去后，我所参捂出"
                     "来的「天地同寿」传于你，切记，非万不得以时"
                     "千万不要使用！紧接着，$n开始详细讲解其中奥"
                     "秘。\n" NOR, me, this_object());
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「天地同寿」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/tong", 1, me);
        addn("family/gongji", -250, me);

        return 1;
}


