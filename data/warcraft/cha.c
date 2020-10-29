// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙虎[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙虎[2;37;0m
它是衩衩的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cha");
        set("owner_name", "衩衩");
        set_temp("owner", "cha");
        set_temp("owner_name", "衩衩");
        ::setup();
}
