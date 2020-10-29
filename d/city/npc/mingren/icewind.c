// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "雪魂" NOR, ({ "icewind" }));
        set("title", HIR "忙碌之神" NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long", sort_msg(HIY"雪魂，2005年8月重返泥潭，始于泥潭（二），终于泥潭（二），以雪浅凝（灭浅）闯荡江湖"
"，一生无为，交友甚多。与友千王之王，发呆虫，狐一剑，楚风，司马天籁共建帮派“雪域苍狼”,闯荡江湖时，处事虽无大善，"
"亦无大恶，以勤奋修练为专长，以团结兄弟为己任，终因私务而离开泥潭。后传：2012年重新现身泥潭（六）。\n" NOR));
        set("combat_exp", 60000);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("apply/attack", 50);
        set("apply/defense", 50);

        set("max_qi", 800);
        set("max_jing", 800);
        set("max_neili", 800);

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
