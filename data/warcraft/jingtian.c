// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("惊[2;37;0m[2;37;0m", ({"jingjing"}));        
        set("gender", "男性");                
        set("long", "惊[2;37;0m
它是惊天的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jingtian");
        set("owner_name", "惊天");
        set_temp("owner", "jingtian");
        set_temp("owner_name", "惊天");
        ::setup();
}
