// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("十二天[2;37;0m[2;37;0m", ({"headalong"}));        
        set("gender", "男性");                
        set("long", "后天[2;37;0m
它是毛太粗的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "heada");
        set("owner_name", "毛太粗");
        set_temp("owner", "heada");
        set_temp("owner_name", "毛太粗");
        ::setup();
}
