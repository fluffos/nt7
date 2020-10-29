// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "苍狼" NOR, ({ "feel" }));
        set("title", HIR "失落之神" NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long", sort_msg(HIY"自泥潭一开站之日便有苍狼的存在，开创叱咤风云的雪域苍狼一派，一时惊天地泣鬼神，然后在雪域苍狼"
        "与大侠红豆,raken,紫雷帮派一战后，都归隐江湖。此战胜负无人知晓。自此不再有苍狼身影。自泥潭一后虽有传闻有苍狼出现，但辉煌不再。\n" NOR));
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
