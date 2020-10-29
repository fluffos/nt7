// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"wwwe"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是糖泰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chtm");
        set("owner_name", "糖泰");
        set_temp("owner", "chtm");
        set_temp("owner_name", "糖泰");
        ::setup();
}
