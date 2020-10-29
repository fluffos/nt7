inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIW "冰狼" NOR, ({ "bing lang", "bing", "lang" }));
        set("long", HIW "浑身被冰雪包裹的巨狼，在冰峰谷的进化了数万年，似乎已经拥有无穷的力量。\n" NOR);

        set("age", 99999);
        set("str",121);
        set("dex", 121);
        set("int", 121);
        set("con", 121);
        set("max_qi", 32000000);
        set("max_jing", 8500000);
        set("max_jingli", 8500000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("combat_exp", 100000000);
        set("no_nuoyi", 1);
        set("gift/exp", 1600);
        set("gift/pot", 550);
        set("gift/mar", 30);
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
        add_money("gold", 1 + random(3));
}

void init()
{
        // 随机攻击玩家
        if (userp(this_player()) && random(2) == 1)
        {
                kill_ob(this_player());
        }
}
