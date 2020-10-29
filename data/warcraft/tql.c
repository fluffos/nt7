// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m", ({"ttt"}));        
        set("gender", "女性");                
        set("long", "好白[2;37;0m
它是浩哥的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tql");
        set("owner_name", "浩哥");
        set_temp("owner", "tql");
        set_temp("owner_name", "浩哥");
        ::setup();
}
