// xiang.c
#include <ansi.h>
inherit NPC;
int ask_kill();

void create()
{
    set_name("向问天", ({ "xiang wentian", "xiang"}));
    set("nickname", HIR "天王老子" NOR );
    set("gender", "男性");
    set("title", "日月神教光明右使");
    set("long", "他就是日月神教的光明右使。为人极为豪爽。\n");
    set("age", 45);
    set("shen_type", -1);

    set("str", 21);
    set("per", 28);
    set("int", 30);
    set("con", 26);
    set("dex", 30);
    set("chat_chance", 1);
    set("inquiry", ([
      "杨莲亭"     : "这种人，该杀！\n",
      "东方不败"   : "篡位叛徒，我非杀了他不可！\n",
      "杀东方不败" : (: ask_kill() :),
      "任我行"     : "教主被困，已历十年......\n",
    ]));
    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3500);
    set("max_neili", 3500);
    set("jiali", 350);

    set("combat_exp", 2500000);
    set("score", 0);

    set_skill("force", 110);
    set_skill("hunyuan-yiqi", 110);
    set_skill("dodge", 110);
    set_skill("shaolin-shenfa", 110);
    set_skill("finger", 110);
    set_skill("strike", 110);
    set_skill("hand", 110);
    set_skill("claw", 110);
    set_skill("parry", 110);
    set_skill("nianhua-zhi", 110);
    set_skill("sanhua-zhang", 110);
    set_skill("fengyun-shou", 110);
    set_skill("longzhua-gong", 110);
    set_skill("buddhism", 110);
    set_skill("literate", 110);

    map_skill("force", "hunyuan-yiqi");
    map_skill("dodge", "shaolin-shenfa");
    map_skill("finger", "nianhua-zhi");
    map_skill("strike", "sanhua-zhang");
    map_skill("hand", "fengyun-shou");
    map_skill("claw", "longzhua-gong");
    map_skill("parry", "nianhua-zhi");

    prepare_skill("finger", "nianhua-zhi");
    prepare_skill("strike", "sanhua-zhang");
    create_family("日月神教", 2, "光明右使");

    setup();
    carry_object("/d/heimuya/npc/obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    command("say 我不收弟子。\n");
    return;
}

int ask_kill()
{
   object ob,me = this_player();

   command("tell"+query("id", this_player())+"你要去杀东方不败？\n");
   message_vision(HIC "向问天对$N点了点头说：我助你一臂之力。\n" NOR,this_player());
   ob=new("/d/heimuya/npc/obj/card4");
   ob->move(me);
   tell_object(me,"向问天从怀里摸出一块令牌塞到你的手上。\n");
   return 1;
}
