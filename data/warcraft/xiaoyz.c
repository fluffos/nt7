// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东方不败[2;37;0m[2;37;0m", ({"bubai"}));        
        set("gender", "女性");                
        set("long", "笑傲江湖[2;37;0m
它是令狐冲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoyz");
        set("owner_name", "令狐冲");
        set_temp("owner", "xiaoyz");
        set_temp("owner_name", "令狐冲");
        ::setup();
}
