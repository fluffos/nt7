// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("「狂风快刀」入门", ({ "kuangfeng book0", "book0", }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",
        "这是一本发旧的秘籍。上书：“狂风快刀(入门)”。\n"
        "书皮泛黄，看来已经保存很久了。\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "blade",
                        "exp_required": 200000,
                        "jing_cost" :  50,
                        "difficulty":  20,
                        "max_skill" :  60,
                        "min_skill" :  0
                ]) );
        }
}
