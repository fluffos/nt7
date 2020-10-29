inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(NOR + WHT "巨型野猪" NOR, ({ "juxing shanzhu", "juxing", "shanzhu" }));
        set("long", HIW "这是一只巨大的野猪，大得令人难以想象，个头似乎超过两头老虎大，凶猛异常。\n" NOR);

        set("age", 500);
        set("str",800);
        set("dex", 80);
        set("max_qi", 8200000);
        set("max_jing", 850000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("neili", 800000);
        set("combat_exp", 20000000);
        set("no_nuoyi", 1);
        set("gift/exp", 1350);
        set("gift/pot", 480);
        set("gift/mar", 20);
        set("oblist", ([
                "/clone/fam/gift/str3" :1,
                "/clone/fam/gift/con3" :1,
                "/clone/fam/gift/dex3" :1,
                "/clone/fam/gift/int3" :1,
        ]));


        set_skill("force", 700);
        set_skill("dodge", 700);
        set_skill("unarmed", 700);
        set_skill("sword", 700);
        set_skill("parry", 700);
        set_skill("claw", 700);

        setup();
        add_money("gold", 1 + random(2));
}
void init()
{
        // 随机攻击玩家
        if (userp(this_player()) && random(2) == 1)
        {
                kill_ob(this_player());
        }
}
