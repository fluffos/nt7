#include <ansi.h>
inherit NPC;

#include "xingxiu.h"

string ask_job();
void create()
{
        set_name("狮吼子", ({ "shihou zi", "shihou" }));
        set("nickname", "星宿派二师兄");
        set("long",
                "他就是丁春秋的二弟子狮吼子。\n"
                "他三十多岁，狮鼻阔口，一望而知不是中土人士。\n");
        set("gender", "男性");
        set("age", 32);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("class", "fighter");
        set("str", 28);
        set("int", 20);
        set("con", 26);
        set("dex", 22);

        set("max_qi", 2500);
        set("max_jing", 1200);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 25);
        set("combat_exp", 220000);

        set_skill("force", 120);
        set_skill("huagong-dafa", 120);
        set_skill("guixi-gong", 140);
        set_skill("dodge", 90);
        set_skill("zhaixing-gong", 90);
        set_skill("strike", 120);
        set_skill("chousui-zhang", 120);
        set_skill("claw", 100);
        set_skill("sanyin-zhua", 100);
        set_skill("parry", 100);
        set_skill("poison", 80);
        set_skill("staff", 50);
        set_skill("tianshan-zhang", 50);

        set("no_teach", ([
                "huagong-dafa" : "化功大法要老仙亲自传授。",
        ]));

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("claw", "sanyin-zhua");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        create_family("星宿派", 2, "弟子");
        set("inquiry", ([
                "丁春秋" : "丁春秋是你叫的吗？没大没小的。以后叫老仙！",
                "老仙"   : (: ask_job :),
                "job"    : (: ask_job :),
        ]));
        set("master_ob", 4);
        setup();
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒！");
        return 0;

        command("say 好吧，我就收下你了。");
        welcome(ob);
        command("recruit "+query("id", ob));
}

string ask_job()
{
        object me, ob;
        mapping fam;
        int shen, exp;
        me = this_player();
        fam=query("family", me);
        shen=query("shen", me);
        exp=query("combat_exp", me);

        if(!fam)
                return "看得出你对老仙态度恭敬，何不先加入我星宿派呢？";
        if( fam["family_name"] != "星宿派" && !query_temp("ding_flatter", me) )
                return "你对老仙的态度看上去不太恭敬啊！";
        if(exp<250000)
                return "哈哈哈，你再加把力练功吧。";
        if(exp>=500000)
                return "老仙最近的情况我不太清楚，你去问问我师兄摘星子吧。";
        if(me->query_condition("wait_xx_task"))
                return "上次搞砸了，这次你就等等吧。";
        if( interactive(me) && query_temp("xx_job", me) )
                return "你怎么还在这里发呆？";
        if(interactive(me) && me->query_condition("wait_xx_task"))
                return "老仙现在心情还好，不用你来为他分忧。";
        if(query("di_count") < 1)
                return "老仙现在心情还好，你别再来烦我了。";

        ob = new(__DIR__"obj/di");
        addn("di_count", -1);
        ob->move(me);
        set("xx_user", getuid(me), ob);
        if(fam["family_name"] != "星宿派")
                set_temp("apply/short", ({WHT"星宿派跟班"NOR+me->name()+"("+query("id", me)+")"}), me);
        set_temp("xx_job", 1, me);
        message_vision("\n$N拿出一只玉制短笛，交给$n。\n", this_object(), me);
        return "老仙最近心情不佳，你可要多多为他老人家分忧才是！\n";
}
