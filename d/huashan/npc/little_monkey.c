// little_monkey.c

inherit NPC;

void create()
{
        set_name("小猴",({ "little monkey", "monkey"}) );
        set("gender", "雄性");
        set("race", "野兽");
        set("age", 2);
        set("long", "这是一只调皮的小猴子，虽是畜牲，却喜欢模仿人样。\n"
            "陆大有整天调教得它无比伶俐，现在正骑在陆大有的脖子上。\n");
        set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("shen_type", 0);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");

        set("no_get", 1);
        set("max_qi", 300);
        set("qi", 300);
        set("max_jing", 100);
        set("jing", 100);
        set("combat_exp", 50000);

        set("fight_times", 0);        

        set("chat_chance", 15);
        set("chat_msg", ({
                "小猴伸出小抓挠挠头，冲你扮个鬼脸。\n",
                "小猴懒洋洋地打了个哈欠，爬到陆大有头顶，又翻身下到主人肩头。\n",
                "小猴伸抓捉住了身上的虱子，看了两眼，使劲就是一捏! \n",
        }));
        setup();
        
}
