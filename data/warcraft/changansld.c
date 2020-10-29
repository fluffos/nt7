// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"huhu"}));        
        set("gender", "女性");                
        set("long", "大[2;37;0m
它是长二安的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "changansld");
        set("owner_name", "长二安");
        set_temp("owner", "changansld");
        set_temp("owner_name", "长二安");
        ::setup();
}
