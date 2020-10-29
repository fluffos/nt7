// renwoxing.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_bijian();

void create()
{
        set_name("任我行", ({ "ren woxing", "ren","woxing" }));
        set("title", BLU "日月神教教主"NOR );
        set("long", "只见他一张长长的脸孔，脸色雪白，更无半分血色，眉目清秀，
身材甚高，一头黑发，穿的是一袭青衫。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("per", 27);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 3000);
        set("max_jing", 1000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 400);
        set("combat_exp", 2000000);
        set("score", 500000);

        set_skill("literate", 100);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("changquan", 200);
        set_skill("kuihua-xinfa", 200);
        set_skill("lingxu-bu", 200);
        set_skill("damo-jian", 200);
        set_skill("taiji-jian", 200);
        set_skill("huifeng-jian", 200);
        set_skill("taishan-sword", 200);
        set_skill("hengshan-jian", 200);
        set_skill("hengshan-sword", 200);
        set_skill("huashan-sword", 200);
        set_skill("songshan-sword", 200);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "kuihua-xinfa");
        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");

        set("inquiry", ([
                "比剑" :  (: ask_bijian :),
                "剑法" :  (: ask_bijian :),
                "黑木令" : "要拿黑木令？老夫想先看看你的剑法！\n",
        ]) );
         setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        message_vision("$N躬身说道：“晚辈今日有幸拜见任老前辈，还望多加指教。”\n
$n笑道：“不用客气，你来解我寂寞，可多谢你啦。”\n", me, ob );
        message_vision("$N道：“不敢。”\n
$n点了点头，说道：“我只想瞧瞧你的剑法，并非真的过
招，再说，我也未必能胜得了你。”\n\n", me, ob);
        say(HIR"任我行大喝一声：“少林剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才一招。”\n");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"任我行大喝一声：“武当剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才两招。”\n");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"任我行大喝一声：“峨嵋剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才三招。”\n");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"任我行大喝一声：“嵩山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才四招。”\n");
                return 1;
        }
        command("enable sword taishan-sword");
        say(HIR"任我行大喝一声：“泰山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才五招。”\n");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"任我行大喝一声：“华山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才六招。”\n");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"任我行大喝一声：“衡山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才七招。”\n");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"任我行大喝一声：“恒山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“还是没过八招。”\n");
                return 1;
        }

        obj = new("/d/heimuya/obj/heimu-ling");
        obj -> move(me);
        say("任我行说道：“这位" + RANK_D->query_respect(me)+"不错，我就送你一块黑木令吧。”\n");
        return 1;
}
