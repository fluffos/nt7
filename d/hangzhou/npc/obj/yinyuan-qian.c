// yinyuan-qian.c 姻缘签
// By Alf, Last Update 2002.1130

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(HIM"姻缘签"NOR, ({"yinyuan qian", "qian"}));
    set_weight(500);
    /*if(clonep())
        set_default_object(__FILE__);
    else*/
    {
        set("unit", "支");
        set("long", HIC"这是一支月老祠内求得的姻缘签，上面写着：\n"NOR);
        set("value", 0);
        set("material", "bamboo");
    }
    setup();
}