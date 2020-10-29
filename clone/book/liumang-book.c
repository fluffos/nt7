// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「流氓神拳」上册", ({ "liumang book", "book", }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",
        "这是一本发旧的秘籍。上书：“流氓神拳”。\n"
        "书皮泛黄，看来已经保存很久了。\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "liumang-shenquan",
                        "exp_required": 2000000,
                        "jing_cost" :  200,
                        "difficulty":  90,
                        "max_skill" :  200,
                        "min_skill" :  0
                ]) );
        }
}
