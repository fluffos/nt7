// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乞灵[2;37;0m[2;37;0m", ({"noneys"}));        
        set("gender", "女性");                
        set("long", "乞灵[2;37;0m
它是钱不通的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "noneyn");
        set("owner_name", "钱不通");
        set_temp("owner", "noneyn");
        set_temp("owner_name", "钱不通");
        ::setup();
}
