#include <ansi.h>
#include "yaowang.h"

#define SHENNONG    "/clone/lonely/shennongjian"
#define SHENPIAN    "/clone/lonely/yaowang_book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_shennong();
mixed ask_shenpian();

void create()
{
        set_name("无嗔", ({ "wu chen", "wu", "chen" }));
        set("nickname", HIR "毒手药王" NOR);
        set("long",@LONG
这是一位身着朴素的老者，面色慈祥，竟不知他便是
号称「毒手药王」的无嗔。他出家之前，脾气很是暴
躁。他出家后法名大嗔，后来他经修性养心，颇有进
益，于是更名一嗔。收程灵素法名再更作微嗔。时至
现在，法名已作无嗔。
LONG );
        set("title", HIG "药王谷谷主" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 380);
        set_skill("yaogu-xinfa", 360);
        set_skill("shennong-xinjing", 380);
        set_skill("dodge", 360);
        set_skill("xuefu-mizong", 300);
        set_skill("strike", 300);
        set_skill("dusha-zhang", 300);
        set_skill("hand", 300);
        set_skill("lansha-shou", 300);
        set_skill("jiuqu-zhegufa", 300);
        set_skill("parry", 300);
        set_skill("staff", 320);
        set_skill("shennong-zhang", 320);
        set_skill("throwing", 320);
        set_skill("xuwen-qixingding", 300);
        set_skill("wuxing-jueming", 320);
        set_skill("literate", 350);
        set_skill("poison", 300);

        set_skill("dispel-poison", 500 );
        set_skill("yaowang-shenxin", 500 );
        set_skill("medical", 500);
        set_skill("yaowang-miaoshu", 500 );
        set_skill("baicao-jue", 500 );
        set_skill("bencao-changshi", 500);
        set_skill("hunting", 300);

        map_skill("force", "shennong-xinjing");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("药王谷", 1, "谷主");
        set("class", "bonze");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.tengshe" :),
                (: perform_action, "whip.panying" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suolong" :),
                (: perform_action, "claw.lianhuan" :),
                (: perform_action, "strike.duchan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        setup();

        set("inquiry", ([
                "神农锏"   : (: ask_shennong :),
                "药王神篇" : (: ask_shenpian :),
                "七星海棠" : "七星海棠乃天下第一毒，无药可治！",
                "苗人凤"   : "呵呵，当年我和那个家伙比武，结果少了一根指头，不过后来还是报复回来了。",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 我已有三个为非作歹的徒弟了，不想再作添加。");
                return;
        }

        if( query("shen", ob)<100000 )
        {
                command("say 欲习我毒技医术，必须将德行放在首位，我可不希望你像我另外三个徒弟一般。");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你现在经验尚浅，领会不了什么，还是先去增长点经验吧。");
                return;
        }
        if( query("family/master_name", ob) == "石万嗔" )
        {
                command("say 你既已经入石万嗔门下，好自为之!");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 150)
        {
                command("say 你本门的心法还学的不够啊。");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 120)
        {
                command("say 你连最基本的学问都没学好，我如何传授你高深的毒技医术。");
                return;
        }

        if ((int)ob->query_skill("yaowang-miaoshu", 1) < 120)
        {
                command("say 你先把药王妙术钻研透彻了再来找我吧。");
                return;
        }

        if ((int)ob->query_skill("dispel-poison", 1) < 120)
        {
                command("say 你的妙手驱毒研究透彻了吗？");
                return;
        }

        command("pat"+query("id", ob));
        command("say 不错，不错！既然你如此有心，老夫就收下你这个徒弟。");
        command("say 本门中人不能放蛊，又有九种没解药的毒药决计不能使用。且记!");
        command("recruit "+query("id", ob));
        set("title", "毒手药王亲传弟子", ob);
        return;
}

mixed ask_shennong()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "药王谷" )
                        message_vision(CYN "$N" CYN "冷哼一声，对$n" CYN "道："
                                       "“你难道忘记了我是怎么教你的吗？现在居"
                                       "然和那三个家伙一样走上了邪道，居然还有"
                                       "脸问我要神农锏？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一声，对$n" CYN "说道"
                                       "：“好一个邪派妖徒，竟敢贪图本派宝物！"
                                       "”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "药王谷" )
                return "你不是我们药王谷的，打听它干什么？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用神农锏。";

        if( query("shen", me)<100000 )
                return "你侠义正事做得还不够，这神农锏我不能教给你。";

        if (me->query_skill("shennong-zhang", 1) < 120)
                return "你连神农杖法都没学好，就算用神农锏也是白搭。";

        ob = find_object(SHENNONG);
        if (! ob) ob = load_object(SHENNONG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "神农锏现在不就在你手里吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了一步，我已经把神农锏借给你同门师兄弟用去了。";

                if( query("family/master_id", owner) == query("id") )
                        return "嗯，神农锏现在暂时是你同门师兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本门的神农锏现在落入了"+query("name", owner)+
                               "之手，你去把它取回来吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“这柄神农锏你就"
                       "拿去，记住，千万不可用它为非作歹！”\n" NOR,
                       this_object(), me);
        command("giveshennongjianto"+query("id", me));
        return 1;
}

mixed ask_shenpian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "药王谷" )
                        message_vision(CYN "$N" CYN "冷哼一声，对$n" CYN "道："
                                       "“你难道忘记了我是怎么教你的吗？现在居"
                                       "然和那三个家伙一样走上了邪道，我如何能"
                                       "将《药王神篇》交予你？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一声，对$n" CYN "说道"
                                       "：“好一个邪派妖徒，竟敢贪图本派宝物！"
                                       "”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "药王谷" )
                return "你不是我们药王谷的，打听它干什么？";

        if( query("family/master_id", me) != query("id") )
                return "你尚未成为我的弟子，我不能将《药王神篇》交给你！";

        if( query("shen", me)<100000 )
                return "你侠义正事做得还不够，《药王神篇》我不能给你。";

        if (me->query_skill("yaowang-shenxin", 1) < 100)
                return "你药王神辛尚未学好，给了你你也读不懂。";

        ob = find_object(SHENPIAN);
        if (! ob) ob = load_object(SHENPIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我这《药王神篇》现在不就在你手里吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了一步，我已经把《药王神篇》借给你同门师兄弟了。";

                if( query("family/master_id", owner) == query("id") )
                        return "嗯，《药王神篇》现在在你同门师兄弟"+query("name", owner)+
                               "手里，你去找他吧。";
                else
                        return "本门的《药王神篇》现在落入了"+query("name", owner)+
                               "之手，你去把它取回来吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“这本《药王神篇》现在"
                       "给你，记住，千万不可用它为非作歹！”\n" NOR,
                       this_object(), me);
        command("giveyaowangshenpianto"+query("id", me));
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))

                return r;

        if (base_name(ob) != SHENNONG)
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多谢这位" + RANK_D->query_respect(me) + "将本门宝物交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}
