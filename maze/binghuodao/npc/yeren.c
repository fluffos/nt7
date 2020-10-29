inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIG "野人" NOR, ({ "ye ren", "ye", "ren" }));
        set("long", HIG "终年生活在冰火岛上的野人，似乎与常人颇有不同。\n" NOR);

        set("age", 500);
        set("str",121);
        set("dex", 80);
        set("int", 80);
        set("con", 80);
        set("max_qi", 12000000);
        set("max_jing", 8500000);
        set("max_jingli", 8500000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("combat_exp", 100000000);
        set("no_nuoyi", 1);
        set("gift/exp", 1300);
        set("gift/pot", 500);
        set("gift/mar", 20);

        set("oblist", ([
                "/clone/fam/gift/str3" :1,
                "/clone/fam/gift/con3" :1,
                "/clone/fam/gift/dex3" :1,
                "/clone/fam/gift/int3" :1,
        ]));

        set_skill("force", 1000);
        set_skill("dodge", 1000);
        set_skill("unarmed", 1000);
        set_skill("sword", 1000);
        set_skill("parry", 1000);
        set_skill("claw", 1000);

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
