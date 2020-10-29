// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奥迪[2;37;0m[2;37;0m", ({"aodi"}));        
        set("gender", "男性");                
        set("long", "奥迪[2;37;0m
它是老祖的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "laozu");
        set("owner_name", "老祖");
        set_temp("owner", "laozu");
        set_temp("owner_name", "老祖");
        ::setup();
}
