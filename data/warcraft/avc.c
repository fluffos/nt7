// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是史诗巨兽的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "avc");
        set("owner_name", "史诗巨兽");
        set_temp("owner", "avc");
        set_temp("owner_name", "史诗巨兽");
        ::setup();
}
