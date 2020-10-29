// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火鸟[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "一只小火鸟[2;37;0m
它是毒公子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dbudong");
        set("owner_name", "毒公子");
        set_temp("owner", "dbudong");
        set_temp("owner_name", "毒公子");
        ::setup();
}
