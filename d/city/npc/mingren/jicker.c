// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "慕容长青" NOR, ({ "jicker" }));
        set("title", HIR "ＰＫ之神" NOR);
        set("gender", "男性");
        set("age", 25);
        set("no_get", 1);
        set("long", sort_msg(HIY"慕容长青，以pk为己任，"
"一生pk无数，曾与梅山一票人进行PK，从泥潭（二）一直pk到泥潭（三），最终梅山一票人落败退出泥潭。"
"与紫雷关系密切，都是喜欢PK类型，一生中遭天神杀档无数，生命不息，PK不止。\n" NOR));
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
