// cuff_book.c 

inherit ITEM;

void create()
{
        set_name("七伤拳谱", ({ "shu", "book" }));
        set_weight(600);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long", 
"这是一本七伤拳谱，是崆峒派的武功秘籍。\n"
                );                                
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":        "cuff",                // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        30,        // jing cost every time study this
                        "difficulty":        10,        // the base int to learn this skill
                        "max_skill":        50        // the maximum level you can learn
                ]) );
        }
}