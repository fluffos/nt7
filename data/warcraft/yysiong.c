// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老虎[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是江海的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yysiong");
        set("owner_name", "江海");
        set_temp("owner", "yysiong");
        set_temp("owner_name", "江海");
        ::setup();
}
