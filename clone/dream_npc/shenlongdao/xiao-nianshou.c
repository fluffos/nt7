inherit DREAM_NPC;
#include <ansi.h>

int is_quarry(){return 1;}

void create()
{
        set_name(HIG "小年兽" NOR, ({ "xiao nianshou"}));

        set("age", 10);
        set("str", 5);
        set("dex", 100);
        set("max_qi", 500000);
        set("max_jing", 500000);
                set("eff_jing", 500000);
                set("max_jing", 500000);
                set("max_neili", 500000);
                set("neili", 500000);
                set("jingli", 500000);
                set("max_jingli", 500000);
                set("jingli", 500000);
                set("eff_jingli", 500000);
        set("combat_exp", 5000000);


                set_skill("dodge", 100);
                set_skill("unarmed", 50);

                set("gift/exp", 5000);
                set("gift/pot", 7000);
                set("oblist", ([
                        "/clone/money/yuanbao" : 20,
                        "/clone/armor/chiyou-zhanpao3" : 5,
                ]));
        setup();
                add_money("silver", 6 + random(8));
}
