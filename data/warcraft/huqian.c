// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小希[2;37;0m[2;37;0m", ({"xxi"}));        
        set("gender", "女性");                
        set("long", "小希一只[2;37;0m
它是胡倩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huqian");
        set("owner_name", "胡倩");
        set_temp("owner", "huqian");
        set_temp("owner_name", "胡倩");
        ::setup();
}
