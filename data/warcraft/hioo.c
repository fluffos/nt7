// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"kissbye"}));        
        set("gender", "女性");                
        set("long", "缔结永生的血之盟约。[2;37;0m
它是玄虚的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hioo");
        set("owner_name", "玄虚");
        set_temp("owner", "hioo");
        set_temp("owner_name", "玄虚");
        ::setup();
}
