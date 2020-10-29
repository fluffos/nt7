// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"huer"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是若天痕的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hhhhh");
        set("owner_name", "若天痕");
        set_temp("owner", "hhhhh");
        set_temp("owner_name", "若天痕");
        ::setup();
}
