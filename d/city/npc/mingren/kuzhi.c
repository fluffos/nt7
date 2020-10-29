#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "枯枝" NOR, ({ "kuzhi" }));
        set("title", HIR "梦想之神" NOR);
        set("gender", "男性");
        set("age", 36);
        set("no_get", 1);
        set("long", @LONG
“一旦让我开始，我就不会停止，人不能没有梦想！”
枯枝，梦想之神，骑车去过千岛湖去过厦门去过海南去过青岛， 
2014年他的梦想是骑车到西藏，历时一个月从昆明到西藏的朝圣之路，梦想实现了。
但没有觉得骑车去西藏是什么英雄壮举，只是因为梦想的力量以及那最朴素的人、最清澈的水、最漂亮的星空、最神圣的雪山。
生命的意义就是不断的前进，去到更高更远。
泥潭7的梦想之神，梦想将继续！
LONG );
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
        //carry_object("/clone/weapon/changjian")->wield();
        call_out("qima", 2);
}

int qima()
{
        object ma;
        if (!objectp(environment())) {
                call_out("qima", 2);
                return 1;
        }
        ma = new("/clone/horse/baima.c");
        set("no_get", 1, ma);
        set("name", "自行车", ma);
        ma->move(environment());
        command("ride bai ma");
        return 1;
}
