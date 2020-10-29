// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白光虎[2;37;0m[2;37;0m", ({"sdbia"}));        
        set("gender", "女性");                
        set("long", "相当神秘[2;37;0m
它是天空九号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sdbi");
        set("owner_name", "天空九号");
        set_temp("owner", "sdbi");
        set_temp("owner_name", "天空九号");
        ::setup();
}
