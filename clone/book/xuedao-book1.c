
inherit ITEM;

void create()
{
        set_name("血刀谱", ({ "xuedao book", "book" }));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long","这是一本薄薄的丝织小册子，上面写着血刀谱三个小字。\n");
                set("no_sell", 1);
                set("material", "silk");
                set("skill", ([
                        "name": "xuedao-daofa",//name of the skill
                        "family_name" : "血刀门",
                        "exp_required": 5000000,  //minimum combat experience required
                        "jing_cost": 100,        // jing cost every time study this
                        "difficulty": 100,       // the base int to learn this skill
                        "max_skill": 200,       // the maximum level you can learn
                        "min_skill": 0,        // the minimum level you can learn
                ]) );
        }
}
