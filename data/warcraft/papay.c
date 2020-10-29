// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽的英[2;37;0m[2;37;0m", ({"papaya"}));        
        set("gender", "女性");                
        set("long", "兽的英[2;37;0m
它是西门学的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "papay");
        set("owner_name", "西门学");
        set_temp("owner", "papay");
        set_temp("owner_name", "西门学");
        ::setup();
}
