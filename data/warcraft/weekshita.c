// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("皇后[2;37;0m[2;37;0m", ({"queen"}));        
        set("gender", "女性");                
        set("long", "主宰[2;37;0m
它是段长的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "weekshita");
        set("owner_name", "段长");
        set_temp("owner", "weekshita");
        set_temp("owner_name", "段长");
        ::setup();
}
