inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIR "火龙" NOR, ({ "huo long", "huo", "long" }));
        set("long", HIR "一只巨大的飞龙，在半空中盘旋，全身燃烧着火焰，甚是壮观。\n" NOR);

        set("age", 99999);
        set("str",500);
        set("dex", 500);
        set("int", 121);
        set("con", 121);
        set("max_qi", 75000000);
        set("max_jing", 8500000);
        set("max_jingli", 8500000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("combat_exp", 100000000);
        set("no_nuoyi", 1);
        set("gift/exp", 2500);
        set("gift/pot", 700);
        set("gift/mar", 40);
        set("oblist", ([
                "/clone/fam/gift/str3" :1,
                "/clone/fam/gift/con3" :1,
                "/clone/fam/gift/dex3" :1,
                "/clone/fam/gift/int3" :1,
        ]));


        set_skill("force", 1500);
        set_skill("dodge", 1500);
        set_skill("unarmed", 1500);
        set_skill("sword", 1500);
        set_skill("parry", 1500);
        set_skill("claw", 1500);

        setup();
        add_money("gold", 2 + random(3));
}

void init()
{
        // 随机攻击玩家
        if (userp(this_player()) && random(2) == 1)
        {
                kill_ob(this_player());
        }
}
