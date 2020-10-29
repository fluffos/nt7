inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIR "赤火蛇" NOR, ({ "chihuo she", "chihuo", "she" }));
        set("long", HIW "这是一只浑身火红的巨蛇，似乎在这里生存了数千年。\n" NOR);

        set("age", 1900);
        set("str",80);
        set("dex", 80);
        set("max_qi", 8200000);
        set("max_jing", 850000);
        set("max_jingli", 8500000);
        set("max_neili", 2500000);
        set("neili", 2500000);  
        set("combat_exp", 20000000);
        set("no_nuoyi", 1);
        set("gift/exp", 1200);
        set("gift/pot", 450);
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
