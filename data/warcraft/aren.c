// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("人人[2;37;0m[2;37;0m", ({"renren"}));        
        set("gender", "女性");                
        set("long", "人人[2;37;0m
它是阿忍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "aren");
        set("owner_name", "阿忍");
        set_temp("owner", "aren");
        set_temp("owner_name", "阿忍");
        ::setup();
}
