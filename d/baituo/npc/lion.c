// lion.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("雄狮", ({ "lion", "xiongshi", "shi" }) );
        set("race", "野兽");
        set("age", 15);
        set("long", "一只矫健的雄狮，十分威风。\n");
//        set("attitude", "aggressive");
        set("attitude", "peace");
        set("shen_type", -1);

        set("limbs", ({ "狮头", "狮身", "前爪", "后抓", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 40000);
        set_temp("apply/attack", 20000);
        set_temp("apply/defense", 30000);
        set_temp("apply/armor", 800);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "雄狮一声长吼，四下传来阵阵会响。\n",
                "雄狮后足一蹬，猛地一跃到你的面前。\n",
        }) );
}
