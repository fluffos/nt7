// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m死亡之翼[2;37;0m[2;37;0m", ({"jsi"}));        
        set("gender", "男性");                
        set("long", "死亡之翼[2;37;0m
它是剑四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jiansi");
        set("owner_name", "剑四");
        set_temp("owner", "jiansi");
        set_temp("owner_name", "剑四");
        ::setup();
}
