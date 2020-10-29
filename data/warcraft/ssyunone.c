// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m霸王[1;32m教[1;35m主[2;37;0m[2;37;0m", ({"mohuansou"}));        
        set("gender", "女性");                
        set("long", "霸王教主[2;37;0m
它是渡欧的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "ssyunone");
        set("owner_name", "渡欧");
        set_temp("owner", "ssyunone");
        set_temp("owner_name", "渡欧");
        ::setup();
}
