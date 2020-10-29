// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m太古金焱凤[2;37;0m[2;37;0m", ({"slash"}));        
        set("gender", "女性");                
        set("long", "太古金焱凤[2;37;0m
它是白素贞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "angie");
        set("owner_name", "白素贞");
        set_temp("owner", "angie");
        set_temp("owner_name", "白素贞");
        ::setup();
}
