

inherit ITEM;

void create()
{
        set_name("玄虚刀法", ({ "xuanxu book", "book" }));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long","这是一本薄薄的丝织小册子，上面写着玄虚刀法四个小字。\n");
                set("no_sell", 1);
                set("material", "silk");
                set("skill", ([
                        "name": "xuanxu-dao",//name of the skill
                        "family_name" : "武当派",
                        "exp_required": 5000000,  //minimum combat experience required
                        "jing_cost": 100,        // jing cost every time study this
                        "difficulty": 100,       // the base int to learn this skill
                        "max_skill": 200,       // the maximum level you can learn
                        "min_skill": 0,        // the minimum level you can learn
                ]) );
        }
}
