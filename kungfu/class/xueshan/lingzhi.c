// /kungfu/class/xueshan/lingzhi.c  灵智上人
// by secret

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"

void create()
{
        set_name("灵智上人", ({ "lingzhi shangren", "shangren", "lingzhi" }));
        set("long",@LONG
灵智上人是雪山寺中地位较高的喇嘛。
身穿一件青色袈裟，头带僧帽。
LONG
        );
        set("nickname",HIR"大手印"NOR);
        set("title",HIY "大喇嘛" NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 25);
        set("int", 27);
        set("con", 28);
        set("dex", 26);
        set("max_qi", 2500);
        set("max_jing", 1200);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 30);
        set("level", 10);
        set("combat_exp", 350000);

        set_skill("mizong-neigong", 60);
        set_skill("literate", 60);
        set_skill("force", 100);
        set_skill("xiaowuxiang", 100);
        set_skill("dodge", 100);
        set_skill("shenkong-xing", 80);
        set_skill("parry", 80);
        set_skill("staff", 60);
        set_skill("xiangmo-chu", 80 );
        set_skill("hand", 80);
        set_skill("dashou-yin", 80);
        set_skill("hammer",50);
        set_skill("riyue-lun",50);
        set_skill("unarmed", 110);
        set_skill("yujiamu-quan", 100);
        set_skill("martial-cognize", 60);
        set_skill("lamaism", 100);


        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("unarmed", "yujiamu-quan");
        map_skill("parry", "yujiamu-quan");
        map_skill("staff", "xiangmo-chu");
        map_skill("hammer", "riyue-lun");
        map_skill("hand", "dashou-yin");

        prepare_skill("hand", "dashou-yin");

        create_family("密宗", 4, "大喇嘛");
        set("class", "bonze");

        set("master_ob", 2);
        setup();

        carry_object("/d/xueshan/obj/c-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);

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
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
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

        command("say 就传你一些武功吧！");
        command("recruit "+query("id", ob));

        set("title", YEL"喇嘛"NOR, ob);
}
