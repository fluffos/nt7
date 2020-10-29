
// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「魅影剑法」上册", ({ "meiying book1", "book1", }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",
        "这是一本发旧的秘籍。上书：“「魅影剑法」上册”。\n"
        "书皮泛黄，看来已经保存很久了。\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "meiying-jian",
                        "exp_required": 20000000,
                        "jing_cost" :  200,
                        "difficulty":  50,
                        "max_skill" :  100,
                        "min_skill" :  0
                ]) );
        }
}
