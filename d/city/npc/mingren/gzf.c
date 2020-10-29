// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "鬼丈夫" NOR, ({ "gzf" }));
        set("title", HIR "冲动之神" NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long", sort_msg(HIY"这是一位仙风道骨的中年道人，早年云游四方，中年"
                "长居泥潭，性好任侠，公正无私。鬼丈夫是泥潭的最忠实玩家之一，可"
                "惜的是他在泥潭天神调整门派任务奖励时以自杀来表示不满而离开泥潭。\n" NOR));
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
