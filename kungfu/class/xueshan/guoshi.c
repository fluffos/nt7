// /kungfu/class/xueshan/guoshi.c  贡唐仓国师
// by secret

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"

string ask_for_join();

void create()
{
        set_name("贡唐仓国师", ({ "gongtangcang guoshi", "guoshi" }));
        set("long",@LONG
贡唐仓国师是雪山寺中地位较高的喇嘛。
身穿一件青色袈裟，头带僧帽。
LONG
        );
        set("title", HIY "大喇嘛" NOR);
        set("nickname", HIG "国师" NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 24);
        set("int", 28);
        set("con", 26);
        set("dex", 25);

        set("max_qi", 1500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 20);
        set("level", 15);
        set("combat_exp", 120000);

        set_skill("lamaism", 1200);
        set_skill("literate", 50);
        set_skill("force", 100);
        set_skill("mizong-neigong", 100);
        set_skill("dodge", 100);
        set_skill("shenkong-xing", 80);
        set_skill("parry", 70);
        set_skill("staff", 80);
        set_skill("xiangmo-chu", 80 );
        set_skill("sword",50);
        set_skill("mingwang-jian",40);
        set_skill("cuff", 90);
        set_skill("yujiamu-quan", 80);
        set_skill("hand", 90);
        set_skill("dashou-yin", 90);
        set_skill("martial-cognize", 60);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xiangmo-chu");
        map_skill("staff", "xiangmo-chu");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("密宗", 4, "大喇嘛");
        set("class", "bonze");

        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));

        set("master_ob", 3);
        setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/xueshan/obj/c-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",100);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 我佛门的清规戒律甚多。");
                set_temp("pending/join_bonze", 1, ob);
                command("say 施主若真心皈依我佛，请跪下(kneel)受戒。\n");
                return;
        }

        if( query("family/family_name", ob) != "密宗" )
        {
                command("say 这位" + RANK_D->query_respect(ob) +
                        "既非本寺弟子，还是请回吧！");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 40)
        {
                command("say 入我雪山寺，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("say 好，就传你一些武功吧！");
        command("recruit "+query("id", ob));

        set("title", HIY"喇嘛"NOR, ob);
}

void init()
{
        add_action("do_kneel", "kneel");
        add_action("do_say", "say");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "阿弥陀佛！ 你已经是出家人了，何故跟贫僧开这等玩笑？\n";

        if( query("gender", me) != "男性" )
                return "施主若真心向佛，真是可喜可贺，可惜本寺只收男徒。\n";

        set_temp("pending/join_bonze", 1, me);

        return "阿弥陀佛！善哉！善哉！施主若真心皈依"
               "我佛，请跪下(kneel)受戒。\n";
}

int do_kneel()
{
        object me = this_player();

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision("$N双手合十，恭恭敬敬地跪了下来。\n\n"
                       "$n伸出手掌，在$N头顶轻轻地摩挲了几下，将"
                       "$N的头发尽数剃去。\n\n", me, this_object());

        set("class", "bonze", me);
        set("title", HIY"喇嘛"NOR, me);

        command("smile");
        command("say 好，就传你一些武功吧！");
        command("recruit "+query("id", me));

        return 1;
}

int do_say(string arg)
{

        object me = this_player();

        if (! arg || arg == "") return 0;

        if (arg == "法轮常转")
        {
                me->move("/d/xueshan/guangchang");
                return 1;
        }
}
