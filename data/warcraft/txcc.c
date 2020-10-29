// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱[2;37;0m[2;37;0m", ({"zhuq"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是通信出村的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txcc");
        set("owner_name", "通信出村");
        set_temp("owner", "txcc");
        set_temp("owner_name", "通信出村");
        ::setup();
}
